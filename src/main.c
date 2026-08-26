#include <stdio.h>
#include <string.h>
#include "init.h"
#include "activate.h"
#include "add.h"
#include "remove.h"
#include "delete.h"

static void print_usage(void)
{
    printf("usage: pmake <command> [arguments]\n\n");
    printf("commands:\n");
    printf("  init [name]        create a virtual environment\n");
    printf("  activate [name]    print the activation command\n");
    printf("  deactivate         print the deactivation command\n");
    printf("  add [--venv name] <packages...>  install packages into the virtual environment\n");
    printf("  remove [--venv name] <packages...>  uninstall packages from the virtual environment\n");
    printf("  delete [name]      remove the virtual environment\n");
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        print_usage();
        return 1;
    }

    if (strcmp(argv[1], "init") == 0)
        return init(argc, argv);

    if (strcmp(argv[1], "activate") == 0)
        return activate(argc, argv);

    if (strcmp(argv[1], "deactivate") == 0)
        return deactivate(argc, argv);

    if (strcmp(argv[1], "add") == 0)
        return add(argc, argv);

    if (strcmp(argv[1], "remove") == 0)
        return remove_packages(argc, argv);

    if (strcmp(argv[1], "delete") == 0)
        return delete_venv(argc, argv);

    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        print_usage();
        return 0;
    }

    fprintf(stderr, "pmake: unknown command '%s'\n", argv[1]);
    print_usage();
    return 1;
}
