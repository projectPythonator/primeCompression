#include "rb5FileIOHeader.h"
#include <primesieve.hpp>

const size_t PADDING = 32;
const size_t BUFFER_IN_SIZE = (1 << 16) - 32;
const size_t BUFFER_OUT_SIZE = 8192; // max amount of uint64_t that fits in 2^16
const uint8_t EOF_VALUE = EOF - '0';

size_t BUFFER_IN_END = 6; // or now this skips 2 3 5 with newlines skipped too

char BUFFER_IN[BUFFER_IN_SIZE + PADDING];
uint64_t BUFFER_OUT[BUFFER_OUT_SIZE];

// add this line instead of memset maybe
// std::fill(std::begin(BUFFER_IN), std::end(BUFFER_IN), 0);
void resetBufferIn() {
    memset(BUFFER_IN, 0, sizeof(BUFFER_IN));
    BUFFER_IN_END = 0;
}

void resetBufferOut() {
    memset(BUFFER_OUT, 0, sizeof(BUFFER_OUT));
}

uint64_t getNextIntUnlocked() {
    uint64_t result = 0;
    uint8_t digit = 0;
    while ((digit = uint8_t(BUFFER_IN[BUFFER_IN_END++] - '0')) <= 9)
        result = result * 10 + digit;
    return result;
}

void checkBufferIn() {
    if (BUFFER_IN_END >= BUFFER_IN_SIZE && EOF_NOT_READ) {
        resetBufferIn();
        readBufferTillNL(BUFFER_IN, BUFFER_IN_SIZE);
    }
}

void fillBufferOut() {
    for (size_t p = 0; p < BUFFER_OUT_SIZE && EOF_NOT_READ; p++) {
        checkBufferIn();
        BUFFER_OUT[p] = getNextIntUnlocked();
    }
}

void convertTillEOF() {
    readBufferTillNL(BUFFER_IN, BUFFER_IN_SIZE);
    while (EOF_NOT_READ) {
        resetBufferOut();
        fillBufferOut();
        writeBuffer_uint64_t(BUFFER_OUT, BUFFER_OUT_SIZE);
    }
}

void initGlobals() {
    uint64_t tmp1 = 0;
    uint64_t tmp2 = 0;
    readInfoForProgram("boundsCompressFromExistingPrimes.txt\0", tmp1, tmp2);
}

int main() {
    initGlobals();
    convertTillEOF();
}
