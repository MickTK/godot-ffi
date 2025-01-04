#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "register_types.h"
#include "dynamic_library_loader.h"
#include "dynamic_library.h"
#include "dynamic_library_function.h"

using namespace godot;

void initialize_ffi_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) { return; }
	// Singletons
	ClassDB::register_class<DynamicLibraryLoader>();
    Engine::get_singleton()->register_singleton("DynamicLibraryLoader", memnew(DynamicLibraryLoader));
	// Classes
	GDREGISTER_CLASS(DynamicLibrary);
	GDREGISTER_CLASS(DynamicLibraryFunction);
}

void uninitialize_ffi_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT ffi_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_ffi_module);
	init_obj.register_terminator(uninitialize_ffi_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}