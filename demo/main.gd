extends Control

func _ready() -> void:
	
	# Example
	var lib:DynamicLibrary = DynamicLibraryLoader.open("testlib.so")
	if lib:
		var fun:DynamicLibraryFunction = lib.get_function("float_sum", [FFI.FLOAT, FFI.FLOAT], FFI.FLOAT)
		if fun:
			var res:Variant = fun.invoke([1.5, 8.4])
			print(res) # 9.9
	
	# Quit
	await get_tree().create_timer(0.25).timeout
	get_tree().quit()
