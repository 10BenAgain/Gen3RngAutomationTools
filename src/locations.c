#include <stdio.h>
#include "../include/locations.h"

const char* EncounterTypeStrings[3] = {
    "Grass",
    "Water",
    "Rock Smash"
};

const char* UnownChambers[7] = {
    "Monean",
    "Liptoo",
    "Weepeth",
    "Dilford",
    "Scufib",
    "Rixy",
    "Viapois"
};

Chamber
LocationsIndex2Chamber(uint8_t index) {
    switch (index) {
        case 89:
            return MONEAN;
        case 90:
            return LIPTOO;
        case 91:
            return WEEPETH;
        case 92:
            return DILFORD;
        case 93:
            return SCUFIB;
        case 94:
            return RIXY;
        case 95:
            return VIAPOIS;
        default:
            return MONEAN;
    }
}

uint8_t
LocationsCheckChamberString(const char* chamber) {
    for (size_t i = 0; i < sizeof(UnownChambers)/sizeof(UnownChambers[0]); i++) {
        if (!strcmp(chamber, UnownChambers[i])) {
            return 0;
        }
    }
    return 1;
}

const char
*get_enc_path(const char *folder, const char* file) {
    char *result = NULL;
    const size_t lfo = strlen(folder);
    const size_t lfd = strlen(file);

    result = malloc(lfo + lfd + 1); // +1 for terminator char

    if (result == NULL) {
        perror("Memory allocation of file path string failed");
        return NULL;
    }

    // Copy folder memory into result with a size of folder string size
    memcpy(result, folder, lfo);

    // Copy file string after into result after the size of folder block
    memcpy(result + lfo, file, lfd + 1);

    return result;
}

const char *LocationGetEncounterFilePath(GameVersion gv, AreaType at) {
#ifdef BUILD_PATH
    char *LGpath = "../data/LGENCSLOTS/";
    char *FRpath = "../data/FRENCSLOTS/";
#else
    char *LGpath = "data/LGENCSLOTS/";
    char *FRpath = "data/FRENCSLOTS/";
#endif

    const char *path;
    const char *file;

    switch (gv) {
        case FR:
            path = FRpath;
            break;
        case LG:
            path = LGpath;
            break;
        default:
            return NULL;
    }
    for (size_t i = 0; i < sizeof(ENCOUNTER_MAPPING) / sizeof(EncounterFileMap); i++) {
        if (ENCOUNTER_MAPPING[i].at == at) {
            file = ENCOUNTER_MAPPING[i].fn;
            break;
        }
    }
    return get_enc_path(path, file);
}

Slot *LocationLoadEncounterSlots(AreaEntry area, const char *fn) {
    FILE *fp = NULL;
    fp = fopen(fn, "r");
    if (fp == NULL) {
        perror("Unable to open encounter slot file!");
        return NULL;
    }

    size_t max_line_size = MAX_LEVEL_LENGTH * SLOTS_COUNT + MAX_MON_LENGTH * SLOTS_COUNT + SLOTS_COUNT + 10;
    char line[max_line_size];
    int c, i, s;

    c = 0;
    while(fgets(line, sizeof(line), fp)) {
        if (c == area.index) {
            break;
        }
        c++;
    }

    if (c != area.index) {
        fclose(fp);
        return NULL;
    }

    Slot *slots = malloc(SLOTS_COUNT * sizeof(Slot));
    if (slots == NULL) {
        perror("Memory allocation of encounter slots failed!");
        return NULL;
    }
    char *token = strtok(line, ",");

    switch(area.at) {
        case LAND:
            s = LAND_SLOTS;
            break;
        case WATER:
        case ROCKSMASH:
            s = ROCK_SLOTS;
            break;
        default:
            return NULL;
    }

    i = 0;
    while(token != NULL && i < s) {
        slots[i].index = (uint8_t)atoi(token);
        token = strtok(NULL, ",");
        if (token != NULL) {
            slots[i].mon = (uint8_t)atoi(token);
        }
        token = strtok(NULL, ",");
        if (token != NULL) {
            slots[i].minL = (uint8_t)atoi(token);
        }
        if (s == LAND_SLOTS) {
            slots[i].maxL = (uint8_t)atoi(token);
        }
        else {
            token = strtok(NULL, ",");
            if (token != NULL) {
                slots[i].maxL = (uint8_t)atoi(token);
            }
        }
        i++;
        token = strtok(NULL, ",");
    }
    return slots;
}

void LocationListMonsInLocation(GameVersion gv, AreaEntry entry) {
    AreaType at = entry.at;
    const char* enc_path = LocationGetEncounterFilePath(gv, at);
    Slot* slots = LocationLoadEncounterSlots(entry, enc_path);
    size_t slot_count;
    switch (at) {
        case LAND:
            slot_count = LAND_SLOTS;
            break;
        case WATER:
            slot_count = WATER_SLOTS;
            break;
        case ROCKSMASH:
            slot_count = ROCK_SLOTS;
            break;
    }

    fprintf(stdout, "\n-----%s----\n", entry.name);
    for (size_t i = 0; i < slot_count; i++) {
        fprintf(stdout, "Slot: %d | %s | Level: %d-%d\n",
               slots[i].index, pokemon[slots[i].mon].name, slots[i].minL, slots[i].maxL);
    }
    fprintf(stdout, "\n");

    free(slots);
}

void LocationListFromEncType(EncounterType et) {
    size_t locations;
    const AreaEntry* map;
    switch (et) {
        case Grass:
            locations = MAPSIZE(LAND_AREA_MAP);
            map = LAND_AREA_MAP;
            break;
        case Water:
            locations = MAPSIZE(WATER_AREA_MAP);
            map = WATER_AREA_MAP;
            break;
        case RockSmash:
            locations = MAPSIZE(ROCK_AREA_MAP);
            map = ROCK_AREA_MAP;
            break;
        default:
            return;
    }

    for (size_t i = 0; i < locations; i++) {
        fprintf(stdout, "%d | %s\n", map[i].index, map[i].name);
    }
}

void LocationsListTanobyChamberStrings() {
    for (size_t i = 0; i < sizeof(UnownChambers)/sizeof(UnownChambers[0]); i++) {
        fprintf(stdout, "%s\n", UnownChambers[i]);
    }
}