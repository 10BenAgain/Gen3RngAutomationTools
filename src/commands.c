#include "../include/commands.h"

void staticSearchExample() {
    fprintf(stdout, "\nMissing required arguements for static search command:\n");
    fprintf(stdout, "Static search arguments: bin search static [Advances] [Pokemon] [Nature] [Level] [Ability] [HP] [ATK] [DEF] [SPA] [SPD] [SPE] [Gender] [Shiny]\n");
    fprintf(stdout, "Exmaple command:\n");
    fprintf(stdout, "   --search static 1000 Snorlax Sassy 30 0 145 80 58 49 73 32 Male Star\n");
    fprintf(stdout, "   --search static 1000 Snorlax 30 Relaxed 1 145 80 58 49 73 32 Female Square\n");
}

void wildSearchExample() {
    fprintf(stdout, "\nMissing required arguements for wild search command:\n");
    fprintf(stdout, "Wild search arguments: bin search wild [Advances] [Encounter Type] [Location] [Pokemon] [Nature] [Level] [Ability] [HP] [ATK] [DEF] [SPA] [SPD] [SPE] [Gender] [Shiny]\n");
    fprintf(stdout, "Exmaple command:\n");
    fprintf(stdout, "   --search wild 1000 grass 55 Sandshrew Sassy 15 0 44 32 38 12 18 21 Female Star\n");
    fprintf(stdout, "   --search wild 1000 grass 55 Sandshrew Jolly 15 1 44 32 38 12 18 21 Male None\n");
}

static Flag searchFlags[8] = {
        { 't', "Hold Select",
                "Use this flag to tell the program to add the held button 'Select' to the seed list. (1)", 0 },
        { 'h', "Hold A",
                "Use this flag to tell the program to add the held button 'A' to the seed list. (12)", 0 },
        { 'm', "Method",
                "Use this flag to set the wild method. By default, the program searches using H1. The only other options are 'H2' and 'H4'", 1},
        { 's', "Advance Start",
                "Use this flag to tell the program where to begin searching. By default, the program will begin at 0.", 1},
        { 'i', "Initial Seed",
                "Use this flag to set a single initial seed to search for. By default, the program uses all possible seeds based on your settings file which becomes slower with higher max advances", 1 },
        { 'r', "Seed Range",
                "Use this flag to specify a range of seeds from your initial seed. This flag requires '-i' to be set FIRST. Example: '-i E585 -r 100'. This will create a seed list starting from 100 below E585 + 100 above E585", 1 },
        { 'P', "Settings Path",
                "Use this flag to tell the program where to search for your settings .ini file. By default this is set to 'settings.ini'", 1},
        { 'L', "Seed List",
          "Use this flag to tell the program where to use a custom seed list for. The list must match the same format as the others from your data folder", 0}
};

void searchMissingArgs(const char* subCommand) {
    if (COMATCH(subCommand, SEARCH_SUBCOMMANDS[0])) {
        staticSearchExample();
        return;
    }
    if (COMATCH(subCommand, SEARCH_SUBCOMMANDS[1])) {
        wildSearchExample();
        return;
    }
}

size_t getSubCommandCount(const char** sc) {
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
        for (size_t j = 0; j < getSubCommandCount(commands[i].subcommands); j++) {
            fprintf(stdout, "   - %s\n", commands[i].subcommands[j]);
            for (size_t k = 0; k < commands[i].f_size; k++) {
                if (k == 0) {fprintf(stdout, "\tflags (flag | Requires arg | Description)\n");}
                Flag flags = commands[i].flags[k];
                fprintf(stdout, "\t ; '-%c' (%d) - %s, %s\n", flags.f, flags.args, flags.name, flags.description);
            }
        }
        fprintf(stdout, "\n");
    }
}

