/**
 @file
 Common functions
*/

#ifndef COMMON_H
#define COMMON_H

#include <ffi.h>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/classes/ref.hpp>

#if defined(__linux__) || defined(__APPLE__) || defined(__unix__)
#include <dlfcn.h>
#define IS_UNIX
typedef void* Handle;
#endif

#ifdef _WIN32
#include <windows.h>
#define IS_WINDOWS
typedef HINSTANCE Handle;
#endif

typedef void* Symbol;

using namespace godot;

/**
 * @brief Open a dynamic library.
 *
 * Open a dynamic library from module relative path and return and handle.
 *
 * @param filename The name of the dynamic library.
 * @return The library handle.
 */
Handle dl_open(char* filename);

/**
 * @brief Get a dl loading error.
 *
 * Get the error given when loading a dynamic library.
 *
 * @return Error message.
 */
char* dl_error();

/**
 * @brief Close a dynamic library.
 *
 * Close a dynamic library and dealloc the reference.
 *
 * @param handle Handle to the dl.
 * @return Current number of dl references.
 */
int dl_close(Handle handle);

/**
 * @brief Get a symbol from a dl.
 *
 * Get a (function) symbol from an opened dynamic library.
 *
 * @param handle Handle to dl.
 * @param symbol Function name.
 * @return Pointer to symbol.
 */
Symbol dl_sym(Handle handle, char* symbol); // get DL symbol

/**
 * @brief Print an error message.
 *
 * Print a custom error message in godot terminal.
 *
 * @param message Message to print
 */
void error_msg(String message);

namespace godot {

/**
 * @class FFI
 * @brief FFI types.
 *
 * FFI types enumeration.
 *
 * @note Singleton.
 */
class FFI : public RefCounted {
    GDCLASS(FFI, RefCounted);

protected:
    static void _bind_methods();

public:
    enum {
        VOID,
        UINT8,   /**< Unsigned 8 bit integer. */
        UINT16,  /**< Unsigned 16 bit integer. */
        UINT32,  /**< Unsigned 32 bit integer. */
        UINT64,  /**< Unsigned 64 bit integer. */
        SINT8,   /**< Signed 8 bit integer. */
        SINT16,  /**< Signed 16 bit integer. */
        SINT32,  /**< Signed 32 bit integer. */
        SINT64,  /**< Signed 64 bit integer. */
        UCHAR,   /**< Unsigned char. */
        SCHAR,   /**< Signed char. */
        FLOAT32, /**< 32 bit float. */
        DOUBLE,  /**< 64 bit float. */
        POINTER, /**< Unsigned 64 bit pointer. */

        /* Aliases */
        BOOL = UINT8,
        INT = SINT64,
        FLOAT = DOUBLE, FLOAT64 = DOUBLE,
        STRING = POINTER,
    };

    /**
    * @brief Get a ffi type from literal.
    *
    * Get and return a ffi type corresponding to the given string name.
    *
    * @param type Type name.
    * @return Pointer to ffi type.
    */
    static ffi_type* get_type(int type);
};

}

#endif // COMMON_H
