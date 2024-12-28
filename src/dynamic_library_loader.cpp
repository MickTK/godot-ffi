#include "dynamic_library_loader.h"

using namespace godot;

DynamicLibraryLoader::DynamicLibraryLoader() { }
DynamicLibraryLoader::~DynamicLibraryLoader() { }


Ref<ForeignLibrary> DynamicLibraryLoader::open(String path) {
    //if (this->handle) {
    //    // Another shared library is already open, close it
    //    dlclose(this->handle);
    //    Godot::print("DynamicLibraryLoader: Unloading shared library " + loadedPath);
    //    this->handle = 0;
    //}

    // Attempt to open shared library
    Godot::print("DynamicLibraryLoader: Loading shared library " + path);
    // TODO: Windows/Linux/Mac
    Handle handle = dl_open(path.alloc_c_string());
    char *error = dl_error();
    if (error) {
        // Opening failed
        Godot::print_error(
                String("DynamicLibraryLoader: Failed to load " + path + ": " + String(error)),
                __FUNCTION__, __FILE__, __LINE__
        );
        return 0;
    }

    ForeignLibrary *library = ForeignLibrary::_new();
    Ref<ForeignLibrary> ref = Ref<ForeignLibrary>::__internal_constructor(library);
    library->setHandle(handle);
    return ref;
}
