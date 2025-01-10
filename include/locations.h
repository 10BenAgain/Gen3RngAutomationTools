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
#define OLD_ROD_SLOTS       2
#define GOOD_ROD_SLOTS      3
#define SUPER_ROD_SLOTS     5

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

static const AreaEntry OLD_ROD_AREA_MAP[49] = {
        { OLD, "Berry Forest", 0 },
        { OLD, "Bond Bridge", 1 },
        { OLD, "Cape Brink", 2 },
        { OLD, "Celadon City", 3 },
        { OLD, "Cerulean Cave 1F", 4 },
        { OLD, "Cerulean Cave B1F", 5 },
        { OLD, "Cerulean City", 6 },
        { OLD, "Cinnabar Island", 7 },
        { OLD, "Five Island", 8 },
        { OLD, "Five Isle Meadow", 9 },
        { OLD, "Four Island", 10 },
        { OLD, "Fuchsia City", 11 },
        { OLD, "Green Path", 12 },
        { OLD, "Icefall Cave Entrance", 13 },
        { OLD, "Icefall Cave Back Cavern", 14 },
        { OLD, "Kindle Road", 15 },
        { OLD, "Memorial Pillar", 16 },
        { OLD, "One Island", 17 },
        { OLD, "Outcast Island", 18 },
        { OLD, "Pallet Town", 19 },
        { OLD, "Resort Gorgeous", 20 },
        { OLD, "Route 4", 21 },
        { OLD, "Route 6", 22 },
        { OLD, "Route 10", 23 },
        { OLD, "Route 11", 24 },
        { OLD, "Route 12", 25 },
        { OLD, "Route 13", 26 },
        { OLD, "Route 19", 27 },
        { OLD, "Route 20", 28 },
        { OLD, "Route 21", 29 },
        { OLD, "Route 22", 30 },
        { OLD, "Route 23", 31 },
        { OLD, "Route 24", 32 },
        { OLD, "Route 25", 33 },
        { OLD, "Ruin Valley", 34 },
        { OLD, "S.S. Anne", 35 },
        { OLD, "Safari Zone Entrance", 36 },
        { OLD, "Safari Zone Area 1 - East", 37 },
        { OLD, "Safari Zone Area 2 - North", 38 },
        { OLD, "Safari Zone Area 3 - West", 39 },
        { OLD, "Seafoam Islands B3F", 40 },
        { OLD, "Seafoam Islands B4F", 41 },
        { OLD, "Tanoby Ruins", 42 },
        { OLD, "Trainer Tower", 43 },
        { OLD, "Treasure Beach", 44 },
        { OLD, "Vermilion City", 45 },
        { OLD, "Viridian City", 46 },
        { OLD, "Water Labyrinth", 47 },
        { OLD, "Water Path", 48 }
};

static const AreaEntry GOOD_ROD_AREA_MAP[49] = {
        { GOOD, "Berry Forest", 0 },
        { GOOD, "Bond Bridge", 1 },
        { GOOD, "Cape Brink", 2 },
        { GOOD, "Celadon City", 3 },
        { GOOD, "Cerulean Cave 1F", 4 },
        { GOOD, "Cerulean Cave B1F", 5 },
        { GOOD, "Cerulean City", 6 },
        { GOOD, "Cinnabar Island", 7 },
        { GOOD, "Five Island", 8 },
        { GOOD, "Five Isle Meadow", 9 },
        { GOOD, "Four Island", 10 },
        { GOOD, "Fuchsia City", 11 },
        { GOOD, "Green Path", 12 },
        { GOOD, "Icefall Cave Entrance", 13 },
        { GOOD, "Icefall Cave Back Cavern", 14 },
        { GOOD, "Kindle Road", 15 },
        { GOOD, "Memorial Pillar", 16 },
        { GOOD, "One Island", 17 },
        { GOOD, "Outcast Island", 18 },
        { GOOD, "Pallet Town", 19 },
        { GOOD, "Resort Gorgeous", 20 },
        { GOOD, "Route 4", 21 },
        { GOOD, "Route 6", 22 },
        { GOOD, "Route 10", 23 },
        { GOOD, "Route 11", 24 },
        { GOOD, "Route 12", 25 },
        { GOOD, "Route 13", 26 },
        { GOOD, "Route 19", 27 },
        { GOOD, "Route 20", 28 },
        { GOOD, "Route 21", 29 },
        { GOOD, "Route 22", 30 },
        { GOOD, "Route 23", 31 },
        { GOOD, "Route 24", 32 },
        { GOOD, "Route 25", 33 },
        { GOOD, "Ruin Valley", 34 },
        { GOOD, "S.S. Anne", 35 },
        { GOOD, "Safari Zone Entrance", 36 },
        { GOOD, "Safari Zone Area 1 - East", 37 },
        { GOOD, "Safari Zone Area 2 - North", 38 },
        { GOOD, "Safari Zone Area 3 - West", 39 },
        { GOOD, "Seafoam Islands B3F", 40 },
        { GOOD, "Seafoam Islands B4F", 41 },
        { GOOD, "Tanoby Ruins", 42 },
        { GOOD, "Trainer Tower", 43 },
        { GOOD, "Treasure Beach", 44 },
        { GOOD, "Vermilion City", 45 },
        { GOOD, "Viridian City", 46 },
        { GOOD, "Water Labyrinth", 47 },
        { GOOD, "Water Path", 48 }
};