void searchHandler(int argc, char** argv) {
    /* bin search static [Advances] [Pokemon] [Nature] [Level] [Ability] [HP] [ATK] [DEF] [SPA] [SPD] [SPE] [Gender] [Shiny] (16) */
    /* bin search wild [Advances] [Encounter Type] [Location] [Pokemon] [Nature] [Level] [Ability] [HP] [ATK] [DEF] [SPA] [SPD] [SPE] [Gender] [Shiny] (18) */
    long l;
    char* lend;
    char* inipath = "settings.ini";
    char* optflags = ":thm:s:i:r:P:L:";
    char* customSeedPath = NULL;

    Player player;
    Settings settings;
    Config cf;

    uint16_t mon, range;
    uint32_t maxAdvances;
    uint32_t initAdvances = 0;
    uint32_t initSeed;

    uint64_t len, s_len;

    EncounterType et = Grass;
    AreaType at = LAND;
    const AreaEntry* map;
    AreaEntry entry;

    /* Uninitialized structs are not guaranteed to have their parameters set to 0. I learned this the hard way */
    StaticFilter sf = {0};
    WildFilter wf = {0};
    IVEstimate est = {0};

    Method wildMethod = H1;

    int wflag = 0, sflag = 0, rflag = 0, iflag = 0, tflag = 0, hflag = 0, lflag = 0;

    if (argc < 18 && argc > 16) {
        searchMissingArgs(argv[2]);
        return;
    }

    if (argc < 17 && argc >= 3) {
        searchMissingArgs(argv[2]);
        return;
    }

    if (COMATCH(argv[2], SEARCH_SUBCOMMANDS[0])) {
        sflag = 1;

        /* Advances */
        l = strtol(argv[3], &lend, 10);
        if (lend == argv[3]) {
            fprintf(stdout, "Advances must be an integer\n");
            return;
        } else
            maxAdvances = (uint32_t)l;

        /* Pokemon */
        int monDex = PokemonSearchIndex(argv[4]);
        if (monDex >= 0) {
            mon = (uint32_t)monDex;
            est.mon = pokemon[mon];
        } else {
            fprintf(stdout, "Unable to find specified Pokemon\n");
            return;
        }

        /* Nature */
        int natIndex = PokemonGetNatureIndex(argv[5]);
        if (natIndex >= 0) {
            Nature nat = natures[(uint32_t)natIndex];
            est.nt = nat;
            FilterApplyNatureToStatic(nat, &sf);
        } else {
            fprintf(stdout, "Unable to find specified Nature\n");
            return;
        }

        /* Level */
        l = strtol(argv[6], &lend, 10);
        if (lend == argv[6]) {
            fprintf(stdout, "Level must be an integer\n");
            return;
        } else {
            sf.level = (uint8_t)l;
            est.level = (uint8_t)l;
        }

        /* Ability */
        l = strtol(argv[7], &lend, 10);
        if (lend == argv[7]) {
            fprintf(stdout, "Ability must be an integer\n");
            return;
        } else if (l == 0) {
            sf.ability[0] = 1;
        } else if (l == 1) {
            sf.ability[1] = 1;
        } else {
            fprintf(stdout, "Ability must be an integer. (0 or 1)\n");
            return;
        }

        /* Stats */
        char* inStats[6] = { argv[8], argv[9], argv[10], argv[11], argv[12], argv[13] };
        for (size_t i = 0; i < 6; i++) {
            l = strtol(inStats[i], &lend, 10);
            if (lend == inStats[i]) {
                fprintf(stdout, "Stat must be an integer\n");
                return;
            } else {
                est.stats[i] = (uint16_t)l;
            }
        }
        FilterApplyIVEstimateToStatic(&est, &sf);

        /*  Gender */
        if (COMATCH(argv[14], GENDER_STRINGS[0])) {
            sf.gender[0] = 1;
        } else if (COMATCH(argv[14], GENDER_STRINGS[1])) {
            sf.gender[1] = 1;
        } else if (COMATCH(argv[14], GENDER_STRINGS[2])) {
            sf.gender[2] = 1;
        } else {
            fprintf(stdout, "Unable to match input gender string\n");
            return;
        }

        /*  Shiny */
        if (COMATCH(argv[15], SHINY_TYPES[0])) {
            sf.shiny[2] = 1;
        } else if (COMATCH(argv[15], SHINY_TYPES[1])) {
            sf.shiny[1] = 1;
        } else if (COMATCH(argv[15], SHINY_TYPES[2])) {
            sf.shiny[0] = 1;
        } else {
            fprintf(stdout, "Unable to match input shiny type string\n");
            return;
        }

    } else if (COMATCH(argv[2], SEARCH_SUBCOMMANDS[1])) {
        wflag = 1;

        /* Advances */
        l = strtol(argv[3], &lend, 10);
        if (lend == argv[3]) {
            fprintf(stdout, "Advances must be an integer\n");
            return;
        } else
            maxAdvances = (uint32_t)l;

        /* Area Entry first as to not check later */
        l = strtol(argv[5], &lend, 10);
        if (lend == argv[5]) {
            fprintf(stdout, "Advances must be an integer\n");
            return;
        }

        /* Encounter Type */
        if (COMATCH(argv[4], "grass")) {
            at = LAND;
            if (l >= 0 && l <= MAPSIZE(LAND_AREA_MAP)) {
                map = LAND_AREA_MAP;
                entry = map[l];
            } else {
                fprintf(stdout, "Area entry for Grass must be a number between 0-89\n");
                return;
            }
        } else if (COMATCH(argv[4], "water")) {
            at = WATER;
            if (l >= 0 && l <= MAPSIZE(WATER_AREA_MAP)) {
                map = WATER_AREA_MAP;
                entry = map[l];
            } else {
                fprintf(stdout, "Area entry for Grass must be a number between 0-49\n");
                return;
            }
        } else if (COMATCH(argv[4], "rock")) {
            at = ROCKSMASH;
            if (l >= 0 && l <= MAPSIZE(ROCK_AREA_MAP)) {
                map = ROCK_AREA_MAP;
                entry = map[l];
            } else {
                fprintf(stdout, "Area entry for Grass must be a number between 0-12\n");
                return;
            }
        } else {
            fprintf(stdout, "Unable to match encounter type to input string.\n");
            return;
        }

        /* Pokemon */
        int monDex = PokemonSearchIndex(argv[6]);
        if (monDex >= 0) {
            mon = (uint32_t)monDex;
            wf.mon = mon;
            est.mon = pokemon[mon];
        } else {
            fprintf(stdout, "Unable to find specified Pokemon\n");
            return;
        }

        /* Nature */
        int natIndex = PokemonGetNatureIndex(argv[7]);
        if (natIndex >= 0) {
            Nature nat = natures[(uint32_t)natIndex];
            est.nt = nat;
            FilterApplyNatureToWild(nat, &wf);
        } else {
            fprintf(stdout, "Unable to find specified Nature\n");
            return;
        }

        /* Level */
        l = strtol(argv[8], &lend, 10);
        if (lend == argv[8]) {
            fprintf(stdout, "Level must be an integer\n");
            return;
        } else {
            wf.level = (uint8_t)l;
            est.level = (uint8_t)l;
        }

        /* Ability */
        l = strtol(argv[9], &lend, 10);
        if (lend == argv[9]) {
            fprintf(stdout, "Ability must be an integer\n");
            return;
        } else if (l == 0) {
            wf.ability[0] = 1;
        } else if (l == 1) {
            wf.ability[1] = 1;
        } else {
            fprintf(stdout, "Ability must be an integer. (0 or 1)\n");
            return;
        }

        /* Stats */
        char* inStats[6] = { argv[10], argv[11], argv[12], argv[13], argv[14], argv[15] };
        for (size_t i = 0; i < 6; i++) {
            l = strtol(inStats[i], &lend, 10);
            if (lend == inStats[i]) {
                fprintf(stdout, "Stat must be an integer\n");
                return;
            } else {
                est.stats[i] = (uint16_t)l;
            }
        }

        FilterApplyIVEstimateToWild(&est, &wf);

        /*  Gender */
        if (COMATCH(argv[16], GENDER_STRINGS[0])) {
            wf.gender[0] = 1;
        } else if (COMATCH(argv[16], GENDER_STRINGS[1])) {
            wf.gender[1] = 1;
        } else if (COMATCH(argv[16], GENDER_STRINGS[2])) {
            wf.gender[2] = 1;
        } else {
            fprintf(stdout, "Unable to match input gender string\n");
            return;
        }

        /*  Shiny */
        if (COMATCH(argv[17], SHINY_TYPES[0])) {
            wf.shiny[2] = 1;
        } else if (COMATCH(argv[17], SHINY_TYPES[1])) {
            wf.shiny[1] = 1;
        } else if (COMATCH(argv[17], SHINY_TYPES[2])) {
            wf.shiny[0] = 1;
        } else {
            fprintf(stdout, "Unable to match input shiny type string\n");
            return;
        }
    } else {
        fprintf(stdout, "Unknown command!\n");
        return;
    }

    int c;
    /* https://stackoverflow.com/questions/18079340/using-getopt-in-c-with-non-option-arguments */
    while (optind < argc) {
        if ((c = getopt(argc, argv, optflags)) != -1) {
            switch (c) {
                case 't':
                    tflag = 1;
                    break;
                case 'h':
                    hflag = 1;
                    break;
                case 'm':
                    if (COMATCH("H2", optarg)) {
                        wildMethod = H2;
                    } else if (COMATCH("H4", optarg)) {
                        wildMethod = H4;
                    } else {
                        fprintf(stdout, "Unable to match wild method string. Use 'H2' or 'H4'. (Default: H1)\n");
                        break;
                    }
                    break;
                case 's':
                    l = strtol(optarg, &lend, 10);
                    if (lend == optarg) {
                        fprintf(stdout, "Advance start point must be an integer. You entered: ('%s')\n", optarg);
                        return;
                    } else {
                        initAdvances = (uint32_t)l;
                    }
                    break;
                case 'i':
                    l = strtol(optarg, &lend, 16);
                    if (lend == optarg) {
                        fprintf(stdout, "Initial seed must be an integer. You entered: ('%s')\n", optarg);
                        return;
                    } else {
                        iflag = 1;
                        initSeed = (uint32_t)l;
                    }
                    break;
                case 'r':
                    if (iflag) {
                        rflag = 1;
                        l = strtol(optarg, &lend, 10);
                        if (lend == optarg) {
                            fprintf(stdout, "Seed range must be an integer. You entered: ('%s')\n", optarg);
                            return;
                        } else {
                            range = (uint16_t)l;
                        }
                    } else {
                        fprintf(stderr, "Seed range '-r' requires initial seed arg! Make sure to include '-i [seed]' before using '-r [range]'\n");
                        return;
                    }
                    break;
                case 'P':
                    inipath = optarg;
                    break;
                case 'L':
                    customSeedPath = optarg;
                    lflag = 1;
                    break;
                default:
                    fprintf(stdout, "Unable to parse flags\n");
                    return;
            }
        } else {
            optind++;
        }
    }

    if (initAdvances > maxAdvances) {
        fprintf(stderr, "Initial advances '%d', is larger than the total advances '%d'. Exiting operation\n",
                initAdvances, maxAdvances);
        return;
    }



    /* Make sure the file actually exists*/
    if (access(inipath, F_OK)) {
        perror("Unable to find ini file!\n");
        return;
    }

    /* Declare config struct and parse the file with the specified handler*/
    if (ini_parse(inipath, handler, &cf) < 0) {
        perror("Unable to load ini file!\n");
        return;
    }

    /* Convert config to player basically */
    player.SID = cf.sid;
    player.TID = cf.tid;

    /* Make sure the loaded values are correct*/
    loadSettings(&cf, &settings);

    const char* seedPath = NULL;
    if (lflag) {
        seedPath = customSeedPath;
    } else {
        seedPath = SeedGetFilePath(settings);
    }

    if (access(seedPath, F_OK)) {
        perror("Data files missing or not loaded properly!\n");
        perror("Ensure that the 'data' folder is in the same directory as your executable!\n");
        return;
    }

    void* seeds;
    SeedOffset ofs = None;

    if (hflag) {
        ofs = HELD_A;
    }

    if (tflag) {
        ofs = HELD_SELECT;
    }

    seeds = (InitialSeed* ) SeedLoadInitial(seedPath, &len, ofs);

    if (rflag) {
        int index;
        if (range > (maxAdvances - initAdvances)) {
            fprintf(stderr, "Seed range is greater than total advances!\n  Advances: %d\n  Range: %d\n", maxAdvances, range);
            return;
        }
        if ((index = SeedFindIndex(seeds, initSeed, len) >= 0)) {
            seeds = (InitialSeed* ) SeedGetSeedRange(seeds, len, index, range, &s_len);
            len = s_len;
        } else {
            fprintf(stderr, "Unable to find initial seed in seed list.\n");
            return;
        }
    }

    if(seeds == NULL) {
        perror("Failed to load initial seed list");
        free(seeds);
        return;
    }

    if (wflag) {
        wenc_node *HEAD = NULL;

        /* Determine the encounter slot data path from game version and area*/
        const char *encounter_data_path = LocationGetEncounterFilePath(settings.gv, at);

        /* Load slot data in Slot struct array based on input path determined earlier*/
        Slot *slots = LocationLoadEncounterSlots(entry, encounter_data_path);

        if (slots == NULL) {
            perror("Failed to load encounter slots");
            free(slots);
            return;
        }

        if (iflag) {
            FilterGenerateWildEncounter(&HEAD, player, wildMethod, slots, et, wf, initSeed, initAdvances, maxAdvances);
        } else {
            FilterGenerateWildEncountersFromSeedList(&HEAD, player, wildMethod, slots, et, wf, seeds, len, initAdvances, maxAdvances);
        }

        FilterPrintWEncounterList(HEAD);
        FilterFreeWEncList(HEAD);
        free(slots);
        free(seeds);

        return;

    } else if (sflag) {
        senc_node *HEAD = NULL;

        if (iflag) {
            FilterGenerateStaticEncounter(&HEAD, player, M1, sf, mon, initSeed, initAdvances, maxAdvances);
        } else {
            FilterGenerateStaticEncounterFromSeedList(&HEAD, player, M1, sf, seeds, len, mon, initAdvances, maxAdvances);
        }

        FilterPrintSEncounterList(HEAD);
        FilterFreeSEncList(HEAD);
        free(seeds);
        return;

    } else {
        fprintf(stderr, "Unknown error has occurred.");
        free(seeds);
        return;
    }
}

