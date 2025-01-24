#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/enums.h"
#include "../include/locations.h"
#include "../include/ivs.h"
#include "../include/seeds.h"
#include "../include/filters.h"
#include "../include/settings.h"

#define COMATCH(s, c) (!strcmp((s),(c)))
#define COMMANDS_COUNT (sizeof(commands)/sizeof(commands[0]))

typedef struct {
    const char* command;
    void (*handler)(int argc, char** argv);
    const char* description;
    const char** subcommands;
    void (*flag)();
} Command;

void commandHelp();
void searchMissingArgs(const char* subCommand);
void listHandler(int argc, char** argv);
void searchHandler(int argc, char** argv);
void shinySIDHandler(int argc, char** argv);

size_t getSubCommandCount(const char** sc);

static const char* LIST_SUB_COMMANDS[7] = {
        "natures",
        "gender",
        "shiny",
        "hidden",
        "locations",
        "encounter",
        NULL
};

static const char* SEARCH_SUB_COMMANDS[3] = {
        "static",
        "wild",
        NULL
};

void PrintSearchFlags();

static Command commands[] = {
        { "list",   listHandler,      "List various related data",               LIST_SUB_COMMANDS,    NULL },
        { "t2s",    shinySIDHandler,  "Calculate the SID/TID shiny combination", NULL,                 NULL },
        { "search", searchHandler,    "Search for Pokemon",                      SEARCH_SUB_COMMANDS,  PrintSearchFlags }
};

#endif
