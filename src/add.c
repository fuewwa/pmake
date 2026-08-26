#include "add.h"
#include "platform.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

int add(int argc, char **argv)
{
    const char *venv_name = "venv";
    char *packages[argc];
    int pkg_count = 0;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--venv") == 0 || strcmp(argv[i], "-n") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "pmake: %s requires a name\n", argv[i]);
                return 1;
            }
            venv_name = argv[++i];
            continue;
        }
        packages[pkg_count++] = argv[i];
    }

    if (pkg_count == 0) {
        fprintf(stderr, "pmake: usage: pmake add [--venv <name>] <package> [package...]\n");
        return 1;
    }

    if (!path_exists(venv_name)) {
        fprintf(stderr, "pmake: '%s' not found, run 'pmake init' first\n", venv_name);
        return 1;
    }

    char pip_path[512];
    venv_pip_executable(pip_path, sizeof(pip_path), venv_name);

    char command[2048];
    snprintf(command, sizeof(command), "\"%s\" install", pip_path);

    for (int i = 0; i < pkg_count; i++) {
        strncat(command, " ", sizeof(command) - strlen(command) - 1);
        strncat(command, packages[i], sizeof(command) - strlen(command) - 1);
    }

    printf("pmake: installing packages\n");
    int result = run_command(command);

    if (result != 0) {
        fprintf(stderr, "pmake: failed to install packages\n");
        return 1;
    }

    printf("pmake: packages installed\n");
    return 0;
}
