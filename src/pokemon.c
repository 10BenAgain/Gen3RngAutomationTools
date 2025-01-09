#include "../include/pokemon.h"

const char* stats[6] = {
        "HP",
        "Atk",
        "Def",
        "SpA",
        "SpD",
        "Spe"
};

const char* GENDER_STRINGS[3] = {
    "Male",
    "Female",
    "None"
};

const char* SHINY_TYPES[3] = {
        "None",
        "Star",
        "Square"
};

const char* ENCOUNTER_CATEGORY[8] = {
        "Starter",
        "Fossil",
        "Gift",
        "Game Corner",
        "Stationary",
        "Legends",
        "Events",
        "Roamers"
};

const HiddenPower HP[16] = {
    {0,     "Fighting"  },
    {1,     "Flying"    },
    {2,     "Poison"    },
    {3,     "Ground"    },
    {4,     "Rock"      },
    {5,     "Bug"       },
    {6,     "Ghost"     },
    {7,     "Steel"     },
    {8,     "Fire"      },
    {9,     "Water"     },
    {10,    "Grass"     },
    {11,    "Electric"  },
    {12,    "Psychic"   },
    {13,    "Ice"       },
    {14,    "Dragon"    },
    {15,    "Dark"      }
};

const Nature natures[25] = {
        {0,     "Hardy"     },
        {1,     "Lonely"    },
        {2,     "Brave"     },
        {3,     "Adamant"   },
        {4,     "Naughty"   },
        {5,     "Bold"      },
        {6,     "Docile"    },
        {7,     "Relaxed"   },
        {8,     "Impish"    },
        {9,     "Lax"       },
        {10,    "Timid"     },
        {11,    "Hasty"     },
        {12,    "Serious"   },
        {13,    "Jolly"     },
        {14,    "Naive"     },
        {15,    "Modest"    },
        {16,    "Mild"      },
        {17,    "Quiet"     },
        {18,    "Bashful"   },
        {19,    "Rash"      },
        {20,    "Calm"      },
        {21,    "Gentle"    },
        {22,    "Sassy"     },
        {23,    "Careful"   },
        {24,    "Quirky"    }
};

/* ATK/DEF/SPA/SPD/SPE */
const double nature_multiplier_table[25][5] = {
    {1.0,   1.0,   1.0,   1.0,   1.0},
    {1.1,   0.9,   1.0,   1.0,   1.0},
    {1.1,   1.0,   1.0,   1.0,   0.9},
    {1.1,   1.0,   0.9,   1.0,   1.0},
    {1.1,   1.0,   1.0,   0.9,   1.0},
    {0.9,   1.1,   1.0,   1.0,   1.0},
    {1.0,   1.0,   1.0,   1.0,   1.0},
    {1.0,   1.1,   1.0,   1.0,   0.9},
    {1.0,   1.1,   0.9,   1.0,   1.0},
    {1.0,   1.1,   1.0,   0.9,   1.0},
    {0.9,   1.0,   1.0,   1.0,   1.1},
    {1.0,   0.9,   1.0,   1.0,   1.1},
    {1.0,   1.0,   1.0,   1.0,   1.0},
    {1.0,   1.0,   0.9,   1.0,   1.1},
    {1.0,   1.0,   1.0,   0.9,   1.1},
    {0.9,   1.0,   1.1,   1.0,   1.0},
    {1.0,   0.9,   1.1,   1.0,   1.0},
    {1.0,   1.0,   1.1,   1.0,   0.9},
    {1.0,   1.0,   1.0,   1.0,   1.0},
    {1.0,   1.0,   1.1,   0.9,   1.0},
    {0.9,   1.0,   1.0,   1.1,   1.0},
    {1.0,   0.9,   1.0,   1.1,   1.0},
    {1.0,   1.0,   1.0,   1.1,   0.9},
    {1.0,   1.0,   0.9,   1.1,   1.0},
    {1.0,   1.0,   1.0,   1.0,   1.0},
};

