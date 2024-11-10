#include "rb5FileIOHeader.h"
#include "rb5GlobalConstants.h"
#include <cmath>



// NEW GLOBALS
// this number is the number of blocks to read that represent primes that are 
// 2^32 but also make up a full span size
const size_t BLOCK_FACTOR = 128;
const size_t WHEEL = 7 * 11 * 13 * 17;
const size_t SIEVE_SPAN = WHEEL * BLOCK_FACTOR;
const size_t SIEVE_SPAN_RANGE = SIEVE_SPAN * RB5_PRIMORIAL;
const size_t BLOCKS_TO_AUTO_READ = SIEVE_SPAN * ((1ULL << 32) / SIEVE_SPAN_RANGE);
const size_t BLOCKS_TO_AUTO_READ_RANGE = BLOCKS_TO_AUTO_READ * RB5_PRIMORIAL;

const size_t BUFFER_SIZE = SIEVE_SPAN;

// try keep fast 32 size to be emcompasing full block 30 * k
const size_t FAST16_MAX_SIZE = 6503;         // accounts for first 7 primes not being used
const size_t FAST32_MAX_SIZE = 82023 - 6510; // accounts for 7 + fast16
//const size_t FASTX_MIN_READ = 34952;
                                      
// try keep fast 32 size to be emcompasing full block 30 * k
const size_t FAST16_END = 2172; 
const size_t FAST32_END = 34952; 
const size_t SLOW32_END_LOOPS = 1089089;
const size_t SLOW32_END_NO_LOOPS = BLOCKS_TO_AUTO_READ;

// STARTS for our sieve 
uint64_t FAST32_CURRENT_INDEX[FAST32_MAX_SIZE];
uint64_t FAST16_CURRENT_INDEX[FAST16_MAX_SIZE];

// JUMP LISTS for our sieve
uint32_t FAST32_JUMPS[FAST32_MAX_SIZE][BITS_PER_MASK];
uint16_t FAST16_JUMPS[FAST16_MAX_SIZE][BITS_PER_MASK];

// PRIME LIST for our sieve
uint32_t FAST32_PRIME_LIST[FAST32_MAX_SIZE];
uint16_t FAST16_PRIME_LIST[FAST16_MAX_SIZE];

// MASK LISTS for our sieve
uint8_t FAST32_MASK_INDEX[FAST32_MAX_SIZE];
uint8_t FAST16_MASK_INDEX[FAST16_MAX_SIZE];

// SLOW WITH LOOPS
std::vector<uint64_t> SLOW32_CURRENT_INDEX_LOOPS;
std::vector<uint64_t> SLOW32_CURRENT_BLOCK_LOOPS;
std::vector<uint32_t> SLOW32_PRIME_LIST_LOOPS;
std::vector<uint8_t> SLOW32_MASK_INDEX_LOOPS;

// slow block info
std::vector<uint64_t> SLOW32_CURRENT_INDEX_NO_LOOPS;
std::vector<uint64_t> SLOW32_CURRENT_BLOCK_NO_LOOPS;
std::vector<uint32_t> SLOW32_PRIME_LIST_NO_LOOPS;
std::vector<uint8_t> SLOW32_MASK_INDEX_NO_LOOPS;

//need better name than BUFFER
uint8_t BUFFER[BUFFER_SIZE] = {0};
uint8_t PATTERN[BUFFER_SIZE] = {0};

uint64_t START_BLOCK = 0;
uint64_t END_BLOCK = 0;

size_t FAST32_ENDO = 0;
size_t SLOW32_ENDO_LOOPS = 0;
size_t SLOW32_ENDO_NO_LOOPS = 0;

size_t FAST16_AMT = 0;
size_t FAST32_AMT = 0;
size_t SLOW32_AMT_LOOPS = 0;
size_t SLOW32_AMT_NO_LOOPS = 0;

//////////////////// reading in precomputed info 
///

