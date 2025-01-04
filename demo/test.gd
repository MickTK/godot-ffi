extends SceneTree

func ASSERT(condition:bool, msg:String = "Assertion failed.") -> void:
	if not condition:
		push_error(msg)
		quit()

func _init():
	
	var dl:DynamicLibrary = DynamicLibraryLoader.open("testlib.so")
	var fn:DynamicLibraryFunction
	
	# void
	fn = dl.get_function("void_identity", [], "void")
	
	# int
	fn = dl.get_function("int_identity", ["sint64"], "sint64")
	ASSERT(fn.invoke([5]) == 5)
	ASSERT(fn.invoke([6543]) == 6543)
	ASSERT(fn.invoke([-7894]) == -7894)
	fn = dl.get_function("int_inc", ["sint64"], "sint64")
	ASSERT(fn.invoke([5]) == 5+1)
	ASSERT(fn.invoke([6543]) == 6543+1)
	ASSERT(fn.invoke([-7894]) == -7894+1)
	fn = dl.get_function("int_neg", ["sint64"], "sint64")
	ASSERT(fn.invoke([5]) == 5*-1)
	ASSERT(fn.invoke([6543]) == 6543*-1)
	ASSERT(fn.invoke([-7894]) == -7894*-1)
	fn = dl.get_function("int_sum", ["sint64", "sint64"], "sint64")
	ASSERT(fn.invoke([5,12]) == 5+12)
	ASSERT(fn.invoke([6543,654]) == 6543+654)
	ASSERT(fn.invoke([-7894,123]) == -7894+123)

	# float
	fn = dl.get_function("float_identity", ["double"], "double")
	ASSERT(fn.invoke([5.6]) == 5.6)
	ASSERT(fn.invoke([6543.123]) == 6543.123)
	ASSERT(fn.invoke([-7894.54]) == -7894.54)
	fn = dl.get_function("float_inc", ["double"], "double")
	ASSERT(fn.invoke([5.3]) == 5.3+1)
	ASSERT(fn.invoke([6543.9]) == 6543.9+1)
	ASSERT(fn.invoke([-7894.4]) == -7894.4+1)
	fn = dl.get_function("float_neg", ["double"], "double")
	ASSERT(fn.invoke([5.3]) == 5.3*-1)
	ASSERT(fn.invoke([6543.9]) == 6543.9*-1)
	ASSERT(fn.invoke([-7894.125]) == -7894.125*-1)
	fn = dl.get_function("float_sum", ["double", "double"], "double")
	ASSERT(fn.invoke([5.7899,12.1]) == 5.7899+12.1)
	ASSERT(fn.invoke([6543.0,654.56]) == 6543.0+654.56)
	ASSERT(fn.invoke([-7894.222,123.369]) == -7894.222+123.369)

	# bool
	fn = dl.get_function("bool_identity", ["uint8"], "uint8")
	ASSERT(fn.invoke([true]) == 1)
	ASSERT(fn.invoke([false]) == 0)

	# string
	fn = dl.get_function("string_identity", ["string"], "string")
	ASSERT(fn.invoke(["Hello world!"]) == "Hello world!")
	fn = dl.get_function("string_join", ["string", "string"], "string")
	ASSERT(fn.invoke(["Ciao, ", "Ciccio!"]) == "Ciao, Ciccio!")

	print("Assertions passed.")
	await create_timer(0.25).timeout
	quit()
