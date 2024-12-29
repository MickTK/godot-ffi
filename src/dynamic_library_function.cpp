#include "dynamic_library_function.h"

using namespace godot;

DynamicLibraryFunction::DynamicLibraryFunction() { }

DynamicLibraryFunction::DynamicLibraryFunction(signature_t signature) {
    this->signature = signature;
}

DynamicLibraryFunction::~DynamicLibraryFunction() { }

Variant DynamicLibraryFunction::invoke(Array args) {
    if (!this->signature->cif) {
        error_msg("Invalid function: " + signature->symbol);
        return nullptr;
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
