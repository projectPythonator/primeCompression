#include "rb5FileIOHeader.h"
#include "rb5GlobalConstants.h"
#include <cmath>


// NEW GLOBALS
const size_t BLOCK_FACTOR = 128;
const size_t WHEEL = 7 * 11 * 13 * 17;
const size_t SIEVE_SPAN = WHEEL * BLOCK_FACTOR;

const size_t BUFFER_SIZE = SIEVE_SPAN;

// try keep fast 32 size to be emcompasing full block 30 * k
const size_t FAST8_MAX_SIZE = 45; 
const size_t FAST16_MAX_SIZE = 6489;    // same as above but for primes below 2^20
const size_t FAST32_MAX_SIZE = 75482; // same as above but for primes below 2^20 + 2 for padding
const size_t FASTX_MIN_READ = 34952;
                                      
// try keep fast 32 size to be emcompasing full block 30 * k
const size_t FAST8_END = 8;
const size_t FAST16_END = 2184;
const size_t FAST32_END = FASTX_MIN_READ; 
const size_t SLOW32_BEGIN = FAST32_END;

// slow block info
std::vector<uint64_t> SLOW32_CURRENT_BLOCK;
std::vector<uint32_t> SLOW32_PRIME_LIST;
std::vector<uint8_t> SLOW32_MASK_INDEX;

// BLOCKS and STARTS for our sieve 
uint64_t FAST32_CURRENT_BLOCK[FAST32_MAX_SIZE] = {0};
uint64_t FAST32_CURRENT_INDEX[FAST32_MAX_SIZE];

uint64_t FAST16_CURRENT_BLOCK[FAST16_MAX_SIZE] = {0};
uint64_t FAST16_CURRENT_INDEX[FAST16_MAX_SIZE];

uint64_t FAST8_CURRENT_BLOCK[FAST8_MAX_SIZE] = {0};
uint64_t FAST8_CURRENT_INDEX[FAST8_MAX_SIZE];

// prime lists and jumps for our sieve 
uint32_t FAST32_JUMPS[FAST32_MAX_SIZE][BITS_PER_MASK];
uint32_t FAST32_PRIME_LIST[FAST32_MAX_SIZE];

uint16_t FAST16_JUMPS[FAST16_MAX_SIZE][BITS_PER_MASK];
uint16_t FAST16_PRIME_LIST[FAST16_MAX_SIZE];

uint8_t FAST8_JUMPS[FAST8_MAX_SIZE][BITS_PER_MASK];
uint8_t FAST8_PRIME_LIST[FAST8_MAX_SIZE];

// current mask index arrays for our sieve
uint8_t FAST32_MASK_INDEX[FAST32_MAX_SIZE];
uint8_t FAST16_MASK_INDEX[FAST16_MAX_SIZE];
uint8_t FAST8_MASK_INDEX[FAST8_MAX_SIZE];

//need better name than BUFFER
uint8_t BUFFER[BUFFER_SIZE] = {0};
uint8_t PATTERN[BUFFER_SIZE] = {0};

size_t SLOW32_AMT = 0;
size_t FAST32_AMT = 0;
size_t FAST16_AMT = 0;
size_t FAST8_AMT = 0;

uint64_t NUMBER_OF_BYTES = 0;
//////////////////// reading in precomputed info 
template<typename T, size_t N> void fillFastPrimeList(auto &rb5Sieve, T (&fastX)[N], size_t fastXBegin, size_t fastXEnd) {
    size_t fastXAmt = 0;
    for (size_t p = fastXBegin; p < fastXEnd; p++)
        if (rb5Sieve[p])
            for (uint8_t mask = rb5Sieve[p]; mask; mask ^= (-mask & mask))
                fastX[fastXAmt++] = RB5_PRIMORIAL * p + MASK_TO_OFFSET[-mask & mask];
}

