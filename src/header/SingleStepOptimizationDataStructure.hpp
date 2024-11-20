// adding this file in for the ds that manages multiple linked lists

// TODO fix the naming of the namespace
// TODO make the functoins into class methods maybe
namespace PlaceHolder {

    void updatePrimeRecordInfo(std::size_t);
    // this function might need a span/array if I make it generalized
    void updatePrimeRecordPlacement(std::size_t); 

    //might be missing one or two parameters
    void sievePrimesInRange(std::span<std::size_t>);

    // class vars
    // mutex maybe
    // likely want to hold the bigger sieves in the class
    // maybe have what range each element of each block of sieves is represented as lists
    //  - for the smaller sized ones I was planning on maybe doing it per byte
    //  - for the bigger ones I was planning on doing each big sieve as a section of its own smaller ones
    // might be forgeting some
}
