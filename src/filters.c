#include "../include/filters.h"
#include <stdio.h>

void pushSEnc(senc_node** h, StaticEncounter enc);
void pushWenc(wenc_node** h, WildEncounter enc);

uint8_t ivFilterCheckWild(WildEncounter* we, WildFilter* filter);
uint8_t abilityFilterCheckWild(WildFilter* filter, uint8_t ability);
uint8_t genderFilterCheckWild(WildFilter* filter, uint8_t gender);
uint8_t natureFilterCheckWild(WildFilter* filter, uint8_t nature);
uint8_t shinyFilterCheckWild(WildFilter* filter, uint8_t shiny);

uint8_t ivFilterCheckStatic(StaticEncounter* we, StaticFilter* filter);
uint8_t abilityFilterCheckStatic(StaticFilter* filter, uint8_t ability);
uint8_t genderFilterCheckStatic(StaticFilter* filter, uint8_t gender);
uint8_t natureFilterCheckStatic(StaticFilter* filter, uint8_t nature);
uint8_t shinyFilterCheckStatic(StaticFilter* filter, uint8_t shiny);

void FilterGenerateStaticEncounterFromSeedList(
        senc_node** list,
        Player pl,
        Method met,
        StaticFilter filter,
        InitialSeed *seeds,
        uint32_t size,
        uint16_t mon,
        uint32_t init,
        uint32_t max
        ) {
    for (size_t i = 0; i <= size; i++) {
        FilterGenerateStaticEncounter(list, pl, met, filter, mon, seeds[i].seed, init, max);
    }
}

void FilterGenerateStaticEncounter(senc_node** list, Player pl, Method met, StaticFilter filter, uint16_t mon, uint32_t seed, uint32_t init, uint32_t max) {
    if (max <= 0 || init > max) {
        return;
    }

    uint32_t advances;
    advances = max - init;

    uint32_t initial_seed = seed;

    seed = RNGJumpAhead(GEN3_JUMP_TABLE, seed, init);

    int i;
    for (i = 0; i <= (int)advances; i++, RNGIncrementSeed(&seed, 1)) {
        uint32_t current_seed = seed;

        StaticEncounter* enc = NULL;
        enc = (StaticEncounter*) malloc(sizeof(StaticEncounter));

        if (enc == NULL) {
            printf("Memory allocation failed");
            return;
        }

        enc->mon = mon;

        RNGIncrementSeed(&current_seed, 1);
        uint32_t second_half = current_seed >> 16;

        RNGIncrementSeed(&current_seed, 1);
        uint32_t first_half = current_seed >> 16;

        enc->PID = (first_half << 16) | second_half;

        RNGIncrementSeed(&current_seed, 1);

        enc->IVs[0] = (current_seed >> 16) & IV_MASK; // HP
        enc->IVs[1] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // Atk
        enc->IVs[2] = ((current_seed >> 16) >> 2 * IV_SHIFT) & IV_MASK; // Def

        if (met == M4) {
            RNGIncrementSeed(&current_seed, 1);
        }

        // Move RNG by one
        RNGIncrementSeed(&current_seed, 1);
        enc->IVs[5] = (current_seed >> 16) & IV_MASK; // SpA
        enc->IVs[3] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // SpD
        enc->IVs[4] = ((current_seed>> 16) >> 2 * IV_SHIFT) & IV_MASK; // Spe

        if (!ivFilterCheckStatic(enc, &filter)) {
            free(enc);
            continue;
        }

        enc->nature = enc->PID % 25;
        if (!natureFilterCheckStatic(&filter, enc->nature)) {
            free(enc);
            continue;
        }

        enc->ability = enc->PID & 1;
        if (!abilityFilterCheckStatic(&filter, enc->ability)) {
            free(enc);
            continue;
        }

        enc->shiny =  PokemonIsShiny(enc->PID, pl.TID, pl.SID);

        if (!shinyFilterCheckStatic(&filter, enc->shiny)) {
            free(enc);
            continue;
        }

        enc->gender = PokemonGetGenderString(PokemonGetGender(enc->PID, pokemon[mon].gr));

        if (!genderFilterCheckStatic(&filter, PokemonGetGender(enc->PID, pokemon[mon].gr))) {
            free(enc);
            continue;
        }

        enc->hp = HP[PokemonGetHPValue(enc->IVs)].type;
        enc->hp_pow = PokemonGetHP(enc->IVs);
        enc->seed = initial_seed;
        enc->advances = i + init;

        pushSEnc(list, *enc);
    }
}

