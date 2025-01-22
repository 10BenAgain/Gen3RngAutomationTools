#ifndef RNG_H
#define RNG_H

#include <stdlib.h>
#include <stdint.h>
#include "encounter_table.h"
#include "locations.h"

/* Found by calculating the modular multiplicative inverse of the LCRNG prime numbers
 * We know that Next Seed = (a * Last Seed + C) % m
 * Where m is the modulus (2^32)
 * a is the multiplier (0x41C64E6D)
 * c is the increment (0x6073)
 * Using the extended Euclidean algorithm we can say that ax + by = gcd(a,b)
 * 0x4702CBA * (2^32 + 1) + -289805467 * 0x41C64E6D = 1
 * Since gcd(a, b) in this case is 1, we can use ax = 1 (mod m) to calculate the inverse
 * It becomes the value we need to multiply the multiplier by so that the remainder of that number divided by mod m is 1
*/

#define MULTIPLIER  0x41C64E6D
#define INCREMENT   0x6073
#define MOD         4294967295 //2^32
#define AINVERSE    0xEEB9EB65
#define CINVERSE    0xA3561A1
#define IV_MASK     0x1F
#define IV_SHIFT    5

#define TID_2_SHINY_TID(TID, PID) ((TID) ^ ((PID) >> 16) ^ ((PID) & 0xFFFF))

typedef struct {
    uint32_t multiplier;
    uint32_t add;
} Jump;

typedef struct {
    Jump jump[32];
} JumpTable;

/* Result from generating jump table with gen 3 LCRNG values (0x6073 , 0x41C64E6D) */
static const Jump GEN3_JUMP_TABLE[32] = {
        { 0x41C64E6D , 0x6073     },
        { 0xC2A29A69 , 0xE97E7B6A },
        { 0xEE067F11 , 0x31B0DDE4 },
        { 0xCFDDDF21 , 0x67DBB608 },
        { 0x5F748241 , 0xCBA72510 },
        { 0x8B2E1481 , 0x1D29AE20 },
        { 0x76006901 , 0xBA84EC40 },
        { 0x1711D201 , 0x79F01880 },
        { 0xBE67A401 , 0x8793100  },
        { 0xDDDF4801 , 0x6B566200 },
        { 0x3FFE9001 , 0x803CC400 },
        { 0x90FD2001 , 0xA6B98800 },
        { 0x65FA4001 , 0xE6731000 },
        { 0xDBF48001 , 0x30E62000 },
        { 0xF7E90001 , 0xF1CC4000 },
        { 0xEFD20001 , 0x23988000 },
        { 0xDFA40001 , 0x47310000 },
        { 0xBF480001 , 0x8E620000 },
        { 0x7E900001 , 0x1CC40000 },
        { 0xFD200001 , 0x39880000 },
        { 0xFA400001 , 0x73100000 },
        { 0xF4800001 , 0xE6200000 },
        { 0xE9000001 , 0xCC400000 },
        { 0xD2000001 , 0x98800000 },
        { 0xA4000001 , 0x31000000 },
        { 0x48000001 , 0x62000000 },
        { 0x90000001 , 0xC4000000 },
        { 0x20000001 , 0x88000000 },
        { 0x40000001 , 0x10000000 },
        { 0x80000001 , 0x20000000 },
        { 0x1 , 0x40000000        },
        { 0x1 , 0x80000000        }
};

/*
 * Never used except to generate the above table
 * There is no need to generate the table multiple times
*/
JumpTable *_computeJumpTable();
uint32_t RNGJumpAhead(const Jump table[32], uint32_t seed, uint32_t advances);

void RNGIncrementSeed(uint32_t *seed, uint32_t advances);
void RNGDecrementSeed(uint32_t *seed, uint32_t advances);

uint32_t RNGNexSeed(const uint32_t *seed);
uint16_t RNGNextUShort(uint16_t max, uint32_t seed);

uint8_t RNGCalculateLevel(Slot s, uint32_t seed);

#endif
