#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "../include/commands.h"
#include "../include/encounter_table.h"
#include "../include/enums.h"
#include "../include/filters.h"
#include "../include/ivs.h"
#include "../include/locations.h"
#include "../include/pokemon.h"
#include "../include/rng.h"
#include "../include/seeds.h"
#include "../include/settings.h"

void TEST_CASE_0();
void TEST_CASE_1();
void TEST_CASE_2();
void TEST_CASE_3();
void TEST_CASE_4();
void TEST_CASE_5();

void FTEST_IVsGetAllStatRanges_Function(IVEstimate* est);
void FTEST_IVsFindBounds_Function(IVEstimate* est, uint8_t stats_e[6][2]);

#define VERIFY_STAT(expected, operation, result, message) if(!((expected) operation (result))) \
    { fprintf(stderr, "%s: Expected (%d %s %d)\n", (message), (expected), #operation, (result)); }

#define VERIFY_STRING(expected, result, message) if(strcmp((expected), (result))) \
    { fprintf(stderr, "%s: Expected ('%s' to match '%s')\n", (message), (expected), (result)); }

static void inline VerifyArray(uint8_t* arr1, uint8_t* arr2, size_t len, const char* message) {
    for (size_t i = 0; i < len; i++) {
        if (arr1[i] != arr2[i]) {
            fprintf(stderr, "%s: Expected (%d to equal %d)\n", message, arr1[i], arr2[i]);
        }
    }
}

int main(void) {

    TEST_CASE_0();
    TEST_CASE_1();
    TEST_CASE_2();
    TEST_CASE_3();
    TEST_CASE_4();
    TEST_CASE_5();

    return EXIT_SUCCESS;
}

/* Static Search Testing */
void FTEST_CheckStaticGeneratorListVals(senc_node* enc, StaticEncounter test) {

    if (enc == NULL) {
        fprintf(stdout, "Static encounter test given list with no encounters!");
        return;
    }

    VERIFY_STAT(
            enc->se.seed,
            ==,
            test.seed,
            "Expected seed filter to match encounter failed"
    )

    VERIFY_STAT(
            enc->se.PID,
            ==,
            test.PID,
            "Expected PID filter to match encounter failed"
    )

    VERIFY_STAT(
            enc->se.advances,
            ==,
            test.advances,
            "Expected Advance filter to match encounter failed"
    )

    VERIFY_STAT(
            enc->se.mon,
            ==,
            test.mon,
            "Expected Pokemon filter to match encounter failed"
    )

    VERIFY_STAT(
            enc->se.nature,
            ==,
            test.nature,
            "Expected Nature filter to match encounter failed"
    )

    VERIFY_STAT(
            enc->se.ability,
            ==,
            test.ability,
            "Expected Ability filter to match encounter failed"
    )

    VERIFY_STAT(
            enc->se.hp_pow,
            ==,
            test.hp_pow,
            "Expected Hidden Power (Stat) filter to match encounter failed"
    )

    VERIFY_STAT(
            enc->se.shiny,
            ==,
            test.shiny,
            "Expected Shiny filter to match encounter failed"
    )

    VERIFY_STRING(
            enc->se.gender,
            test.gender,
            "Expected Gender string filter to match encounter failed"
    )

    VERIFY_STRING(
            enc->se.hp,
            test.hp,
            "Expected Hidden Power string filter to match encounter failed"
    )

    VerifyArray(enc->se.IVs, test.IVs, 6, "Expected IV filter to match encounter failed");
}

/* IV Estimate Testing
 *
 * I basically want to make sure that the calculations for estimating IVs
 * Always work because they can make a huge difference in searches when they don't
 * Ideally, we would want to test every single Pokemon to verify that the base stats
 * Are correct but that would be incredibly tedious. Let's just assume that nobody
 * Changes the base stats of the Pokemon array:)
*/

#define MAX_IV 31
#define IV_DEFAULT -1
void FTEST_IVsGetAllStatRanges_Function(IVEstimate* est) {

    IVsGetAllStatRanges(est);

    for (size_t i = 0; i < 6; i++) {
        for (size_t j = 0; j < 32; j++) {

            /* Ensure that each element is within the possible IV range with
               -1 being the default value on estimate not matching range */

            VERIFY_STAT(
                est->rs[i][j],
                >=,
                IV_DEFAULT,
                "Expected IV minimum value mismatched"
            )

            VERIFY_STAT(
                est->rs[i][j],
                <=,
                MAX_IV,
                "Expected IV maximum value mismatched"
            )
        }
    }
}

void FTEST_IVsFindBounds_Function(IVEstimate* est, uint8_t stats_e[6][2]) {
    int l, u;

    IVsGetAllStatRanges(est);

    for (size_t i = 0; i < 6; i++) {

        IVsFindBounds(est->rs[i], &l, &u);

        /* Ensure that the lower and upper bounds calculated are between -1-31 */
        VERIFY_STAT(
                l,
                >=,
                IV_DEFAULT,
                "Lower bound calculation beyond minimum value"
        )

        VERIFY_STAT(
                u,
                <=,
                MAX_IV,
                "Upper bound calculation beyond maximum value"
        )

        /* Ensure that the lower and upper bounds from the estimate array match expected values */
        VERIFY_STAT(
                l,
                ==,
                stats_e[i][0],
                "Expected lower bound does not match calculated bound from IVsFindBounds"
        )

        VERIFY_STAT(
                u,
                ==,
                stats_e[i][1],
                "Expected upper bound does not match calculated bound from IVsFindBounds"
        )
    }
}

void TEST_CASE_0() {
    uint8_t SPEAROW_TEST_STAT_EXPECTED_0[6][2] = {
            { 5, 12 },
            { 0, 3 },
            { 2, 9 },
            { 8, 14 },
            { 0, 7 },
            { 7, 13 }
    };

    IVEstimate SPEAROW_TEST_ESTIMATE_0 = {
            pokemon[20],
            natures[8],
            13,
            { 34, 20, 14, 12, 13, 24 },
            {0}
    };

    /* Test 0 [Spearow IV Check] */
    FTEST_IVsGetAllStatRanges_Function(&SPEAROW_TEST_ESTIMATE_0);
    FTEST_IVsFindBounds_Function(&SPEAROW_TEST_ESTIMATE_0, SPEAROW_TEST_STAT_EXPECTED_0);
}

void TEST_CASE_1() {
    uint8_t GOLBAT_TEST_STAT_EXPECTED_1[6][2] = {
            { 29, 30 },
            { 21, 22 },
            { 26, 27 },
            { 0, 0 },
            { 0, 2 },
            { 7, 9 }
    };

    IVEstimate GOLBAT_TEST_ESTIMATE_1 = {
            pokemon[41],
            natures[4],
            46,
            { 138, 96, 81, 64, 66, 91 },
            {0}
    };

    /* Test 1 [Golbat IV Check] */
    FTEST_IVsGetAllStatRanges_Function(&GOLBAT_TEST_ESTIMATE_1);
    FTEST_IVsFindBounds_Function(&GOLBAT_TEST_ESTIMATE_1, GOLBAT_TEST_STAT_EXPECTED_1);
}

void TEST_CASE_2() {
    uint8_t BELLSPROUT_TEST_STAT_EXPECTED_2[6][2] = {
            { 0, 4 },
            { 0, 4 },
            { 0, 2 },
            { 0, 0 },
            { 0, 3 },
            { 0, 1 }
    };

    IVEstimate BELLSPROUT_TEST_ESTIMATE_2 = {
            pokemon[68],
            natures[7],
            22,
            { 54, 38, 22, 35, 18, 19 },
            {0}
    };

    FTEST_IVsGetAllStatRanges_Function(&BELLSPROUT_TEST_ESTIMATE_2);
    FTEST_IVsFindBounds_Function(&BELLSPROUT_TEST_ESTIMATE_2, BELLSPROUT_TEST_STAT_EXPECTED_2);
}

void TEST_CASE_3() {
    uint8_t PIDGEY_TEST_STAT_EXPECTED_3[6][2] = {
            { 28, 31 },
            { 29, 31 },
            { 28, 31 },
            { 30, 31 },
            { 30, 31 },
            { 29, 31 }
    };

    IVEstimate PIDGEY_TEST_ESTIMATE_3= {
            pokemon[15],
            natures[10],
            27,
            { 66, 33, 34, 32, 32, 47 },
            {0}
    };

    FTEST_IVsGetAllStatRanges_Function(&PIDGEY_TEST_ESTIMATE_3);
    FTEST_IVsFindBounds_Function(&PIDGEY_TEST_ESTIMATE_3, PIDGEY_TEST_STAT_EXPECTED_3);
}

void TEST_CASE_4() {
    uint8_t MEWTWO_TEST_STAT_EXPECTED_4[6][2] = {
            { 4, 5 },
            { 30, 31 },
            { 20, 21 },
            { 31, 31 },
            { 16, 17 },
            { 10, 11 }
    };

    IVEstimate MEWTWO_TEST_ESTIMATE_4= {
            pokemon[149],
            natures[16],
            70,
            { 231, 180, 130, 266, 142, 194 },
            {0}
    };

    FTEST_IVsGetAllStatRanges_Function(&MEWTWO_TEST_ESTIMATE_4);
    FTEST_IVsFindBounds_Function(&MEWTWO_TEST_ESTIMATE_4, MEWTWO_TEST_STAT_EXPECTED_4);
}

void TEST_CASE_5() {

    senc_node *HEAD = NULL;

    uint32_t seed = 0xE585;

    Player pl = { 34437, 44782 };

    uint8_t mon = 0;

    Nature nt = natures[7];

    uint32_t max = 101;

    uint32_t init = 0;

    StaticFilter sf = {
        5,
        {0, 1},
        {0, 9},
        {22, 31},
        {2, 21},
        {10, 29},
        {10, 29},
        {10, 31},
        {1 , 0 , 0},
        {0, 0, 1},
        {0}
    };

    FilterApplyNatureToStatic(nt, &sf);
    FilterGenerateStaticEncounter(&HEAD, pl, M1, sf, mon, seed, init, max);

    StaticEncounter EXPECTED_SEARCH_ENCOUNTER_5 = {
            mon,
            0xBD140841,
            7,
            1,
            { 7, 30, 21, 19, 29, 27 },
            "Male",
            "Dragon",
            47,
            0,
            0xE585,
            100
    };

    FTEST_CheckStaticGeneratorListVals(HEAD, EXPECTED_SEARCH_ENCOUNTER_5);
}