void fillFastLookupPrimes(uint64_t upperBound){
    size_t numberOfBlocks = std::max(FASTX_MIN_READ, upperBound/RB5_PRIMORIAL); 
    std::vector<uint8_t> rb5Sieve(numberOfBlocks); 
    readBlockFromInfoFile("primesBelow_uint32_t.bin", rb5Sieve.data(), numberOfBlocks); 

    rb5Sieve[0] = 224; // first block only requires 19, 23, 29 because wheel sieve
    fillFastPrimeList<uint8_t ,FAST8_MAX_SIZE>(rb5Sieve, FAST8_PRIME_LIST, 0, FAST8_END);
    fillFastPrimeList<uint16_t ,FAST16_MAX_SIZE>(rb5Sieve, FAST16_PRIME_LIST, FAST8_END, FAST16_END);
    fillFastPrimeList<uint32_t ,FAST32_MAX_SIZE>(rb5Sieve, FAST32_PRIME_LIST, FAST16_END, FAST32_END);
    for (size_t block = SLOW32_BEGIN; block < numberOfBlocks; block++)
        if (rb5Sieve[block])
            for (uint8_t mask = rb5Sieve[block]; mask; mask ^= (-mask & mask))
                SLOW32_PRIME_LIST.push_back(block * RB5_PRIMORIAL + MASK_TO_OFFSET[(-mask & mask)]);
    SLOW32_AMT = SLOW32_PRIME_LIST.size();
}

void correctAmtValues(uint32_t sqrtValue) {
    FAST32_AMT = std::distance(std::begin(FAST32_PRIME_LIST), std::upper_bound(std::begin(FAST32_PRIME_LIST), std::end(FAST32_PRIME_LIST), sqrtValue));
    FAST16_AMT = std::distance(std::begin(FAST16_PRIME_LIST), std::upper_bound(std::begin(FAST16_PRIME_LIST), std::end(FAST16_PRIME_LIST), sqrtValue));
    FAST8_AMT = std::distance(std::begin(FAST8_PRIME_LIST), std::upper_bound(std::begin(FAST8_PRIME_LIST), std::end(FAST8_PRIME_LIST), sqrtValue));
}

void fillJumps() {
    for (size_t p = 0; p < FAST32_MAX_SIZE; p++) 
        for(size_t b = 0; b < BITS_PER_MASK; b++)
            FAST32_JUMPS[p][b] = (JUMP_VALUE[b] * FAST32_PRIME_LIST[p]) / RB5_PRIMORIAL;
    for (size_t p = 0; p < FAST16_MAX_SIZE; p++) 
        for(size_t b = 0; b < BITS_PER_MASK; b++)
            FAST16_JUMPS[p][b] = (JUMP_VALUE[b] * FAST16_PRIME_LIST[p]) / RB5_PRIMORIAL;
    for (size_t p = 0; p < FAST8_MAX_SIZE; p++) 
        for(size_t b = 0; b < BITS_PER_MASK; b++)
            FAST8_JUMPS[p][b] = (JUMP_VALUE[b] * FAST8_PRIME_LIST[p]) / RB5_PRIMORIAL;
}

void fillIndexes() {
    for (size_t p = 0; p < FAST32_MAX_SIZE; p++) 
        FAST32_CURRENT_INDEX[p] = FAST32_JUMPS[p][1];
    for (size_t p = 0; p < FAST16_MAX_SIZE; p++) 
        FAST16_CURRENT_INDEX[p] = FAST16_JUMPS[p][1];
    for (size_t p = 0; p < FAST8_MAX_SIZE; p++) 
        FAST8_CURRENT_INDEX[p] = FAST8_JUMPS[p][1];
}

void fillMaskIndexs() {
    std::fill(std::begin(FAST32_MASK_INDEX), std::end(FAST32_MASK_INDEX), 1);
    std::fill(std::begin(FAST16_MASK_INDEX), std::end(FAST16_MASK_INDEX), 1);
    std::fill(std::begin(FAST8_MASK_INDEX), std::end(FAST8_MASK_INDEX), 1);
}

