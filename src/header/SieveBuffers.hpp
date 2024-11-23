#ifndef SIEVE_BUFFERS_HPP
#define SIEVE_BUFFERS_HPP


#include <ContainerIncludes.hpp> // for arrays idk 
#include <SieveConstants.hpp>    // for sieve bounds 

// TODO fix naming and typing 
// TODO change arrays to our own typing
namespace Sieves {
    std::array<uint8_t, BoundConstants::block_size> single_thread_sieve;
    
    std::array<
        std::array<uint8_t, BoundConstants::block_size>, 
        BoundConstants::block_count> multi_thread_sieve;

    void mergeSieveSection(std::size_t, std::size_t);
}

#endif
