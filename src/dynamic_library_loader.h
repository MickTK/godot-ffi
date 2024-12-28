/**
 @file
 Dynamic library loader
*/

#ifndef FOREIGNER_H
#define FOREIGNER_H

#include <Godot.hpp>
#include <Reference.hpp>
#include <String.hpp>

#include "common.h"
#include "foreignlibrary.h"

namespace godot {

class DynamicLibraryLoader : public Reference {
    GODOT_CLASS(DynamicLibraryLoader, Reference)

protected:
    static void _bind_methods();

public:
    DynamicLibraryLoader();
    ~DynamicLibraryLoader();

    Ref<ForeignLibrary> open(String path);

};

}

#endif
