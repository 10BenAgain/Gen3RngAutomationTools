#include "../include/seeds.h"

static const char optionFiles[14][18] = {
        "Mono-HELP-A",
        "Mono-HELP-Start",
        "Mono-LA-A",
        "Mono-LA-L",
        "Mono-LA-Start",
        "Mono-LR-A",
        "Mono-LR-Start",
        "Stereo-HELP-A",
        "Stereo-HELP-Start",
        "Stereo-LA-A",
        "Stereo-LA-L",
        "Stereo-LA-Start",
        "Stereo-LR-A",
        "Stereo-LR-Start"
};

static const OptionFileMap optionFileMappings[] = {
        { MONO,     HELP,   A,      optionFiles[0] },
        { MONO,     HELP,   START,  optionFiles[1] },
        { MONO,     LA,     A,      optionFiles[2] },
        { MONO,     LA,     L,      optionFiles[3] },
        { MONO,     LA,     START,  optionFiles[4] },
        { MONO,     LR,     A,      optionFiles[5] },
        { MONO,     LR,     START,  optionFiles[6] },
        { STEREO,   HELP,   A,      optionFiles[7] },
        { STEREO,   HELP,   START,  optionFiles[8] },
        { STEREO,   LA,     A,      optionFiles[9] },
        { STEREO,   LA,     L,      optionFiles[10] },
        { STEREO,   LA,     START,  optionFiles[11] },
        { STEREO,   LR,     A,      optionFiles[12] },
        { STEREO,   LR,     START,  optionFiles[13] },
};

// https://stackoverflow.com/questions/8465006/how-do-i-concatenate-two-strings-in-c
const char
*get_seed_path(const char *folder, const char *file) {
    char *result = NULL;
    const size_t lfo = strlen(folder);
    const size_t lfd = strlen(file);

    result = malloc(lfo + lfd + 1); // +1 for terminator char

    if (result == NULL)
        return NULL;

    // Copy folder memory into result with a size of folder string size
    memcpy(result, folder, lfo);

    // Copy file string after into result after the size of folder block
    memcpy(result + lfo, file, lfd + 1);

    return result;
}

uint64_t
count_lines_in_file(const char *fp) {
    FILE *file = NULL;

    file = fopen(fp, "r");
    if (file == NULL) {
        return 0;
    }
    int count = 0;
    char line[MAX_TIMER_LENGTH + MAX_SEED_LENGTH + 2];

    while(fgets(line, sizeof(line), file)) {
        count ++;
    }
    fclose(file);
    return count;
}

InitialSeed
*SeedLoadInitial(const char *fn, uint64_t *len, SeedOffset ofs) {
    uint64_t lc = count_lines_in_file(fn);
    if (lc <= 0) return NULL;

    *len = lc;
    InitialSeed *seeds = malloc(lc * sizeof(InitialSeed));
    if (!seeds) {
        free(seeds);
        return NULL;
    }

    FILE *fp;
    fp = fopen(fn, "r");

    if (!fp) {
        free(seeds);
        return NULL;
    }

    uint64_t count = 0;
    char line[MAX_TIMER_LENGTH + MAX_SEED_LENGTH + 2];
    while (fgets(line, sizeof(line), fp) && count < lc) {
        char *token = strtok(line, ",");
        if (token != NULL) {
            seeds[count].timer = (uint32_t)atoi(token);
            token = strtok(NULL, "\n");
            if (token != NULL) {
                seeds[count].seed = (uint32_t)strtol(token, NULL, 16);
                switch (ofs) {
                    case HELD_SELECT:
                        seeds[count].seed -= HELD_SELECT;
                        break;
                    case HELD_A:
                        seeds[count].seed -= HELD_A;
                        break;
                    default:
                        break;
                }
                count++;
            }
        }
    }

    fclose(fp);
    return seeds;
}

const char
*SeedGetFilePath(Settings set) {
#ifdef BUILD_PATH
    char *LGpath = "../data/LG/";
    char *FRpath = "../data/FR/";
#else
    char *LGpath = "data/LG/";
    char *FRpath = "data/FR/";
#endif
    const char *path = NULL;
    const char *language = NULL;
    const char *file = NULL;

    switch (set.gv) {
        case FR:
            path = FRpath;
            break;
        case LG:
            path = LGpath;
            break;
        default:
            return NULL;
    }

    switch(set.lang) {
        case ENGLISH:
            language = "ENG/";
            break;
        case EU:
            language = "EU/";
            break;
        case JPN:
            if (set.gv == FR) {
                switch (set.jgv) {
                    case J10:
                        language = "JPN1_0/";
                        break;
                    case J11:
                        language = "JPN1_1/";
                        break;
                    default:
                        break;
                }
            } else {
                language = "JPN/";
                break;
            }
        default:
            break;
    }

    for (size_t i = 0; i < sizeof(optionFileMappings) / sizeof(OptionFileMap); i++) {
        if (optionFileMappings[i].audS ==   set.audio &&
            optionFileMappings[i].btnS ==   set.buttonSetting &&
            optionFileMappings[i].btn  ==   set.buttonSeed) {
            file = optionFileMappings[i].file;
            break;
        }
    }
    if (file != NULL) {
        const char *new_path = get_seed_path(path, language);
        const char* result = get_seed_path(new_path, file);
        if (access(result, F_OK)) {
            return NULL;
        }
        else {
            return result;
        }
    }

    return NULL;
}

/* Linear search is probably bad but w/e */
int
SeedFindIndex(InitialSeed *set, uint32_t seed, uint64_t length) {
    if (set == NULL) return 0;

    for (size_t i = 0; i < length; i++) {
        if (set[i].seed == seed) {
            return i;
        }
    }
    return -1;
}

InitialSeed
*SeedGetSeedRange(InitialSeed *set, uint64_t length, int index, uint16_t range, uint64_t *newLen) {
    uint64_t start, end;

    if (index - range > 0) {
        start = index - range;
    } else {
        start = 0;
    }

    if ((index + range) <= length) {
        end = index + range;
    } else {
        end = length;
    }

    *newLen = end - start;
    InitialSeed *seedR = malloc(*newLen * sizeof(InitialSeed));
    if (seedR == NULL) {
        free(seedR);
        return NULL;
    }
    memcpy(seedR, &set[start], *newLen * sizeof(InitialSeed));
    return seedR;
}