void getStartPosition(
        uint64_t *indexLookup, uint64_t *blockLookup, uint8_t *maskLookup, 
        uint64_t prime, size_t pIndex) {
    uint64_t posSqPrime = prime * prime;
    uint64_t posAfterAutoRead = BLOCKS_TO_AUTO_READ_RANGE;
    uint64_t posAfterInpRead = RB5_PRIMORIAL * START_BLOCK;
    uint64_t rPosIndex = std::max(posSqPrime, std::max(posAfterAutoRead, posAfterInpRead));
    uint64_t rPosBlock = rPosIndex / RB5_PRIMORIAL; // this might need to be * prime again to correct it
    uint64_t rPrimeBlock =   prime * (uint64_t)floor(rPosBlock / prime);
    uint64_t rPrimeIndex = 0;
    uint8_t rPrimeMask = 0;
    do {
        for (size_t p = 0; p < BITS_PER_MASK; p++) {
            if ((rPrimeBlock + (JUMP_VALUE[p] * prime) / RB5_PRIMORIAL) >= rPosBlock) {
                rPrimeIndex = rPrimeBlock + (JUMP_VALUE[p] * prime) / RB5_PRIMORIAL;
                rPrimeMask = p;
                break;
            }
        }
        if (!rPrimeIndex) {
            rPrimeBlock += prime;
        }
    } while (!rPrimeIndex);
    indexLookup[pIndex] = rPrimeIndex;
    maskLookup[pIndex] = rPrimeMask;
    if (blockLookup)
        blockLookup[pIndex] = rPrimeBlock;
    if (0 == rPrimeIndex || 9 == rPrimeMask) {
        perror("failed to set the index or mask on this code\n");
        fprintf(stderr, "prime was %llu, pindex was %zu\n", (unsigned long long) prime, (size_t) pIndex);
        fprintf(stderr, "index was %llu, mask was %zu\n", (unsigned long long) rPrimeIndex, (size_t) rPrimeMask);
        fprintf(stderr, "other info is p^2=%llu, autoRead=%llu, inpRead=%llu, posInd=%llu, posBlock=%llu\n",
                (unsigned long long) posSqPrime, (unsigned long long) posAfterAutoRead, 
                (unsigned long long) posAfterInpRead, (unsigned long long) rPosIndex,
                (unsigned long long) rPosIndex);
    }
}

template<typename T>
void fillFastXPrimes(T *fastX, uint8_t *sieve, size_t fastXbegin, size_t fastXend) {
    size_t fastXAmt = 0;
    for (size_t p = fastXbegin; p < fastXend; p++)
        if (sieve[p])
            for (uint8_t mask = sieve[p]; mask; mask ^= (-mask & mask))
                fastX[fastXAmt++] = RB5_PRIMORIAL * p + MASK_TO_OFFSET[(-mask & mask)];
    //fprintf(stderr, "%zu\n", fastXAmt);
}

void fillSlowXPrimes(auto &slowX, uint8_t *sieve, size_t slowXbegin, size_t slowXend) {
    for (size_t p = slowXbegin; p < slowXend; p++)
        if (sieve[p])
            for (uint8_t mask = sieve[p]; mask; mask ^= (-mask & mask))
                slowX.push_back(RB5_PRIMORIAL * p + MASK_TO_OFFSET[(-mask & mask)]);
}

void assignVectors() {
    SLOW32_CURRENT_INDEX_LOOPS.assign(SLOW32_AMT_LOOPS, 0);
    SLOW32_CURRENT_BLOCK_LOOPS.assign(SLOW32_AMT_LOOPS, 0);
    SLOW32_CURRENT_INDEX_NO_LOOPS.assign(SLOW32_AMT_NO_LOOPS, 0);
    SLOW32_CURRENT_BLOCK_NO_LOOPS.assign(SLOW32_AMT_NO_LOOPS, 0);
    SLOW32_MASK_INDEX_LOOPS.assign(SLOW32_AMT_LOOPS, 0);
    SLOW32_MASK_INDEX_NO_LOOPS.assign(SLOW32_AMT_NO_LOOPS, 0);
}

