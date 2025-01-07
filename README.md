![Godot](https://badgen.net/badge/Godot/4.3/blue)
![Version](https://badgen.net/badge/Version/1.0.0/green)

<p align="center">
<img src="https://godotengine.org/assets/press/icon_color.png" alt="Godot logo" width="150">
</p>

<h1 align="center">Godot FFI</h1>

<p align="center">
A foreign function interface plugin written with GDExtension, based on <a href="https://github.com/and3rson/foreigner">foreigner</a>.
</p>

## Building and testing

Informations and dependencies can be found in the [official page](https://docs.godotengine.org/en/4.3/tutorials/scripting/gdextension/index.html).

```bash
# Compile the plugin (with default parameters)
scons
# Compile the test library
gcc -shared testlib/testlib.cpp -o demo/bin/testlib.so
# Execute gd tests
cd demo
godot --no-window --headless --script test.gd
```

## Example

```gdscript
var lib:DynamicLibrary = DynamicLibraryLoader.open("testlib.so")
if lib:
  var fun:DynamicLibraryFunction = lib.get_function("float_sum", [FFI.FLOAT, FFI.FLOAT], FFI.FLOAT)
  if fun:
    var res:Variant = fun.invoke([1.5, 8.4])
    print(res) # 9.9
```