const Pokemon pokemon[] = {
    { 1, "Bulbasaur", {45, 49, 49, 65, 65, 45}, F1M7, "Overgrow", "Overgrow" },
    { 2, "Ivysaur", {60, 62, 63, 80, 80, 60}, F1M7, "Overgrow", "Overgrow" },
    { 3, "Venusaur", {80, 82, 83, 100, 100, 80}, F1M7, "Overgrow", "Overgrow" },
    { 4, "Charmander", {39, 52, 43, 60, 50, 65}, F1M7, "Blaze", "Blaze" },
    { 5, "Charmeleon", {58, 64, 58, 80, 65, 80}, F1M7, "Blaze", "Blaze" },
    { 6, "Charizard", {78, 84, 78, 109, 85, 100}, F1M7, "Blaze", "Blaze" },
    { 7, "Squirtle", {44, 48, 65, 50, 64, 43}, F1M7, "Torrent", "Torrent" },
    { 8, "Wartortle", {59, 63, 80, 65, 80, 58}, F1M7, "Torrent", "Torrent" },
    { 9, "Blastoise", {79, 83, 100, 85, 105, 78}, F1M7, "Torrent", "Torrent" },
    { 10, "Caterpie", {45, 30, 35, 20, 20, 45}, F1M1, "Shield Dust", "Shield Dust" },
    { 11, "Metapod", {50, 20, 55, 25, 25, 30}, F1M1, "Shed Skin", "Shed Skin" },
    { 12, "Butterfree", {60, 45, 50, 80, 80, 70}, F1M1, "Compound Eyes", "Compound Eyes" },
    { 13, "Weedle", {40, 35, 30, 20, 20, 50}, F1M1, "Shield Dust", "Shield Dust" },
    { 14, "Kakuna", {45, 25, 50, 25, 25, 35}, F1M1, "Shed Skin", "Shed Skin" },
    { 15, "Beedrill", {65, 80, 40, 45, 80, 75}, F1M1, "Swarm", "Swarm" },
    { 16, "Pidgey", {40, 45, 40, 35, 35, 56}, F1M1, "Keen Eye", "Tangled Feet" },
    { 17, "Pidgeotto", {63, 60, 55, 50, 50, 71}, F1M1, "Keen Eye", "Tangled Feet" },
    { 18, "Pidgeot", {83, 80, 75, 70, 70, 91}, F1M1, "Keen Eye", "Tangled Feet" },
    { 19, "Rattata", {30, 56, 35, 25, 35, 72}, F1M1, "Run Away", "Guts" },
    { 20, "Raticate", {55, 81, 60, 50, 70, 97}, F1M1, "Run Away", "Guts" },
    { 21, "Spearow", {40, 60, 30, 31, 31, 70}, F1M1, "Keen Eye", "Keen Eye" },
    { 22, "Fearow", {65, 90, 65, 61, 61, 100}, F1M1, "Keen Eye", "Keen Eye" },
    { 23, "Ekans", {35, 60, 44, 40, 54, 55}, F1M1, "Intimidate", "Shed Skin" },
    { 24, "Arbok", {60, 85, 69, 65, 79, 80}, F1M1, "Intimidate", "Shed Skin" },
    { 25, "Pikachu", {35, 55, 30, 50, 40, 90}, F1M1, "Static", "Static" },
    { 26, "Raichu", {60, 90, 55, 90, 80, 100}, F1M1, "Static", "Static" },
    { 27, "Sandshrew", {50, 75, 85, 20, 30, 40}, F1M1, "Sand Veil", "Sand Veil" },
    { 28, "Sandslash", {75, 100, 110, 45, 55, 65}, F1M1, "Sand Veil", "Sand Veil" },
    { 29, "Nidoran-f", {55, 47, 52, 40, 40, 41}, FemaleOnly, "Poison Point", "Rivalry" },
    { 30, "Nidorina", {70, 62, 67, 55, 55, 56}, FemaleOnly, "Poison Point", "Rivalry" },
    { 31, "Nidoqueen", {90, 82, 87, 75, 85, 76}, FemaleOnly, "Poison Point", "Rivalry" },
    { 32, "Nidoran-m", {46, 57, 40, 40, 40, 50}, MaleOnly, "Poison Point", "Rivalry" },
    { 33, "Nidorino", {61, 72, 57, 55, 55, 65}, MaleOnly, "Poison Point", "Rivalry" },
    { 34, "Nidoking", {81, 92, 77, 85, 75, 85}, MaleOnly, "Poison Point", "Rivalry" },
    { 35, "Clefairy", {70, 45, 48, 60, 65, 35}, F3M1, "Cute Charm", "Magic Guard" },
    { 36, "Clefable", {95, 70, 73, 85, 90, 60}, F3M1, "Cute Charm", "Magic Guard" },
    { 37, "Vulpix", {38, 41, 40, 50, 65, 65}, F3M1, "Flash Fire", "Flash Fire" },
    { 38, "Ninetales", {73, 76, 75, 81, 100, 100}, F3M1, "Flash Fire", "Flash Fire" },
    { 39, "Jigglypuff", {115, 45, 20, 45, 25, 20}, F3M1, "Cute Charm", "Competitive" },
    { 40, "Wigglytuff", {140, 70, 45, 75, 50, 45}, F3M1, "Cute Charm", "Competitive" },
    { 41, "Zubat", {40, 45, 35, 30, 40, 55}, F1M1, "Inner Focus", "Inner Focus" },
    { 42, "Golbat", {75, 80, 70, 65, 75, 90}, F1M1, "Inner Focus", "Inner Focus" },
    { 43, "Oddish", {45, 50, 55, 75, 65, 30}, F1M1, "Chlorophyll", "Chlorophyll" },
    { 44, "Gloom", {60, 65, 70, 85, 75, 40}, F1M1, "Chlorophyll", "Chlorophyll" },
    { 45, "Vileplume", {75, 80, 85, 100, 90, 50}, F1M1, "Chlorophyll", "Chlorophyll" },
    { 46, "Paras", {35, 70, 55, 45, 55, 25}, F1M1, "Effect Spore", "Dry Skin" },
    { 47, "Parasect", {60, 95, 80, 60, 80, 30}, F1M1, "Effect Spore", "Dry Skin" },
    { 48, "Venonat", {60, 55, 50, 40, 55, 45}, F1M1, "Compound Eyes", "Tinted Lens" },
    { 49, "Venomoth", {70, 65, 60, 90, 75, 90}, F1M1, "Shield Dust", "Tinted Lens" },
    { 50, "Diglett", {10, 55, 25, 35, 45, 95}, F1M1, "Sand Veil", "Arena Trap" },
    { 51, "Dugtrio", {35, 80, 50, 50, 70, 120}, F1M1, "Sand Veil", "Arena Trap" },
    { 52, "Meowth", {40, 45, 35, 40, 40, 90}, F1M1, "Pickup", "Technician" },
    { 53, "Persian", {65, 70, 60, 65, 65, 115}, F1M1, "Limber", "Technician" },
    { 54, "Psyduck", {50, 52, 48, 65, 50, 55}, F1M1, "Damp", "Cloud Nine" },
    { 55, "Golduck", {80, 82, 78, 95, 80, 85}, F1M1, "Damp", "Cloud Nine" },
    { 56, "Mankey", {40, 80, 35, 35, 45, 70}, F1M1, "Vital Spirit", "Anger Point" },
    { 57, "Primeape", {65, 105, 60, 60, 70, 95}, F1M1, "Vital Spirit", "Anger Point" },
    { 58, "Growlithe", {55, 70, 45, 70, 50, 60}, F1M3, "Intimidate", "Flash Fire" },
    { 59, "Arcanine", {90, 110, 80, 100, 80, 95}, F1M3, "Intimidate", "Flash Fire" },
    { 60, "Poliwag", {40, 50, 40, 40, 40, 90}, F1M1, "Water Absorb", "Damp" },
    { 61, "Poliwhirl", {65, 65, 65, 50, 50, 90}, F1M1, "Water Absorb", "Damp" },
    { 62, "Poliwrath", {90, 85, 95, 70, 90, 70}, F1M1, "Water Absorb", "Damp" },
    { 63, "Abra", {25, 20, 15, 105, 55, 90}, F1M3, "Synchronize", "Inner Focus" },
    { 64, "Kadabra", {40, 35, 30, 120, 70, 105}, F1M3, "Synchronize", "Inner Focus" },
    { 65, "Alakazam", {55, 50, 45, 135, 85, 120}, F1M3, "Synchronize", "Inner Focus" },
    { 66, "Machop", {70, 80, 50, 35, 35, 35}, F1M3, "Guts", "No Guard" },
    { 67, "Machoke", {80, 100, 70, 50, 60, 45}, F1M3, "Guts", "No Guard" },
    { 68, "Machamp", {90, 130, 80, 65, 85, 55}, F1M3, "Guts", "No Guard" },
    { 69, "Bellsprout", {50, 75, 35, 70, 30, 40}, F1M1, "Chlorophyll", "Chlorophyll" },
    { 70, "Weepinbell", {65, 90, 50, 85, 45, 55}, F1M1, "Chlorophyll", "Chlorophyll" },
    { 71, "Victreebel", {80, 105, 65, 100, 60, 70}, F1M1, "Chlorophyll", "Chlorophyll" },
    { 72, "Tentacool", {40, 40, 35, 50, 100, 70}, F1M1, "Clear Body", "Liquid Ooze" },
    { 73, "Tentacruel", {80, 70, 65, 80, 120, 100}, F1M1, "Clear Body", "Liquid Ooze" },
    { 74, "Geodude", {40, 80, 100, 30, 30, 20}, F1M1, "Rock Head", "Sturdy" },
    { 75, "Graveler", {55, 95, 115, 45, 45, 35}, F1M1, "Rock Head", "Sturdy" },
    { 76, "Golem", {80, 120, 130, 55, 65, 45}, F1M1, "Rock Head", "Sturdy" },
    { 77, "Ponyta", {50, 85, 55, 65, 65, 90}, F1M1, "Run Away", "Flash Fire" },
    { 78, "Rapidash", {65, 100, 70, 80, 80, 105}, F1M1, "Run Away", "Flash Fire" },
    { 79, "Slowpoke", {90, 65, 65, 40, 40, 15}, F1M1, "Oblivious", "Own Tempo" },
    { 80, "Slowbro", {95, 75, 110, 100, 80, 30}, F1M1, "Oblivious", "Own Tempo" },
    { 81, "Magnemite", {25, 35, 70, 95, 55, 45}, Unknown, "Magnet Pull", "Sturdy" },
    { 82, "Magneton", {50, 60, 95, 120, 70, 70}, Unknown, "Magnet Pull", "Sturdy" },
    { 83, "Farfetchd", {52, 65, 55, 58, 62, 60}, F1M1, "Keen Eye", "Inner Focus" },
    { 84, "Doduo", {35, 85, 45, 35, 35, 75}, F1M1, "Run Away", "Early Bird" },
    { 85, "Dodrio", {60, 110, 70, 60, 60, 100}, F1M1, "Run Away", "Early Bird" },
    { 86, "Seel", {65, 45, 55, 45, 70, 45}, F1M1, "Thick Fat", "Hydration" },
    { 87, "Dewgong", {90, 70, 80, 70, 95, 70}, F1M1, "Thick Fat", "Hydration" },
    { 88, "Grimer", {80, 80, 50, 40, 50, 25}, F1M1, "Stench", "Sticky Hold" },
    { 89, "Muk", {105, 105, 75, 65, 100, 50}, F1M1, "Stench", "Sticky Hold" },
    { 90, "Shellder", {30, 65, 100, 45, 25, 40}, F1M1, "Shell Armor", "Skill Link" },
    { 91, "Cloyster", {50, 95, 180, 85, 45, 70}, F1M1, "Shell Armor", "Skill Link" },
    { 92, "Gastly", {30, 35, 30, 100, 35, 80}, F1M1, "Levitate", "Levitate" },
    { 93, "Haunter", {45, 50, 45, 115, 55, 95}, F1M1, "Levitate", "Levitate" },
    { 94, "Gengar", {60, 65, 60, 130, 75, 110}, F1M1, "Cursed Body", "Cursed Body" },
    { 95, "Onix", {35, 45, 160, 30, 45, 70}, F1M1, "Rock Head", "Sturdy" },
    { 96, "Drowzee", {60, 48, 45, 43, 90, 42}, F1M1, "Insomnia", "Forewarn" },
    { 97, "Hypno", {85, 73, 70, 73, 115, 67}, F1M1, "Insomnia", "Forewarn" },
    { 98, "Krabby", {30, 105, 90, 25, 25, 50}, F1M1, "Hyper Cutter", "Shell Armor" },
    { 99, "Kingler", {55, 130, 115, 50, 50, 75}, F1M1, "Hyper Cutter", "Shell Armor" },
    { 100, "Voltorb", {40, 30, 50, 55, 55, 100}, Unknown, "Soundproof", "Static" },
    { 101, "Electrode", {60, 50, 70, 80, 80, 140}, Unknown, "Soundproof", "Static" },
    { 102, "Exeggcute", {60, 40, 80, 60, 45, 40}, F1M1, "Chlorophyll", "Chlorophyll" },
    { 103, "Exeggutor", {95, 95, 85, 125, 65, 55}, F1M1, "Chlorophyll", "Chlorophyll" },
    { 104, "Cubone", {50, 50, 95, 40, 50, 35}, F1M1, "Rock Head", "Lightning Rod" },
    { 105, "Marowak", {60, 80, 110, 50, 80, 45}, F1M1, "Rock Head", "Lightning Rod" },
    { 106, "Hitmonlee", {50, 120, 53, 35, 110, 87}, MaleOnly, "Limber", "Reckless" },
    { 107, "Hitmonchan", {50, 105, 79, 35, 110, 76}, MaleOnly, "Keen Eye", "Iron Fist" },
    { 108, "Lickitung", {90, 55, 75, 60, 75, 30}, F1M1, "Own Tempo", "Oblivious" },
    { 109, "Koffing", {40, 65, 95, 60, 45, 35}, F1M1, "Levitate", "Neutralizing Gas" },
    { 110, "Weezing", {65, 90, 120, 85, 70, 60}, F1M1, "Levitate", "Neutralizing Gas" },
    { 111, "Rhyhorn", {80, 85, 95, 30, 30, 25}, F1M1, "Lightning Rod", "Rock Head" },
    { 112, "Rhydon", {105, 130, 120, 45, 45, 40}, F1M1, "Lightning Rod", "Rock Head" },
    { 113, "Chansey", {250, 5, 5, 35, 105, 50}, FemaleOnly, "Natural Cure", "Serene Grace" },
    { 114, "Tangela", {65, 55, 115, 100, 40, 60}, F1M1, "Chlorophyll", "Leaf Guard" },
    { 115, "Kangaskhan", {105, 95, 80, 40, 80, 90}, FemaleOnly, "Early Bird", "Scrappy" },
    { 116, "Horsea", {30, 40, 70, 70, 25, 60}, F1M1, "Swift Swim", "Sniper" },
    { 117, "Seadra", {55, 65, 95, 95, 45, 85}, F1M1, "Poison Point", "Sniper" },
    { 118, "Goldeen", {45, 67, 60, 35, 50, 63}, F1M1, "Swift Swim", "Water Veil" },
    { 119, "Seaking", {80, 92, 65, 65, 80, 68}, F1M1, "Swift Swim", "Water Veil" },
    { 120, "Staryu", {30, 45, 55, 70, 55, 85}, Unknown, "Illuminate", "Natural Cure" },
    { 121, "Starmie", {60, 75, 85, 100, 85, 115}, Unknown, "Illuminate", "Natural Cure" },
    { 122, "Mr-mime", {40, 45, 65, 100, 120, 90}, F1M1, "Soundproof", "Filter" },
    { 123, "Scyther", {70, 110, 80, 55, 80, 105}, F1M1, "Swarm", "Technician" },
    { 124, "Jynx", {65, 50, 35, 115, 95, 95}, FemaleOnly, "Oblivious", "Forewarn" },
    { 125, "Electabuzz", {65, 83, 57, 95, 85, 105}, F1M3, "Static", "Static" },
    { 126, "Magmar", {65, 95, 57, 100, 85, 93}, F1M3, "Flame Body", "Flame Body" },
    { 127, "Pinsir", {65, 125, 100, 55, 70, 85}, F1M1, "Hyper Cutter", "Mold Breaker" },
    { 128, "Tauros", {75, 100, 95, 40, 70, 110}, MaleOnly, "Intimidate", "Anger Point" },
    { 129, "Magikarp", {20, 10, 55, 15, 20, 80}, F1M1, "Swift Swim", "Swift Swim" },
    { 130, "Gyarados", {95, 125, 79, 60, 100, 81}, F1M1, "Intimidate", "Intimidate" },
    { 131, "Lapras", {130, 85, 80, 85, 95, 60}, F1M1, "Water Absorb", "Shell Armor" },
    { 132, "Ditto", {48, 48, 48, 48, 48, 48}, Unknown, "Limber", "Limber" },
    { 133, "Eevee", {55, 55, 50, 45, 65, 55}, F1M7, "Run Away", "Adaptability" },
    { 134, "Vaporeon", {130, 65, 60, 110, 95, 65}, F1M7, "Water Absorb", "Water Absorb" },
    { 135, "Jolteon", {65, 65, 60, 110, 95, 130}, F1M7, "Volt Absorb", "Volt Absorb" },
    { 136, "Flareon", {65, 130, 60, 95, 110, 65}, F1M7, "Flash Fire", "Flash Fire" },
    { 137, "Porygon", {65, 60, 70, 85, 75, 40}, Unknown, "Trace", "Download" },
    { 138, "Omanyte", {35, 40, 100, 90, 55, 35}, F1M7, "Swift Swim", "Shell Armor" },
    { 139, "Omastar", {70, 60, 125, 115, 70, 55}, F1M7, "Swift Swim", "Shell Armor" },
    { 140, "Kabuto", {30, 80, 90, 55, 45, 55}, F1M7, "Swift Swim", "Battle Armor" },
    { 141, "Kabutops", {60, 115, 105, 65, 70, 80}, F1M7, "Swift Swim", "Battle Armor" },
    { 142, "Aerodactyl", {80, 105, 65, 60, 75, 130}, F1M7, "Rock Head", "Pressure" },
    { 143, "Snorlax", {160, 110, 65, 65, 110, 30}, F1M7, "Immunity", "Thick Fat" },
    { 144, "Articuno", {90, 85, 100, 95, 125, 85}, Unknown, "Pressure", "Pressure" },
    { 145, "Zapdos", {90, 90, 85, 125, 90, 100}, Unknown, "Pressure", "Pressure" },
    { 146, "Moltres", {90, 100, 90, 125, 85, 90}, Unknown, "Pressure", "Pressure" },
    { 147, "Dratini", {41, 64, 45, 50, 50, 50}, F1M1, "Shed Skin", "Shed Skin" },
    { 148, "Dragonair", {61, 84, 65, 70, 70, 70}, F1M1, "Shed Skin", "Shed Skin" },
    { 149, "Dragonite", {91, 134, 95, 100, 100, 80}, F1M1, "Inner Focus", "Inner Focus" },
    { 150, "Mewtwo", {106, 110, 90, 154, 90, 130}, Unknown, "Pressure", "Pressure" },
    { 151, "Mew", {100, 100, 100, 100, 100, 100}, Unknown, "Synchronize", "Synchronize" },
    { 152, "Chikorita", {45, 49, 65, 49, 65, 45}, F1M7, "Overgrow", "Overgrow" },
    { 153, "Bayleef", {60, 62, 80, 63, 80, 60}, F1M7, "Overgrow", "Overgrow" },
    { 154, "Meganium", {80, 82, 100, 83, 100, 80}, F1M7, "Overgrow", "Overgrow" },
    { 155, "Cyndaquil", {39, 52, 43, 60, 50, 65}, F1M7, "Blaze", "Blaze" },
    { 156, "Quilava", {58, 64, 58, 80, 65, 80}, F1M7, "Blaze", "Blaze" },
    { 157, "Typhlosion", {78, 84, 78, 109, 85, 100}, F1M7, "Blaze", "Blaze" },
    { 158, "Totodile", {50, 65, 64, 44, 48, 43}, F1M7, "Torrent", "Torrent" },
    { 159, "Croconaw", {65, 80, 80, 59, 63, 58}, F1M7, "Torrent", "Torrent" },
    { 160, "Feraligatr", {85, 105, 100, 79, 83, 78}, F1M7, "Torrent", "Torrent" },
    { 161, "Sentret", {35, 46, 34, 35, 45, 20}, F1M1, "Run Away", "Keen Eye" },
    { 162, "Furret", {85, 76, 64, 45, 55, 90}, F1M1, "Run Away", "Keen Eye" },
    { 163, "Hoothoot", {60, 30, 30, 36, 56, 50}, F1M1, "Insomnia", "Keen Eye" },
    { 164, "Noctowl", {100, 50, 50, 76, 96, 70}, F1M1, "Insomnia", "Keen Eye" },
    { 165, "Ledyba", {40, 20, 30, 40, 80, 55}, F1M1, "Swarm", "Early Bird" },
    { 166, "Ledian", {55, 35, 50, 55, 110, 85}, F1M1, "Swarm", "Early Bird" },
    { 167, "Spinarak", {40, 60, 40, 40, 40, 30}, F1M1, "Swarm", "Insomnia" },
    { 168, "Ariados", {70, 90, 70, 60, 60, 40}, F1M1, "Swarm", "Insomnia" },
    { 169, "Crobat", {85, 90, 80, 70, 80, 130}, F1M1, "Inner Focus", "Inner Focus" },
    { 170, "Chinchou", {75, 38, 38, 56, 56, 67}, F1M1, "Volt Absorb", "Illuminate" },
    { 171, "Lanturn", {125, 58, 58, 76, 76, 67}, F1M1, "Volt Absorb", "Illuminate" },
    { 172, "Pichu", {20, 40, 15, 35, 35, 60}, F1M1, "Static", "Static" },
    { 173, "Cleffa", {50, 25, 28, 45, 55, 15}, F3M1, "Cute Charm", "Magic Guard" },
    { 174, "Igglybuff", {90, 30, 15, 40, 20, 15}, F3M1, "Cute Charm", "Competitive" },
    { 175, "Togepi", {35, 20, 65, 40, 65, 20}, F1M7, "Hustle", "Serene Grace" },
    { 176, "Togetic", {55, 40, 85, 80, 105, 40}, F1M7, "Hustle", "Serene Grace" },
    { 177, "Natu", {40, 50, 45, 70, 45, 70}, F1M1, "Synchronize", "Early Bird" },
    { 178, "Xatu", {65, 75, 70, 95, 70, 95}, F1M1, "Synchronize", "Early Bird" },
    { 179, "Mareep", {55, 40, 40, 65, 45, 35}, F1M1, "Static", "Static" },
    { 180, "Flaaffy", {70, 55, 55, 80, 60, 45}, F1M1, "Static", "Static" },
    { 181, "Ampharos", {90, 75, 75, 115, 90, 55}, F1M1, "Static", "Static" },
    { 182, "Bellossom", {75, 80, 85, 90, 100, 50}, F1M1, "Chlorophyll", "Chlorophyll" },
    { 183, "Marill", {70, 20, 50, 20, 50, 40}, F1M1, "Thick Fat", "Huge Power" },
    { 184, "Azumarill", {100, 50, 80, 50, 80, 50}, F1M1, "Thick Fat", "Huge Power" },
    { 185, "Sudowoodo", {70, 100, 115, 30, 65, 30}, F1M1, "Sturdy", "Rock Head" },
    { 186, "Politoed", {90, 75, 75, 90, 100, 70}, F1M1, "Water Absorb", "Damp" },
    { 187, "Hoppip", {35, 35, 40, 35, 55, 50}, F1M1, "Chlorophyll", "Leaf Guard" },
    { 188, "Skiploom", {55, 45, 50, 45, 65, 80}, F1M1, "Chlorophyll", "Leaf Guard" },
    { 189, "Jumpluff", {75, 55, 70, 55, 85, 110}, F1M1, "Chlorophyll", "Leaf Guard" },
    { 190, "Aipom", {55, 70, 55, 40, 55, 85}, F1M1, "Run Away", "Pickup" },
    { 191, "Sunkern", {30, 30, 30, 30, 30, 30}, F1M1, "Chlorophyll", "Solar Power" },
    { 192, "Sunflora", {75, 75, 55, 105, 85, 30}, F1M1, "Chlorophyll", "Solar Power" },
    { 193, "Yanma", {65, 65, 45, 75, 45, 95}, F1M1, "Speed Boost", "Compound Eyes" },
    { 194, "Wooper", {55, 45, 45, 25, 25, 15}, F1M1, "Damp", "Water Absorb" },
    { 195, "Quagsire", {95, 85, 85, 65, 65, 35}, F1M1, "Damp", "Water Absorb" },
    { 196, "Espeon", {65, 65, 60, 130, 95, 110}, F1M7, "Synchronize", "Synchronize" },
    { 197, "Umbreon", {95, 65, 110, 60, 130, 65}, F1M7, "Synchronize", "Synchronize" },
    { 198, "Murkrow", {60, 85, 42, 85, 42, 91}, F1M1, "Insomnia", "Super Luck" },
    { 199, "Slowking", {95, 75, 80, 100, 110, 30}, F1M1, "Oblivious", "Own Tempo" },
    { 200, "Misdreavus", {60, 60, 60, 85, 85, 85}, F1M1, "Levitate", "Levitate" },
    { 201, "Unown", {48, 72, 48, 72, 48, 48}, Unknown, "Levitate", "Levitate" },
    { 202, "Wobbuffet", {190, 33, 58, 33, 58, 33}, F1M1, "Shadow Tag", "Shadow Tag" },
    { 203, "Girafarig", {70, 80, 65, 90, 65, 85}, F1M1, "Inner Focus", "Early Bird" },
    { 204, "Pineco", {50, 65, 90, 35, 35, 15}, F1M1, "Sturdy", "Sturdy" },
    { 205, "Forretress", {75, 90, 140, 60, 60, 40}, F1M1, "Sturdy", "Sturdy" },
    { 206, "Dunsparce", {100, 70, 70, 65, 65, 45}, F1M1, "Serene Grace", "Run Away" },
    { 207, "Gligar", {65, 75, 105, 35, 65, 85}, F1M1, "Hyper Cutter", "Sand Veil" },
    { 208, "Steelix", {75, 85, 200, 55, 65, 30}, F1M1, "Rock Head", "Sturdy" },
    { 209, "Snubbull", {60, 80, 50, 40, 40, 30}, F3M1, "Intimidate", "Run Away" },
    { 210, "Granbull", {90, 120, 75, 60, 60, 45}, F3M1, "Intimidate", "Quick Feet" },
    { 211, "Qwilfish", {65, 95, 75, 55, 55, 85}, F1M1, "Poison Point", "Swift Swim" },
    { 212, "Scizor", {70, 130, 100, 55, 80, 65}, F1M1, "Swarm", "Technician" },
    { 213, "Shuckle", {20, 10, 230, 10, 230, 5}, F1M1, "Sturdy", "Gluttony" },
    { 214, "Heracross", {80, 125, 75, 40, 95, 85}, F1M1, "Swarm", "Guts" },
    { 215, "Sneasel", {55, 95, 55, 35, 75, 115}, F1M1, "Inner Focus", "Keen Eye" },
    { 216, "Teddiursa", {60, 80, 50, 50, 50, 40}, F1M1, "Pickup", "Quick Feet" },
    { 217, "Ursaring", {90, 130, 75, 75, 75, 55}, F1M1, "Guts", "Quick Feet" },
    { 218, "Slugma", {40, 40, 40, 70, 40, 20}, F1M1, "Magma Armor", "Flame Body" },
    { 219, "Magcargo", {60, 50, 120, 80, 80, 30}, F1M1, "Magma Armor", "Flame Body" },
    { 220, "Swinub", {50, 50, 40, 30, 30, 50}, F1M1, "Oblivious", "Snow Cloak" },
    { 221, "Piloswine", {100, 100, 80, 60, 60, 50}, F1M1, "Oblivious", "Snow Cloak" },
    { 222, "Corsola", {55, 55, 95, 65, 95, 35}, F3M1, "Hustle", "Natural Cure" },
    { 223, "Remoraid", {35, 65, 35, 65, 35, 65}, F1M1, "Hustle", "Sniper" },
    { 224, "Octillery", {75, 105, 75, 105, 75, 45}, F1M1, "Suction Cups", "Sniper" },
    { 225, "Delibird", {45, 55, 45, 65, 45, 75}, F1M1, "Vital Spirit", "Hustle" },
    { 226, "Mantine", {65, 40, 70, 80, 140, 70}, F1M1, "Swift Swim", "Water Absorb" },
    { 227, "Skarmory", {65, 80, 140, 40, 70, 70}, F1M1, "Keen Eye", "Sturdy" },
    { 228, "Houndour", {45, 60, 30, 80, 50, 65}, F1M1, "Early Bird", "Flash Fire" },
    { 229, "Houndoom", {75, 90, 50, 110, 80, 95}, F1M1, "Early Bird", "Flash Fire" },
    { 230, "Kingdra", {75, 95, 95, 95, 95, 85}, F1M1, "Swift Swim", "Sniper" },
    { 231, "Phanpy", {90, 60, 60, 40, 40, 40}, F1M1, "Pickup", "Pickup" },
    { 232, "Donphan", {90, 120, 120, 60, 60, 50}, F1M1, "Sturdy", "Sturdy" },
    { 233, "Porygon2", {85, 80, 90, 105, 95, 60}, Unknown, "Trace", "Download" },
    { 234, "Stantler", {73, 95, 62, 85, 65, 85}, F1M1, "Intimidate", "Frisk" },
    { 235, "Smeargle", {55, 20, 35, 20, 45, 75}, F1M1, "Own Tempo", "Technician" },
    { 236, "Tyrogue", {35, 35, 35, 35, 35, 35}, MaleOnly, "Guts", "Steadfast" },
    { 237, "Hitmontop", {50, 95, 95, 35, 110, 70}, MaleOnly, "Intimidate", "Technician" },
    { 238, "Smoochum", {45, 30, 15, 85, 65, 65}, FemaleOnly, "Oblivious", "Forewarn" },
    { 239, "Elekid", {45, 63, 37, 65, 55, 95}, F1M3, "Static", "Static" },
    { 240, "Magby", {45, 75, 37, 70, 55, 83}, F1M3, "Flame Body", "Flame Body" },
    { 241, "Miltank", {95, 80, 105, 40, 70, 100}, FemaleOnly, "Thick Fat", "Scrappy" },
    { 242, "Blissey", {255, 10, 10, 75, 135, 55}, FemaleOnly, "Natural Cure", "Serene Grace" },
    { 243, "Raikou", {90, 85, 75, 115, 100, 115}, Unknown, "Pressure", "Pressure" },
    { 244, "Entei", {115, 115, 85, 90, 75, 100}, Unknown, "Pressure", "Pressure" },
    { 245, "Suicune", {100, 75, 115, 90, 115, 85}, Unknown, "Pressure", "Pressure" },
    { 246, "Larvitar", {50, 64, 50, 45, 50, 41}, F1M1, "Guts", "Guts" },
    { 247, "Pupitar", {70, 84, 70, 65, 70, 51}, F1M1, "Shed Skin", "Shed Skin" },
    { 248, "Tyranitar", {100, 134, 110, 95, 100, 61}, F1M1, "Sand Stream", "Sand Stream" },
    { 249, "Lugia", {106, 90, 130, 90, 154, 110}, Unknown, "Pressure", "Pressure" },
    { 250, "Ho-oh", {106, 130, 90, 110, 154, 90}, Unknown, "Pressure", "Pressure" },
    { 251, "Celebi", {100, 100, 100, 100, 100, 100}, Unknown, "Natural Cure", "Natural Cure" },
    { 252, "Treecko", {40, 45, 35, 65, 55, 70}, F1M7, "Overgrow", "Overgrow" },
    { 253, "Grovyle", {50, 65, 45, 85, 65, 95}, F1M7, "Overgrow", "Overgrow" },
    { 254, "Sceptile", {70, 85, 65, 105, 85, 120}, F1M7, "Overgrow", "Overgrow" },
    { 255, "Torchic", {45, 60, 40, 70, 50, 45}, F1M7, "Blaze", "Blaze" },
    { 256, "Combusken", {60, 85, 60, 85, 60, 55}, F1M7, "Blaze", "Blaze" },
    { 257, "Blaziken", {80, 120, 70, 110, 70, 80}, F1M7, "Blaze", "Blaze" },
    { 258, "Mudkip", {50, 70, 50, 50, 50, 40}, F1M7, "Torrent", "Torrent" },
    { 259, "Marshtomp", {70, 85, 70, 60, 70, 50}, F1M7, "Torrent", "Torrent" },
    { 260, "Swampert", {100, 110, 90, 85, 90, 60}, F1M7, "Torrent", "Torrent" },
    { 261, "Poochyena", {35, 55, 35, 30, 30, 35}, F1M1, "Run Away", "Quick Feet" },
    { 262, "Mightyena", {70, 90, 70, 60, 60, 70}, F1M1, "Intimidate", "Quick Feet" },
    { 263, "Zigzagoon", {38, 30, 41, 30, 41, 60}, F1M1, "Pickup", "Gluttony" },
    { 264, "Linoone", {78, 70, 61, 50, 61, 100}, F1M1, "Pickup", "Gluttony" },
    { 265, "Wurmple", {45, 45, 35, 20, 30, 20}, F1M1, "Shield Dust", "Shield Dust" },
    { 266, "Silcoon", {50, 35, 55, 25, 25, 15}, F1M1, "Shed Skin", "Shed Skin" },
    { 267, "Beautifly", {60, 70, 50, 90, 50, 65}, F1M1, "Swarm", "Swarm" },
    { 268, "Cascoon", {50, 35, 55, 25, 25, 15}, F1M1, "Shed Skin", "Shed Skin" },
    { 269, "Dustox", {60, 50, 70, 50, 90, 65}, F1M1, "Shield Dust", "Shield Dust" },
    { 270, "Lotad", {40, 30, 30, 40, 50, 30}, F1M1, "Swift Swim", "Rain Dish" },
    { 271, "Lombre", {60, 50, 50, 60, 70, 50}, F1M1, "Swift Swim", "Rain Dish" },
    { 272, "Ludicolo", {80, 70, 70, 90, 100, 70}, F1M1, "Swift Swim", "Rain Dish" },
    { 273, "Seedot", {40, 40, 50, 30, 30, 30}, F1M1, "Chlorophyll", "Early Bird" },
    { 274, "Nuzleaf", {70, 70, 40, 60, 40, 60}, F1M1, "Chlorophyll", "Early Bird" },
    { 275, "Shiftry", {90, 100, 60, 90, 60, 80}, F1M1, "Chlorophyll", "Wind Rider" },
    { 276, "Taillow", {40, 55, 30, 30, 30, 85}, F1M1, "Guts", "Guts" },
    { 277, "Swellow", {60, 85, 60, 50, 50, 125}, F1M1, "Guts", "Guts" },
    { 278, "Wingull", {40, 30, 30, 55, 30, 85}, F1M1, "Keen Eye", "Hydration" },
    { 279, "Pelipper", {60, 50, 100, 85, 70, 65}, F1M1, "Keen Eye", "Drizzle" },
    { 280, "Ralts", {28, 25, 25, 45, 35, 40}, F1M1, "Synchronize", "Trace" },
    { 281, "Kirlia", {38, 35, 35, 65, 55, 50}, F1M1, "Synchronize", "Trace" },
    { 282, "Gardevoir", {68, 65, 65, 125, 115, 80}, F1M1, "Synchronize", "Trace" },
    { 283, "Surskit", {40, 30, 32, 50, 52, 65}, F1M1, "Swift Swim", "Swift Swim" },
    { 284, "Masquerain", {70, 60, 62, 80, 82, 60}, F1M1, "Intimidate", "Intimidate" },
    { 285, "Shroomish", {60, 40, 60, 40, 60, 35}, F1M1, "Effect Spore", "Poison Heal" },
    { 286, "Breloom", {60, 130, 80, 60, 60, 70}, F1M1, "Effect Spore", "Poison Heal" },
    { 287, "Slakoth", {60, 60, 60, 35, 35, 30}, F1M1, "Truant", "Truant" },
    { 288, "Vigoroth", {80, 80, 80, 55, 55, 90}, F1M1, "Vital Spirit", "Vital Spirit" },
    { 289, "Slaking", {150, 160, 100, 95, 65, 100}, F1M1, "Truant", "Truant" },
    { 290, "Nincada", {31, 45, 90, 30, 30, 40}, F1M1, "Compound Eyes", "Compound Eyes" },
    { 291, "Ninjask", {61, 90, 45, 50, 50, 160}, F1M1, "Speed Boost", "Speed Boost" },
    { 292, "Shedinja", {1, 90, 45, 30, 30, 40}, Unknown, "Wonder Guard", "Wonder Guard" },
    { 293, "Whismur", {64, 51, 23, 51, 23, 28}, F1M1, "Soundproof", "Soundproof" },
    { 294, "Loudred", {84, 71, 43, 71, 43, 48}, F1M1, "Soundproof", "Soundproof" },
    { 295, "Exploud", {104, 91, 63, 91, 63, 68}, F1M1, "Soundproof", "Soundproof" },
    { 296, "Makuhita", {72, 60, 30, 20, 30, 25}, F1M3, "Thick Fat", "Guts" },
    { 297, "Hariyama", {144, 120, 60, 40, 60, 50}, F1M3, "Thick Fat", "Guts" },
    { 298, "Azurill", {50, 20, 40, 20, 40, 20}, F3M1, "Thick Fat", "Huge Power" },
    { 299, "Nosepass", {30, 45, 135, 45, 90, 30}, F1M1, "Sturdy", "Magnet Pull" },
    { 300, "Skitty", {50, 45, 45, 35, 35, 50}, F3M1, "Cute Charm", "Normalize" },
    { 301, "Delcatty", {70, 65, 65, 55, 55, 70}, F3M1, "Cute Charm", "Normalize" },
    { 302, "Sableye", {50, 75, 75, 65, 65, 50}, F1M1, "Keen Eye", "Stall" },
    { 303, "Mawile", {50, 85, 85, 55, 55, 50}, F1M1, "Hyper Cutter", "Intimidate" },
    { 304, "Aron", {50, 70, 100, 40, 40, 30}, F1M1, "Sturdy", "Rock Head" },
    { 305, "Lairon", {60, 90, 140, 50, 50, 40}, F1M1, "Sturdy", "Rock Head" },
    { 306, "Aggron", {70, 110, 180, 60, 60, 50}, F1M1, "Sturdy", "Rock Head" },
    { 307, "Meditite", {30, 40, 55, 40, 55, 60}, F1M1, "Pure Power", "Pure Power" },
    { 308, "Medicham", {60, 60, 75, 60, 75, 80}, F1M1, "Pure Power", "Pure Power" },
    { 309, "Electrike", {40, 45, 40, 65, 40, 65}, F1M1, "Static", "Lightning Rod" },
    { 310, "Manectric", {70, 75, 60, 105, 60, 105}, F1M1, "Static", "Lightning Rod" },
    { 311, "Plusle", {60, 50, 40, 85, 75, 95}, F1M1, "Plus", "Plus" },
    { 312, "Minun", {60, 40, 50, 75, 85, 95}, F1M1, "Minus", "Minus" },
    { 313, "Volbeat", {65, 73, 55, 47, 75, 85}, MaleOnly, "Illuminate", "Swarm" },
    { 314, "Illumise", {65, 47, 55, 73, 75, 85}, FemaleOnly, "Oblivious", "Tinted Lens" },
    { 315, "Roselia", {50, 60, 45, 100, 80, 65}, F1M1, "Natural Cure", "Poison Point" },
    { 316, "Gulpin", {70, 43, 53, 43, 53, 40}, F1M1, "Liquid Ooze", "Sticky Hold" },
    { 317, "Swalot", {100, 73, 83, 73, 83, 55}, F1M1, "Liquid Ooze", "Sticky Hold" },
    { 318, "Carvanha", {45, 90, 20, 65, 20, 65}, F1M1, "Rough Skin", "Rough Skin" },
    { 319, "Sharpedo", {70, 120, 40, 95, 40, 95}, F1M1, "Rough Skin", "Rough Skin" },
    { 320, "Wailmer", {130, 70, 35, 70, 35, 60}, F1M1, "Water Veil", "Oblivious" },
    { 321, "Wailord", {170, 90, 45, 90, 45, 60}, F1M1, "Water Veil", "Oblivious" },
    { 322, "Numel", {60, 60, 40, 65, 45, 35}, F1M1, "Oblivious", "Simple" },
    { 323, "Camerupt", {70, 100, 70, 105, 75, 40}, F1M1, "Magma Armor", "Solid Rock" },
    { 324, "Torkoal", {70, 85, 140, 85, 70, 20}, F1M1, "White Smoke", "Drought" },
    { 325, "Spoink", {60, 25, 35, 70, 80, 60}, F1M1, "Thick Fat", "Own Tempo" },
    { 326, "Grumpig", {80, 45, 65, 90, 110, 80}, F1M1, "Thick Fat", "Own Tempo" },
    { 327, "Spinda", {60, 60, 60, 60, 60, 60}, F1M1, "Own Tempo", "Tangled Feet" },
    { 328, "Trapinch", {45, 100, 45, 45, 45, 10}, F1M1, "Hyper Cutter", "Arena Trap" },
    { 329, "Vibrava", {50, 70, 50, 50, 50, 70}, F1M1, "Levitate", "Levitate" },
    { 330, "Flygon", {80, 100, 80, 80, 80, 100}, F1M1, "Levitate", "Levitate" },
    { 331, "Cacnea", {50, 85, 40, 85, 40, 35}, F1M1, "Sand Veil", "Sand Veil" },
    { 332, "Cacturne", {70, 115, 60, 115, 60, 55}, F1M1, "Sand Veil", "Sand Veil" },
    { 333, "Swablu", {45, 40, 60, 40, 75, 50}, F1M1, "Natural Cure", "Natural Cure" },
    { 334, "Altaria", {75, 70, 90, 70, 105, 80}, F1M1, "Natural Cure", "Natural Cure" },
    { 335, "Zangoose", {73, 115, 60, 60, 60, 90}, F1M1, "Immunity", "Immunity" },
    { 336, "Seviper", {73, 100, 60, 100, 60, 65}, F1M1, "Shed Skin", "Shed Skin" },
    { 337, "Lunatone", {70, 55, 65, 95, 85, 70}, Unknown, "Levitate", "Levitate" },
    { 338, "Solrock", {70, 95, 85, 55, 65, 70}, Unknown, "Levitate", "Levitate" },
    { 339, "Barboach", {50, 48, 43, 46, 41, 60}, F1M1, "Oblivious", "Anticipation" },
    { 340, "Whiscash", {110, 78, 73, 76, 71, 60}, F1M1, "Oblivious", "Anticipation" },
    { 341, "Corphish", {43, 80, 65, 50, 35, 35}, F1M1, "Hyper Cutter", "Shell Armor" },
    { 342, "Crawdaunt", {63, 120, 85, 90, 55, 55}, F1M1, "Hyper Cutter", "Shell Armor" },
    { 343, "Baltoy", {40, 40, 55, 40, 70, 55}, Unknown, "Levitate", "Levitate" },
    { 344, "Claydol", {60, 70, 105, 70, 120, 75}, Unknown, "Levitate", "Levitate" },
    { 345, "Lileep", {66, 41, 77, 61, 87, 23}, F1M7, "Suction Cups", "Suction Cups" },
    { 346, "Cradily", {86, 81, 97, 81, 107, 43}, F1M7, "Suction Cups", "Suction Cups" },
    { 347, "Anorith", {45, 95, 50, 40, 50, 75}, F1M7, "Battle Armor", "Battle Armor" },
    { 348, "Armaldo", {75, 125, 100, 70, 80, 45}, F1M7, "Battle Armor", "Battle Armor" },
    { 349, "Feebas", {20, 15, 20, 10, 55, 80}, F1M1, "Swift Swim", "Oblivious" },
    { 350, "Milotic", {95, 60, 79, 100, 125, 81}, F1M1, "Marvel Scale", "Competitive" },
    { 351, "Castform", {70, 70, 70, 70, 70, 70}, F1M1, "Forecast", "Forecast" },
    { 352, "Kecleon", {60, 90, 70, 60, 120, 40}, F1M1, "Color Change", "Color Change" },
    { 353, "Shuppet", {44, 75, 35, 63, 33, 45}, F1M1, "Insomnia", "Frisk" },
    { 354, "Banette", {64, 115, 65, 83, 63, 65}, F1M1, "Insomnia", "Frisk" },
    { 355, "Duskull", {20, 40, 90, 30, 90, 25}, F1M1, "Levitate", "Levitate" },
    { 356, "Dusclops", {40, 70, 130, 60, 130, 25}, F1M1, "Pressure", "Pressure" },
    { 357, "Tropius", {99, 68, 83, 72, 87, 51}, F1M1, "Chlorophyll", "Solar Power" },
    { 358, "Chimecho", {65, 50, 70, 95, 80, 65}, F1M1, "Levitate", "Levitate" },
    { 359, "Absol", {65, 130, 60, 75, 60, 75}, F1M1, "Pressure", "Super Luck" },
    { 360, "Wynaut", {95, 23, 48, 23, 48, 23}, F1M1, "Shadow Tag", "Shadow Tag" },
    { 361, "Snorunt", {50, 50, 50, 50, 50, 50}, F1M1, "Inner Focus", "Ice Body" },
    { 362, "Glalie", {80, 80, 80, 80, 80, 80}, F1M1, "Inner Focus", "Ice Body" },
    { 363, "Spheal", {70, 40, 50, 55, 50, 25}, F1M1, "Thick Fat", "Ice Body" },
    { 364, "Sealeo", {90, 60, 70, 75, 70, 45}, F1M1, "Thick Fat", "Ice Body" },
    { 365, "Walrein", {110, 80, 90, 95, 90, 65}, F1M1, "Thick Fat", "Ice Body" },
    { 366, "Clamperl", {35, 64, 85, 74, 55, 32}, F1M1, "Shell Armor", "Shell Armor" },
    { 367, "Huntail", {55, 104, 105, 94, 75, 52}, F1M1, "Swift Swim", "Swift Swim" },
    { 368, "Gorebyss", {55, 84, 105, 114, 75, 52}, F1M1, "Swift Swim", "Swift Swim" },
    { 369, "Relicanth", {100, 90, 130, 45, 65, 55}, F1M7, "Swift Swim", "Rock Head" },
    { 370, "Luvdisc", {43, 30, 55, 40, 65, 97}, F3M1, "Swift Swim", "Swift Swim" },
    { 371, "Bagon", {45, 75, 60, 40, 30, 50}, F1M1, "Rock Head", "Rock Head" },
    { 372, "Shelgon", {65, 95, 100, 60, 50, 50}, F1M1, "Rock Head", "Rock Head" },
    { 373, "Salamence", {95, 135, 80, 110, 80, 100}, F1M1, "Intimidate", "Intimidate" },
    { 374, "Beldum", {40, 55, 80, 35, 60, 30}, Unknown, "Clear Body", "Clear Body" },
    { 375, "Metang", {60, 75, 100, 55, 80, 50}, Unknown, "Clear Body", "Clear Body" },
    { 376, "Metagross", {80, 135, 130, 95, 90, 70}, Unknown, "Clear Body", "Clear Body" },
    { 377, "Regirock", {80, 100, 200, 50, 100, 50}, Unknown, "Clear Body", "Clear Body" },
    { 378, "Regice", {80, 50, 100, 100, 200, 50}, Unknown, "Clear Body", "Clear Body" },
    { 379, "Registeel", {80, 75, 150, 75, 150, 50}, Unknown, "Clear Body", "Clear Body" },
    { 380, "Latias", {80, 80, 90, 110, 130, 110}, FemaleOnly, "Levitate", "Levitate" },
    { 381, "Latios", {80, 90, 80, 130, 110, 110}, MaleOnly, "Levitate", "Levitate" },
    { 382, "Kyogre", {100, 100, 90, 150, 140, 90}, Unknown, "Drizzle", "Drizzle" },
    { 383, "Groudon", {100, 150, 140, 100, 90, 90}, Unknown, "Drought", "Drought" },
    { 384, "Rayquaza", {105, 150, 90, 150, 90, 95}, Unknown, "Air Lock", "Air Lock" },
    { 385, "Jirachi", {100, 100, 100, 100, 100, 100}, Unknown, "Serene Grace", "Serene Grace" },
    { 386, "Deoxys", {50, 150, 50, 150, 50, 150}, Unknown, "Pressure", "Pressure" }
};

