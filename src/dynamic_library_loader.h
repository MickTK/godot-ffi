/**
 @file
 Load and open a dynamic library
*/

#ifndef DYNAMIC_LIBRARY_LOADER_H
#define DYNAMIC_LIBRARY_LOADER_H

//#include <godot_cpp/variant/ref.hpp>
#include <godot_cpp/variant/string.hpp>
//#include <godot_cpp/classes/reference.hpp>

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