void listHandler(int argc, char** argv) {
    long l;
    char* lend;

    if (argc < 3) {
        fprintf(stdout, "Error: 'list requires additional arguments.\n");
        fprintf(stdout, "   'list natures'\n");
        fprintf(stdout, "   'list encounters grass'\n");
        return;
    }
    const char* subcommand = argv[2];

    if (COMATCH(subcommand, LIST_SUB_COMMANDS[0])) {
        PokemonListNatures();
    } else if (COMATCH(subcommand, LIST_SUB_COMMANDS[1])) {
        PokemonListGenderStrings();
    } else if (COMATCH(subcommand, LIST_SUB_COMMANDS[2])) {
        PokemonListShinyTypes();
    } else if (COMATCH(subcommand, LIST_SUB_COMMANDS[3])) {
        PokemonListHiddenPowerTypes();
    } else if (COMATCH(subcommand, LIST_SUB_COMMANDS[4])) {
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
    } else if (COMATCH(subcommand, LIST_SUB_COMMANDS[5])) {
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
        } else if (COMATCH(location, "grass") && l < MAPSIZE(LAND_AREA_MAP)) {
            LocationListMonsInLocation(gv, LAND_AREA_MAP[l]);
        } else if (COMATCH(location, "water") && l < MAPSIZE(WATER_AREA_MAP)) {
            LocationListMonsInLocation(gv, WATER_AREA_MAP[l]);
        } else if (COMATCH(location, "rock") && l < MAPSIZE(ROCK_AREA_MAP)) {
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