#include "common.h"

#include <godot_cpp/variant/utility_functions.hpp>

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


void error_msg(String message) {
    UtilityFunctions::print("\x1b[31;1mGodot FFI error:\x1b[0m " + String("\x1b[31m" + message + "\x1b[0m"));
}


ffi_type* get_type(String type) {
    if      (type == "uchar")  return &ffi_type_uchar;
    else if (type == "uint8")  return &ffi_type_uint8;
    else if (type == "uint16") return &ffi_type_uint16;
    else if (type == "uint32") return &ffi_type_uint32;
    else if (type == "uint64") return &ffi_type_uint64;
    else if (type == "schar")  return &ffi_type_schar;
    else if (type == "sint8")  return &ffi_type_sint8;
    else if (type == "sint16") return &ffi_type_sint16;
    else if (type == "sint32") return &ffi_type_sint32;
    else if (type == "sint64") return &ffi_type_sint64;
    else if (type == "float")  return &ffi_type_float;
    else if (type == "double") return &ffi_type_double;
    else if (type == "void")   return &ffi_type_void;
    else if (type == "pointer" || type == "string")
        return &ffi_type_pointer;
    else {
        error_msg("Unknown argument type: " + type);
        return &ffi_type_void;
    }
}
