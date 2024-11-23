#ifndef SINGLE_STEP_OPTIMIZATION_HPP
#define SINGLE_STEP_OPTIMIZATION_HPP

#include "ArrayList.hpp"
#include "IntegralIncludes.hpp"
#include "ContainerIncludes.hpp" // stays in the header?

// TODO missing 1 or 2 includes 
// TODO make the functoins into class methods maybe
// NOTE 1: locked is for when we have each thread update its own nodes as part 
//  of the loop process.
// NOTE 2: unlocked is for single thread or when we do batch updates since 
//  batches single threaded, we might need a mutex but will consider that when
//  closer to done and when I got to compare as its external.
namespace SingleStepSection {
    uint32_t getHeadValueLocked(uint32_t);
    uint32_t getHeadValueUnlocked(uint32_t);

    // need to profile this to see how expensive it is
    // inline or hardcode if too expensive
    int32_t setHeadValueLocked(uint32_t, uint32_t);
    uint32_t setHeadValueUnlocked(uint32_t, uint32_t);
}

#endif
