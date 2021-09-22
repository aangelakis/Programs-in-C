/*###########################################
# Alexandros Angelakis                      #
# csd4334                                   #
# Exercise 3 ~ HY255                        #
# csd4334@csd.uoc.gr                        #
#                                           #
#############################################*/


#include "symtable.h"
#define BUCKETS 509
#define HASH_MULTIPLIER 65599


/* The struct of each node of the list. */
struct node {
    char* key;
    void* value;
    struct node *next;
};


/* The struct of SymTable. */
struct SymTable {
    struct node **head;
    unsigned int count;
};


/* Returns a hash code for pcKey. */
static unsigned int SymTable_hash(SymTable_T oSymTable, const char *pcKey){
	size_t ui;
	unsigned int uiHash = 0U;

	for (ui = 0U; pcKey[ui] != '\0'; ui++){ /* While pcKey is not over. */
		uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui]; /* The hash function. */
    }

    return uiHash % 509; /* Return the hash code for pcKey. */
}


/* This function applies the function *pfApply to each binding in the 'oSymTable'. It is checked runtime error
   for 'oSymTable' and '*pfApply' to be NULL. */
void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),const void *pvExtra){
    int i;
    struct node *traverse = NULL; /* A pointer to struct node that is going to traverse the list of each bucket in oSymTable. */

    assert(oSymTable != NULL); /* Checked runtime error. */
    assert(pfApply != NULL); /* Checked runtime error. */

    for(i = 0; i < BUCKETS; i++){ /* For each bucket in 'oSymTable'. */
        traverse = oSymTable->head[i];

        while(traverse != NULL){ /* While traverse node does not point to NULL. */
            pfApply(traverse->key, traverse->value, (void*)pvExtra);
            traverse = traverse->next;
        }
    }
}


/* This function frees all the allocated memory used by 'oSymTable'. */
void SymTable_free(SymTable_T oSymTable){
    int i;
    struct node *traverse = NULL; /* A pointer to struct node that is going to traverse the list of each bucket in oSymTable. */
    struct node *previous = NULL; /* A pointer to struct node that is going to point at the previous node where traverse points. */

    assert(oSymTable != NULL); /* Checked runtime error. */

    for(i = 0; i < BUCKETS; i++){ /* For each bucket in 'oSymTable'. */
        traverse = oSymTable->head[i];

        while(traverse != NULL){ /* While traverse node does not point to NULL. */
            previous = traverse;
            traverse = traverse->next;

            free(previous->key); /* Free the key of each binding. */
            previous->key = NULL;

            free(previous); /* Free the node of each binding. */
            previous = NULL;
        }
    }

    oSymTable->count = 0;
    free(oSymTable->head); /* Free the hash table. */
    oSymTable->head = NULL;

    free(oSymTable); /* Free the 'oSymTable'. */
    oSymTable = NULL;
}


/* This function returns the value of a binding with key 'pcKey' in 'oSymTable'.
   Otherwise it returns NULL. It is checked runtime errors for 'oSymTable' and 'pcKey' to be NULL. */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
    struct node *traverse = NULL; /* A pointer to struct node that is going to traverse the list of each bucket in oSymTable, to check if pcKey exists in 'oSymTable'. */
    unsigned int hash_result = 0U; /* The hash code for pcKey. */

    assert(oSymTable != NULL); /* Checked runtime error. */
    assert(pcKey != NULL); /* Checked runtime error. */

    hash_result = SymTable_hash(oSymTable, pcKey);
    traverse = oSymTable->head[hash_result];

    while((traverse != NULL) && (strcmp(pcKey,traverse->key) != 0)){ /* While traverse is not at the end of the list and the key is not equal to traverse's key. */
        traverse = traverse->next;
    }

    if(traverse != NULL){  /* If the binding with key 'pcKey' exists in 'oSymTable', then return its value. */
        return traverse->value;
    }
    return NULL; /* Return NULL if the binding with the key 'pcKey' does not exist in 'oSymTable'. */
}


/* This function is checking if there is a binding in 'oSymTable' with key 'pcKey'. If it exists, return 1. Otherwise return 0.
   It is checked runtime error for 'oSymTable' and 'pcKey' to be NULL. */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    struct node *traverse = NULL; /* A pointer to struct node that is going to traverse the list of each bucket in oSymTable, to check if pcKey exists in 'oSymTable'. */
    unsigned int hash_result = 0U; /* The hash code for pcKey. */

    assert(oSymTable != NULL); /* Checked runtime error. */
    assert(pcKey != NULL); /* Checked runtime error. */

    hash_result = SymTable_hash(oSymTable,pcKey);
    traverse = oSymTable->head[hash_result];

    while((traverse != NULL) && (strcmp(pcKey,traverse->key) != 0)){ /* While traverse is not at the end of the list and the key is not equal to traverse's key. */
        traverse = traverse->next;
    }

    return (traverse != NULL); /* Returns 1 if the 'oSymTable' contains the pcKey, 0 otherwise. */
}


