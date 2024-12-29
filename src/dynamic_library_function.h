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

typedef struct {
    ffi_cif *cif; // call interface
    std::string symbol; // function name
    std::vector<std::string> arg_types; // argument types
    ffi_type *ret_type; // return type
} signature_t;

class DynamicLibraryFunction : public Reference {
    GODOT_CLASS(DynamicLibraryFunction, Reference)

private:
    signature_t signature;

protected:
    static void _bind_methods();

public:
    DynamicLibraryFunction();
    DynamicLibraryFunction(signature_t signature);
    ~DynamicLibraryFunction();

    Variant invoke(Array args);
}

}

#endif // DYNAMIC_LIBRARY_FUNCTION_H
