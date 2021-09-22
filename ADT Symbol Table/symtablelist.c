/*###########################################
# Alexandros Angelakis                      #
# csd4334                                   #
# Exercise 3 ~ HY255                        #
# csd4334@csd.uoc.gr                        #
#                                           #
#############################################*/


#include "symtable.h"


/* The struct of each node of the list. */
struct node {
    char* key;
    void* value;
    struct node *next;
};


/* The struct of SymTable. */
struct SymTable {
    struct node *head;
    unsigned int length;
};


/* This function applies the function *pfApply to each binding in the 'oSymTable'. It is checked runtime error
   for 'oSymTable' and '*pfApply' to be NULL. */
void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra){
    struct node *traverse = NULL; /* A pointer to struct node that is going to traverse the list of oSymTable. */

    assert(oSymTable != NULL); /* Checked runtime error. */
    assert(pfApply != NULL); /* Checked runtime error. */

    traverse = oSymTable->head;

    while(traverse != NULL){ /* While traverse is not at the end of the list. */
        pfApply(traverse->key, traverse->value, (void *)pvExtra); /* Apply the pfApply function to each binding. */
        traverse = traverse->next;
    }
}


/* This function frees all the allocated memory used by 'oSymTable'. */
void SymTable_free(SymTable_T oSymTable){
    struct node *traverse = NULL; /* A pointer to struct node that is going to traverse the list of oSymTable. */
    struct node *previous = NULL; /* A pointer to struct node that is going to point at the previous node where traverse points. */

    if(oSymTable != NULL){ /* If 'oSymTable' is NULL then do nothing. */
        traverse = oSymTable->head;

        while(traverse != NULL){ /* While traverse is not at the end of the list. */
            previous = traverse;
            traverse = traverse->next;

            free(previous->key); /* Free the key of each binding. */
            previous->key = NULL;

            free(previous); /* Free the node of each binding. */
            previous = NULL;
        }

        oSymTable->length = 0;
        oSymTable->head = NULL;

        free(oSymTable); /* Free the 'oSymTable'. */
        oSymTable = NULL;
    }
}


/* This function returns the value of a binding with key 'pcKey' in 'oSymTable'.
   Otherwise it returns NULL. It is checked runtime errors for 'oSymTable' and 'pcKey' to be NULL. */
void* SymTable_get(SymTable_T oSymTable, const char *pcKey){
    struct node *traverse = NULL; /* A pointer to struct node that is going to traverse the list of oSymTable, to check if pcKey exists in the list. */

    assert(oSymTable != NULL); /* Checked runtime error. */
    assert(pcKey != NULL); /* Checked runtime error. */

    traverse = oSymTable->head;

    while((traverse != NULL) && (strcmp(pcKey,traverse->key) != 0)){ /* While traverse is not at the end of the list and the key is not equal to traverse's key. */
        traverse = traverse->next;
    }

    if(traverse != NULL){ /* If the binding with key 'pcKey' exists in the list, then return its value. */
        return traverse->value;
    }
    return NULL; /* Return NULL if the binding with the key 'pcKey' does not exist in the list. */
}


/* This function is checking if there is a binding in 'oSymTable' with key 'pcKey'. If it exists, return 1. Otherwise return 0.
   It is checked runtime error for 'oSymTable' and 'pcKey' to be NULL. */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    struct node *traverse = NULL; /* A pointer to struct node that is going to traverse the list of oSymTable, to check if pcKey exists in the list. */

    assert(oSymTable != NULL); /* Checked runtime error. */
    assert(pcKey != NULL); /* Checked runtime error. */

    traverse = oSymTable->head;

    while((traverse != NULL) && (strcmp(pcKey,traverse->key) != 0)){ /* While traverse is not at the end of the list and the key is not equal to traverse's key. */
        traverse = traverse->next;
    }

    return (traverse != NULL); /* Returns 1 if the 'oSymTable' contains the pcKey, 0 otherwise. */
}


