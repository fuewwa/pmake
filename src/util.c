#include "util.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int path_exists(const char *path)
{
    struct stat st;
    return stat(path, &st) == 0;
}

int run_command(const char *command)
{
    return system(command);
}

int remove_directory_recursive(const char *path)
{
    char command[1024];

#if defined(_WIN32) || defined(_WIN64)
    snprintf(command, sizeof(command), "rmdir /s /q \"%s\"", path);
#else
    snprintf(command, sizeof(command), "rm -rf \"%s\"", path);
#endif

    return system(command);
}
