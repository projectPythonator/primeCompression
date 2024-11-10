#include "rb5FileIOHeader.h"
#include "rb5GlobalConstants.h"
#include <bit>
#include <cmath>
#include <string>

std::vector<size_t> DAT_BLOCKS;
std::vector<uint8_t> DAT_MASKS;
std::vector<uint8_t> BUFFER_IN;
std::vector<uint8_t> BUFFER_OUT;

uint64_t RBX_PRIME = 0;
size_t RBX_PRIMORIAL = 1;
size_t RBX_PHI = 1;

size_t BUFFER_IN_SIZE = 0;
size_t BUFFER_OUT_SIZE = 0;

void resetBuffers() {
    std::fill(BUFFER_IN.begin(), BUFFER_IN.end(), 0);
    std::fill(BUFFER_OUT.begin(), BUFFER_OUT.end(), 0);
}

void __attribute__((optimize("Os"))) setPrimorialAndPhi() {
    for(size_t p = 0; FIRST_16_PRIMES[p] <= RBX_PRIME; p++) {
        RBX_PRIMORIAL *= FIRST_16_PRIMES[p];
        RBX_PHI *= (FIRST_16_PRIMES[p] - 1);
    }
}

void assignVectorSizes() {
    BUFFER_IN_SIZE = ceil(RBX_PHI / RB5_PHI);
    BUFFER_OUT_SIZE = RBX_PRIMORIAL / RB5_PRIMORIAL;

    DAT_BLOCKS.assign(RBX_PHI, 0);
    DAT_MASKS.assign(RBX_PHI, 0);
    BUFFER_IN.assign(BUFFER_IN_SIZE, 0);
    BUFFER_OUT.assign(BUFFER_OUT_SIZE, 0);
}

void fillDATInfo() {
    size_t rbXIndex = 0;
    for (size_t block = 0; block < BUFFER_OUT_SIZE; block++) 
        if (BUFFER_OUT[block])
            for (uint8_t mask = BUFFER_OUT[block]; mask; mask ^= (-mask & mask)) {
                DAT_BLOCKS[rbXIndex] = block; 
                DAT_MASKS[rbXIndex] = (-mask & mask);
                rbXIndex++;
            }
}

void setUpDATArray() {
    std::string fileName = "dataForLevelCompress" + std::to_string(RBX_PRIME) + ".bin";
    readBlockFromInfoFile(fileName.c_str(), BUFFER_OUT.data(), BUFFER_OUT_SIZE);
    fillDATInfo();
}

void initGlobals() {
    uint64_t tmp1 = 0;
    uint64_t tmp2 = 0;
    readInfoForProgram("boundsGoFromRBXtoRB5.txt\0", tmp1, tmp2);
    setPrimorialAndPhi();
    assignVectorSizes();
    setUpDATArray();
    resetBuffers();
}

void convert() {
    for (size_t block = 0; block < BUFFER_IN_SIZE; block++) 
        if (BUFFER_IN[block])
            for(uint8_t mask = BUFFER_IN[block]; mask; mask ^= (-mask & mask)) {
                size_t pos = BITS_PER_MASK * block + std::countr_zero(mask);
                BUFFER_OUT[DAT_BLOCKS[pos]] |= DAT_MASKS[pos];
            }
}

void convertDataTillEOF() {
    BUFFER_OUT[0] = ~1;
    readBuffer(BUFFER_IN.data(), BUFFER_IN_SIZE);
    for (; EOF_NOT_READ; ) {
        convert();
        writeBuffer(BUFFER_OUT.data(), BUFFER_OUT_SIZE);
        resetBuffers();
        readBuffer(BUFFER_IN.data(), BUFFER_IN_SIZE);
    }
    convert();
    flushBuffer(BUFFER_OUT.data(), BUFFER_OUT_SIZE);
}


int main() {
    initGlobals();
    convertDataTillEOF();
    return 0;
}