/* This function removes a binding from oSymTable with a specific key ('pcKey'). If that key ('pcKey')
   does not exist in the 'oSymTable' then do nothing. Returns one (1) in success or zero (0) in failure.
   It is checked runtime errors for 'oSymTable' and 'pcKey' to be NULL. */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    unsigned int hash_result = 0U; /* The hash code for pcKey. */
    struct node *traverse = NULL; /* A pointer to struct node that is going to traverse the list of each bucket in oSymTable, to check if pcKey exists in 'oSymTable'. */
    struct node *previous = NULL; /* A pointer to struct node that is going to point at the previous node where traverse points. */

    assert(oSymTable != NULL); /* Checked runtime error. */
    assert(pcKey != NULL); /* Checked runtime error. */

    hash_result = SymTable_hash(oSymTable,pcKey);
    traverse = oSymTable->head[hash_result];
    
    while(traverse != NULL){ /* While traverse node does not point to NULL. */
        if(strcmp(pcKey, traverse->key) == 0){ /* If pcKey exists in 'oSymTable' remove it. */
            if(previous == NULL){ /* If the node the pcKey exists is the head of the list of the specific bucket. */
                oSymTable->head[hash_result] = oSymTable->head[hash_result]->next;
            }
            else{
                previous->next = traverse->next;
            }
            traverse->next = NULL;
            free(traverse->key);
            free(traverse);
            oSymTable->count--;

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
    unsigned int hash_result = 0U; /* The hash code for pcKey. */
    struct node *new_node = NULL; /* A pointer to struct node to insert in the 'oSymTable', if 'pcKey' does not exist in oSymTable. */

    assert(oSymTable != NULL); /* Checked runtime error. */
    assert(pcKey != NULL); /* Checked runtime error. */

    hash_result = SymTable_hash(oSymTable,pcKey);
    new_node = malloc(sizeof(struct node)); /* Allocate memory for the new_node. */

    if(new_node == NULL){ /* If malloc can not find memory for new_node exit. */
        printf("Error Allocating Memory\n");
        exit(1);
    }

    if(oSymTable->head[hash_result] == NULL){ /* If the bucket with the specific hash code is empty, then just insert the node in 'oSymTable'. */
        new_node->next = NULL;
    }
    else{ /* If the bucket with the specific hash code is not empty, then traverse the list to check if it already exists and if not, insert it in 'oSymTable. */
        if(SymTable_contains(oSymTable,pcKey)){ /* If pcKey exists do nothing and return 0. */
            printf("%s already exists in the list\n", pcKey);
            free(new_node);
            return 0; /* Return failure (0). */
        }
        new_node->next = oSymTable->head[hash_result];
    }

    new_node->key = malloc(strlen(pcKey) + 1);

    if(new_node->key == NULL){ /* If malloc can not find memory for the new_node's key exit. */
        printf("Error Allocating Memory\n");
        exit(1);
    }
    
    strcpy(new_node->key,pcKey);
    new_node->value = (void *)pvValue;
    oSymTable->head[hash_result] = new_node;

    oSymTable->count++;

    return 1; /* Return success (1). */
}


/* This function returns the number of bindings in 'oSymTable'.
   It is checked runtime error for 'oSymTable' to be NULL. */
unsigned int SymTable_getLength(SymTable_T oSymTable){

    assert(oSymTable != NULL); /* Checked runtime error. */

    return oSymTable->count; /* Return the count of oSymTable's bindings. */
}


/* This function allocates memory for a new empty SymTable and returns a pointer to it. */
SymTable_T SymTable_new(void){
    int i; /* A variable to initialize every bucket with NULL. */
    SymTable_T new_SymTable; /* A new SymTable ADT. */

    new_SymTable = malloc(sizeof(SymTable_T)); /* Allocate memory for the new SymTable_T. */

    if(new_SymTable == NULL){ /* If malloc can not find memory for new_Symtable exit. */
        printf("Error Allocating Memory\n");
        exit(1);
    }

    new_SymTable->count = 0U; /* Initialize the count of new_SymTable's hash table nodes. */
    new_SymTable->head = malloc(BUCKETS * sizeof(struct node)); /* Allocate memory for the hash table. */

    if(new_SymTable->head == NULL){ /* If malloc can not find memory for the hash table exit. */
        printf("Error Allocating Memory\n");
        exit(1);
    }

    for(i = 0; i < BUCKETS; i++){ /* Initialize each brucket with NULL. */
        new_SymTable->head[i] = NULL;
    }

    return new_SymTable;
}


/* A function that prints the bindings inside the 'oSymTable'. */
void print(SymTable_T oSymTable){
    int i;
    struct node *traverse = NULL; /* A pointer to struct node for each bucket that is going to point to the head of each list. */

    assert(oSymTable); /* Checked runtime error. */

    for(i = 0; i < BUCKETS; i++){ /* For each bucket in the 'oSymTable'. */
        traverse = oSymTable->head[i];
        if(traverse != NULL){ /* If the specific bucket is not empty then print the list. */
            printf("Bucket[%d]'s list: ",i);

            while(traverse != NULL){ /* While traverse is not at the end of the list, then print the keys of each node. */
                printf("%s goes with %p -> ", traverse->key, traverse->value); /* Print. */
                traverse = traverse->next;
            }

            printf("\n");
        }
    }
}
