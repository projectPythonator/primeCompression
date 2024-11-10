#pragma once
#include "rb5GlobalIncludes.h"

const size_t BITS_PER_MASK = 8;
const size_t RB5_PRIMORIAL = 30;
const size_t RB5_PHI = BITS_PER_MASK;

const uint8_t MASK_LOOKUP[RB5_PRIMORIAL][BITS_PER_MASK] = {
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {254, 253, 251, 247, 239, 223, 191, 127},
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {253, 223, 239, 254, 127, 247, 251, 191},
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {251, 239, 254, 191, 253, 127, 247, 223},
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {247, 254, 191, 223, 251, 253, 127, 239}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {239, 127, 253, 251, 223, 191, 254, 247},
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {223, 247, 127, 253, 191, 254, 239, 251},
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {191, 251, 247, 127, 254, 239, 223, 253},
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {127, 191, 223, 239, 247, 251, 253, 254}};

const uint8_t MASK_TO_OFFSET[129] = {0,1,7,0,11,0,0,0,13,0,0,0,0,0,0,0,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,29};

const uint8_t OFFSET_TO_MASK[RB5_PRIMORIAL] = {0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 4, 0, 8, 0, 0, 0, 16, 0, 32, 0, 0, 0, 64, 0, 0, 0, 0, 0, 128};

const uint8_t JUMP_VALUE[BITS_PER_MASK] = {1, 7, 11, 13, 17, 19, 23, 29}; 

const uint8_t FIRST_16_PRIMES[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53}; 

