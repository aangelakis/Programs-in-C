# Alexandros Angelakis                      #
# csd4334                                   #
# Exercise 2 ~ HY255                        #
# csd4334@csd.uoc.gr                        #
# angelakis@ics.forth.gr                    #

Answer for question 1:
Functions ms_copy, ms_ncopy, ms_concat and ms_nconcat could
use the assert function to check if the size of the destination
array is enough, but since the functions in the "string.h" header file
does not check these mistakes by itself, we can also do not check it.


Answer for question 2:
Since the parameter length in functions ms_ncopy, ms_nconcat and ms_ncompare
is type of size_t ( unsigned int ), there is no reason to check if it has
a negative value. But if it has a negative value, because of its type, the
program will take its unsigned value in 2's complement.


Function ms_search for the arrays returns a pointer to a character,
so my return value has no array brackets.


I searched for every function how it works on the internet,
and my functions work the same way.


Every function is checked for runtime NULL pointer input with assert.
