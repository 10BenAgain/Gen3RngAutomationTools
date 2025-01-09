#ifndef ENCOUNTERS_H
#define ENCOUNTERS_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "enums.h"
#include "pokemon.h"

#define MAX_LEVEL_LENGTH    4
#define MAX_MON_LENGTH      4
#define SLOTS_COUNT         12

#define LAND_SLOTS          12
#define ROCK_SLOTS          5
#define WATER_SLOTS         5

#define MAPSIZE(map) (sizeof(map)/sizeof(AreaEntry))

typedef struct {
    AreaType at;
    const char *name;
    uint8_t index;
} AreaEntry;

typedef struct {
    uint8_t index;
    uint8_t mon;
    uint8_t minL;
    uint8_t maxL;
} Slot;

typedef struct {
    GameVersion gv;
    AreaType at;
    const char *fn;
} EncounterFileMap;

static const AreaEntry LAND_AREA_MAP[96] = {
    { LAND, "Altering Cave (Default)", 0 },
    { LAND, "Altering Cave (Mystery Gift)", 1 },
    { LAND, "Altering Cave (Mystery Gift)", 2 },
    { LAND, "Altering Cave (Mystery Gift)", 3 },
    { LAND, "Altering Cave (Mystery Gift)", 4 },
    { LAND, "Altering Cave (Mystery Gift)", 5 },
    { LAND, "Altering Cave (Mystery Gift)", 6 },
    { LAND, "Altering Cave (Mystery Gift)", 7 },
    { LAND, "Altering Cave (Mystery Gift)", 8 },
    { LAND, "Berry Forest ", 9 },
    { LAND, "Bond Bridge", 10 },
    { LAND, "Cape Brink ", 11 },
    { LAND, "Cerulean Cave 1F ", 12 },
    { LAND, "Cerulean Cave 2F ", 13 },
    { LAND, "Cerulean Cave B1F ", 14 },
    { LAND, "Diglett's Cave", 15 },
    { LAND, "Five Isle Meadow", 16 },
    { LAND, "Icefall Cave Entrance", 17 },
    { LAND, "Icefall Cave 1F", 18 },
    { LAND, "Icefall Cave BF", 19 },
    { LAND, "Icefall Cave Back Cavern", 20 },
    { LAND, "Kindle Road", 21 },
    { LAND, "Lost Cave (All Rooms)", 22 },
    { LAND, "Memorial Pillar ", 23 },
    { LAND, "Mt. Ember Exterior ", 24 },
    { LAND, "Mt. Ember Summit Path 1F ", 25 },
    { LAND, "Mt. Ember Summit Path 2F ", 26 },
    { LAND, "Mt. Ember Summit Path 3F ", 27 },
    { LAND, "Mt. Ember Ruby Path 1F ", 28 },
    { LAND, "Mt. Ember Ruby Path B1F", 29 },
    { LAND, "Mt. Ember Ruby Path B2F ", 30 },
    { LAND, "Mt. Ember Ruby Path B3F", 31 },
    { LAND, "Mt. Moon 1F", 32 },
    { LAND, "Mt. Moon B1F", 33 },
    { LAND, "Mt. Moon B2F", 34 },
    { LAND, "Pattern Bush", 35 },
    { LAND, "Pokemon Mansion Upper Floors", 36 },
    { LAND, "Pokemon Mansion Basement", 37 },
    { LAND, "Pokemon Tower 3F", 38 },
    { LAND, "Pokemon Tower 4F", 39 },
    { LAND, "Pokemon Tower 5F", 40 },
    { LAND, "Pokemon Tower 6F", 41 },
    { LAND, "Pokemon Tower 7F", 42 },
    { LAND, "Power Plant", 43 },
    { LAND, "Rock Tunnel 1F", 44 },
    { LAND, "Rock Tunnel B1F", 45 },
    { LAND, "Route 1", 46 },
    { LAND, "Route 2", 47 },
    { LAND, "Route 3", 48 },
    { LAND, "Route 4", 49 },
    { LAND, "Route 5", 50 },
    { LAND, "Route 6", 51 },
    { LAND, "Route 7", 52 },
    { LAND, "Route 8", 53 },
    { LAND, "Route 9", 54 },
    { LAND, "Route 10", 55 },
    { LAND, "Route 11", 56 },
    { LAND, "Route 12", 57 },
    { LAND, "Route 13", 58 },
    { LAND, "Route 14", 59 },
    { LAND, "Route 15", 60 },
    { LAND, "Route 16", 61 },
    { LAND, "Route 17", 62 },
    { LAND, "Route 18", 63 },
    { LAND, "Route 21", 64 },
    { LAND, "Route 22", 65 },
    { LAND, "Route 23", 66 },
    { LAND, "Route 24", 67 },
    { LAND, "Route 25", 68 },
    { LAND, "Ruin Valley", 69 },
    { LAND, "Safari Zone Entrance", 70 },
    { LAND, "Safari Zone Area 1 - East", 71 },
    { LAND, "Safari Zone Area 2 - North", 72 },
    { LAND, "Safari Zone Area 3 - West", 73 },
    { LAND, "Seafoam Islands 1F", 74 },
    { LAND, "Seafoam Islands B1F", 75 },
    { LAND, "Seafoam Islands B2F", 76 },
    { LAND, "Seafoam Islands B3F", 77 },
    { LAND, "Seafoam Islands B4F", 78 },
    { LAND, "Sevault Canyon Entrance", 79 },
    { LAND, "Sevault Canyon", 80 },
    { LAND, "Tanoby Ruins Chambers", 81 },
    { LAND, "Three Isle Port", 82 },
    { LAND, "Treasure Beach", 83 },
    { LAND, "Victory Road 1F", 84 },
    { LAND, "Victory Road 2F", 85 },
    { LAND, "Victory Road 3F", 86 },
    { LAND, "Viridian Forest", 87 },
    { LAND, "Water Path", 88 },
    { LAND, "Tanoby Ruins Chamber - Monean", 89 },
    { LAND, "Tanoby Ruins Chamber - Liptoo", 90 },
    { LAND, "Tanoby Ruins Chamber - Weepeth", 91 },
    { LAND, "Tanoby Ruins Chamber - Dilford", 92 },
    { LAND, "Tanoby Ruins Chamber - Scufib", 93 },
    { LAND, "Tanoby Ruins Chamber - Rixy", 94 },
    { LAND, "Tanoby Ruins Chamber - Viapois", 95 },
};

