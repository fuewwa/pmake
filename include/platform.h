#ifndef PLATFORM_H
#define PLATFORM_H

#include <stddef.h>

typedef enum {
    OS_LINUX,
    OS_MACOS,
    OS_WINDOWS,
    OS_UNKNOWN
} os_type_t;

os_type_t current_os(void);
const char *python_executable(void);
void venv_pip_executable(char *buffer, size_t size, const char *venv_name);
void venv_python_executable(char *buffer, size_t size, const char *venv_name);
void venv_activate_command(char *buffer, size_t size, const char *venv_name);

#endif
