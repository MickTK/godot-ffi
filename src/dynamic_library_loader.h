/**
 @file
 Load and open a dynamic library
*/

#ifndef DYNAMIC_LIBRARY_LOADER_H
#define DYNAMIC_LIBRARY_LOADER_H

#include <Godot.hpp>
#include <Reference.hpp>
#include <String.hpp>

#include "common.h"
#include "dynamic_library.h"

namespace godot {

class DynamicLibraryLoader : public Reference {
    GODOT_CLASS(DynamicLibraryLoader, Reference)

protected:
    static void _bind_methods();

public:
    DynamicLibraryLoader();
    ~DynamicLibraryLoader();

    Ref<DynamicLibrary> open(String filename);

};

}

#endif // DYNAMIC_LIBRARY_LOADER_H
