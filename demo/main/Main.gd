extends Control
class_name Main

func exit(secs:float = 0.25) -> void:
	await get_tree().create_timer(secs).timeout
	get_tree().quit()


func _ready() -> void:
	
	var loader:DynamicLibraryLoader = DynamicLibraryLoader.new()
	var dl:DynamicLibrary = loader.open("testlib.so")
	var fn:DynamicLibraryFunction
	
	# void
	fn = dl.get_function("void_identity", [], "void")
	# int
	fn = dl.get_function("int_identity", ["sint64"], "sint64")
	assert(fn.invoke([5]) == 5)
	assert(fn.invoke([6543]) == 6543)
	assert(fn.invoke([-7894]) == -7894)
	fn = dl.get_function("int_inc", ["sint64"], "sint64")
	assert(fn.invoke([5]) == 5+1)
	assert(fn.invoke([6543]) == 6543+1)
	assert(fn.invoke([-7894]) == -7894+1)
	fn = dl.get_function("int_neg", ["sint64"], "sint64")
	assert(fn.invoke([5]) == 5*-1)
	assert(fn.invoke([6543]) == 6543*-1)
	assert(fn.invoke([-7894]) == -7894*-1)
	fn = dl.get_function("int_sum", ["sint64", "sint64"], "sint64")
	assert(fn.invoke([5,12]) == 5+12)
	assert(fn.invoke([6543,654]) == 6543+654)
	assert(fn.invoke([-7894,123]) == -7894+123)
	# float
	fn = dl.get_function("float_identity", ["double"], "double")
	assert(fn.invoke([5.6]) == 5.6)
	assert(fn.invoke([6543.123]) == 6543.123)
	assert(fn.invoke([-7894.54]) == -7894.54)
	fn = dl.get_function("float_inc", ["double"], "double")
	assert(fn.invoke([5.3]) == 5.3+1)
	assert(fn.invoke([6543.9]) == 6543.9+1)
	assert(fn.invoke([-7894.4]) == -7894.4+1)
	fn = dl.get_function("float_neg", ["double"], "double")
	assert(fn.invoke([5.3]) == 5.3*-1)
	assert(fn.invoke([6543.9]) == 6543.9*-1)
	assert(fn.invoke([-7894.125]) == -7894.125*-1)
	fn = dl.get_function("float_sum", ["double", "double"], "double")
	assert(fn.invoke([5.7899,12.1]) == 5.7899+12.1)
	assert(fn.invoke([6543.0,654.56]) == 6543.0+654.56)
	assert(fn.invoke([-7894.222,123.369]) == -7894.222+123.369)
	# bool
	fn = dl.get_function("bool_identity", ["sint64"], "sint64")
	assert(fn.invoke([int(true)]) == int(true))
	assert(fn.invoke([int(false)]) == int(false))
	
	print("Test completed.")
	exit()
