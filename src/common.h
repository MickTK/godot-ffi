/**
 @file
 Common functions
*/

#ifndef COMMON_H
#define COMMON_H

#include <ffi.h>
#include <godot_cpp/variant/string.hpp>

#if defined(__linux__) || defined(__APPLE__) || defined(__unix__)
#include <dlfcn.h>
#define IS_UNIX
typedef void* Handle;
#endif

#ifdef _WIN32
#include <windows.h>
#define IS_WINDOWS
typedef HINSTANCE Handle;
#endif

typedef void* Symbol;

Handle dl_open(char* filename);
char* dl_error();
int dl_close(Handle handle);
Symbol dl_sym(Handle handle, char* symbol); // get DL symbol

void error_msg(String message);

ffi_type* get_type(String type); // get ffi type

#endif // COMMON_H
