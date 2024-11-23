// source file for the single step optimzation 
//

#include "./header/SingleStepOptimization.hpp"
// #include "./header/IntegralIncludes.hpp"
// #include "./header/ContainerIncludes.hpp" // replace with ours when done

// TODO update uint32_t to std::uint32_t
// TODO consider using std::intptr_t or std::int32_t 
//  Reason: apparently we might get an index type that is signed plus I need
//      to conserve space when possible
namespace {
    // might just put this inside in the list file
    constexpr uint32_t list_end = UINT32_MAX;

    // unlocked is for single thread / batch update version
    // locked for multithread
    std::vector<uint32_t> list_of_heads_unlocked;
    std::vector<std::atomic<uint32_t>> list_of_heads_locked;
}

// TODO turn into a class?
// TODO move code and vectors to header?
// TODO same as the header file for this
// TODO add the actual code and includes
// TODO might be missing a function or two
// NOTE: we use memory_order::relaxed because we only care that things get done
//  not the specific order, loading or to do things 
namespace PlaceHolder{
    // load will be used till I see if I can do it without safely 
    // even though we know we don't need to
    uint32_t getHeadValueLocked(uint32_t headIndex) {
        return list_of_heads_locked[headIndex].load(memory_order::relaxed);
    }

    uint32_t getHeadValueUnlocked(uint32_t headIndex){
        return list_of_heads_unlocked[headIndex];
    }

    // need to profile this to see how expensive it is
    // inline or hardcode if too expensive
    // NOTE: mem order relaxed used because we only care that exhange gets done 
    //  if this turns out to not work in a function will pull into calling code
    //  which I am confident it will work there 
    uint32_t setHeadValueLocked(uint32_t headIndex, uint32_t newHead) {
        return list_of_heads_locked[headIndex].exchange(newHead, memory_order::relaxed);
    }

    uint32_t setHeadValueUnlocked(uint32_t headIndex, uint32_t newHead) {
        return std::exchange(list_of_heads_unlocked[headIndex], newHead);
    }


}
