Lab #4 README
Joshua Newman, Andy Weaver
2/28/2020

- Per the lab description, the kernel.c code was modified to:
-- added a function runProgram(int, int, int) that uses the blackDOS functions
   putInMemory(int, int, char) and launchProgram(int) to read a program
   from the disk, then place in the selected segment of memory
-- used the provided kitty1 and kitty2 programs to initally test
-- used the provided Stenv program to test changing the screen colors and test
   running a mutiple-sector program
-- compiled the fib.c code and used it to test the blackdos.h header
-- also tested with a pi calculation program and a simple vowel vs consonant
   test program (both 1 sector programs)