const Encounter StaticEncounters[] = {
        {Starters,      "Bulbasaur",    5},
        {Starters,      "Charmander",   5},
        {Starters,      "Squirtle",     5},
        {Fossils,       "Omanyte",      5},
        {Fossils,       "Kabuto",       5},
        {Fossils,       "Aerodactyl",   5},
        {Gifts,         "Hitmonlee",    25},
        {Gifts,         "Hitmonchan",   25},
        {Gifts,         "Magikarp",     5},
        {Gifts,         "Lapras",       25},
        {Gifts,         "Eevee",        25},
        {Gifts,         "Togepi",       5},
        {GameCorner,    "Abra",         9},
        {GameCorner,    "Clefairy",     8},
        {GameCorner,    "Scyther",      25},
        {GameCorner,    "Pinsir",       25},
        {GameCorner,    "Dratini",      18},
        {GameCorner,    "Porygon",      26},
        {Stationary,    "Snorlax",      30},
        {Stationary,    "Hypno",        30},
        {Stationary,    "Electrode",    34},
        {Legends,       "Articuno",     50},
        {Legends,       "Zapdos",       50},
        {Legends,       "Moltres",      50},
        {Legends,       "Mewtwo",       70},
        {Events,        "Deoxys",       30},
        {Events,        "Lugia",        70},
        {Events,        "Ho-Oh",        70},
        {Roamers,       "Raikou",       50},
        {Roamers,       "Entei",        50},
        {Roamers,       "Suicune",      50},
};

