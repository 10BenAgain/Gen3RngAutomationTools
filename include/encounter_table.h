#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include <stdint.h>
#include "enums.h"

static const uint8_t
GRASS_ENCOUNTER_SLOT_LOOKUP_TABLE[100] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6,
        7, 7, 7, 7, 7,
        8, 8, 8, 8,
        9, 9, 9, 9,
        10,
        11
};

static const uint8_t
WATER_ENCOUNTER_SLOT_LOOKUP_TABLE[100] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2,
        3, 3, 3, 3,
        4
};

static const uint8_t
ROCK_SMASH_ENCOUNTER_SLOT_LOOKUP_TABLE[100] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2,
        3, 3, 3, 3,
        4
};

static const uint8_t
OLD_ROD_ENCOUNTER_SLOT_LOOKUP_TABLE[100] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

static const uint8_t
GOOD_ROD_ENCOUNTER_SLOT_LOOKUP_TABLE[100] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

static const uint8_t
SUPER_ROD_ENCOUNTER_SLOT_LOOKUP_TABLE[100] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        3, 3, 3, 3,
        4
};


/* This structure is taken from the decomp, but I changed the values to match the characters ASCII
 * Values to make it easier to compare the Unown symbol
 * Original structure: https://github.com/pret/pokefirered/blob/2a3e92e10f8353e167874d1d2f6b311560a2a80d/src/wild_encounter.c#L49
*/
static const int
CHAMBER_SLOT_LOOKUP_TABLE[7][12] = {
        //  A   A   A   A   A   A   A   A   A   A   A   ?
        { 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 63}, // MONEAN
        //  C   C   C   D   D   D   H   H   H   U   U   O
        { 67, 67, 67, 68, 68, 68, 72, 72,  72, 85, 85, 9}, // LIPTOO
        //  N   N   N   N   S   S   S   S   I   I   E   E
        { 78, 78, 78, 78, 83, 83, 83, 83, 73, 73, 69, 69}, // WEEPETH
        //  P   P   L   L   J   J   R   R   R   Q   Q   Q
        { 80, 80, 76, 76, 74, 74, 82, 82, 82, 81, 81, 81}, // DILFORD
        //  Y   Y   T   T   G   G   G   F   F   F   K   K
        { 89, 89, 84, 84, 71, 71, 71, 70, 70, 70, 75, 75 }, // SCUFIB
        //  V   V   V   W   W   W   X   X   M   M   B   B
        { 86, 86, 86, 87, 87, 87, 88, 88, 78, 78, 66, 66 }, // RIXY
        //  Z   Z   Z   Z   Z   Z   Z   Z   Z   Z   Z   !
        { 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 33 }, // VIAPOIS
};

static const uint8_t
*get_enc_table(EncounterType enc) {
    switch (enc) {
        case Grass:
            return GRASS_ENCOUNTER_SLOT_LOOKUP_TABLE;
        case Water:
            return WATER_ENCOUNTER_SLOT_LOOKUP_TABLE;
        case RockSmash:
            return ROCK_SMASH_ENCOUNTER_SLOT_LOOKUP_TABLE;
        case OldRod:
            return OLD_ROD_ENCOUNTER_SLOT_LOOKUP_TABLE;
        case GoodRod:
            return GOOD_ROD_ENCOUNTER_SLOT_LOOKUP_TABLE;
        case SuperRod:
            return SUPER_ROD_ENCOUNTER_SLOT_LOOKUP_TABLE;
        default:
            return GRASS_ENCOUNTER_SLOT_LOOKUP_TABLE;
    }
}

#endif
