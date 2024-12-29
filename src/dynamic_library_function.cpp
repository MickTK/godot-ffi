#include "dynamic_library_function.h"

using namespace godot;

DynamicLibraryFunction::DynamicLibraryFunction() { }

DynamicLibraryFunction::DynamicLibraryFunction(Symbol symbol, ffi_cif *cif) {
    this->symbol = symbol;
    this->cif = cif;
}

DynamicLibraryFunction::~DynamicLibraryFunction() { }

Variant DynamicLibraryFunction::invoke(Array args) {
    if (!this->signature->cif) {
        error_msg("Invalid function: " + signature->symbol);
        return nullptr;
    }

    void *arg_values[signature->cif->nargs];
    bool mem_flag[signature->cif->nargs]; // keep the arg ids to free

    // Casting Godot types to ffi types
    // TODO: add more argument types
    for (int i = 0; i < args.size(); i++) {
        mem_flag[i] = false;
        switch(args[i].get_type()) {
            case Variant::Type::NIL:
                arg_values[i] = NULL;
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
                // There must be a better way... using std::string? or smart pointers?
                arg_values[i] = new char[args[i].length() + 1];
                memcpy(arg_values[i], args[i].alloc_c_string(), args[i].length());
                arg_values[i][args[i].length()] = 0; // why not "\0"?
                mem_flag[i] = true;
                break;
            default:
                error_msg("Unsopported argument of type: " + String::num(args[i].get_type()));
                arg_values[i] = NULL;
        }
    }

    unsigned char result[8]; // 64 bit

    ffi_call(signature->cif, FFI_FN(symbol), result, arg_values);

    // Free memory
    for (int i = 0; i < signature->cif->nargs; i++) {
        if (mem_flag[i]) {
            delete arg_values[i];
            arg_values[i] = NULL;
        }
    }

    // Cast result from ffi type to Godot type
    if      (cif->rtype == &ffi_type_uchar)   return Variant(*(uint8_t*) result);
    else if (cif->rtype == &ffi_type_uint16)  return Variant(*(uint16_t*) result);
    else if (cif->rtype == &ffi_type_uint32)  return Variant(*(uint32_t*) result);
    else if (cif->rtype == &ffi_type_uint64)  return Variant(*(uint64_t*) result);
    else if (cif->rtype == &ffi_type_schar)   return Variant(*(int8_t*) result);
    else if (cif->rtype == &ffi_type_sint16)  return Variant(*(int16_t*) result);
    else if (cif->rtype == &ffi_type_sint32)  return Variant(*(int32_t*) result);
    else if (cif->rtype == &ffi_type_sint64)  return Variant(*(int64_t*) result);
    else if (cif->rtype == &ffi_type_float)   return Variant(*(float*) result);
    else if (cif->rtype == &ffi_type_double)  return Variant(*(double*) result);
    else if (cif->rtype == &ffi_type_void)    return Variant(*(uint64_t*) result);
    else if (cif->rtype == &ffi_type_pointer) return Variant(*(const char**) result);
    else { error_msg("Invalid result type");  return Variant(NULL); }
}
