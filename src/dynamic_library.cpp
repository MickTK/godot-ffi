#include <dlfcn.h>

#include "dynamic_library.h"

using namespace godot;

DynamicLibrary::DynamicLibrary() { }

DynamicLibrary::DynamicLibrary(Handle handle) {
    this->handle = handle;
}

DynamicLibrary::~DynamicLibrary() {
    Godot::print("Destroying DynamicLibrary");
    for (signature_map_t::iterator it = signature_map.begin(); it != signature_map.end(); it++) {
        signature_t *signature = it->second;
        delete signature->cif;
        delete signature;
    }
    if (this->handle) {
        dl_close(this->handle);
    }
}

void DynamicLibrary::get_function(String name, PoolStringArray argument_types, String return_type) {
    signature_t *signature = new signature_t();
    signature->cif = new ffi_cif();
    signature.symbol = name.utf8().get_data();
    ffi_type **arg_types = new ffi_type*[argument_types.size()];
    ffi_status status;

    for (int i = 0; i < argument_types.size(); i++) {
        arg_types[i] = get_type(argument_types[i]);
        signature->arg_types.push_back(std::string(argument_types[i].alloc_c_string()));
    }
    signature->ret_type = get_type(return_type);
    ffi_prep_cif(
        signature->cif,
        FFI_DEFAULT_ABI,
        argument_types.size(),
        signature->ret_type,
        arg_types
    );
}

String variant_to_string(String a) { return a; }

Variant DynamicLibrary::invoke(String method, Array args) {
    if (!this->handle) {
        Godot::print_error(
                "DynamicLibrary: no library loaded, cannot invoke method " + method,
                __FUNCTION__, __FILE__, __LINE__
        );
        return 0;
    }

    void *sym;
    if (!(sym = this->symbol_map[method.hash()])) {
        sym = dl_sym(this->handle, method.alloc_c_string());

        if (!sym) {
            Godot::print_error(
                    "DynamicLibrary: unresolved symbol - " + method,
                    __FUNCTION__, __FILE__, __LINE__
            );
            return 0;
        }
        this->symbol_map[method.hash()] = sym;
    }

    signature_t *signature;
    if (!(signature = this->signature_map[method.hash()])) {
        Godot::print_error(
                "DynamicLibrary: method " + method + " not prepared yet, cannot call",
                __FUNCTION__, __FILE__, __LINE__
        );
        return 0;
    }

    void *arg_values[signature->cif->nargs];
    uint64_t *arg_values_data[signature->cif->nargs];
    // TODO: Suport more arg types
    String str;
    char* pStr;
    for (int i = 0; i < args.size(); i++) {
        switch(args[i].get_type()) {
            case Variant::Type::NIL:
                arg_values[i] = 0;
                break;
            case Variant::Type::INT:
                arg_values[i] = new uint64_t(args[i]);
                break;
            case Variant::Type::REAL:
                arg_values[i] = new double(args[i]);
                break;
            case Variant::Type::BOOL:
                arg_values[i] = new bool(&args[i]);
                break;
            case Variant::Type::STRING:
                // There must be a better way.
                str = args[i];
                pStr = new char[str.length() + 1];
                memcpy(pStr, str.alloc_c_string(), str.length());
                pStr[str.length()] = 0;
                arg_values[i] = new char*(pStr);
                break;
            default:
                // Variant::___get_type_name(args[i].get_type())
                Godot::print_error(
                        String("DynamicLibrary: argument of type ") + \
                            String::num(args[i].get_type()) + \
                            " not yet supported",
                        __FUNCTION__, __FILE__, __LINE__
                );
                arg_values[i] = 0;
        }
    }
    //uint64_t result;
    unsigned char result[8];

    ffi_call(signature->cif, FFI_FN(sym), result, arg_values);

    // Release memory of allocated variables
    for (int i = 0; i < signature->cif->nargs; i++) {
        // TODO: Fix this
        if (signature->argtypes[i] == "string") {
            delete (char*)(*(char**)arg_values[i]);
        } else {
            delete (uint64_t*) arg_values[i];
        }
    }

    if (signature->restype == "uchar") {
        return Variant(*(uint8_t*) result);
    } else if (signature->restype == "schar") {
        return Variant(*(int8_t*) result);
    } else if (signature->restype == "uint16") {
        return Variant(*(uint16_t*) result);
    } else if (signature->restype == "sint16") {
        return Variant(*(int16_t*) result);
    } else if (signature->restype == "uint32") {
        return Variant(*(uint32_t*) result);
    } else if (signature->restype == "sint32") {
        return Variant(*(int32_t*) result);
    } else if (signature->restype == "uint64") {
        return Variant(*(uint64_t*) result);
    } else if (signature->restype == "sint64") {
        return Variant(*(int64_t*) result);
    } else if (signature->restype == "float") {
        return Variant(*(float*) result);
    } else if (signature->restype == "double") {
        return Variant(*(double*)result);
    } else if (signature->restype == "void") {
        return Variant(*(uint64_t*) result);
    } else if (signature->restype == "pointer") {
        return Variant(*(uint64_t*) result);
    } else if (signature->restype == "string") {
        return Variant(*(const char**) result);
    } else {
        return 0;
    }
}
