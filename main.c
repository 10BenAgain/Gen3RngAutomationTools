#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "include/enums.h"
#include "include/locations.h"
#include "include/pokemon.h"
#include "include/ivs.h"
#include "include/seeds.h"
#include "include/filters.h"
#include "include/settings.h"

#define COMATCH(s, c) (!strcmp((s),(c)))
#define COMMANDS_COUNT (sizeof(commands)/sizeof(commands[0]))

size_t _getSubCommandCount(const char** sc);

void listHandler(int argc, char** argv);
void commandHelp();

typedef struct {
    const char* command;
    void (*handler)(int argc, char** argv);
    const char* description;
    const char** subcommands;
} Command;

const char* LIST_SUB_COMMANDS[4] = {
    "natures",
    "locations",
    "encounter",
    NULL
};

Command commands[] = {
    { "list", listHandler, "List various related data", LIST_SUB_COMMANDS }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        commandHelp();
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < COMMANDS_COUNT; i++) {
        if (COMATCH(argv[1], commands[i].command)) {
            commands[i].handler(argc, argv);
            return EXIT_SUCCESS;
        }
    }

    char* path = "settings.ini";

    /* Make sure the file actually exists*/
    if (access(path, F_OK)) {
        perror("Unable to find ini file!\n");
        return EXIT_FAILURE;
    }

    /* Declare config struct and parse the file with the specified handler*/
    Config cf;
    if (ini_parse(path, handler, &cf) < 0) {
        perror("Unable to load ini file!\n");
        return EXIT_FAILURE;
    }

    /* Declare player struct */
    Player player;

    /* Declare setting enums to be used from config file */
    Settings settings;

    /* Convert config to player basically */
    player.SID = cf.sid;
    player.TID = cf.tid;

    /* Make sure the loaded values are correct*/
    loadSettings(&cf, &settings);

    /* Search target */
    Pokemon mon = pokemon[20]; // Spearow
    Nature nat = natures[8]; // Impish
    uint8_t level = 13;
    uint32_t target_seed = 0xE585;

    /* Declare the encounter type and the area where the encounter happens */
    EncounterType encT = Grass;
    AreaEntry at = LAND_AREA_MAP[55]; // Route 10

    /* Create a path to the seed data based on the game version and in game settings */
    const char* fp = SeedGetFilePath(settings);
    if (access(fp, F_OK)) {
        perror("Data files missing or not loaded properly!\n");
        return EXIT_FAILURE;
    }

    /* Declare variable to store the amount of seeds that are going to be added to the seeds array*/
    uint64_t len, s_len;
    int index;

    /* Load the seed data based on the file path determined earlier */
    InitialSeed *seeds = SeedLoadInitial(fp, &len, None);

    if(seeds == NULL) {
        perror("Failed to load initial seed list");
        free(seeds);
        return EXIT_FAILURE;
    }

    /* Find the index of the target seed from the seed data file */
    index = SeedFindIndex(seeds, target_seed, len);

    if (index < 0) {
        perror("Seed not found in data!");
        return EXIT_FAILURE;
    }

    /* Declare and initialize the range of seeds to look thru (+/-) target index */
    uint16_t range = 10;

    /* Create an array of new seed structs from range input and copy the new range to s_len*/
    InitialSeed *seedRange = SeedGetSeedRange(seeds, len, index, range, &s_len);
    if(seedRange == NULL) {
        perror("Failed to load new seed list");
        free(seeds);
        return EXIT_FAILURE;
    }

    /* Free the original total list of seeds */
    free(seeds);

    /* Determine the encounter slot data path from game version and area*/
    const char *encounter_data_path = LocationGetEncounterFilePath(settings.gv, at.at);

    /* Load slot data in Slot struct array based on input path determined earlier*/
    Slot *slots = LocationLoadEncounterSlots(at, encounter_data_path);

    if (slots == NULL) {
        perror("Failed to load encounter slots");
        free(slots);
        return EXIT_FAILURE;
    }

    /* Declare a filter struct with values to search for while generating encounters */
    WildFilter wf = {
            mon.dex - 1,
            level,
            {1, 1},
            {0},
            {0},
            {0},
            {0},
            {0},
            {0},
            {1, 1, 0},
            {0, 0, 1},
            {0}
    };

    /* IV Estimator struct where our only known values are the total stat, nature, level, and mon*/
    IVEstimate target = {
            mon,
            nat,
            level,
            {34, 20, 14, 12, 13, 24},
            {0}
    };

    /* This is probably really stupid, but it sets the nature array to search values*/
    FilterApplyNatureToWild(nat, &wf);

    /* Calculate the upper and lower bounds for each stat based on the estimate struct then add them into the filter*/
    FilterApplyIVEstimateToWild(&target, &wf);

    clock_t t;
    t = clock();

    /* Create the head node of a linked list to add encounters to */
    wenc_node *head = NULL;

    /* Declare and initialize search parameters*/
    uint32_t init, max;
    init = 0;
    max = 100;

    /* Generate some wild encounters */
    FilterGenerateWildEncountersFromSeedList(&head, player, H1, slots, encT, wf, seedRange, s_len, init, max);

    /* Print results of generated encounters from linked list*/
    FilterPrintWEncounterList(head);

    t = clock() - t;
    double time_taken = (double)t/CLOCKS_PER_SEC;
    fprintf(stdout, "\nCompleted in %f seconds\n", time_taken);

    /* Free all the memory that was created */
    FilterFreeWEncList(head);
    free(seedRange);
    free(slots);

    return EXIT_SUCCESS;
}

