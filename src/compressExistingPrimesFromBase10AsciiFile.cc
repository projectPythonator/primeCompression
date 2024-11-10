#include "rb5FileIOHeader.h"
#include "rb5GlobalConstants.h"

const size_t PADDING = 32;
const size_t BUFFER_IN_SIZE = (1 << 15) - 32;
const size_t BUFFER_OUT_SIZE = (1 << 15);
const size_t BUFFER_OUT_RANGE = BUFFER_OUT_SIZE * 30;
const size_t BUFFER_MOD = BUFFER_OUT_SIZE - 1;
const uint8_t EOF_VALUE = EOF - '0';

size_t BUFFER_IN_END = 0;
char BUFFER_IN[BUFFER_IN_SIZE + PADDING];
uint8_t BUFFER_OUT[BUFFER_OUT_SIZE];

uint64_t getNextIntUnlocked() {
    if (BUFFER_IN_END >= BUFFER_IN_SIZE && EOF_NOT_READ) {
        memset(BUFFER_IN, 0, sizeof(BUFFER_IN));
        readBufferTillNL(BUFFER_IN, BUFFER_IN_SIZE);
        BUFFER_IN_END = 0;
    }
    uint64_t result = 0;
    uint8_t digit = 0;
    while ((digit = uint8_t(BUFFER_IN[BUFFER_IN_END++] - '0')) <= 9)
        result = result * 10 + digit;
    return result;
}

void zeroBuffer() {
    memset(BUFFER_OUT, 0, sizeof(BUFFER_OUT));
}

void convertPrime(uint64_t prime) {
    size_t primeMod = prime % RB5_PRIMORIAL;
    size_t primeBlock = prime / RB5_PRIMORIAL;
    BUFFER_OUT[primeBlock & BUFFER_MOD] |= OFFSET_TO_MASK[primeMod];
}

uint64_t fillBufferOut(uint64_t bound) {
    uint64_t prime = 0;
    for (; EOF_NOT_READ && (prime = getNextIntUnlocked()) < bound;) 
        convertPrime(prime);
    return prime;
}

void compressTillEOF() {
    readBufferTillNL(BUFFER_IN, BUFFER_IN_SIZE);
    getNextIntUnlocked();
    getNextIntUnlocked();
    getNextIntUnlocked();
    for (uint64_t bound = BUFFER_OUT_RANGE; EOF_NOT_READ; bound += BUFFER_OUT_RANGE) {
        uint64_t prime = fillBufferOut(bound);
        if (prime >= bound) {
            writeBuffer(BUFFER_OUT, BUFFER_OUT_SIZE);
            zeroBuffer();
            convertPrime(prime);
        }
    }
    flushBuffer(BUFFER_OUT, BUFFER_OUT_SIZE); 
}

void initGlobals() {
    uint64_t tmp1 = 0;
    uint64_t tmp2 = 0;
    readInfoForProgram("boundsCompressFromExistingPrimes.txt\0", tmp1, tmp2);
    zeroBuffer();
}

int main() {
    initGlobals();
    compressTillEOF();
    return 0;
}
