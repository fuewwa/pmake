#ifndef UTIL_H
#define UTIL_H

int path_exists(const char *path);
int run_command(const char *command);
int remove_directory_recursive(const char *path);

#endif
