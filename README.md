TODO fix docs in files   
TODO Complete todos in files   
TODO Fix make file so program can work   
TODO create or find way to nicely handle cli    
TODO fix a few file name bugs   
TODO profile best layout for some files   
TODO check if loop unrolling i worth with profiling   
Updates: Scope change listed in last commit now this project is just handling list of primes either from file or from stdin.  
CURRENT_STATE   
need to get IO hooked up and a few more things in place   
with how i programmed it we should be able to drop a few different multi thread versions to test the best one   
  
CURRENT USAGE   
None yet doesn't work as a program but will fix the make file   
Steps once program works   
1.) type make [need to type it twice with make -j since have dep bug]   
2.) type "./moveIt" to move data to the build/data for program   
3.) adjust the current bounds file [not user friendly that much]   
4.) ./prog.out > yourFileName.bin [or what ever extention]   
will give a short mapping of programs to txt files  
  
NOTE on Python3 files  
these files for the most part are just to generate various info in the project.  
I might just move them to their own directory but they just give info on how I  
got some of my values and literals  

  
BOUND INFO  
some information on the bounds and ranges I am planning to work with  
1.) I am planning to use 2^15 sieve block sizes per thread bounds listed below    
2.) I am also planning to use a bigger sieve that is based on thread count    
3.) from my python program for bounds I found the following    

STYLE GUIDES used  
C++: using the c++ core guidelines style guide as much as possible  
Python3: will use a linter when possible  
Bash: not sure for this one yet  

