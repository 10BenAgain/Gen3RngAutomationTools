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
    char f;
    const char* name;
    const char* description;
    uint8_t args;
} Flag;

typedef struct {
    const char* command;
    void (*handler)(int argc, char** argv);
    const char* description;
    const char** subcommands;
    Flag* flags;
    size_t f_size;
} Command;

void commandHelp();
void staticSearchExample();
void wildSearchExample();

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

static const char* SEARCH_SUBCOMMANDS[3] = {
        "static",
        "wild",
        NULL
};

static Flag searchFlags[9];

static Command commands[] = {
        { "list", listHandler, "List various related data", LIST_SUB_COMMANDS },
        { "t2s", shinySIDHandler, "Calculate the SID/TID shiny combination", NULL },
        { "search", searchHandler, "Search for Pokemon", SEARCH_SUBCOMMANDS, searchFlags, sizeof(searchFlags)/sizeof(searchFlags[0]) }
};

#endif
