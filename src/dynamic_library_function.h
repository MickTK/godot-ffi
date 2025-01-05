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

/**
 * @class DynamicLibraryFunction
 * @brief Dynamic library function wrapper.
 *
 * Dl function wrapper.
 */
class DynamicLibraryFunction : public RefCounted {
    GDCLASS(DynamicLibraryFunction, RefCounted);

private:
    /**
     * @brief Dynamic library reference (keeps it allocated).
     */
    Ref<DynamicLibrary> dl = nullptr;
    /**
     * @brief Call interface structure
     */
    ffi_cif* cif = nullptr;
    /**
     * @brief (Function) symbol pointer
     */
    Symbol symbol = nullptr;

protected:
    static void _bind_methods();

public:
    DynamicLibraryFunction();
    ~DynamicLibraryFunction();

    /**
    * @brief Bind the object to a dl function.
    *
    * Bind the object to a dl function.
    *
    * @param dl Dynamic library reference.
    * @param symbol Function name.
    * @param cif Call interface.
    */
    void bind(Ref<DynamicLibrary> dl, Symbol symbol, ffi_cif* cif);

    /**
    * @brief Invoke the function.
    *
    * Invoke the function with the given arguments and return the value.
    *
    * @param args Function arguments.
    * @return Function return value.
    */
    Variant invoke(Array args = Array());
};

}

#endif // DYNAMIC_LIBRARY_FUNCTION_H
