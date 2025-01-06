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

/**
 * @class DynamicLibrary
 * @brief Dynamic library handle wrapper.
 *
 * Wrapper of dl handle. Used to get dl informations.
 */
class DynamicLibrary : public RefCounted {
    GDCLASS(DynamicLibrary, RefCounted);

private:
    /**
     * @brief Dynamic library handle.
     */
    Handle handle = nullptr;

protected:
    /**
    * @brief GDScript API.
    */
    static void _bind_methods();

public:
    DynamicLibrary();
    ~DynamicLibrary();

    /**
    * @brief Set a new handle.
    *
    * Set a new dynamic library handle.
    *
    * @param handle Dl handle.
    */
    void set_handle(Handle handle);

    /**
    * @brief Get a function from the dl.
    *
    * Get a function from the dynamic library.
    *
    * @param name The name of the function (symbol).
    * @param argument_types The types of the arguments.
    * @param return_type The type of the value returned by the function.
    * @return Reference to dl function.
    */
    Ref<DynamicLibraryFunction> get_function(String name, PackedInt32Array argument_types, int return_type);

};

}

#endif // DYNAMIC_LIBRARY_H
