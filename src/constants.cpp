#include "constants.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void FFI::_bind_methods() {
    ClassDB::bind_integer_constant(get_class_static(), "", "VOID", VOID);
    ClassDB::bind_integer_constant(get_class_static(), "", "UINT8", UINT8);
    ClassDB::bind_integer_constant(get_class_static(), "", "BOOL", BOOL);
    ClassDB::bind_integer_constant(get_class_static(), "", "UINT16", UINT16);
    ClassDB::bind_integer_constant(get_class_static(), "", "UINT32", UINT32);
    ClassDB::bind_integer_constant(get_class_static(), "", "UINT64", UINT64);
    ClassDB::bind_integer_constant(get_class_static(), "", "SINT8", SINT8);
    ClassDB::bind_integer_constant(get_class_static(), "", "SINT16", SINT16);
    ClassDB::bind_integer_constant(get_class_static(), "", "SINT32", SINT32);
    ClassDB::bind_integer_constant(get_class_static(), "", "SINT64", SINT64);
    ClassDB::bind_integer_constant(get_class_static(), "", "INT", INT);
    ClassDB::bind_integer_constant(get_class_static(), "", "UCHAR", UCHAR);
    ClassDB::bind_integer_constant(get_class_static(), "", "SCHAR", SCHAR);
    ClassDB::bind_integer_constant(get_class_static(), "", "FLOAT32", FLOAT32);
    ClassDB::bind_integer_constant(get_class_static(), "", "DOUBLE", DOUBLE);
    ClassDB::bind_integer_constant(get_class_static(), "", "FLOAT", FLOAT);
    ClassDB::bind_integer_constant(get_class_static(), "", "FLOAT64", FLOAT64);
    ClassDB::bind_integer_constant(get_class_static(), "", "POINTER", POINTER);
    ClassDB::bind_integer_constant(get_class_static(), "", "STRING", STRING);
}
