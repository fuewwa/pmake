#include "init.h"
#include "platform.h"
#include "util.h"
#include <stdio.h>

int init(int argc, char **argv)
{
    const char *venv_name = "venv";
    if (argc > 2)
        venv_name = argv[2];

    if (path_exists(venv_name)) {
        fprintf(stderr, "pmake: '%s' already exists\n", venv_name);
        return 1;
    }

    char command[512];
    snprintf(command, sizeof(command), "%s -m venv %s", python_executable(), venv_name);

    printf("pmake: creating virtual environment '%s'\n", venv_name);
    int result = run_command(command);

    if (result != 0) {
        fprintf(stderr, "pmake: failed to create virtual environment\n");
        return 1;
    }

    printf("pmake: virtual environment '%s' created\n", venv_name);
    return 0;
}
