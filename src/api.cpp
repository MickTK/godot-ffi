#include "dynamic_library_loader.h"
#include "dynamic_library.h"
#include "dynamic_library_function.h"

void DynamicLibraryLoader::_bind_methods() {
	ClassDB::bind_method(D_METHOD("open", "filename"), &DynamicLibraryLoader::open);
}
