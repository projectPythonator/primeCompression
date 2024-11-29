TODO add in automated checks for style guides chosen  
TODO fix README.md tab indenting (hopefully find a automated fix)  
Updates: project currently in migration to better portablility and faster code  
changes being made to support mutliple threads, have better cache usage  
and also able to bench and analyze it better.  
CURRENT_STATE  
old files use .cc and .h  
new files using .cpp and .hpp  
will move over the old files to new extentions and update make file later  
  
CURRENT USAGE  
currently you can try this out but its not that user friendly  
steps are  
1.) type make [need to type it twice with make -j since have dep bug]  
2.) type "./moveIt" to move data to the build/data for program  
3.) adjust the current bounds file [not user friendly that much]  
4.) ./prog.out > yourFileName.bin [or what ever extention]  
will give a short mapping of programs to txt files  
  
NOTE on Python3 files  
these files for the most part are just to generate various info in the project.  
I might just move them to their own directory but they just give info on how I  
got some of my values and literals  
like example would be the layout of the fastPrimesWithLoop  
I got this from printInfoForSievingMod30Class.py which just found cycles  

  
BOUND INFO  
some information on the bounds and ranges I am planning to work with  
1.) I am planning to use 2^15 sieve block sizes per thread bounds listed below  
2.) I am also planning to use a bigger sieve that is based on thread count  
3.) bigger sieve size will be max(8 * 2^15, n * 2^15)  
4.) TBD if n is a power of 2 or not  
5.) from my python program for bounds I found the following  
&nbsp;&nbsp;&nbsp;&nbsp;Small Sieve  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- we can fit the first 14998 primes with full loops + switch   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- we can fit the first 40883 primes into switch functions(a bit slower)   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- past this we can apply single step optimization code   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.) this code is slower per step but doesn't need to consider loops   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.) only one write per byte to the big sieve   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.) unfortunately has a single thread section but should be fast   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4.) lower bound is static start stated in bullet 2   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5.) upper bound is dynamic based on the bigger sieve size   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;so less bloated code that can handle mutliple threads   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;I might just opt to use a copy of bigger sieve stuct   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- this is all for the smaller 2^15 thread size sieve  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- I havent found a good way to merge sieves that isn't just  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;threads * 2^15 / threads (O(n) but has weird constant)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;vs (n log n) / threads  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;will have to do some tests later  
&nbsp;&nbsp;&nbsp;&nbsp;Big Sieve  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- starts at least at 278737th prime = 3932167   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- every write will have max(8, n) sieve segments per write  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- one thread per sieve segment will handle each segment  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- all segments will only deal with a prime once  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- by this we kinda keep them sorted and only traverse primes in the  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;current block  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- the upper bound goes upto the pi(sqrt(n)) minus smaller primes  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- the idea is to have a array of lists that store which primes are part  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;of that segment/block for us we will just use indexes for now  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- I might switch over to nodes and refs later but for now this will work  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- we apply similar single step optimization listed in smaller sieve  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- we also opt to apply preseiving during this time  
6.) very rough process listed below  
&nbsp;&nbsp;&nbsp;&nbsp;N = max(8, numThreads)  
&nbsp;&nbsp;&nbsp;&nbsp;1.) apply presieves  [N parallel]  
&nbsp;&nbsp;&nbsp;&nbsp;2.) apply big primes [N parallel]   
&nbsp;&nbsp;&nbsp;&nbsp;3.0) update big primes [single thread, can block 2 if current not done, concurrent to 3.1]   
&nbsp;&nbsp;&nbsp;&nbsp;3.1) this happens N times over   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3-1.) apply fast smalle primes [I concurrent in a queue]  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3-2.) apply fast medium primes [J concurrent in a queue]  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3-3.) apply slow medium primes [K concurrent in a queue]  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3-4.) update slow medium primes [same as 3.0 but blocks 3-3, and concurrent to next 3-5+]  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3-5.) apply thread sieves to big sieve segment [N parallel, technically blocks next 3.1 till done]   
&nbsp;&nbsp;&nbsp;&nbsp;4.) Once all sieve segments written print out each one   
&nbsp;&nbsp;&nbsp;&nbsp;4.) [single threaded, blocking till data copied to buffers then its concurrent to next iteration]  
&nbsp;&nbsp;&nbsp;&nbsp;4.) {blocking current iteration if IO is slow so, to solve this spawn threads to print io???}  
&nbsp;&nbsp;&nbsp;&nbsp;I am not sure if it is better to have 1, 2, 3.0 after 3.1 or before  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;technically we have more time to do 3.0 when its before  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;but after you have potential to do part of 2 write to buffer finnish 2 and do 3 currently   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;while doing IO so idk yet.  
&nbsp;&nbsp;&nbsp;&nbsp;blocking, 3.0 needs to happen before the next 2, and same for 3-4 otherwise no blocking, for IO  
&nbsp;&nbsp;&nbsp;&nbsp;you just need to write IO before 3.1 finishes otherwise you will have threads waiting to fill  
&nbsp;&nbsp;&nbsp;&nbsp;the IO buffers again I have some ideas on how to do to take advantage of this when I get there  

STYLE GUIDES used  
C++: using the c++ core guidelines style guide as much as possible  
Python3: will use a linter when possible  
Bash: not sure for this one yet  