/* This function removes a binding from oSymTable with a specific key ('pcKey'). If that key ('pcKey')
   does not exist in the 'oSymTable' then do nothing. Returns one (1) in success or zero (0) in failure.
   It is checked runtime errors for 'oSymTable' and 'pcKey' to be NULL. */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    struct node *traverse = NULL; /* A pointer to struct node that is going to traverse the list of oSymTable, to check if pcKey exists in the list. */
    struct node *previous = NULL; /* A pointer to struct node that is going to point at the previous node where traverse points. */

    assert(oSymTable != NULL); /* Checked runtime error. */
    assert(pcKey != NULL); /* Checked runtime error. */

    traverse = oSymTable->head;

    while(traverse != NULL){ /* While traverse node does not point to NULL. */
        if(strcmp(pcKey, traverse->key) == 0){ /* If pcKey exists in the list remove it. */
            if(previous == NULL){ /* If the node the pcKey exists is the head of the list. */
                oSymTable->head = oSymTable->head->next;
            }
            else{
                previous->next = traverse->next;
            }
            traverse->next = NULL;
            free(traverse->key);
            free(traverse);
            oSymTable->length--;

            return 1; /* Return success (1). */
        }
        previous = traverse;
        traverse = traverse->next;
    }
    printf("%s does not exist in the list\n", pcKey);

    return 0; /* Return failure (0). */
}


/* This function adds a new binding to 'oSymTable' with key 'pcKey' and value 'pvValue', 
   only if there is no binding with the same pcKey in the list. It returns one (1) in success or zero (0) in failure.
   It is checked runtime errors for 'oSymTable', 'pcKey' and 'pvValue' to be NULL. */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){
    struct node *new_node = NULL; /* A pointer to struct node to insert in the list if pcKey does not exist in the list. */

    assert(oSymTable != NULL); /* Checked runtime error. */
    assert(pcKey != NULL); /* Checked runtime error. */

    new_node = malloc(sizeof(struct node)); /* Allocating memory for the new_node. */

    if(new_node == NULL){
        printf("Error Allocating Memory\n");
        exit(1);
    }

    if(SymTable_getLength(oSymTable) == 0){ /* If the list is empty then just put the new pcKey in the beginning of the list. */
        new_node->next = NULL;
    }
    else{
        if(SymTable_contains(oSymTable,pcKey)){ /* If pcKey exists do nothing and return 0. */
            printf("%s already exists in the list\n", pcKey);
            free(new_node);
            return 0; /* Return failure (0). */
        }
        new_node->next = oSymTable->head;
    }

    new_node->key = malloc(strlen(pcKey) + 1);
    
    if(new_node->key == NULL){
        printf("Error Allocating Memory\n");
        exit(1);
    }

    strcpy(new_node->key,pcKey);
    new_node->value = (void *)pvValue;
    oSymTable->head = new_node;

    oSymTable->length++;

    return 1; /* Return success (1). */
}


/* This function returns the number of bindings in 'oSymTable'.
   It is checked runtime error for 'oSymTable' to be NULL. */
unsigned int SymTable_getLength(SymTable_T oSymTable){

    assert(oSymTable != NULL); /* Checked runtime error. */

    return oSymTable->length; /* Return the length of oSymTable list. */
}


/* This function allocates memory for a new empty SymTable and returns a pointer to it. */
SymTable_T SymTable_new(void){

    SymTable_T new_SymTable = NULL; /* A new SymTable ADT. */

    new_SymTable = malloc(sizeof(SymTable_T)); /* Allocate memory for the new SymTable_T. */

    if(new_SymTable == NULL){
        printf("Error Allocating Memory\n");
        exit(1);
    }

    new_SymTable->length = 0U; /* Initialize the length of new_SymTable's list. */
    new_SymTable->head = NULL; /* Initialize the head of new_SymTable's list. */

    return new_SymTable;
}


/* A function that prints the bindings inside the 'oSymTable'. */
void print(SymTable_T oSymTable){
    struct node *traverse = NULL; /* A pointer to struct node that is going to traverse the list of oSymTable, to print the key of each node. */
    
    assert(oSymTable != NULL); /* Checked runtime error. */

    traverse = oSymTable->head;

    while(traverse != NULL){ /* While traverse does not point at the end of the list. */
        printf("%s goes with %p\n", traverse->key, traverse->value); /* Print. */
        traverse = traverse->next;
    }
}
