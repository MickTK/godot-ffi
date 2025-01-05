#include <godot_cpp/core/class_db.hpp>

#include "dynamic_library.h"
#include "dynamic_library_function.h"

using namespace godot;

void DynamicLibrary::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_function", "name", "argument_types", "return_type"), &DynamicLibrary::get_function);
}

DynamicLibrary::DynamicLibrary() { }

DynamicLibrary::~DynamicLibrary() {
    if (this->handle) {
        dl_close(this->handle);
    }
}

void DynamicLibrary::set_handle(Handle handle) {
    this->handle = handle;
}

Ref<DynamicLibraryFunction> DynamicLibrary::get_function(String name, PackedStringArray argument_types, String return_type) {
    // Get (function) symbol from the library
    Symbol symbol = dl_sym(this->handle, (char*) name.utf8().get_data());
    if (!symbol) {
        error_msg("Function \"" + name + "\" not found in the current dl.");
        return Ref<DynamicLibraryFunction>();
    }

    ffi_cif *cif = new ffi_cif();
    ffi_type **arg_types = new ffi_type*[argument_types.size()];
    
    // Get all the ffi types from literal
    for (int i = 0; i < argument_types.size(); i++) {
        arg_types[i] = get_type(argument_types[i]);
    }

    switch (
        ffi_prep_cif(
            cif,
            FFI_DEFAULT_ABI, // application binary interface (call standard)
            argument_types.size(),
            get_type(return_type),
            arg_types
        )
    ) {
        case FFI_OK: break;
        case FFI_BAD_TYPEDEF:
            error_msg("FFI_BAD_TYPEDEF: cif is NULL or atypes or rtype is malformed.");
            return Ref<DynamicLibraryFunction>();
            break;
        case FFI_BAD_ABI:
            error_msg("FFI_BAD_ABI: abi does not refer to a valid ABI.");
            return Ref<DynamicLibraryFunction>();
            break;
        default:
            error_msg("Unknown FFI error: unknown ffi_status given by ffi_prep_cif.");
            return Ref<DynamicLibraryFunction>();
            break;
    }

    Ref<DynamicLibraryFunction> ref;
    ref.instantiate();
    ref->bind(Ref<DynamicLibrary>(this), symbol, cif);
    return ref;
}
