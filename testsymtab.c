/*###########################################
# Alexandros Angelakis                      #
# csd4334                                   #
# Exercise 3 ~ HY255                        #
# csd4334@csd.uoc.gr                        #
#                                           #
#############################################*/

#include "symtable.h"

void discount(const char *pcKey, void *pvValue, void *pvExtra){
    long unsigned int discount = /*(long unsigned int)*/ ((long unsigned int*) pvExtra);
    long unsigned int price = /*(long unsigned int)*/ ((long unsigned int*) pvValue);
    long unsigned int price_after_discount = price - (discount * price / 100);

    printf("%s's price before the discount is -> %lu , after the discount is -> %lu\n", pcKey, price, price_after_discount);
}

void age(const char *pcKey, void *pvValue, void *pvExtra){
    long unsigned int birthYear = /*(long unsigned int)*/ ((long unsigned int*) pvValue);
    long unsigned int today = /*(long unsigned int)*/ ((long unsigned int*) pvExtra);
    long unsigned int age = today - birthYear;

    printf("%s's age is -> %lu\n", pcKey, age);
}



int main(){
    SymTable_T GraphicsCards, AmericanPresidents;

    printf("\n======== THE BEGINNING OF TEST FILE ========\n");

    printf("\nCreating a SymTable with Graphics Cards and their MSRP price...\n");
    GraphicsCards = SymTable_new();

    printf("\nAdding Graphics Cards in the table. (1) Success , (0) Failure...\n");
    printf("Inserting NVIDIA GEFORCE RTX 3070 in the table -> %d\n", SymTable_put(GraphicsCards, "NVIDIA GEFORCE RTX 3070", ( void *)499));
    printf("Inserting NVIDIA GEFORCE RTX 3060TI in the table -> %d\n", SymTable_put(GraphicsCards, "NVIDIA GEFORCE RTX 3060TI", (void *)399));
    printf("Inserting NVIDIA GEFORCE RTX 3080 in the table -> %d\n", SymTable_put(GraphicsCards, "NVIDIA GEFORCE RTX 3080", (void *)699));
    printf("Inserting NVIDIA GEFORCE RTX 3090 in the table -> %d\n", SymTable_put(GraphicsCards, "NVIDIA GEFORCE RTX 3090", (void *)1499));
    printf("Inserting NVIDIA GEFORCE RTX 3060 in the table -> %d\n", SymTable_put(GraphicsCards, "NVIDIA GEFORCE RTX 3060", (void *)329));
    printf("Inserting NVIDIA GEFORCE RTX 3080 in the table -> %d (Duplicate)\n", SymTable_put(GraphicsCards, "NVIDIA GEFORCE RTX 3080", (void *)699));
    printf("Inserting AMD RADEON RX 6900XT in the table -> %d\n", SymTable_put(GraphicsCards, "AMD RADEON RX 6900XT", (void *)999));
    printf("Inserting AMD RADEON RX 6800XT in the table -> %d\n", SymTable_put(GraphicsCards, "AMD RADEON RX 6800XT", (void *)649));
    printf("Inserting AMD RADEON RX 6700XT in the table -> %d\n", SymTable_put(GraphicsCards, "AMD RADEON RX 6700XT", (void *)479));
    printf("Inserting AMD RADEON RX 6800 in the table -> %d\n", SymTable_put(GraphicsCards, "AMD RADEON RX 6800", (void *)579));
    printf("Inserting NVIDIA GEFORCE RTX 3060 in the table -> %d (Duplicate)\n", SymTable_put(GraphicsCards, "NVIDIA GEFORCE RTX 3060", (void *)329));

    printf("\nPrinting the Graphics Cards with their MSRP price...\n");
    print(GraphicsCards); /* Prints their prices in hexadecimal. */

    printf("\nThe number of Graphics Cards in SymTable -> %u\n", SymTable_getLength(GraphicsCards));

    printf("\nRemoving some Graphics Cards from the table. (1) Success , (0) Failure...\n");
    printf("Removing NVIDIA GEFORCE RTX 3060TI from the table -> %d\n", SymTable_remove(GraphicsCards, "NVIDIA GEFORCE RTX 3060TI"));
    printf("Removing NVIDIA GEFORCE RTX 3080 from the table -> %d\n", SymTable_remove(GraphicsCards, "NVIDIA GEFORCE RTX 3080"));
    printf("Removing NVIDIA GEFORCE RTX 2080SUPER from the table -> %d\n", SymTable_remove(GraphicsCards, "NVIDIA GEFORCE RTX 2080SUPER"));
    printf("Removing AMD RADEON RX 6700XT from the table -> %d\n", SymTable_remove(GraphicsCards, "AMD RADEON RX 6700XT"));

    printf("\nPrinting the Graphics Cards with their MSRP price after the removes...\n");
    print(GraphicsCards); /* Prints their prices in hexadecimal. */

    printf("\nThe number of Graphics Cards in SymTable after the removes -> %u\n", SymTable_getLength(GraphicsCards));

    printf("\nSearching for Graphics Cards inside the SymTable. (1) Success , (0) Failure...\n");
    printf("Does RTX 3070 exist in the SymTable? -> %d\n", SymTable_contains(GraphicsCards, "NVIDIA GEFORCE RTX 3070"));
    printf("Does RTX 3060TI exist in the SymTable? -> %d\n", SymTable_contains(GraphicsCards, "NVIDIA GEFORCE RTX 3060TI"));
    printf("Does RX 6900XT exist in the SymTable? -> %d\n", SymTable_contains(GraphicsCards, "AMD RADEON RX 6900XT"));
    printf("Does RTX 3080 exist in the SymTable? -> %d\n", SymTable_contains(GraphicsCards, "NVIDIA GEFORCE RTX 3080"));
    printf("Does RX 6800 exist in the SymTable? -> %d\n", SymTable_contains(GraphicsCards, "AMD RADEON RX 6800"));

    printf("\nGetting the prices of some Graphics Cards inside the SymTable. (0) if a Graphics Card does not exist...\n");
    printf("NVIDIA GEFORCE RTX 3070's price -> %lu\n", (long unsigned int) ((long unsigned int*)SymTable_get(GraphicsCards, "NVIDIA GEFORCE RTX 3070")));
    printf("NVIDIA GEFORCE RTX 3060s price -> %lu\n", (long unsigned int) ((long unsigned int*)SymTable_get(GraphicsCards, "NVIDIA GEFORCE RTX 3060")));
    printf("AMD RADEON RX 6800XT's price -> %lu\n", (long unsigned int) ((long unsigned int*)SymTable_get(GraphicsCards, "AMD RADEON RX 6800XT")));
    printf("NVIDIA GEFORCE RTX 3090's price -> %lu\n", (long unsigned int) ((long unsigned int*)SymTable_get(GraphicsCards, "NVIDIA GEFORCE RTX 3090")));
    printf("NVIDIA GEFORCE RTX 3060TI's price -> %lu\n", (long unsigned int) ((long unsigned int*)SymTable_get(GraphicsCards, "NVIDIA GEFORCE RTX 3060TI")));

    printf("\nApplying on each Graphics Card an amount of 25 per cent discount...\n");
    SymTable_map(GraphicsCards, discount, (void *)25);


    printf("\nFree the memory of the SymTable with Graphics Card...\n");
    SymTable_free(GraphicsCards);

    printf("\n============================================================\n");

    printf("\nCreating a SymTable with the American Presidents of the last 50 years with their birth year...\n");
    AmericanPresidents = SymTable_new();

    printf("\nAdding the Presidents in the table. (1) Success , (0) Failure...\n");
    printf("Inserting Joe Biden in the table -> %d\n", SymTable_put(AmericanPresidents, "Joe Biden", ( void *)1942));
    printf("Inserting Donald Trump in the table -> %d\n", SymTable_put(AmericanPresidents, "Donald Trump", ( void *)1946));
    printf("Inserting Barack Obama in the table -> %d\n", SymTable_put(AmericanPresidents, "Barack Obama", ( void *)1961));
    printf("Inserting George W. Bush in the table -> %d\n", SymTable_put(AmericanPresidents, "George W. Bush", ( void *)1946));
    printf("Inserting Bill Clinton in the table -> %d\n", SymTable_put(AmericanPresidents, "Bill Clinton", ( void *)1946));
    printf("Inserting Ronald Reagan in the table -> %d\n", SymTable_put(AmericanPresidents, "Ronald Reagan", ( void *)1911));
    printf("Inserting George W. Bush in the table -> %d (Duplicate)\n", SymTable_put(AmericanPresidents, "George W. Bush", ( void *)1946));
    printf("Inserting Jimmy Carter in the table -> %d\n", SymTable_put(AmericanPresidents, "Jimmy Carter", ( void *)1924));
    printf("Inserting Gerald Ford in the table -> %d\n", SymTable_put(AmericanPresidents, "Gerald Ford", ( void *)1913));
    printf("Inserting Richard Nixon in the table -> %d\n", SymTable_put(AmericanPresidents, "Richard Nixon", ( void *)1913));
    printf("Inserting Barack Obama in the table -> %d (Duplicate)\n", SymTable_put(AmericanPresidents, "Barack Obama", ( void *)1961));

    printf("\nPrinting the American Presidents with their birth year...\n");
    print(AmericanPresidents); /* Prints their birth year in hexadecimal. */

    printf("\nThe number of Presidents in the table -> %u\n", SymTable_getLength(AmericanPresidents));

    printf("\nRemoving some Presidents from the table. (1) Success , (0) Failure...\n");
    printf("Removing Donald Trump from the table -> %d\n", SymTable_remove(AmericanPresidents, "Donald Trump"));
    printf("Removing Gerald Ford from the table -> %d\n", SymTable_remove(AmericanPresidents, "Gerald Ford"));
    printf("Removing John F. Kennedy from the table -> %d\n", SymTable_remove(AmericanPresidents, "John F. Kennedy"));
    printf("Removing Bill Clinton from the table -> %d\n", SymTable_remove(AmericanPresidents, "Bill Clinton"));
    printf("Removing Abraham Lincoln from the table -> %d\n", SymTable_remove(AmericanPresidents, "Abraham Lincoln"));

    printf("\nPrinting the American Presidents with their birth year after the removes...\n");
    print(AmericanPresidents); /* Prints their birth year in hexadecimal. */

    printf("\nThe number of Presidents in the table after the removes -> %u\n", SymTable_getLength(AmericanPresidents));

    printf("\nSearching for Presidents inside the SymTable. (1) Success , (0) Failure...\n");
    printf("Does Jimmy Carter exist in the SymTable? -> %d\n", SymTable_contains(AmericanPresidents, "Jimmy Carter"));
    printf("Does Barack Obama exist in the SymTable? -> %d\n", SymTable_contains(AmericanPresidents, "Barack Obama"));
    printf("Does Donald Trump exist in the SymTable? -> %d\n", SymTable_contains(AmericanPresidents, "Donald Trump"));
    printf("Does George W. Bush exist in the SymTable? -> %d\n", SymTable_contains(AmericanPresidents, "George W. Bush"));
    printf("Does Abraham Lincoln exist in the SymTable? -> %d\n", SymTable_contains(AmericanPresidents, "Abraham Lincoln"));

    printf("\nGetting the birth year of some American Presidents. (0) if a president does not exist...\n");
    printf("Barack Obama's birth year -> %lu\n", (long unsigned int) ((long unsigned int*)SymTable_get(AmericanPresidents, "Barack Obama")));
    printf("Donald Trump's birth year -> %lu\n", (long unsigned int) ((long unsigned int*)SymTable_get(AmericanPresidents, "Donald Trump")));
    printf("Gerald Ford's birth year -> %lu\n", (long unsigned int) ((long unsigned int*)SymTable_get(AmericanPresidents, "Gerald Ford")));
    printf("Ronald Reagan's birth year -> %lu\n", (long unsigned int) ((long unsigned int*)SymTable_get(AmericanPresidents, "Ronald Reagan")));
    printf("Abraham Lincoln's birth year -> %lu\n", (long unsigned int) ((long unsigned int*)SymTable_get(AmericanPresidents, "Abraham Lincoln")));

    printf("\nGetting the age of each American President in the SymTable...\n");
    SymTable_map(AmericanPresidents, age, (void *)2021);

    printf("\nFree the memory of the SymTable with American Presidents...\n");
    SymTable_free(AmericanPresidents);

    printf("\n======== END OF TEST FILE ========\n");
    return 0;
}
