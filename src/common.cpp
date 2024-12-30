#include "common.h"

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
    // print error msg
}


ffi_type* get_type(String type) {
    switch (type) {
        case "uchar":  return &ffi_type_uchar;
        case "uint16": return &ffi_type_uint16;
        case "uint32": return &ffi_type_uint32;
        case "uint64": return &ffi_type_uint64;
        case "schar":  return &ffi_type_schar;
        case "sint16": return &ffi_type_sint16;
        case "sint32": return &ffi_type_sint32;
        case "sint64": return &ffi_type_sint64;
        case "float":  return &ffi_type_float;
        case "double": return &ffi_type_double;
        case "void":   return &ffi_type_void;
        case "pointer":
        case "string": return &ffi_type_pointer;
        default:
            error_msg("Unknown argument type: " + type);
            return &ffi_type_void;
    }
}