const char*
PokemonGetNatureString(uint8_t key) {
    if (key > 25)
        return "Huh?!";
    return natures[key].name;
}

int
PokemonGetNatureIndex(const char* nat) {
    for (size_t i = 0; i < sizeof(natures)/sizeof(natures[0]); i++) {
        if (!strcmp(nat, natures[i].name)) {
            return natures[i].key;
        }
    }
    return -1;
}

const char*
PokemonGetGenderString(uint8_t key) {
    switch (key)
    {
    case 0:
    case 1:
        return GENDER_STRINGS[key];
    default:
        return GENDER_STRINGS[2];
    }
}

uint8_t
PokemonIsShiny(uint32_t PID, uint32_t TID, uint32_t SID) {
    uint16_t psv = (TID ^ SID) ^ (PID >> 16) ^ (PID & 0xFFFF);

    if (psv == 0)
        // Square
        return 2;
    else if (psv < 8)
        // Star
        return 1;
    else
        // None
        return 0;
}

uint8_t
PokemonGetGender(uint32_t PID, GenderRatio gr) {
    switch (gr)
        {
        case 0:
        case 1:
        case 3:
            return gr;
        default:
            return (PID & 255) < gr;
        }
};

// https://bulbapedia.bulbagarden.net/wiki/Hidden_Power_(move)/Calculation
uint8_t
PokemonGetHPValue(const uint8_t *IVs) {
    int sum = 0;
    int i, j;
    for (i = 0, j = 1; i < 3; i++, j *= 2) {
        sum += (IVs[i] % 2) * j;
    }
    sum += (IVs[5] % 2) * 8;
    sum += (IVs[3] % 2) * 16;
    sum += (IVs[4] % 2) * 32;

    return (sum * 15) / 63;
}

