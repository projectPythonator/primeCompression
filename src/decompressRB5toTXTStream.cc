#include "rb5FileIOHeader.h"
#include "rb5GlobalConstants.h"

const size_t BUFFER_SIZE = KIBIBYTE * PAGE_FACTOR;

const size_t BUF_SIZE = 17;
const size_t BUF_BEG = BUF_SIZE - 1;

const char BASE = 10;

uint64_t NUMBER_OF_BYTES = 0;
size_t BUFFER_OUT_STACK_END = 0;

uint8_t BUFFER_IN[BUFFER_SIZE];
uint8_t BUFFER_OUT[BUFFER_SIZE + BUF_SIZE]; 

void resetBuffer() {
    std::fill(std::begin(BUFFER_IN), std::end(BUFFER_IN), 0);
}

void writeAndClear() {
    writeBuffer(BUFFER_OUT, BUFFER_OUT_STACK_END);
    BUFFER_OUT_STACK_END = 0;
}

void printNumber(uint64_t n) {
    uint8_t buf[BUF_SIZE] = {0};
    buf[BUF_BEG] = '\n';
    size_t b = BUF_BEG;
    do {
        buf[--b] = n % BASE + '0';
        n /= BASE;
    } while (n);
    std::memcpy(BUFFER_OUT + BUFFER_OUT_STACK_END, buf + b, BUF_SIZE - b);
    BUFFER_OUT_STACK_END += (BUF_SIZE - b);
    if (BUFFER_OUT_STACK_END > BUFFER_SIZE)
        writeAndClear();
}

void convertBuffer(uint64_t block) {
    for (size_t p = 0; p < BUFFER_SIZE; p++)
        if (BUFFER_IN[p])
            for (uint8_t mask = BUFFER_IN[p]; mask; mask ^= (-mask & mask)) 
                printNumber(RB5_PRIMORIAL * (block + p) + MASK_TO_OFFSET[(-mask & mask)]);
}

void convertDataTillEOF() {
    printNumber(2);
    printNumber(3);
    printNumber(5);
    for (uint64_t block = 0; EOF_NOT_READ; block += BUFFER_SIZE) {
        resetBuffer();
        readBuffer(BUFFER_IN, BUFFER_SIZE);
        convertBuffer(block);
    }
    writeAndClear();
}

void initGlobals() {
    uint64_t tmp1 = 0;
    uint64_t tmp2 = 0;
    readInfoForProgram("boundsDecompressRB5toTXT.txt", tmp1, tmp2);
}

int main() {
    initGlobals();    
    convertDataTillEOF();
    return 0;
}
