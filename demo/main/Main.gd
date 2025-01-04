extends Control
class_name Main

func _ready() -> void:
	
	var dl:DynamicLibrary = DynamicLibraryLoader.open("testlib.so")
	var fn:DynamicLibraryFunction
	fn = dl.get_function("void_identity", [], "void")
	
	
	
	
	await get_tree().create_timer(0.25).timeout
	get_tree().quit()