uint8_t
PokemonGetHP(const uint8_t *IVs) {
    int sum = 0;
    int i, j;
    for (i = 0, j = 1; i < 3; i++, j *= 2) {
        sum += ((IVs[i] >> 1) & 1) * j;
    }
    sum += ((IVs[5] >> 1) & 1) * 8;
    sum += ((IVs[3] >> 1) & 1) * 16;
    sum += ((IVs[4] >> 1) & 1) * 32;

    return (int)((sum * 40) / 63) + 30;
}

const Unown unown[28] = {
        { 'A', MONEAN   },
        { 'B', RIXY     },
        { 'C', LIPTOO   },
        { 'D', LIPTOO   },
        { 'E', WEEPETH  },
        { 'F', SCUFIB   },
        { 'G', SCUFIB   },
        { 'H', LIPTOO   },
        { 'I', WEEPETH  },
        { 'J', DILFORD  },
        { 'K', SCUFIB   },
        { 'L', DILFORD  },
        { 'M', RIXY     },
        { 'N', WEEPETH  },
        { 'O', LIPTOO   },
        { 'P', DILFORD  },
        { 'Q', DILFORD  },
        { 'R', DILFORD  },
        { 'S', WEEPETH  },
        { 'T', SCUFIB   },
        { 'U', LIPTOO   },
        { 'V', RIXY     },
        { 'W', RIXY     },
        { 'X', RIXY     },
        { 'Y', SCUFIB   },
        { 'Z', VIAPOIS  },
        { '?', MONEAN   },
        { '!', VIAPOIS  },
};

