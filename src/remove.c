#include "remove.h"
#include "platform.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

int remove_packages(int argc, char **argv)
{
    const char *venv_name = "venv";

    if (argc < 3) {
        fprintf(stderr, "pmake: usage: pmake remove <package> [package...]\n");
        return 1;
    }

    if (!path_exists(venv_name)) {
        fprintf(stderr, "pmake: '%s' not found, run 'pmake init' first\n", venv_name);
        return 1;
    }

    char pip_path[512];
    venv_pip_executable(pip_path, sizeof(pip_path), venv_name);

    char command[2048];
    snprintf(command, sizeof(command), "\"%s\" uninstall -y", pip_path);

    for (int i = 2; i < argc; i++) {
        strncat(command, " ", sizeof(command) - strlen(command) - 1);
        strncat(command, argv[i], sizeof(command) - strlen(command) - 1);
    }

    printf("pmake: removing packages\n");
    int result = run_command(command);

    if (result != 0) {
        fprintf(stderr, "pmake: failed to remove packages\n");
        return 1;
    }

    printf("pmake: packages removed\n");
    return 0;
}
