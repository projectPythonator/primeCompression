// place holder file for now
// the idea is that I will use a circular queue each with n linked lists
// (one list per thread) and each node in the queue represents a block
// of (30 * 2**15) * n threads, while each linked list represents 30 * 2 ** 15
// primes, I might hard limit/ min limit the amount each block represents but 
// but still debating on that one. this way each prime only needs to be 
// iterated on if the prime is in the current block for slowprimeswithcheck
// i might use similar thing too or I might just stick with the check
// I am split since technically all the primes in the greater block are size
// get iterated on at lesat once per iteration but for each smaller one 
// a check is needed since it is not garuenteeed faster primes I believe are
// safe from this even on the smaller blocks will need to add in this python
// script to show how I am getting my bounds