void readPresetData(auto &sieve) {
    sieve.assign(BLOCKS_TO_AUTO_READ, 0);
    readBlockFromInfoFile("primesBelow_uint32_t.bin\0", sieve.data(), BLOCKS_TO_AUTO_READ); 
    readBlockFromInfoFile("PATTERN_SIEVE_DATA.bin\0", PATTERN, BUFFER_SIZE); 
    sieve[0] = 254; // first block only requires 19, 23, 29 because wheel sieve
    if (START_BLOCK < BLOCKS_TO_AUTO_READ)
        writeBuffer(sieve.data() + START_BLOCK, BLOCKS_TO_AUTO_READ - START_BLOCK);    
    sieve[0] = 224; // first block only requires 19, 23, 29 because wheel sieve
}

void fillFastLookupPrimes(uint64_t upperBound, auto &sieve){
    size_t loopsBound = std::min(upperBound/RB5_PRIMORIAL, SLOW32_END_LOOPS);
    size_t noloopsBound = std::min(upperBound/RB5_PRIMORIAL, SLOW32_END_NO_LOOPS);
    fillFastXPrimes(FAST16_PRIME_LIST, sieve.data(), 0, FAST16_END);
    fillFastXPrimes(FAST32_PRIME_LIST, sieve.data(), FAST16_END, FAST32_END);
    fillSlowXPrimes(SLOW32_PRIME_LIST_LOOPS, sieve.data(), FAST32_END, loopsBound);
    fillSlowXPrimes(SLOW32_PRIME_LIST_NO_LOOPS, sieve.data(), SLOW32_END_LOOPS, noloopsBound);
    FAST16_AMT = FAST16_MAX_SIZE;
    while (FAST32_AMT < FAST32_MAX_SIZE && FAST32_PRIME_LIST[FAST32_AMT] <= upperBound)
        FAST32_AMT++;
    SLOW32_AMT_LOOPS = SLOW32_PRIME_LIST_LOOPS.size();
    SLOW32_AMT_NO_LOOPS = SLOW32_PRIME_LIST_NO_LOOPS.size();
    //fprintf(stderr, "%zu\n", SLOW32_AMT_LOOPS);
    //fprintf(stderr, "%zu\n", SLOW32_AMT_NO_LOOPS);
}

void fillJumpLookups() {
    const uint32_t tmpJumps[9] = {1, 7, 11, 13, 17, 19, 23, 29, 31};
    for (size_t p = 0; p < FAST16_MAX_SIZE; p++) 
        for(size_t b = 0; b < BITS_PER_MASK; b++) {
            uint16_t upper = (tmpJumps[b+1] * FAST16_PRIME_LIST[p]) / RB5_PRIMORIAL; 
            uint16_t lower = (tmpJumps[b]   * FAST16_PRIME_LIST[p]) / RB5_PRIMORIAL; 
            FAST16_JUMPS[p][b] = upper - lower;
        }
    for (size_t p = 0; p < FAST32_MAX_SIZE; p++) 
        for(size_t b = 0; b < BITS_PER_MASK; b++) {
            uint32_t upper = (tmpJumps[b+1] * FAST32_PRIME_LIST[p]) / RB5_PRIMORIAL; 
            uint32_t lower = (tmpJumps[b]   * FAST32_PRIME_LIST[p]) / RB5_PRIMORIAL; 
            FAST32_JUMPS[p][b] = upper - lower;
        }
}