void fillLookupValues() {
    fillJumps();
    fillIndexes();
    fillMaskIndexs();
    SLOW32_MASK_INDEX.assign(SLOW32_AMT, 1);
    SLOW32_CURRENT_BLOCK.assign(SLOW32_AMT, 0);
}

void readPrecomputedData() {
    uint64_t limit = NUMBER_OF_BYTES * RB5_PRIMORIAL;
    size_t sqrtLimit = sqrt(limit);
    sqrtLimit = (sqrtLimit * sqrtLimit < limit)? sqrtLimit + 1: sqrtLimit;
    readBlockFromInfoFile("PATTERN_SIEVE_DATA.bin", PATTERN, BUFFER_SIZE); 
    fillFastLookupPrimes(sqrtLimit);
    correctAmtValues(sqrtLimit);
    fillLookupValues();
}

void initGlobals() {
    uint64_t tmp=0;
    readInfoForProgram("boundsCompressFromSieve.txt\0", tmp, NUMBER_OF_BYTES); // might need & iirw
    readPrecomputedData();
}
//////////////////// end of reading in precomputed info 
///
//////////////////// start of sieving
void applyWheelPrimes() {
    std::copy(std::cbegin(PATTERN), std::cend(PATTERN), std::begin(BUFFER)); 
}

void updateFast8Primes(uint64_t upperBound) {
    for (size_t p = 0; p < FAST8_AMT; p++) {
        uint64_t currIndex = FAST8_CURRENT_INDEX[p];
        uint64_t currBlock = FAST8_CURRENT_BLOCK[p];
        uint8_t prime = FAST8_PRIME_LIST[p];
        uint8_t indexByModuloClass = prime % RB5_PRIMORIAL;
        uint8_t currMask = FAST8_MASK_INDEX[p];
        for (; currMask < BITS_PER_MASK && (currIndex = currBlock + FAST8_JUMPS[p][currMask]) < upperBound; currMask++)
            BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
        for (; currIndex < upperBound; ){
            currBlock += prime;
            currMask = 0;
            for (; currMask < BITS_PER_MASK && (currIndex = currBlock + FAST8_JUMPS[p][currMask]) < upperBound; currMask++)
                BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
        }
        FAST8_CURRENT_INDEX[p] = currIndex;
        FAST8_CURRENT_BLOCK[p] = currBlock;
        FAST8_MASK_INDEX[p] = currMask;
    }
}

void updateFast16Primes(uint64_t upperBound) {
    for (size_t p = 0; p < FAST16_AMT; p++) {
        uint64_t currIndex = FAST16_CURRENT_INDEX[p];
        uint64_t currBlock = FAST16_CURRENT_BLOCK[p];
        uint16_t prime = FAST16_PRIME_LIST[p];
        uint8_t indexByModuloClass = prime % RB5_PRIMORIAL;
        uint8_t currMask = FAST16_MASK_INDEX[p];
        for (; currMask < BITS_PER_MASK && (currIndex = currBlock + FAST16_JUMPS[p][currMask]) < upperBound; currMask++)
            BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
        for (; currIndex < upperBound; ){
            currBlock += prime;
            currMask = 0;
            for (; currMask < BITS_PER_MASK && (currIndex = currBlock + FAST16_JUMPS[p][currMask]) < upperBound; currMask++)
                BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
        }
        FAST16_CURRENT_INDEX[p] = currIndex;
        FAST16_CURRENT_BLOCK[p] = currBlock;
        FAST16_MASK_INDEX[p] = currMask;
    }
}

