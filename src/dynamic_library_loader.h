/**
 @file
 Load and open a dynamic library
*/

#ifndef DYNAMIC_LIBRARY_LOADER_H
#define DYNAMIC_LIBRARY_LOADER_H

#include "common.h"
#include "dynamic_library.h"

namespace godot {

class DynamicLibraryLoader : public RefCounted {
    GDCLASS(DynamicLibraryLoader, RefCounted);

protected:
    static void _bind_methods();

public:
    DynamicLibraryLoader();
    ~DynamicLibraryLoader();

    Ref<DynamicLibrary> open(String filename);

};

}

#endif // DYNAMIC_LIBRARY_LOADER_H
