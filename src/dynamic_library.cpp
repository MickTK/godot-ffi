#include <dlfcn.h>

#include "dynamic_library.h"

using namespace godot;

DynamicLibrary::DynamicLibrary() { }

DynamicLibrary::DynamicLibrary(Handle handle) {
    this->handle = handle;
}

DynamicLibrary::~DynamicLibrary() {
    if (this->handle) {
        dl_close(this->handle);
    }
}

Ref<DynamicLibraryFunction> DynamicLibrary::get_function(String name, PoolStringArray argument_types, String return_type) {
    // Get symbol from the library
    Symbol symbol = dl_sym(this->handle, name.utf8().get_data());
    if (!symbol) {
        error_msg("Function \"" + name + "\" not found in the current dl.");
        return nullptr;
    }

    ffi_cif *cif = new ffi_cif();
    ffi_type **arg_types = new ffi_type*[argument_types.size()];
    ffi_status status;
    
    cif = new ffi_cif();

    for (int i = 0; i < argument_types.size(); i++) {
        arg_types[i] = get_type(argument_types[i]);
    }

    status = ffi_prep_cif(
        cif,
        FFI_DEFAULT_ABI, // application binary interface (call standard)
        argument_types.size(),
        get_type(return_type),
        arg_types
    );

    // TODO
    switch (status) {
        case FFI_OK: break;
        case FFI_BAD_TYPEDEF: break;
        case FFI_BAD_ABI: break;
        default: break;
    }

    return Ref<DynamicLibraryFunction>::__internal_constructor(
        DynamicLibraryFunction(symbol, cif)
    );
}