void updateFast32Primes(uint64_t upperBound) {
    for (size_t p = 0; p < FAST32_AMT; p++) {
        uint64_t currIndex = FAST32_CURRENT_INDEX[p];
        uint64_t currBlock = FAST32_CURRENT_BLOCK[p];
        uint32_t prime = FAST32_PRIME_LIST[p];
        uint8_t indexByModuloClass = prime % RB5_PRIMORIAL;
        uint8_t currMask = FAST32_MASK_INDEX[p];
        for (; currMask < BITS_PER_MASK && (currIndex = currBlock + FAST32_JUMPS[p][currMask]) < upperBound; currMask++)
            BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
        for (; currIndex < upperBound; ){
            currBlock += prime;
            currMask = 0;
            for (; currMask < BITS_PER_MASK && (currIndex = currBlock + FAST32_JUMPS[p][currMask]) < upperBound; currMask++)
                BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
        }
        FAST32_CURRENT_INDEX[p] = currIndex;
        FAST32_CURRENT_BLOCK[p] = currBlock;
        FAST32_MASK_INDEX[p] = currMask;
    }
}

void updateSlowPrimes(uint64_t upperBound) {
    if(SLOW32_AMT == 0 || SLOW32_CURRENT_BLOCK[0] + (SLOW32_PRIME_LIST[0] / RB5_PRIMORIAL) > upperBound) 
        return;
    for (size_t p = 0; p < SLOW32_AMT; p++) {
        uint64_t currBlock = SLOW32_CURRENT_BLOCK[p];
        uint8_t currMask = SLOW32_MASK_INDEX[p];
        uint32_t prime = SLOW32_PRIME_LIST[p];
        uint64_t currIndex = currBlock + (JUMP_VALUE[currMask] * prime) / RB5_PRIMORIAL; 
        if (upperBound <= currIndex)
            continue;
        uint8_t indexByModuloClass = prime % RB5_PRIMORIAL;
        for (; currMask < BITS_PER_MASK && (currIndex = currBlock + (JUMP_VALUE[currMask] * prime) / RB5_PRIMORIAL) < upperBound; currMask++)
            BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
        for (; currIndex < upperBound; ){
            currBlock += prime;
            currMask = 0;
            for (; currMask < BITS_PER_MASK && (currIndex = currBlock + (JUMP_VALUE[currMask] * prime) / RB5_PRIMORIAL) < upperBound; currMask++)
                BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
        }
        SLOW32_CURRENT_BLOCK[p] = currBlock;
        SLOW32_MASK_INDEX[p] = currMask;
    }
}

void update_sieve(uint64_t offset) {
    const uint64_t upperBound = offset + BUFFER_SIZE; 
    applyWheelPrimes();
    updateFast8Primes(upperBound);
    updateFast16Primes(upperBound);
    updateFast32Primes(upperBound);
    updateSlowPrimes(upperBound);
}

void sieve(uint64_t limit) {
    uint64_t offset = 0;
    for (; offset < limit; offset += BUFFER_SIZE) {
        update_sieve(offset);
        if (offset == 0)
            BUFFER[0] = 254;
        if (offset + BUFFER_SIZE < limit)
            writeBuffer(BUFFER, BUFFER_SIZE);
    }
    if (offset != limit) {
        offset -= BUFFER_SIZE;
        flushBuffer(BUFFER, limit-offset);
    }
}

int main() {
    initGlobals();
    sieve(NUMBER_OF_BYTES);
    return 0;
}

/*
void generateModuloClass(uint64_t prime) {
    for (auto ind = 0; ind < 8; ind++) 
        CURRENT_INDEX_CLASS[ind] = (JUMP_VALUE[ind] * prime) / RB5_PRIMORIAL;
}

void fillPatternArrayHelper(size_t prime) {
    generateModuloClass(prime);
    size_t mod = prime % RB5_PRIMORIAL;
    for (size_t blockN = 0; blockN < BUFFER_SIZE; blockN += prime)
        for (size_t p = 0; p < 8; p++)
            PATTERN[blockN + CURRENT_INDEX_CLASS[p]] &= MASK_LOOKUP[mod][p];
}

void fillPatternArray() {
    std::fill(std::begin(PATTERN), std::end(PATTERN), 255);
    fillPatternArrayHelper(7);
    fillPatternArrayHelper(11);
    fillPatternArrayHelper(13);
    fillPatternArrayHelper(17);
}
*/

