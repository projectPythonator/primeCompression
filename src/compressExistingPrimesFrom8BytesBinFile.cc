#include "rb5FileIOHeader.h"
#include "rb5GlobalConstants.h"

const size_t BUFFER_IN_SIZE = 8192;
const size_t BUFFER_OUT_SIZE = (1 << 16);
const size_t BUFFER_OUT_RANGE = BUFFER_OUT_SIZE * 30;
const size_t BUFFER_MOD = BUFFER_OUT_SIZE - 1;

size_t BOUND = 0;
size_t BUFFER_IN_END = 0; // assumes input starts as 2, 3, 5
uint64_t BUFFER_IN[BUFFER_IN_SIZE];
uint8_t BUFFER_OUT[BUFFER_OUT_SIZE];

//std::fill(std::begin(BUFFER_IN), std::end(BUFFER_IN), 0);
void resetBufferIn() {
    std::fill(std::begin(BUFFER_IN), std::end(BUFFER_IN), 0);
    BUFFER_IN_END = 0;
}

void resetBufferOut() { 
    std::fill(std::begin(BUFFER_OUT), std::end(BUFFER_OUT), 0);
    BOUND += BUFFER_OUT_RANGE;
}

void convertPrime(uint64_t prime) {
    if (prime >= BOUND) {
        writeBuffer(BUFFER_OUT, BUFFER_OUT_SIZE);
        resetBufferOut();
    }
    size_t primeMod = prime % RB5_PRIMORIAL;
    size_t primeBlock = prime / RB5_PRIMORIAL;
    BUFFER_OUT[primeBlock & BUFFER_MOD] |= OFFSET_TO_MASK[primeMod];
}

void fillBufferOut() {
    for (size_t p = BUFFER_IN_END; p < BUFFER_IN_SIZE; p++)
        convertPrime(BUFFER_IN[p]);
}

void compressTillEOF() {
    do {
        resetBufferIn();
        readBuffer_uint64_t(BUFFER_IN, BUFFER_IN_SIZE);
        fillBufferOut();
    }while (EOF_NOT_READ);
    flushBuffer(BUFFER_OUT, BUFFER_OUT_SIZE); 
}

void initGlobals() {
    uint64_t tmp1 = 0;
    uint64_t tmp2 = 0;
    readInfoForProgram("boundsCompressFromExistingPrimes.txt\0", tmp1, tmp2);
    resetBufferOut();
}

int main() {
    initGlobals();
    compressTillEOF();
    return 0;
}
