extends SceneTree

func ASSERT(condition:bool, msg:String = "Assertion failed.") -> void:
	if not condition:
		push_error(msg)
		quit()

func _init():
	
	var dl:DynamicLibrary = DynamicLibraryLoader.open("testlib.so")
	var fn:DynamicLibraryFunction
	
	# void
	fn = dl.get_function("void_identity", [], FFI.VOID)

	# int
	fn = dl.get_function("int_identity", [FFI.INT], FFI.INT)
	ASSERT(fn.invoke([5]) == 5)
	ASSERT(fn.invoke([6543]) == 6543)
	ASSERT(fn.invoke([-7894]) == -7894)
	fn = dl.get_function("int_inc", [FFI.INT], FFI.INT)
	ASSERT(fn.invoke([5]) == 5+1)
	ASSERT(fn.invoke([6543]) == 6543+1)
	ASSERT(fn.invoke([-7894]) == -7894+1)
	fn = dl.get_function("int_neg", [FFI.INT], FFI.INT)
	ASSERT(fn.invoke([5]) == 5*-1)
	ASSERT(fn.invoke([6543]) == 6543*-1)
	ASSERT(fn.invoke([-7894]) == -7894*-1)
	fn = dl.get_function("int_sum", [FFI.INT, FFI.INT], FFI.INT)
	ASSERT(fn.invoke([5,12]) == 5+12)
	ASSERT(fn.invoke([6543,654]) == 6543+654)
	ASSERT(fn.invoke([-7894,123]) == -7894+123)

	# float
	fn = dl.get_function("float_identity", [FFI.FLOAT], FFI.FLOAT)
	ASSERT(fn.invoke([5.6]) == 5.6)
	ASSERT(fn.invoke([6543.123]) == 6543.123)
	ASSERT(fn.invoke([-7894.54]) == -7894.54)
	fn = dl.get_function("float_inc", [FFI.FLOAT], FFI.FLOAT)
	ASSERT(fn.invoke([5.3]) == 5.3+1)
	ASSERT(fn.invoke([6543.9]) == 6543.9+1)
	ASSERT(fn.invoke([-7894.4]) == -7894.4+1)
	fn = dl.get_function("float_neg", [FFI.FLOAT], FFI.FLOAT)
	ASSERT(fn.invoke([5.3]) == 5.3*-1)
	ASSERT(fn.invoke([6543.9]) == 6543.9*-1)
	ASSERT(fn.invoke([-7894.125]) == -7894.125*-1)
	fn = dl.get_function("float_sum", [FFI.FLOAT, FFI.FLOAT], FFI.FLOAT)
	ASSERT(fn.invoke([5.7899,12.1]) == 5.7899+12.1)
	ASSERT(fn.invoke([6543.0,654.56]) == 6543.0+654.56)
	ASSERT(fn.invoke([-7894.222,123.369]) == -7894.222+123.369)

	# bool
	fn = dl.get_function("bool_identity", [FFI.BOOL], FFI.BOOL)
	ASSERT(fn.invoke([true]) == 1)
	ASSERT(fn.invoke([false]) == 0)

	# string
	fn = dl.get_function("string_identity", [FFI.STRING], FFI.STRING)
	ASSERT(fn.invoke(["Hello world!"]) == "Hello world!")
	fn = dl.get_function("string_join", [FFI.STRING, FFI.STRING], FFI.STRING)
	ASSERT(fn.invoke(["Ciao, ", "Ciccio!"]) == "Ciao, Ciccio!")

	print("Assertions passed.")
	await create_timer(0.25).timeout
	quit()
