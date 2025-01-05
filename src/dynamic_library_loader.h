/**
 @file
 Load and open a dynamic library
*/

#ifndef DYNAMIC_LIBRARY_LOADER_H
#define DYNAMIC_LIBRARY_LOADER_H

#include "common.h"
#include "dynamic_library.h"

namespace godot {

/**
 * @class DynamicLibraryLoader
 * @brief Dynamic library loader.
 *
 * Load a new dynamic library.
 *
 * @note Singleton.
 */
class DynamicLibraryLoader : public RefCounted {
    GDCLASS(DynamicLibraryLoader, RefCounted);

protected:
    static void _bind_methods();

public:
    DynamicLibraryLoader();
    ~DynamicLibraryLoader();

    /**
    * @brief Open a dynamic library.
    *
    * Open a dynamic library with the given filename, relative to module folder.
    *
    * @param filename The name of the dl.
    * @return Reference to dl.
    */
    Ref<DynamicLibrary> open(String filename);

};

}

#endif // DYNAMIC_LIBRARY_LOADER_H
