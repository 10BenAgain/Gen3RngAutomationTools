#include <stdlib.h>
#include <string.h>

#include "include/commands.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        commandHelp();
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < COMMANDS_COUNT; i++) {
        if (COMATCH(argv[1], commands[i].command)) {
            commands[i].handler(argc, argv);
            return EXIT_SUCCESS;
        }
    }

    return EXIT_SUCCESS;
}