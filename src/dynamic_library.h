/**
 @file
 Dynamic library reference
*/

#ifndef DYNAMIC_LIBRARY_H
#define DYNAMIC_LIBRARY_H

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>

#include "common.h"

namespace godot {

class DynamicLibraryFunction; // forward declaration

class DynamicLibrary : public RefCounted {
    GDCLASS(DynamicLibrary, RefCounted);

private:
    Handle handle = nullptr;

protected:
    static void _bind_methods();

public:
    DynamicLibrary();
    ~DynamicLibrary();

    void set_handle(Handle handle);
    Ref<DynamicLibraryFunction> get_function(String name, PackedStringArray argument_types, String return_type);

};

}

#endif // DYNAMIC_LIBRARY_H