size_t _getSubCommandCount(const char** sc) {
    size_t count = 0;
    while(sc[count] != NULL) {
        count++;
    }
    return count;
}

void commandHelp() {
    fprintf(stdout, "----List of available commands:----\n\n");
    for (size_t i = 0; i < COMMANDS_COUNT; i++) {
        fprintf(stdout, "Name: '%s'\n", commands[i].command);
        fprintf(stdout, "Description: '%s'\nSubcommands:\n", commands[i].description);
        for (size_t j = 0; j < _getSubCommandCount(commands[i].subcommands); j++) {
            fprintf(stdout, "   - %s\n", commands[i].subcommands[j]);
        }
    }
}

void listHandler(int argc, char** argv) {
    long l;
    char* lend;

    /* List command */
    const char* command = commands[0].command;

    if (argc < 3) {
        fprintf(stdout, "Error: 'list requires additional arguments.\n");
        fprintf(stdout, "   'list natures'\n");
        fprintf(stdout, "   'list encounters grass'\n");
        return;
    }
    const char* subcommand = argv[2];

    if (COMATCH(subcommand, LIST_SUB_COMMANDS[0])) {
        /* bin list natures (3)*/
        PokemonListNatures();
    } else if (COMATCH(subcommand, LIST_SUB_COMMANDS[1])) {
        /* bin list locations grass (4) */
        if (argc < 4) {
            fprintf(stdout, "Missing encounter arguments. Encounter type required:\n");
            fprintf(stdout, "Available options:\n");
            fprintf(stdout, "   'grass'\n");
            fprintf(stdout, "   'water'\n");
            fprintf(stdout, "   'rock'\n");
            return;
        }
        const char* location = argv[3];
        if (COMATCH(location, "grass")) {
            LocationListFromEncType(Grass);
        } else if (COMATCH(location, "water")) {
            LocationListFromEncType(Water);
        } else if (COMATCH(location, "rock")) {
            LocationListFromEncType(RockSmash);
        } else {
            fprintf(stdout, "unable to match location string string\n");
            return;
        }
    } else if (COMATCH(subcommand, LIST_SUB_COMMANDS[2])) {
        if (argc < 6) {
            /* bin list encounter grass 46 lg */
            fprintf(stdout, "Missing location arguments. Example command:\n");
            fprintf(stdout, "   'list encounter [location type] [index] [Game Version]\n");
            fprintf(stdout, "   'list encounter grass 46 lg'\n");
            fprintf(stdout, "   'list encounter grass 46 fr'\n");
            return;
        }
        const char* location = argv[3];
        const char* map = argv[4];
        const char* version = argv[5];

        GameVersion gv = FR;
        if (COMATCH(version, "lg")) {
            gv = LG;
        }

        l = strtol(map, &lend, 10);
        if (lend == map) {
            fprintf(stdout, "Encounter location index must be an integer!");
            return;
        } else if (COMATCH(location, "grass") && l < 90) {
            LocationListMonsInLocation(gv, LAND_AREA_MAP[l]);
        } else if (COMATCH(location, "water") && l < 50) {
            LocationListMonsInLocation(gv, WATER_AREA_MAP[l]);
        } else if (COMATCH(location, "rock") && l < 13) {
            LocationListMonsInLocation(gv, ROCK_AREA_MAP[l]);
        } else {
            fprintf(stderr, "An unknown error occurred.\n");
            return;
        }
    } else {
        fprintf(stderr, "Subcommand not recognized!\n");
        return;
    }
}
