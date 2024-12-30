#include <godot_cpp/core/class_db.hpp>

#include "dynamic_library_loader.h"

using namespace godot;

void DynamicLibraryLoader::_bind_methods() {
	ClassDB::bind_method(D_METHOD("open", "filename"), &DynamicLibraryLoader::open);
}

DynamicLibraryLoader::DynamicLibraryLoader() { }
DynamicLibraryLoader::~DynamicLibraryLoader() { }

Ref<DynamicLibrary> DynamicLibraryLoader::open(String filename) {
    Handle handle = dl_open(filename.utf8().get_data());
    char* error = dl_error();
    if (error) {
        push_error("Failed to load " + filename + ": " + String(error));
        return nullptr;
    }
    return Ref<DynamicLibrary>::__internal_constructor(
        DynamicLibrary(handle)
    );
}
