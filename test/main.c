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

void FTEST_IVsGetAllStatRanges_Function(IVEstimate* est);
void FTEST_IVsFindBounds_Function(IVEstimate* est, uint8_t stats_e[6][2]);

#define VERIFY_STAT(expected, operation, result, message) if(!((expected) operation (result))) \
    { fprintf(stderr, "%s: Expected (%d %s %d)\n", (message), (expected), #operation, (result)); }

int main(void) {

    TEST_CASE_0();
    TEST_CASE_1();

    fprintf(stdout, "All tests successful.\n");
    return EXIT_SUCCESS;
}

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
            );

            VERIFY_STAT(
                est->rs[i][j],
                <=,
                MAX_IV,
                "Expected IV maximum value mismatched"
            );
        }
    }
}

void FTEST_IVsFindBounds_Function(IVEstimate* est, uint8_t stats_e[6][2]) {
    int l, u;

    IVsGetAllStatRanges(est);

    for (size_t i = 0; i < 6; i++) {

        IVsFindBounds(est->rs[i], &l, &u);

        /* Ensure that the lower and upper bounds calculated are between -1-31 */
        assert(l >= IV_DEFAULT && "Lower bound calculation beyond minimum value of -1\n");
        assert(u <= MAX_IV && "Lower bound calculation exceeded maximum value of 31\n");

        /* Ensure that the lower and upper bounds from the estimate array match expected valeus */
        assert(l == stats_e[i][0] && "Expected lower bound does not match calculated bound from IVsFindBounds\n");
        assert(u == stats_e[i][1] && "Expected upper bound does not match calculated bound from IVsFindBounds\n");
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