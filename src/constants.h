#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <godot_cpp/classes/ref.hpp>

namespace godot {

class FFI : public RefCounted {
    GDCLASS(FFI, RefCounted);

protected:
    static void _bind_methods();

public:
    enum {
        VOID,

        UINT8, BOOL = UINT8,
        UINT16,
        UINT32,
        UINT64,
        SINT8,
        SINT16,
        SINT32,
        SINT64, INT = SINT64,
        
        UCHAR,
        SCHAR,

        FLOAT32,
        DOUBLE, FLOAT = DOUBLE, FLOAT64 = DOUBLE,

        POINTER, STRING = POINTER,
    };

};

}

#endif // CONSTANTS_H