void FilterGenerateWildEncountersFromSeedList(
        wenc_node** list,
        Player pl,
        Method met,
        Slot *slots,
        EncounterType et,
        WildFilter filter,
        InitialSeed *seeds,
        uint32_t size,
        uint32_t init,
        uint32_t max) {

    for (size_t i = 0; i <= size; i++) {
        FilterGenerateWildEncounter(list, pl, met, slots, et, filter, seeds[i].seed, init, max);
    }
};

void FilterGenerateWildEncounter(
        wenc_node** list,
        Player pl,
        Method met,
        Slot *slots,
        EncounterType et,
        WildFilter filter,
        uint32_t seed,
        uint32_t init,
        uint32_t max
) {
    if (max <= 0 || init > max) {
        return;
    }

    uint32_t advances;
    advances = max - init;

    uint32_t initial_seed = seed;

    seed = RNGJumpAhead(GEN3_JUMP_TABLE, seed, init);

    int i;
    for (i = 0; i <= (int)advances; i++, RNGIncrementSeed(&seed, 1)) {
        uint32_t current_seed = seed;

        WildEncounter* enc = NULL;
        enc = (WildEncounter* )malloc(sizeof(WildEncounter));
        if (enc == NULL) {
            return;
        }

        enc->slot = get_enc_table(et)[RNGNextUShort(100, current_seed)];
        RNGIncrementSeed(&current_seed, 1);
        enc->level = RNGCalculateLevel(slots[enc->slot], current_seed);

        if (enc->level != filter.level) {
            free(enc);
            continue;
        }

        enc->mon = slots[enc->slot].mon;

        if (!(enc->mon == filter.mon)){
            free(enc);
            continue;
        }

        RNGIncrementSeed(&current_seed, 2);

        enc->nature = (current_seed >> 16) % 25;

        if (!natureFilterCheckWild(&filter, enc->nature)) {
            free(enc);
            continue;
        }

        do
        {
            // PID re-roll https://docs.google.com/spreadsheets/d/1hCZznFa4cez3l2qx1DmYPbuB_dNGTqqCoaksZf-Q44s/edit?usp=sharing
            RNGIncrementSeed(&current_seed, 1);
            uint32_t second_half = current_seed >> 16;
            RNGIncrementSeed(&current_seed, 1);
            uint32_t first_half = current_seed >> 16;
            enc->PID = (first_half << 16) | second_half;
        } while (enc->PID % 25 != enc->nature);

        enc->shiny =  PokemonIsShiny(enc->PID, pl.TID, pl.SID);

        if (!shinyFilterCheckWild(&filter, enc->shiny)) {
            free(enc);
            continue;
        }

        Pokemon poke = pokemon[enc->mon];

        if (!genderFilterCheckWild(&filter, PokemonGetGender(enc->PID, poke.gr))) {
            free(enc);
            continue;
        }

        enc->ability = enc->PID & 1;

        if (!abilityFilterCheckWild(&filter, enc->ability)) {
            free(enc);
            continue;
        }

        if (met == H2) {
            RNGIncrementSeed(&current_seed, 1);
        }

        RNGIncrementSeed(&current_seed, 1);

        enc->IVs[0] = (current_seed >> 16) & IV_MASK; // HP
        enc->IVs[1] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // Atk
        enc->IVs[2] = ((current_seed >> 16) >> 2 * IV_SHIFT) & IV_MASK; // Def

        if (met == H4) {
            RNGIncrementSeed(&current_seed, 1);
        }
        // Move RNG by one
        RNGIncrementSeed(&current_seed, 1);
        enc->IVs[5] = (current_seed >> 16) & IV_MASK; // SpA
        enc->IVs[3] = ((current_seed >> 16) >> IV_SHIFT) & IV_MASK; // SpD
        enc->IVs[4] = ((current_seed>> 16) >> 2 * IV_SHIFT) & IV_MASK; // Spe

        if (!ivFilterCheckWild(enc, &filter)) {
            free(enc);
            continue;
        }

        enc->hp = HP[PokemonGetHPValue(enc->IVs)].type;
        enc->hp_pow = PokemonGetHP(enc->IVs);
        enc->advances = i + init;
        enc->seed = initial_seed;

        pushWenc(list, *enc);
    }
}

uint8_t
ivFilterCheckWild(WildEncounter* we, WildFilter* filter) {
    return (we->IVs[0] >= filter->hp_iv_bounds[0] && we->IVs[0] <= filter->hp_iv_bounds[1] &&
        we->IVs[1] >= filter->atk_iv_bounds[0] && we->IVs[1] <= filter->atk_iv_bounds[1] &&
        we->IVs[2] >= filter->def_iv_bounds[0] && we->IVs[2] <= filter->def_iv_bounds[1] &&
        we->IVs[3] >= filter->spa_iv_bounds[0] && we->IVs[3] <= filter->spa_iv_bounds[1] &&
        we->IVs[4] >= filter->spd_iv_bounds[0] && we->IVs[4] <= filter->spd_iv_bounds[1] &&
        we->IVs[5] >= filter->spe_iv_bounds[0] && we->IVs[5] <= filter->spe_iv_bounds[1] );
}

