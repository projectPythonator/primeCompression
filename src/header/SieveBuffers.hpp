#ifndef SIEVE_BUFFERS_HPP
#define SIEVE_BUFFERS_HPP

#include <Vector.hpp> // need this line for arrays and vectors????
#include <SieveConstants.hpp> // need this line for arrays and vectors????

// TODO fix naming and typing 
namespace Sieves {
    Array<uint8_t, SmallSieveInformation::THREAD_SIEVE_SIZE> single_thread_sieve; // maybe need better naming
    Vector<Array<uint8_t, SmallSieveInformation::THREAD_SIEVE_SIZE>> multi_thread_sieves; // maybe need better naming

    // not sure if want this one
    // TODO fix write sieve size name
    Array<uint8_t, SmallSieveInformation::WRITE_SIEVE_SIZE> single_thread_sieve; // maybe need better naming

}

#endif
