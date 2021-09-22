############################################
# Alexandros Angelakis                      #
# csd4334                                   #
# Exercise 3 ~ HY255                        #
# csd4334@csd.uoc.gr                        #
#                                           #
#############################################


hash: symtablehash.o symtable.h testsymtab.c
	gcc -ansi -pedantic -Wall symtablehash.o testsymtab.c symtable.h -o hash.out

symtablehash.o: symtablehash.c symtable.h
	gcc -ansi -pedantic -Wall -c symtablehash.c


list: symtable.h symtablelist.o testsymtab.c
	gcc -ansi -pedantic -Wall symtablelist.o testsymtab.c symtable.h -o list.out

symtablelist.o: symtablelist.c symtable.h
	gcc -ansi -pedantic -Wall -c symtablelist.c


clean:
	rm -f *.o 
	rm -f *.out
