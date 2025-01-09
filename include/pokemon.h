#ifndef POKEMON_H
#define POKEMON_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "enums.h"

#define MAX_DEX 386

typedef struct {
    int key;
    const char *name;
} Nature;

typedef struct {
    int key;
    const char *type;
} HiddenPower;

typedef struct {
    uint32_t dex;
    const char* name;
    uint8_t base_stats[6];
    GenderRatio gr;
    const char* ab0;
    const char* ab1;
} Pokemon;

typedef struct {
    const char symbol;
    Chamber chamber;
} Unown;

typedef struct {
    Category cat;
    const char* mon;
    int level;
} Encounter;

extern const Nature natures[25];
extern const Pokemon pokemon[MAX_DEX];
extern const Unown unown[28];
extern const Encounter StaticEncounters[];
extern const HiddenPower HP[16];
extern const double nature_multiplier_table[25][5];

extern const char* GENDER_STRINGS[3];
extern const char* SHINY_TYPES[3];
extern const char* ENCOUNTER_CATEGORY[8];

const char* PokemonGetNatureString(uint8_t key);
const char* PokemonGetGenderString(uint8_t key);

char PokemonGetUnownSymbolChar(int val);

void PokemonListNatures();
void PokemonListShinyTypes();
void PokemonListHiddenPowerTypes();
void PokemonListGenderStrings();

int PokemonSearchIndex(const char* name);
int PokemonGetNatureIndex(const char* nat);

uint8_t PokemonIsShiny(uint32_t PID, uint32_t TID, uint32_t SID);
uint8_t PokemonGetHPValue(const uint8_t *IVs);
uint8_t PokemonGetHP(const uint8_t *IVs);
uint8_t PokemonGetUnownLetter(uint32_t PID);
uint8_t PokemonFindAbilityIndex(uint16_t dex, const char* name);
uint8_t PokemonGetGender(uint32_t PID, GenderRatio gr);

#endif
