#include <stdlib.h>
#include <string.h>

#include "include/commands.h"

#define PROG_NAME "gts"

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Unable to process request. Use '%s help' for a list of commands\n", PROG_NAME);
        return EXIT_FAILURE;
    } else if (argc < 3 && COMATCH(argv[1], "help")) {
        commandHelp();
        return EXIT_SUCCESS;
    } else {
        for (size_t i = 0; i < COMMANDS_COUNT; i++) {
            if (COMATCH(argv[1], commands[i].command)) {
                commands[i].handler(argc, argv);
                return EXIT_SUCCESS;
            }
        }
    }
    return EXIT_SUCCESS;
}