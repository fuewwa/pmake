#include "activate.h"
#include "platform.h"
#include "util.h"
#include <stdio.h>

int activate(int argc, char **argv)
{
    const char *venv_name = "venv";
    if (argc > 2)
        venv_name = argv[2];

    if (!path_exists(venv_name)) {
        fprintf(stderr, "pmake: '%s' not found, run 'pmake init' first\n", venv_name);
        return 1;
    }

    char command[512];
    venv_activate_command(command, sizeof(command), venv_name);
    printf("%s\n", command);
    return 0;
}

int deactivate(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("deactivate\n");
    return 0;
}
