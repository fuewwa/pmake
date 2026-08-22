#include "platform.h"
#include <stdio.h>

os_type_t current_os(void)
{
#if defined(_WIN32) || defined(_WIN64)
    return OS_WINDOWS;
#elif defined(__APPLE__)
    return OS_MACOS;
#elif defined(__linux__)
    return OS_LINUX;
#else
    return OS_UNKNOWN;
#endif
}

const char *python_executable(void)
{
    if (current_os() == OS_WINDOWS)
        return "python";
    return "python3";
}

void venv_pip_executable(char *buffer, size_t size, const char *venv_name)
{
    if (current_os() == OS_WINDOWS)
        snprintf(buffer, size, "%s\\Scripts\\pip.exe", venv_name);
    else
        snprintf(buffer, size, "%s/bin/pip", venv_name);
}

void venv_python_executable(char *buffer, size_t size, const char *venv_name)
{
    if (current_os() == OS_WINDOWS)
        snprintf(buffer, size, "%s\\Scripts\\python.exe", venv_name);
    else
        snprintf(buffer, size, "%s/bin/python", venv_name);
}

void venv_activate_command(char *buffer, size_t size, const char *venv_name)
{
    if (current_os() == OS_WINDOWS)
        snprintf(buffer, size, "%s\\Scripts\\activate.bat", venv_name);
    else
        snprintf(buffer, size, "source %s/bin/activate", venv_name);
}