uint8_t
abilityFilterCheckWild(WildFilter* filter, uint8_t ability) {
   return (filter->ability[ability] == 1);
}

uint8_t
genderFilterCheckWild(WildFilter* filter, uint8_t gender) {
    return  (filter->gender[0] == 1 && gender == 0) ||  // Male gender[0] == 1
            (filter->gender[1] == 1 && gender == 1) ||  // Female gender[1] == 1
            (filter->gender[2] == 1 && gender == 3);    // Genderless gender[2] == 1
}

uint8_t
shinyFilterCheckWild(WildFilter* filter, uint8_t shiny) {
    return (filter->shiny[0] == 1 && shiny == 2) ||     // Square shiny[0] == 1
           (filter->shiny[1] == 1 && shiny == 1) ||     // Star shiny[1] == 1
           (filter->shiny[2] == 1 && shiny == 0);       // None
}

uint8_t
natureFilterCheckWild(WildFilter* filter, uint8_t nature) {
    return (filter->natures[nature] == 1);
}

uint8_t
ivFilterCheckStatic(StaticEncounter* se, StaticFilter* filter) {
    return (se->IVs[0] >= filter->hp_iv_bounds[0] && se->IVs[0]  <= filter->hp_iv_bounds[1]  &&
            se->IVs[1] >= filter->atk_iv_bounds[0] && se->IVs[1] <= filter->atk_iv_bounds[1] &&
            se->IVs[2] >= filter->def_iv_bounds[0] && se->IVs[2] <= filter->def_iv_bounds[1] &&
            se->IVs[3] >= filter->spa_iv_bounds[0] && se->IVs[3] <= filter->spa_iv_bounds[1] &&
            se->IVs[4] >= filter->spd_iv_bounds[0] && se->IVs[4] <= filter->spd_iv_bounds[1] &&
            se->IVs[5] >= filter->spe_iv_bounds[0] && se->IVs[5] <= filter->spe_iv_bounds[1] );
}

uint8_t
abilityFilterCheckStatic(StaticFilter* filter, uint8_t ability) {
    return (filter->ability[ability] == 1);
}

uint8_t
genderFilterCheckStatic(StaticFilter* filter, uint8_t gender) {
    return  (filter->gender[0] == 1 && gender == 0) ||  // Male gender[0] == 1
            (filter->gender[1] == 1 && gender == 1) ||  // Female gender[1] == 1
            (filter->gender[2] == 1 && gender == 3);    // Genderless gender[2] == 1
}

uint8_t
shinyFilterCheckStatic(StaticFilter* filter, uint8_t shiny) {
    return (filter->shiny[0] == 1 && shiny == 2) ||     // Square shiny[0] == 1
           (filter->shiny[1] == 1 && shiny == 1) ||     // Star shiny[1] == 1
           (filter->shiny[2] == 1 && shiny == 0);       // None
}

uint8_t
natureFilterCheckStatic(StaticFilter* filter, uint8_t nature) {
    return (filter->natures[nature] == 1);
}

void
pushSEnc(senc_node** h, StaticEncounter enc) {
    // Create node pointer
    senc_node * temp = NULL;

    // Allocate memory to the pointer
    temp = (senc_node*)malloc(sizeof(senc_node));

    if (temp == NULL)
        return;

    // Set the value of its static encounter to the value passed by the function
    temp->se = enc;
    temp->next = *h;

    // Address of head is now the inserted temp pointer
    *h = temp;
}

void
pushWenc(wenc_node** h, WildEncounter enc) {
    wenc_node* temp = NULL;

    temp = (wenc_node*)malloc(sizeof(wenc_node));
    if (temp == NULL)
        return;

    temp->we = enc;
    temp->next = *h;

    *h = temp;
}

