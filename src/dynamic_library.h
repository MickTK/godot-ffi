/**
 @file
 Dynamic library reference
*/

#ifndef DYNAMIC_LIBRARY_H
#define DYNAMIC_LIBRARY_H

#include <ffi.h>
#include <unordered_map>
#include <vector>

#include <Godot.hpp>
#include <Reference.hpp>
#include <Array.hpp>
#include <Variant.hpp>
#include <String.hpp>

#include "common.h"

namespace godot {

typedef struct {
    ffi_cif* cif;
    std::vector<std::string> argtypes;
    std::string restype;
} signature_t;

class DynamicLibrary : public Reference {
    GODOT_CLASS(DynamicLibrary, Reference)

private:
    Handle handle = nullptr;

protected:
    static void _bind_methods();

public:
    DynamicLibrary();
    DynamicLibrary(Handle handle);
    ~DynamicLibrary();

    // bool status();
    void get_function(String name, PoolStringArray argument_types, String return_type);
    //Variant invoke(String method, Array args);

};

}

#endif // DYNAMIC_LIBRARY_H
