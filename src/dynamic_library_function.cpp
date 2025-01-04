#include <godot_cpp/core/class_db.hpp>

#include "dynamic_library_function.h"

using namespace godot;

void DynamicLibraryFunction::_bind_methods() {
	ClassDB::bind_method(D_METHOD("invoke", "args"), &DynamicLibraryFunction::invoke);
}

DynamicLibraryFunction::DynamicLibraryFunction() { }

DynamicLibraryFunction::~DynamicLibraryFunction() {
    if (cif != nullptr) delete this->cif;
}

void DynamicLibraryFunction::bind(Symbol symbol, ffi_cif* cif) {
    this->symbol = symbol;
    this->cif = cif;
}

Variant DynamicLibraryFunction::invoke(Array args) {
    if (this->cif == nullptr) {
        error_msg("Invalid function.");
        return Variant();
    }

    void* arg_values[this->cif->nargs]; // argument values (for function call)
    String str; // wrapper
    char* pStr; // pointer to given string
    bool mem_flag[this->cif->nargs]; // used to free the allocated memory

    // Casting Godot types to ffi types
    // TODO: add more argument types
    for (int i = 0; i < args.size(); i++) {
        mem_flag[i] = false;
        switch(args[i].get_type()) {
            case Variant::NIL:
                arg_values[i] = nullptr;
                break;
            case Variant::INT:
                arg_values[i] = new uint64_t(args[i]);
                break;
            case Variant::FLOAT:
                arg_values[i] = new double(args[i]);
                break;
            case Variant::BOOL:
                arg_values[i] = new bool(args[i]);
                break;
            case Variant::STRING:
                str = args[i];
                pStr = new char[str.length()+1];
                memcpy(pStr, str.utf8().get_data(), str.length());
                pStr[str.length()] = 0;
                arg_values[i] = new char*(pStr);
                mem_flag[i] = true;
                break;
            default:
                error_msg("Unsupported argument of type: " + String::num(args[i].get_type()));
                arg_values[i] = nullptr;
        }
    }

    ffi_arg result; // function result

    ffi_call(this->cif, FFI_FN(this->symbol), &result, arg_values);

    Variant res; // return value

    // Cast result from ffi type to Godot type
    if      (cif->rtype == &ffi_type_uchar)   res = Variant(*(uint8_t*) &result);
    else if (cif->rtype == &ffi_type_uint8)   res = Variant(*(uint8_t*) &result);
    else if (cif->rtype == &ffi_type_uint16)  res = Variant(*(uint16_t*) &result);
    else if (cif->rtype == &ffi_type_uint32)  res = Variant(*(uint32_t*) &result);
    else if (cif->rtype == &ffi_type_uint64)  res = Variant(*(uint64_t*) &result);
    else if (cif->rtype == &ffi_type_schar)   res = Variant(*(int8_t*) &result);
    else if (cif->rtype == &ffi_type_sint8)   res = Variant(*(int8_t*) &result);
    else if (cif->rtype == &ffi_type_sint16)  res = Variant(*(int16_t*) &result);
    else if (cif->rtype == &ffi_type_sint32)  res = Variant(*(int32_t*) &result);
    else if (cif->rtype == &ffi_type_sint64)  res = Variant(*(int64_t*) &result);
    else if (cif->rtype == &ffi_type_float)   res = Variant(*(float*) &result);
    else if (cif->rtype == &ffi_type_double)  res = Variant(*(double*) &result);
    else if (cif->rtype == &ffi_type_void)    res = Variant(*(uint64_t*) &result);
    else if (cif->rtype == &ffi_type_pointer) res = Variant(*(char**) &result);
    else { error_msg("Invalid result type."); res = Variant(); }

    // Free the memory
    pStr = nullptr;
    for (int i = 0; i < this->cif->nargs; i++) {
        if (mem_flag[i]) {
            delete[] *(char**)(arg_values[i]); // pStr
            delete (char**)(arg_values[i]);    // arg_values[i]
            arg_values[i] = nullptr;
        }
    }

    return res;
}