static const AreaEntry WATER_AREA_MAP[49] = {
    { WATER, "Berry Forest", 0 },
    { WATER, "Bond Bridge", 1 },
    { WATER, "Cape Brink", 2 },
    { WATER, "Celadon City", 3 },
    { WATER, "Cerulean Cave 1F", 4 },
    { WATER, "Cerulean Cave B1F", 5 },
    { WATER, "Cerulean City", 6 },
    { WATER, "Cinnabar Island", 7 },
    { WATER, "Five Island", 8 },
    { WATER, "Five Isle Meadow", 9 },
    { WATER, "Four Island", 10 },
    { WATER, "Fuchsia City", 11 },
    { WATER, "Green Path", 12 },
    { WATER, "Icefall Cave Entrance", 13 },
    { WATER, "Icefall Cave Back Cavern", 14 },
    { WATER, "Kindle Road", 15 },
    { WATER, "Memorial Pillar", 16 },
    { WATER, "One Island", 17 },
    { WATER, "Outcast Island", 18 },
    { WATER, "Pallet Town", 19 },
    { WATER, "Resort Gorgeous", 20 },
    { WATER, "Route 4", 21 },
    { WATER, "Route 6", 22 },
    { WATER, "Route 10", 23 },
    { WATER, "Route 11", 24 },
    { WATER, "Route 12", 25 },
    { WATER, "Route 13", 26 },
    { WATER, "Route 19", 27 },
    { WATER, "Route 20", 28 },
    { WATER, "Route 21", 29 },
    { WATER, "Route 22", 30 },
    { WATER, "Route 23", 31 },
    { WATER, "Route 24", 32 },
    { WATER, "Route 25", 33 },
    { WATER, "Ruin Valley", 34 },
    { WATER, "S.S. Anne", 35 },
    { WATER, "Safari Zone Entrance", 36 },
    { WATER, "Safari Zone Area 1 - East", 37 },
    { WATER, "Safari Zone Area 2 - North", 38 },
    { WATER, "Safari Zone Area 3 - West", 39 },
    { WATER, "Seafoam Islands B3F", 40 },
    { WATER, "Seafoam Islands B4F", 41 },
    { WATER, "Tanoby Ruins", 42 },
    { WATER, "Trainer Tower", 43 },
    { WATER, "Treasure Beach", 44 },
    { WATER, "Vermilion City", 45 },
    { WATER, "Viridian City", 46 },
    { WATER, "Water Labyrinth", 47 },
    { WATER, "Water Path", 48 }
};

static const AreaEntry ROCK_AREA_MAP[12] = {
    { ROCKSMASH, "Cerulean Cave 1F", 0 },
    { ROCKSMASH, "Cerulean Cave 2F", 1 },
    { ROCKSMASH, "Cerulean Cave B1F", 2 },
    { ROCKSMASH, "Kindle Road", 3 },
    { ROCKSMASH, "Mt. Ember Exterior", 4 },
    { ROCKSMASH, "Mt. Ember Summit Path 2F", 5 },
    { ROCKSMASH, "Mt. Ember Ruby Path 1F", 6 },
    { ROCKSMASH, "Mt. Ember Ruby Path B1F", 7 },
    { ROCKSMASH, "Mt. Ember Ruby Path B2F", 8 },
    { ROCKSMASH, "Mt. Ember Ruby Path B3F", 9 },
    { ROCKSMASH, "Rock Tunnel B1F", 10 },
    { ROCKSMASH, "Sevault Canyon", 11 }
};

static const EncounterFileMap ENCOUNTER_MAPPING[] = {
        { FR, LAND,         "land"  },
        { FR, ROCKSMASH,    "rock"  },
        { FR, WATER,        "water" },
        { LG, LAND,         "land"  },
        { LG, ROCKSMASH,    "rock"  },
        { LG, WATER,        "water" },
};

extern const char* EncounterTypeStrings[3];
extern const char* UnownChambers[7];

void LocationsListTanobyChamberStrings();
void LocationListFromEncType(EncounterType et);
void LocationListMonsInLocation(GameVersion gv, AreaEntry entry);

const char *LocationGetEncounterFilePath(GameVersion gv, AreaType at);

uint8_t LocationsCheckChamberString(const char* chamber);

Slot *LocationLoadEncounterSlots(AreaEntry area, const char *fn);

Chamber LocationsIndex2Chamber(uint8_t index);

#endif
