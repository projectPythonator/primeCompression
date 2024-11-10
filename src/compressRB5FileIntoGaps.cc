#include "rb5FileIOHeader.h"
#include "rb5GlobalConstants.h"
#include <bit>

const size_t BUFFER_IN_SIZE = (1 << 16);
const size_t BUFFER_OUT_SIZE = (1 << 16);

uint64_t LAST_BIT_POS = 0;
size_t BUFFER_IN_END = 1;
size_t BUFFER_OUT_END = 0;

uint8_t BUFFER_IN[BUFFER_IN_SIZE];
uint8_t BUFFER_OUT[BUFFER_OUT_SIZE];

// add this line instead of memset maybe
// std::fill(std::begin(BUFFER_IN), std::end(BUFFER_IN), 0);
void resetBufferIn() {
    memset(BUFFER_IN, 0, sizeof(BUFFER_IN));
    BUFFER_IN_END = 0;
}

void resetBufferOut() {
    memset(BUFFER_OUT, 0, sizeof(BUFFER_OUT));
    BUFFER_OUT_END = 0;
}

void fillBufferOut(uint64_t block) {
    if (BUFFER_IN_END)
        LAST_BIT_POS = std::countr_zero(BUFFER_IN[0]);
    for (size_t p = BUFFER_IN_END; p < BUFFER_IN_SIZE && EOF_NOT_READ; p++) 
        if (BUFFER_IN[p])
            for (uint8_t mask = BUFFER_IN[p]; mask; mask ^= (-mask & mask)) {
                if (BUFFER_OUT_END == BUFFER_OUT_SIZE) {
                    writeBuffer(BUFFER_OUT, BUFFER_OUT_SIZE);
                    resetBufferOut();
                }
                uint64_t currPos = block + (p * 8) + std::countr_zero(mask);
                BUFFER_OUT[BUFFER_OUT_END++] = currPos - LAST_BIT_POS;
                LAST_BIT_POS = currPos;
            }
}

void convertTillEOF() {
    readBuffer(BUFFER_IN, BUFFER_IN_SIZE);
    for (size_t p = 0; EOF_NOT_READ; p += (8 * BUFFER_IN_SIZE)) {
        fillBufferOut(p);
        resetBufferIn();
        readBuffer(BUFFER_IN, BUFFER_IN_SIZE);
    }
    if (BUFFER_OUT_END)
        writeBuffer(BUFFER_OUT, BUFFER_OUT_END);
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
