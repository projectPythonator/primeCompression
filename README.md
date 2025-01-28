TODO touch up function docs in files(mostly done)   
TODO add comments to namespace variables and source file namespace scoped functions   
TODO Complete todos in files(updated todos and getting some done)   
TODO Put the program together so it works   
TODO create or find way to nicely handle cli wip going okay for now    
TODO profile best layout for some files   
TODO check if loop unrolling i worth with profiling   
Updates: Scope change listed in last commit now this project is just handling list of primes either from file or from stdin.  
   
CURRENT_STATE   
need to get IO hooked up and a few more things in place   
Hooked up meaning I need to call the right functions then it hsould work.   
Currently going with this method, We will use tasks for each stage of compresssion.   
Each stage below would be put into a queue allowing for multithreading.  
Stage example: input -> convert text to numbers -> compress numbers into RB5 -> output.   

  
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