void fillLookupGeneral() {
    for (size_t p = 0; p < FAST16_AMT; p++) 
        getStartPosition(FAST16_CURRENT_INDEX, nullptr, FAST16_MASK_INDEX, (uint64_t) FAST16_PRIME_LIST[p], p); 
    for (size_t p = 0; p < FAST32_AMT; p++) 
        getStartPosition(FAST32_CURRENT_INDEX, nullptr, FAST32_MASK_INDEX, (uint64_t) FAST32_PRIME_LIST[p], p); 
    for (size_t p = 0; p < SLOW32_AMT_LOOPS; p++) {
        getStartPosition(
                SLOW32_CURRENT_INDEX_LOOPS.data(), 
                SLOW32_CURRENT_BLOCK_LOOPS.data(), 
                SLOW32_MASK_INDEX_LOOPS.data(), 
                (uint64_t) SLOW32_PRIME_LIST_LOOPS[p], p); 
    }
    for (size_t p = 0; p < SLOW32_AMT_NO_LOOPS; p++) {
        getStartPosition(
                SLOW32_CURRENT_INDEX_NO_LOOPS.data(), 
                SLOW32_CURRENT_BLOCK_NO_LOOPS.data(), 
                SLOW32_MASK_INDEX_NO_LOOPS.data(), 
                (uint64_t) SLOW32_PRIME_LIST_NO_LOOPS[p], p); 
    }
}

void readPrecomputedData() {
    std::vector<uint8_t> sieve; 
    readPresetData(sieve);
    uint64_t limit = END_BLOCK * RB5_PRIMORIAL;
    size_t limitSqrt = ceil(sqrt(limit));
    fillFastLookupPrimes(limitSqrt, sieve);
    assignVectors();
    fillJumpLookups();
    fillLookupGeneral();
    sieve.clear();
    sieve.shrink_to_fit();
}

void initGlobals() {
    readInfoForProgram("boundsCompressFromSieve.txt\0", START_BLOCK, END_BLOCK); // might need & iirw
    readPrecomputedData();
}

//////////////////// end of reading in precomputed info 
///
//////////////////// start of sieving

void loopArray(uint32_t *primes, size_t &endo, size_t maxSize, uint64_t upperBound) {
    for (; endo < maxSize && (uint64_t)primes[endo] * primes[endo] < upperBound; endo++) {}
}

void checkEnds(uint64_t upperBound) {
    if (FAST32_ENDO != FAST32_AMT)
        loopArray(FAST32_PRIME_LIST, FAST32_ENDO, FAST32_AMT, upperBound);
    if (SLOW32_ENDO_LOOPS != SLOW32_AMT_LOOPS)
        loopArray(SLOW32_PRIME_LIST_LOOPS.data(), SLOW32_ENDO_LOOPS, SLOW32_AMT_LOOPS, upperBound);
    if (SLOW32_ENDO_NO_LOOPS != SLOW32_AMT_NO_LOOPS)
        loopArray(SLOW32_PRIME_LIST_NO_LOOPS.data(), SLOW32_ENDO_NO_LOOPS, SLOW32_AMT_NO_LOOPS, upperBound);
}

void applyWheelPrimes() {
    std::copy(std::cbegin(PATTERN), std::cend(PATTERN), std::begin(BUFFER)); 
}

void updateFast16Primes(uint64_t upperBound) {
    for (size_t p = 0; p < FAST16_AMT; p++) {
        uint64_t currIndex = FAST16_CURRENT_INDEX[p];
        uint16_t prime = FAST16_PRIME_LIST[p];
        uint8_t indexByModuloClass = prime % RB5_PRIMORIAL;
        uint8_t currMask = FAST16_MASK_INDEX[p];
        for (; currMask < BITS_PER_MASK && currIndex < upperBound; currIndex += (uint64_t)FAST16_JUMPS[p][currMask++]) 
            BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
        for (; currIndex < upperBound; ){
            currMask = 0;
            for (; currMask < BITS_PER_MASK && currIndex < upperBound; currIndex += (uint64_t)FAST16_JUMPS[p][currMask++]) 
                BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
        }
        FAST16_CURRENT_INDEX[p] = currIndex;
        FAST16_MASK_INDEX[p] = currMask;
    }
}

