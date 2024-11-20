// source file for the single step optimzation 
//


// TODO same as the header file for this
// TODO add the actual code and includes
// TODO might be missing a function or two
namespace PlaceHolder{
    void updatePrimeRecordInfo(std::size_t primeIndex) {
        // happens in parrallel
        // update each info for each sieve 
        // like its current prime mod index 
        // its current position in the update new sieve block
        // maybe its over all prime block or at the very least a offset of its current block
        // does not actually move the prime node
    }
    
    // find better name for the parameter
    void updatePrimeRecordPlacement(std::size_t blockIndex) {
        // happens in single thread 
        // maybe set mutex on here
        // for each prime in block
        //      read its new sieve position
        //      remove node from current position
        //      move to next updated block position
        // unset the mutex for the block
        // can happen currently to when the other threads are updating non single step sections
        // other threads will block untill this is done if they finish their sections before 
        // the positions are updated
        // NOTE I might update this to break it up abit
    }

    // better name for the span??/
    void sievePrimesInRange(std::span<uint8_t> sieve, std::span<std::size_t> blockOfPrimeIndexes) {
        // happens in parrallel with other threads but gets blocks till the previous block updated
        // wait till mutex not locked
        // (continue when unlocked but don't lock since nothing happens here
        // for each index in span
        //      get currIndex from prime info
        //      sieve[currIndex] &= bitmasks_lookup[primeMod][currMask];
        //      updatePrimeRecordInfo(index)
        // idk if better to pull update call into this function or pass sieve to function call maybe neither
        // idk if I want this section handled in lock free queue ranges 
        //      if it is you just return and handle next and everyone blocks till everyone done 
        //      if not then you just sleep till everyone else done 
        //  after this threads will merge their data into the bigger sieves block or all into one 
        //  then send it off to be printed later
    }



}
