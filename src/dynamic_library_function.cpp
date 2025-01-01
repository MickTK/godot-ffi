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

    void* arg_values[this->cif->nargs];

    // Casting Godot types to ffi types
    // TODO: add more argument types
    for (int i = 0; i < args.size(); i++) {
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
                arg_values[i] = new bool(&args[i]);
                break;
            case Variant::STRING:
                arg_values[i] = (char*) String(args[i]).utf8().get_data();
                break;
            default:
                error_msg("Unsupported argument of type: " + String::num(args[i].get_type()));
                arg_values[i] = nullptr;
        }
    }

    ffi_arg result;

    ffi_call(this->cif, FFI_FN(this->symbol), &result, arg_values);

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
    else { error_msg("Invalid result type."); return Variant(); }
}