void updateFast32Primes(uint64_t upperBound) {
    for (size_t p = 0; p < FAST32_ENDO; p++) {
        if (FAST32_CURRENT_INDEX[p] >= upperBound) 
            continue;
        uint64_t currIndex = FAST32_CURRENT_INDEX[p];
        uint32_t prime = FAST32_PRIME_LIST[p];
        uint8_t indexByModuloClass = prime % RB5_PRIMORIAL;
        uint8_t currMask = FAST32_MASK_INDEX[p];
        for (; currMask < BITS_PER_MASK && currIndex < upperBound; currIndex += (uint64_t)FAST32_JUMPS[p][currMask++]) 
            BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
        for (; currIndex < upperBound; ){
            currMask = 0;
            for (; currMask < BITS_PER_MASK && currIndex < upperBound; currIndex += (uint64_t)FAST32_JUMPS[p][currMask++]) 
                BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
        }
        FAST32_CURRENT_INDEX[p] = currIndex;
        FAST32_MASK_INDEX[p] = currMask;
    }
}

void updateSlow32Loops(uint64_t upperBound) {
    for (size_t p = 0; p < SLOW32_ENDO_LOOPS; p++) {
        if (SLOW32_CURRENT_INDEX_LOOPS[p] >= upperBound) 
            continue;
        uint64_t currIndex = SLOW32_CURRENT_INDEX_LOOPS[p];
        uint64_t currBlock = SLOW32_CURRENT_BLOCK_LOOPS[p];
        uint32_t prime = SLOW32_PRIME_LIST_LOOPS[p];
        uint8_t currMask = SLOW32_MASK_INDEX_LOOPS[p];
        uint8_t indexByModuloClass = prime % RB5_PRIMORIAL;
        do {
            for (; currMask < BITS_PER_MASK && (currIndex = currBlock + (JUMP_VALUE[currMask] * prime) / RB5_PRIMORIAL) < upperBound; currMask++)
                BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
            if (currMask == BITS_PER_MASK) {
                currMask = 0;
                currBlock += prime;
            }
        } while (currIndex < upperBound);
        SLOW32_CURRENT_INDEX_LOOPS[p] = currIndex;
        SLOW32_CURRENT_BLOCK_LOOPS[p] = currBlock;
        SLOW32_MASK_INDEX_LOOPS[p] = currMask;
    }
}

void updateSlow32NoLoop(uint64_t upperBound) {
    for (size_t p = 0; p < SLOW32_ENDO_NO_LOOPS; p++) {
        if (SLOW32_CURRENT_INDEX_NO_LOOPS[p] >= upperBound) 
            continue;
        uint64_t currIndex = SLOW32_CURRENT_INDEX_NO_LOOPS[p];
        uint64_t currBlock = SLOW32_CURRENT_BLOCK_NO_LOOPS[p];
        uint32_t prime = SLOW32_PRIME_LIST_NO_LOOPS[p];
        uint8_t currMask = SLOW32_MASK_INDEX_NO_LOOPS[p];
        uint8_t indexByModuloClass = prime % RB5_PRIMORIAL;
        BUFFER[currIndex % BUFFER_SIZE] &= MASK_LOOKUP[indexByModuloClass][currMask];
        if (++currMask == BITS_PER_MASK) {
            currMask = 0;
            currBlock += prime;
        }
        SLOW32_CURRENT_INDEX_NO_LOOPS[p] = currBlock + (JUMP_VALUE[currMask] * prime) / RB5_PRIMORIAL;
        SLOW32_CURRENT_BLOCK_NO_LOOPS[p] = currBlock;
        SLOW32_MASK_INDEX_NO_LOOPS[p] = currMask;
    }
}

void update_sieve(uint64_t offset) {
    const uint64_t upperBound = offset + BUFFER_SIZE; 
    checkEnds(upperBound * RB5_PRIMORIAL);
    applyWheelPrimes();
    updateFast16Primes(upperBound);
    updateFast32Primes(upperBound);
    if (SLOW32_ENDO_LOOPS) {
        updateSlow32Loops(upperBound);
        if (SLOW32_ENDO_NO_LOOPS)
            updateSlow32NoLoop(upperBound);
    }
}

void sieve(uint64_t limit) {
    uint64_t offset = BLOCKS_TO_AUTO_READ;
    for (; offset < limit; offset += BUFFER_SIZE) {
        update_sieve(offset);
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
    sieve(END_BLOCK);
    return 0;
}

