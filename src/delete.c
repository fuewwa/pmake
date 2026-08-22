#include "delete.h"
#include "util.h"
#include <stdio.h>

int delete_venv(int argc, char **argv)
{
    const char *venv_name = "venv";
    if (argc > 2)
        venv_name = argv[2];

    if (!path_exists(venv_name)) {
        fprintf(stderr, "pmake: '%s' not found\n", venv_name);
        return 1;
    }

    printf("pmake: deleting '%s'\n", venv_name);
    int result = remove_directory_recursive(venv_name);

    if (result != 0) {
        fprintf(stderr, "pmake: failed to delete '%s'\n", venv_name);
        return 1;
    }

    printf("pmake: '%s' deleted\n", venv_name);
    return 0;
}