// https://bulbapedia.bulbagarden.net/wiki/Personality_value#Unown.27s_letter
// 0000011 00000011 00000011 00000011 = (0x3030303 & 3000000) = (00000011 00000000 00000000 00000000) >> 18 = 1100 0000
// 0000011 00000011 00000011 00000011 = (0x3030303 & 30000  ) = (         00000011 00000000 00000000) >> 12 = 0011 0000
// 0000011 00000011 00000011 00000011 = (0x3030303 & 300  ) =   (                  00000011 00000000) >> 6  = 0000 1100
// 0000011 00000011 00000011 00000011 = (0x3030303 & 3  ) =   (                             00000011)

uint8_t
PokemonGetUnownLetter(uint32_t PID) {
    return (
        ((PID & 0x3000000) >> 18) |
        ((PID & 0x30000) >> 12) |
        ((PID & 0x300) >> 6) |
        (PID & 0x3)) % 28;
}

char
PokemonGetUnownSymbolChar(int val) {
    if (val > 25) {
        switch (val) {
            case 26:
                return '!';
            case 27:
                return '?';
            default:
                return '$';
        }
    } else
        return (char)(val + 65);
}


int
PokemonSearchIndex(const char* name) {
    for (size_t i = 0; i < MAX_DEX; i++) {
        if (!strcmp(name, pokemon[i].name)) {
            return (int)(pokemon[i].dex - 1);
        }
    }
    return -1;
}

