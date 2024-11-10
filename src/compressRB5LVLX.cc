#include "rb5FileIOHeader.h"
#include "rb5GlobalConstants.h" 
#include <bit>
#include <cmath>
#include <string>

std::vector<size_t> DAT_LOOKUP;
std::vector<size_t> DAT_BYTE_INDS;
std::vector<uint8_t> DAT_MASKS;
std::vector<uint8_t> BUFFER_IN;
std::vector<uint8_t> BUFFER_OUT;

size_t BUFFER_IN_SIZE = 0;
size_t BUFFER_OUT_SIZE = 0;
size_t LOOKUP_SIZE = 0;
size_t LOOKUP_CONVERT_SIZE = 0; 

size_t RBX_PRIME = 0;
size_t RBX_PRIMORIAL = 1;
size_t RBX_PHI = 1;

void resetBuffers() {
    std::fill(BUFFER_IN.begin(), BUFFER_IN.end(), 0);
    std::fill(BUFFER_OUT.begin(), BUFFER_OUT.end(), 0);
}

void setPrimorialAndPhi() {
    for(size_t p = 0; FIRST_16_PRIMES[p] <= RBX_PRIME; p++) {
        RBX_PRIMORIAL = RBX_PRIMORIAL * FIRST_16_PRIMES[p];
        RBX_PHI = RBX_PHI * (FIRST_16_PRIMES[p] - 1);
    }
}

void assignVectorSizes() {
    BUFFER_IN_SIZE = RBX_PRIMORIAL / RB5_PRIMORIAL;
    BUFFER_OUT_SIZE = ceil(RBX_PHI / RB5_PHI);
    LOOKUP_SIZE = BUFFER_IN_SIZE * RB5_PHI;
    LOOKUP_CONVERT_SIZE = RBX_PHI;
    //fprintf(stderr, "%zu %zu\n", RBX_PHI, RBX_PRIMORIAL);
    //fprintf(stderr, "%zu %zu %zu %zu\n", BUFFER_IN_SIZE, BUFFER_OUT_SIZE, LOOKUP_CONVERT_SIZE, LOOKUP_SIZE);

    DAT_LOOKUP.assign(LOOKUP_SIZE, 0);
    DAT_BYTE_INDS.assign(LOOKUP_CONVERT_SIZE, 0);
    DAT_MASKS.assign(LOOKUP_CONVERT_SIZE, 0);
    BUFFER_IN.assign(BUFFER_IN_SIZE, 0);
    BUFFER_OUT.assign(BUFFER_OUT_SIZE, 0);
}

void fillLookupInfo() {
    size_t rbXIndex = 0;
    uint8_t rotatingMask = 1;
    for (size_t block = 0; block < BUFFER_IN_SIZE; block++) 
        if (BUFFER_IN[block])
            for (uint8_t mask = BUFFER_IN[block]; mask; mask ^= (-mask & mask)) {
                size_t lookupIndex = 8 * block + std::countr_zero(mask);
                DAT_LOOKUP[lookupIndex] = rbXIndex;
                DAT_BYTE_INDS[rbXIndex] = rbXIndex/8; 
                DAT_MASKS[rbXIndex] = rotatingMask;
                rotatingMask = std::rotl(rotatingMask, 1);
                rbXIndex++;
            }
}

void setUpLookupArray() {
    std::string fileName = "dataForLevelCompress" + std::to_string(RBX_PRIME) + ".bin";
    readBlockFromInfoFile(fileName.c_str(), BUFFER_IN.data(), BUFFER_IN_SIZE);
    fillLookupInfo();
}

void initGlobals() {
    uint64_t tmp = 0;
    readInfoForProgram("boundsGoFromRB5toRBX.txt\0", RBX_PRIME, tmp);
    setPrimorialAndPhi();
    assignVectorSizes();
    setUpLookupArray();
    resetBuffers();
}

void fixFirstByte() {
    for (size_t p = 3; FIRST_16_PRIMES[p] <= RBX_PRIME; p++) {
        BUFFER_IN[0] &= ~OFFSET_TO_MASK[FIRST_16_PRIMES[p] % RB5_PRIMORIAL];
    }
}

void convert() {
    for (size_t block = 0; block < BUFFER_IN_SIZE; block++)
        if (BUFFER_IN[block]) 
            for (uint8_t mask = BUFFER_IN[block]; mask; mask ^= (-mask & mask)) {
                size_t lookupIndex = DAT_LOOKUP[8 * block + std::countr_zero(mask)]; 
                BUFFER_OUT[DAT_BYTE_INDS[lookupIndex]] |= DAT_MASKS[lookupIndex];
            }
}

void convertDataTillEOF() {
    readBuffer(BUFFER_IN.data(), BUFFER_IN_SIZE);
    fixFirstByte();
    convert();
    writeBuffer(BUFFER_OUT.data(), BUFFER_OUT_SIZE);
    while (EOF_NOT_READ) {
        readBuffer(BUFFER_IN.data(), BUFFER_IN_SIZE);
        convert();
        writeBuffer(BUFFER_OUT.data(), BUFFER_OUT_SIZE);
        resetBuffers();
    }
}


int main() {
    initGlobals();
    convertDataTillEOF();
    return 0;
}
