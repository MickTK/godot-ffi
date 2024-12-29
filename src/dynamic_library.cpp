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

Ref<DynamicLibraryFunction> DynamicLibrary::get_function(String name, PoolStringArray argument_types, String return_type) {
    signature_t *signature = new signature_t();
    ffi_type **arg_types = new ffi_type*[argument_types.size()];
    ffi_status status;
    
    signature->cif = new ffi_cif();
    signature.symbol = name.utf8().get_data();

    for (int i = 0; i < argument_types.size(); i++) {
        arg_types[i] = get_type(argument_types[i]);
    }

    status = ffi_prep_cif(
        signature->cif,
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
        DynamicLibraryFunction(signature)
    );
}
