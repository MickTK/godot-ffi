#include "common.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>

Handle dl_open(char* filename) {
#ifdef IS_UNIX
    return dlopen(filename, RTLD_LAZY);
#else
    return LoadLibrary(filename);
#endif
}

char* dl_error() {
#ifdef IS_UNIX
    return dlerror();
#else
    return GetLastError();
#endif
}

int dl_close(Handle handle) {
#ifdef IS_UNIX
    return dlclose(handle);
#else
    return FreeLibrary((HMODULE) handle);
#endif
}

Symbol dl_sym(Handle handle, char* symbol) {
#ifdef IS_UNIX
    return dlsym(handle, symbol);
#else
    return (Symbol)GetProcAddress((HMODULE) handle, symbol);
#endif
}

void error_msg(String message = "Generic error.") {
    UtilityFunctions::push_error("Godot FFI error: " + message);
}

using namespace godot;

void FFI::_bind_methods() {
    ClassDB::bind_integer_constant(get_class_static(), "", "VOID", VOID);
    ClassDB::bind_integer_constant(get_class_static(), "", "UINT8", UINT8);
    ClassDB::bind_integer_constant(get_class_static(), "", "BOOL", BOOL);
    ClassDB::bind_integer_constant(get_class_static(), "", "UINT16", UINT16);
    ClassDB::bind_integer_constant(get_class_static(), "", "UINT32", UINT32);
    ClassDB::bind_integer_constant(get_class_static(), "", "UINT64", UINT64);
    ClassDB::bind_integer_constant(get_class_static(), "", "SINT8", SINT8);
    ClassDB::bind_integer_constant(get_class_static(), "", "SINT16", SINT16);
    ClassDB::bind_integer_constant(get_class_static(), "", "SINT32", SINT32);
    ClassDB::bind_integer_constant(get_class_static(), "", "SINT64", SINT64);
    ClassDB::bind_integer_constant(get_class_static(), "", "INT", INT);
    ClassDB::bind_integer_constant(get_class_static(), "", "UCHAR", UCHAR);
    ClassDB::bind_integer_constant(get_class_static(), "", "SCHAR", SCHAR);
    ClassDB::bind_integer_constant(get_class_static(), "", "FLOAT32", FLOAT32);
    ClassDB::bind_integer_constant(get_class_static(), "", "DOUBLE", DOUBLE);
    ClassDB::bind_integer_constant(get_class_static(), "", "FLOAT", FLOAT);
    ClassDB::bind_integer_constant(get_class_static(), "", "FLOAT64", FLOAT64);
    ClassDB::bind_integer_constant(get_class_static(), "", "POINTER", POINTER);
    ClassDB::bind_integer_constant(get_class_static(), "", "STRING", STRING);
}

ffi_type* FFI::get_type(int type) {
    switch (type) {
        case FFI::VOID:    return &ffi_type_void;
        case FFI::UINT8:   return &ffi_type_uint8;
        case FFI::UINT16:  return &ffi_type_uint16;
        case FFI::UINT32:  return &ffi_type_uint32;
        case FFI::UINT64:  return &ffi_type_uint64;
        case FFI::SINT8:   return &ffi_type_sint8;
        case FFI::SINT16:  return &ffi_type_sint16;
        case FFI::SINT32:  return &ffi_type_sint32;
        case FFI::SINT64:  return &ffi_type_sint64;
        case FFI::UCHAR:   return &ffi_type_uchar;
        case FFI::SCHAR:   return &ffi_type_schar;
        case FFI::FLOAT32: return &ffi_type_float;
        case FFI::DOUBLE:  return &ffi_type_double;
        case FFI::POINTER: return &ffi_type_pointer;
        default:
            error_msg("Unknown argument type: " + String(Variant(type)) + ".");
            return &ffi_type_void;
    }
}
