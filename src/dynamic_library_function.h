/**
 @file
 Dynamic library function reference
*/

#ifndef DYNAMIC_LIBRARY_FUNCTION_H
#define DYNAMIC_LIBRARY_FUNCTION_H

#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/object.hpp>

#include "common.h"

namespace godot {

class DynamicLibrary; // forward declaration

class DynamicLibraryFunction : public RefCounted {
    GDCLASS(DynamicLibraryFunction, RefCounted);

private:
    Ref<DynamicLibrary> dl = nullptr;  // dl reference (keeps it alive)
    ffi_cif* cif = nullptr;  // call interface
    Symbol symbol = nullptr; // lib function pointer

protected:
    static void _bind_methods();

public:
    DynamicLibraryFunction();
    ~DynamicLibraryFunction();

    void bind(Ref<DynamicLibrary>,Symbol,ffi_cif*);
    Variant invoke(Array args);
};

}

#endif // DYNAMIC_LIBRARY_FUNCTION_H
