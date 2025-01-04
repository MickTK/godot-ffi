#include <cstdint>
#include <cstring>
#include <stdio.h>

extern "C" {
    // void
    void void_identity() {return;}
    // int
    int64_t int_identity(int64_t val) {return val;}
    int64_t int_inc(int64_t val) {return ++val;}
    int64_t int_neg(int64_t val) {return val*-1;}
    int64_t int_sum(int64_t val0, int64_t val1) {return val0+val1;}
    // float
    double float_identity(double val) {return val;}
    double float_inc(double val) {return ++val;}
    double float_neg(double val) {return val*-1;}
    double float_sum(double val0, double val1) {return val0+val1;}
    // bool
    uint8_t bool_identity(uint8_t val) {return val;}
    // string
    const char* string_identity(const char* val) {return val;}
    char* string_join(const char *a, const char *b) {
        char *c = new char[strlen(a) + strlen(b) + 1];
        strncpy(c, a, strlen(a));
        strncpy(c + strlen(a), b, strlen(b));
        c[strlen(a) + strlen(b)] = 0;
        return c;
    }
}
