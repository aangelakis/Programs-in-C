/*###########################################
# Alexandros Angelakis                      #
# csd4334                                   #
# Exercise 3 ~ HY255                        #
# csd4334@csd.uoc.gr                        #
#                                           #
#############################################*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

typedef struct SymTable *SymTable_T;


/* This function allocates memory for a new empty SymTable and returns a pointer to it. */
SymTable_T SymTable_new(void);


/* This function frees all the allocated memory used by 'oSymTable'. */
void SymTable_free(SymTable_T oSymTable);


/* This function returns the number of bindings in 'oSymTable'.
   It is checked runtime error for 'oSymTable' to be NULL. */
unsigned int SymTable_getLength(SymTable_T oSymTable);


/* This function adds a new binding to 'oSymTable' with key 'pcKey' and value 'pvValue', 
   only if there is no binding with the same pcKey in the list. It returns one (1) in success or zero (0) in failure.
   It is checked runtime errors for 'oSymTable', 'pcKey' and 'pvValue' to be NULL. */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue);


/* This function removes a binding from oSymTable with a specific key ('pcKey'). If that key ('pcKey')
   does not exist in the 'oSymTable' then do nothing. Returns one (1) in success or zero (0) in failure.
   It is checked runtime errors for 'oSymTable' and 'pcKey' to be NULL. */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey);


/* This function is checking if there is a binding in 'oSymTable' with key 'pcKey'. If it exists, return 1. Otherwise return 0.
   It is checked runtime error for 'oSymTable' and 'pcKey' to be NULL. */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);


/* This function returns the value of a binding with key 'pcKey' in 'oSymTable'.
   Otherwise it returns NULL. It is checked runtime errors for 'oSymTable' and 'pcKey' to be NULL. */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey);


/* This function applies the function *pfApply to each binding in the 'oSymTable'. It is checked runtime error
   for 'oSymTable' and '*pfApply' to be NULL. */
void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra);


/* A function that prints the bindings inside the 'oSymTable'. */
void print(SymTable_T oSymTable);
