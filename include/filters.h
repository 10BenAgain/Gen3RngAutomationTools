#ifndef FILTERS_H
#define FILTERS_H

#include <stdio.h>
#include <stdint.h>
#include "rng.h"
#include "pokemon.h"
#include "encounter_table.h"
#include "seeds.h"
#include "enums.h"
#include "ivs.h"

typedef struct {
    uint32_t TID;
    uint32_t SID;
} Player;

typedef struct {
    uint16_t mon;
    uint32_t PID;
    uint8_t nature;
    uint8_t ability;
    uint8_t IVs[6];
    const char* gender;
    const char* hp;
    uint8_t hp_pow;
    uint8_t shiny;
    uint32_t seed;
    uint32_t advances;
} StaticEncounter;

typedef struct {
    uint32_t PID;
    uint16_t mon;
    uint8_t nature;
    uint8_t ability;
    uint8_t IVs[6];
    uint8_t slot;
    uint8_t level;
    const char* hp;
    uint8_t hp_pow;
    uint8_t shiny;
    uint32_t seed;
    uint32_t advances;
    Chamber chamber;
    char symbol;
} WildEncounter;

typedef struct SNode {
    StaticEncounter se;
    struct SNode* next;
} senc_node;

typedef struct WNode {
    WildEncounter we;
    struct WNode* next;
} wenc_node;

typedef struct {
    uint8_t level;
    uint8_t ability[2]; // 0 = 0, 1 = 1
    uint8_t hp_iv_bounds[2];
    uint8_t atk_iv_bounds[2];
    uint8_t def_iv_bounds[2];
    uint8_t spa_iv_bounds[2];
    uint8_t spd_iv_bounds[2];
    uint8_t spe_iv_bounds[2];
    uint8_t gender[3]; // 0 = M , 1 = F, 2 = U
    uint8_t shiny[3]; // 0 = Square, 1 = Star, 2 = None
    uint8_t natures[25];
} StaticFilter;

typedef struct {
    uint16_t mon;
    uint8_t level;
    uint8_t ability[2]; // 0 = 0, 1 = 1
    uint8_t hp_iv_bounds[2];
    uint8_t atk_iv_bounds[2];
    uint8_t def_iv_bounds[2];
    uint8_t spa_iv_bounds[2];
    uint8_t spd_iv_bounds[2];
    uint8_t spe_iv_bounds[2];
    uint8_t gender[3]; // 0 = M , 1 = F, 2 = U
    uint8_t shiny[3]; // 0 = Square, 1 = Star, 2 = None
    uint8_t natures[25];
    Chamber chamber;
    char symbol;
} WildFilter;

inline void FilterApplyNatureToStatic(Nature nt, StaticFilter* filter) { filter->natures[nt.key] = 1; }
inline void FilterApplyNatureToWild(Nature nt, WildFilter* filter) { filter->natures[nt.key] = 1; }

void FilterApplyIVEstimateToWild(IVEstimate* target, WildFilter* filter);
void FilterApplyIVEstimateToStatic(IVEstimate* target, StaticFilter* filter);

void FilterPrintSEncounterList(senc_node* enc);
void FilterPrintWEncounterList(wenc_node* enc);

void FilterFreeSEncList(senc_node* head);
void FilterFreeWEncList(wenc_node* head);

void FilterGenerateAllStaticEncounters(senc_node** list, Player pl, Method met, StaticFilter filter, uint16_t mon, uint32_t init, uint32_t max);
void FilterGenerateStaticEncounter(senc_node** list, Player pl, Method met, StaticFilter filter, uint16_t mon, uint32_t seed, uint32_t init, uint32_t max);
void FilterGenerateStaticEncounterFromSeedList(senc_node** list, Player pl, Method met, StaticFilter filter, InitialSeed *seeds, uint32_t size, uint16_t mon, uint32_t init, uint32_t max);

void FilterGenerateAllWildEncounters(wenc_node** list, Player pl, Method met, Slot *slots, EncounterType et, WildFilter filter, uint32_t init, uint32_t max);
void FilterGenerateWildEncounter(wenc_node** list, Player pl, Method met, Slot *slots, EncounterType et, WildFilter filter, uint32_t seed, uint32_t init, uint32_t max);
void FilterGenerateWildEncountersFromSeedList(wenc_node** list, Player pl, Method met, Slot *slots, EncounterType et, WildFilter filter, InitialSeed *seeds, uint32_t size, uint32_t init, uint32_t max);

#endif
