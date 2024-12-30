/**
 @file
 Dynamic library reference
*/

#ifndef DYNAMIC_LIBRARY_H
#define DYNAMIC_LIBRARY_H

//#include <godot_cpp/variant/ref.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
//#include <godot_cpp/classes/reference.hpp>

#include "common.h"
#include "dynamic_library_function.h"

namespace godot {

class DynamicLibrary : public RefCounted {
    GDCLASS(DynamicLibrary, RefCounted);

private:
    Handle handle = nullptr;

protected:
    static void _bind_methods();

public:
    DynamicLibrary();
    DynamicLibrary(Handle handle);
    ~DynamicLibrary();

    Ref<DynamicLibraryFunction> get_function(String name, PackedStringArray argument_types, String return_type);

};

}

#endif // DYNAMIC_LIBRARY_H
