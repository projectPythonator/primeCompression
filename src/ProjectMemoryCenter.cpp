#include "header/ProjectMemoryCenter.hpp"

namespace { 
    constexpr int InputTask = 0;
    std::array<std::atomic<std::size_t>, 4> task_queue_inds = {0};
    std::array<std::size_t, 4> task_queue_sizes = {0};
}

namespace MemoryPools {
    std::size_t getNextTask(std::size_t taskNumber) {
        std::size_t rTask = task_queue_inds[taskNumber].fetch_add(1u, std::memory_order_relaxed);
        return rTask % task_queue_sizes[taskNumber];
    }

}
