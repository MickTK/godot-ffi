/**
 @file
 Common functions
*/

#ifndef COMMON_H
#define COMMON_H

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

Handle dl_open(char *filename);
char* dl_error();
int dl_close(Handle handle);
Symbol dl_sym(Handle handle, char *symbol); // Get DL symbol

#endif // COMMON_H
