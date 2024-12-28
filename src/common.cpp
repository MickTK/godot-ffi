#include "common.h"

Handle dl_open(char *filename) {
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

Symbol dl_sym(Handle handle, char *symbol) {
#ifdef IS_UNIX
    return dlsym(handle, symbol);
#else
    return (Symbol)GetProcAddress((HMODULE) handle, symbol);
#endif
}