void
FilterPrintSEncounterList(senc_node* enc) {
    senc_node* temp = NULL;
    temp = enc;

    int i;
    fprintf(stdout, "Seed | Advances | PID | Nature | Ability | HP | Atk | Def | Spa | Spd | Spe | Shiny | HP | HP Power | Gender\n");
    fprintf(stdout, "-------------------------------------------------------------------------------------------------------------\n");
    while(temp != NULL) {
        fprintf(stdout, "%X | ", temp->se.seed);
        fprintf(stdout, "%d | ", temp->se.advances);
        fprintf(stdout, "%X | ", temp->se.PID);
        fprintf(stdout, "%s | ", PokemonGetNatureString(temp->se.nature));
        fprintf(stdout, "Ability: %X | ", temp->se.ability );
        for (i = 0; i < 6; i ++) {
            printf("%d | ", temp->se.IVs[i]);
        }
        fprintf(stdout, " %s ", SHINY_TYPES[temp->se.shiny]);
        fprintf(stdout, "| %s ", temp->se.hp);
        fprintf(stdout, "| %d ", temp->se.hp_pow);
        fprintf(stdout, "| %s \n", temp->se.gender);

        temp = temp->next;
    }
}

void
FilterPrintWEncounterList(wenc_node* enc) {
    wenc_node* temp = NULL;
    temp = enc;

    int i, c;
    c = 0;
    fprintf(stdout, "Seed | Advances | Name | Slot | Level | PID | Nature | Ability | HP | Atk | Def | Spa | Spd | Spe | Shiny | HP | HP Power | Gender\n");
    fprintf(stdout, "-----------------------------------------------------------------------------------------------------------------------------------\n");
    while(temp != NULL) {
        Pokemon m = pokemon[temp->we.mon];
        fprintf(stdout, "%X | ", temp->we.seed);
        fprintf(stdout, "%d | ", temp->we.advances);
        fprintf(stdout, "%s | ", m.name);
        fprintf(stdout, "%d | ", temp->we.slot);
        fprintf(stdout, "%d | ", temp->we.level);
        fprintf(stdout, "%X | ", temp->we.PID);
        fprintf(stdout, "%s | ", PokemonGetNatureString(temp->we.nature));
        fprintf(stdout, "%s (%d)| ", (temp->we.ability) ? m.ab1 : m.ab0, temp->we.ability);

        for (i = 0; i < 6; i ++) {
            fprintf(stdout, "%d | ", temp->we.IVs[i]);
        }

        fprintf(stdout, " %s ", SHINY_TYPES[temp->we.shiny]);
        fprintf(stdout, "| %s ", temp->we.hp);
        fprintf(stdout, "| %d ", temp->we.hp_pow);
        fprintf(stdout, "| %s\n", PokemonGetGenderString(PokemonGetGender(temp->we.PID, m.gr)));

        temp = temp->next;
        c++;
    }
}

void
FilterFreeSEncList(senc_node* head) {
    senc_node* currentTemp = head;
    senc_node *next = NULL;
    while(currentTemp != NULL) {
        next = currentTemp->next;
        free(currentTemp);
        currentTemp = next;
    }
}

void
FilterFreeWEncList(wenc_node* head) {
    wenc_node* currentTemp = head;
    wenc_node *next = NULL;
    while(currentTemp != NULL) {
        next = currentTemp->next;
        free(currentTemp);
        currentTemp = next;
    }
}

void FilterApplyNatureToStatic(Nature nt, StaticFilter* filter) { filter->natures[nt.key] = 1; }
void FilterApplyNatureToWild(Nature nt, WildFilter* filter) { filter->natures[nt.key] = 1; }

void FilterApplyIVEstimateToStatic(IVEstimate* target, StaticFilter* filter) {
    int i, l, u;
    IVsGetAllStatRanges(target);

    /* An array of pointers that point to the start of the filter struct arrays... yeesh*/
    uint8_t (*iv_bounds[6])[2] = {
            &filter->hp_iv_bounds,
            &filter->atk_iv_bounds,
            &filter->def_iv_bounds,
            &filter->spa_iv_bounds,
            &filter->spd_iv_bounds,
            &filter->spe_iv_bounds
    };

    for (i = 0; i < 6; i++ ){
        IVsFindBounds(target->rs[i], &l, &u);
        iv_bounds[i][0][0] = (uint8_t)l;
        iv_bounds[i][0][1] = (uint8_t)u;
    }
}

void FilterApplyIVEstimateToWild(IVEstimate* target, WildFilter* filter) {
    int i, l, u;
    IVsGetAllStatRanges(target);

    /* An array of pointers that point to the start of the filter struct arrays... yeesh*/
    uint8_t (*iv_bounds[6])[2] = {
            &filter->hp_iv_bounds,
            &filter->atk_iv_bounds,
            &filter->def_iv_bounds,
            &filter->spa_iv_bounds,
            &filter->spd_iv_bounds,
            &filter->spe_iv_bounds
    };

    for (i = 0; i < 6; i++ ){
        IVsFindBounds(target->rs[i], &l, &u);
        iv_bounds[i][0][0] = (uint8_t)l;
        iv_bounds[i][0][1] = (uint8_t)u;
    }
}
