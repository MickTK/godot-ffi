/**
 @file
 Dynamic library function reference
*/

#ifndef DYNAMIC_LIBRARY_FUNCTION_H
#define DYNAMIC_LIBRARY_FUNCTION_H

#include <ffi.h>
#include <vector>

#include "common.h"

namespace godot {

class DynamicLibraryFunction : public Reference {
    GODOT_CLASS(DynamicLibraryFunction, Reference)

private:
    ffi_cif *cif = nullptr;  // call interface
    Symbol symbol = nullptr; // lib function pointer

protected:
    static void _bind_methods();

public:
    DynamicLibraryFunction();
    DynamicLibraryFunction(ffi_cif*);
    ~DynamicLibraryFunction();

    Variant invoke(Array args);
}

}

#endif // DYNAMIC_LIBRARY_FUNCTION_H
