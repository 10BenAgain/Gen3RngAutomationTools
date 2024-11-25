#include "../include/settings.h"

int handler(void* player, const char* section, const char* name, const char * value) {
    Config* pconfig = (Config*)player;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("player", "name")) {
        pconfig->name = strdup(value);
    } else if  (MATCH("player", "sid")){
        pconfig->sid = (uint32_t)atoi(value);
    } else if  (MATCH("player", "tid")){
        pconfig->tid = (uint32_t)atoi(value);
    } else if  (MATCH("game", "version")){
        pconfig->game_version = strdup(value);
    } else if  (MATCH("game", "sub")){
        pconfig->sub_version = (uint8_t)atoi(value);
    } else if  (MATCH("game", "language")){
        pconfig->language = strdup(value);
    } else if  (MATCH("settings", "audio")){
        pconfig->audio = strdup(value);
    } else if  (MATCH("settings", "seed")){
        pconfig->seed = strdup(value);
    } else if  (MATCH("settings", "button")){
        pconfig->button = strdup(value);
    } else {
        return 0;
    }
    return 1;
}

int cfToAudio(Config* cf, AudioSetting* as) {
    if (!strcmp(cf->audio, "STEREO")) {
        *as = STEREO;
        return 0;
    } else if (!strcmp(cf->audio, "MONO")) {
        *as = MONO;
        return 0;
    } else {
        return 1;
    }
}

int cfToButtonSetting(Config* cf, ButtonSetting* bs) {
    if (!strcmp(cf->button, "LA")) {
        *bs = LA;
        return 0;
    } else if (!strcmp(cf->button, "Help")) {
        *bs = HELP;
        return 0;
    } else if (!strcmp(cf->button, "LR")) {
        *bs = LR;
        return 0;
    } else {
        return 1;
    }
}

int cfToButtonSeed(Config *cf, ButtonSeed* bs) {
    if (!strcmp(cf->seed, "A")) {
        *bs = A;
        return 0;
    } else if (!strcmp(cf->seed, "Start")) {
        *bs = START;
        return 0;
    } else if (!strcmp(cf->seed, "L")) {
        *bs = L;
        return 0;
    } else {
        return 1;
    }
}

int cfToGameVersion(Config *cf, GameVersion* gv) {
    if (!strcmp(cf->game_version, "LG")) {
        *gv = 1;
        return 0;
    } else if (!strcmp(cf->game_version, "FR")) {
        *gv = 0;
        return 0;
    } else {
        return 1;
    }
}

int cfToGameSubVersion(Config *cf, GameVersion gv, JPNVersion* sv) {
    if (gv == FR) {
        switch (cf->sub_version) {
            case 10:
                *sv = J10;
                return 0;
            case 11:
                *sv = J11;
                return 0;
            default:
                return 1;
        }
    } else {
        *sv = LEAF_GREEN;
        return 0;
    }
}

int cfToLanguage(Config *cf, Language* lg) {
    if (!strcmp(cf->language, "English")) {
        *lg = English;
        return 0;
    } else if (!strcmp(cf->language, "EU")) {
        *lg = EU;
        return 0;
    } else if (!strcmp(cf->language, "Japanese")) {
        *lg = JPN;
        return 0;
    } else {
        return 1;
    }
}