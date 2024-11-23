// adding this file in for the ds that manages multiple linked lists

#ifndef SINGLE_STEP_OPTIMIZATION_HPP
#define SINGLE_STEP_OPTIMIZATION_HPP
// #include "./header/IntegralIncludes.hpp"
// #include "./header/ContainerIncludes.hpp" // stays in the header?

// TODO add includes
// TODO fix the naming of the namespace
// TODO make the functoins into class methods maybe
// NOTE 1: locked is for when we have each thread update its own nodes as part 
//  of the loop process.
// NOTE 2: unlocked is for single thread or when we do batch updates since 
//  batches single threaded, we might need a mutex but will consider that when
//  closer to done and when I got to compare as its external.
namespace PlaceHolder {
    uint32_t getHeadValueLocked(uint32_t);
    uint32_t getHeadValueUnlocked(uint32_t);

    // need to profile this to see how expensive it is
    // inline or hardcode if too expensive
    uint32_t setHeadValueLocked(uint32_t, uint32_t);
    uint32_t setHeadValueUnlocked(uint32_t, uint32_t);
}

#endif
