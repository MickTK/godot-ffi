#ifndef FOREIGNLIBRARY_H
#define FOREIGNLIBRARY_H

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
    Handle handle = 0;
    //std::unordered_map<uint64_t, ffi_cif*> cif_map;
    //std::unordered_map<uint64_t,
    signature_map_t signature_map;
    symbol_map_t symbol_map;
    ffi_type* get_ffi_type(String name);

public:
    static void _register_methods();

    static inline const char *___get_class_name() {
        return (const char *) "DynamicLibrary";
    }

    DynamicLibrary();
    ~DynamicLibrary();

    void _init();
    //void _notification(int64_t what);

    void setHandle(void *handle);
    void define(String method, String retType, PoolStringArray argTypes);
    Variant invoke(String method, Array args);

    void _process(float delta);
};

}

#endif
