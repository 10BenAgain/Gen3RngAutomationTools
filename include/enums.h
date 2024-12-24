
#ifndef GENERATION3LCRNG_ENUMS_H
#define GENERATION3LCRNG_ENUMS_H

typedef enum {
    STEREO,
    MONO
} AudioSetting;

typedef enum {
    LA,
    HELP,
    LR
} ButtonSetting;

typedef enum {
    A,
    START,
    L
} ButtonSeed;

typedef enum {
    FR,
    LG
} GameVersion;

typedef enum {
    ENGLISH,
    EU,
    JPN
} Language;

typedef enum {
    LEAF_GREEN,
    J10,
    J11
} JPNVersion;

typedef enum {
    M1,
    M4,
    H1,
    H2,
    H4
} Method;

typedef enum {
    None,
    HELD_SELECT = 1,
    HELD_A = 12,
} SeedOffset;

typedef enum {
    LAND,
    WATER,
    ROCKSMASH
} AreaType;

typedef enum {
    Grass,
    Water,
    RockSmash,
    OldRod,
    GoodRod,
    SuperRod
} EncounterType;

static EncounterType
area2enc(AreaType at) {
    switch (at) {
        case LAND:
            return Grass;
        case WATER:
            return Water;
        case ROCKSMASH:
            return RockSmash;
        default:
            return Grass;
    }
}
#endif