void
PokemonListNatures() {
    fprintf(stdout, "\n----Nature Information----\n");
    for (size_t i = 0; i < 25; i++) {
        const char* stat_up = "None";
        const char* stat_down = "None";
        for (size_t s = 0; s < 5; s++) {
            if (nature_multiplier_table[i][s] > 1.0) {
                stat_up = stats[s + 1];
            }
            if (nature_multiplier_table[i][s] < 1.0) {
                stat_down = stats[s + 1];
            }
        }
        fprintf(stdout, "%d | %s | +%s -%s\n", natures[i].key, natures[i].name, stat_up, stat_down);
    }
    fprintf(stdout, "\n");
}

void
PokemonListShinyTypes() {
    fprintf(stdout, "\n----Shiny Type Strings----\n");
    for (size_t i = 0; i < 3; i++) {
        fprintf(stdout, "%s\n", SHINY_TYPES[i]);
    }
    fprintf(stdout, "\n");
}

void
PokemonListHiddenPowerTypes() {
    fprintf(stdout, "\n----Hidden Power Strings----\n");
    for (size_t i = 0; i < 16; i++) {
        fprintf(stdout, "%s\n", HP[i].type);
    }
    fprintf(stdout, "\n");
}

void
PokemonListGenderStrings() {
    fprintf(stdout, "\n----Gender Strings----\n");
    for (size_t i = 0; i < 3; i++) {
        fprintf(stdout, "%s\n", GENDER_STRINGS[i]);
    }
    fprintf(stdout, "\n");
}

uint8_t
PokemonFindAbilityIndex(uint16_t dex, const char* name) {
    if (dex > MAX_DEX || name == NULL) return 2;
    Pokemon mon = pokemon[dex - 1];

    fprintf(stdout, "%s\n", mon.name);

    int ab0 = strcmp(name, mon.ab0);
    int ab1 = strcmp(name, mon.ab1);

    if (ab0 & ab1) return 2;
    if (!ab0) return 0;
    if (!ab1) return 1;
}
