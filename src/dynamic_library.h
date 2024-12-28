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

typedef std::unordered_map<uint64_t, signature_t*> signature_map_t;
typedef std::unordered_map<uint64_t, Symbol> symbol_map_t;

class DynamicLibrary : public Reference {
    GODOT_CLASS(DynamicLibrary, Reference)

private:
    Handle handle = nullptr;
    signature_map_t signature_map; // TODO: REPLACE
    symbol_map_t symbol_map; // TODO: REPLACE
    ffi_type* get_ffi_type(String name);

protected:
    static void _bind_methods();

public:
    DynamicLibrary();
    DynamicLibrary(Handle handle);
    ~DynamicLibrary();

    // bool status();
    void define(String method, String retType, PoolStringArray argTypes);
    Variant invoke(String method, Array args);

};

}

#endif // DYNAMIC_LIBRARY_H