static const AreaEntry SUPER_ROD_AREA_MAP[49] = {
        { SUPER, "Berry Forest", 0 },
        { SUPER, "Bond Bridge", 1 },
        { SUPER, "Cape Brink", 2 },
        { SUPER, "Celadon City", 3 },
        { SUPER, "Cerulean Cave 1F", 4 },
        { SUPER, "Cerulean Cave B1F", 5 },
        { SUPER, "Cerulean City", 6 },
        { SUPER, "Cinnabar Island", 7 },
        { SUPER, "Five Island", 8 },
        { SUPER, "Five Isle Meadow", 9 },
        { SUPER, "Four Island", 10 },
        { SUPER, "Fuchsia City", 11 },
        { SUPER, "Green Path", 12 },
        { SUPER, "Icefall Cave Entrance", 13 },
        { SUPER, "Icefall Cave Back Cavern", 14 },
        { SUPER, "Kindle Road", 15 },
        { SUPER, "Memorial Pillar", 16 },
        { SUPER, "One Island", 17 },
        { SUPER, "Outcast Island", 18 },
        { SUPER, "Pallet Town", 19 },
        { SUPER, "Resort Gorgeous", 20 },
        { SUPER, "Route 4", 21 },
        { SUPER, "Route 6", 22 },
        { SUPER, "Route 10", 23 },
        { SUPER, "Route 11", 24 },
        { SUPER, "Route 12", 25 },
        { SUPER, "Route 13", 26 },
        { SUPER, "Route 19", 27 },
        { SUPER, "Route 20", 28 },
        { SUPER, "Route 21", 29 },
        { SUPER, "Route 22", 30 },
        { SUPER, "Route 23", 31 },
        { SUPER, "Route 24", 32 },
        { SUPER, "Route 25", 33 },
        { SUPER, "Ruin Valley", 34 },
        { SUPER, "S.S. Anne", 35 },
        { SUPER, "Safari Zone Entrance", 36 },
        { SUPER, "Safari Zone Area 1 - East", 37 },
        { SUPER, "Safari Zone Area 2 - North", 38 },
        { SUPER, "Safari Zone Area 3 - West", 39 },
        { SUPER, "Seafoam Islands B3F", 40 },
        { SUPER, "Seafoam Islands B4F", 41 },
        { SUPER, "Tanoby Ruins", 42 },
        { SUPER, "Trainer Tower", 43 },
        { SUPER, "Treasure Beach", 44 },
        { SUPER, "Vermilion City", 45 },
        { SUPER, "Viridian City", 46 },
        { SUPER, "Water Labyrinth", 47 },
        { SUPER, "Water Path", 48 },
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
        { FR, OLD,          "old"   },
        { FR, GOOD,         "good"  },
        { FR, SUPER,        "super" },
        { LG, LAND,         "land"  },
        { LG, ROCKSMASH,    "rock"  },
        { LG, WATER,        "water" },
        { LG, OLD,          "old"   },
        { LG, GOOD,         "good"  },
        { LG, SUPER,        "super" },
};

extern const char* EncounterTypeStrings[6];
extern const char* UnownChambers[7];

void LocationsListTanobyChamberStrings();
void LocationListFromEncType(EncounterType et);
void LocationListMonsInLocation(GameVersion gv, AreaEntry entry);

const char *LocationGetEncounterFilePath(GameVersion gv, AreaType at);

uint8_t LocationsCheckChamberString(const char* chamber);

Slot *LocationLoadEncounterSlots(AreaEntry area, const char *fn);

Chamber LocationsIndex2Chamber(uint8_t index);

#endif
