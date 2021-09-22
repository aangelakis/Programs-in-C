/*###########################################
# Alexandros Angelakis                      #
# csd4334                                   #
# Exercise 3 ~ HY255                        #
# csd4334@csd.uoc.gr                        #
# angelakis@ics.forth.gr                    #
#############################################*/

1) I made the Symtable_put function so it adds the new node at the beggining of the list, to reduce the time complexity of the function.

2) I added a new function in symtable.h ("void print(Symtable_T oSymTable);") to print each key with its value. The value is in hexadecimal.

3) In testsymtab.c i tested two symtables, one for graphics card and their price and one for all the american presidents the last 50 years.

My previous knowledge from the course: HY240 Data Structures, made this assignment a lot easier.

Assignment took about 6-8 hours to complete.

Bonus: I tried implementing the bonus part (expanding hash table) but I couldn't because of some segmentation faults.
       It was working in some cases, but I decided not to include it in my solution of this exercise.
       Here's how I tried implementing it.

First of all, I initialized three new functions, the first one -> int SymTable_isExpandable(SymTable_T oSymTable); is checking if oSymTable is expandable. If you are to put a new node in the table
                                                                  and the number of buckets in it surpass a limit, then return 1 (Expandable). 0 otherwise (not Expandable). */

                                                 the second one -> int SymTable_expand(SymTable_T oSymTable); is expanding the oSymTable.

                                                 and the third one -> int SymTable_putWithoutExpanding(SymTable_T oSymTable, const char *pcKey, const void *pvValue); is putting bindings into oSymTable
                                                                      without checking if it needs expanding.

I also had a global variable -> unsigned int current_buckets = 509;  Initialize the current buckets with 509 (the first limit).


My implementation of the function SymTable_isExpandable(...):

    /* Checking if oSymTable is expandable. If you are to put a new node in the table
        and the number of buckets in it surpass a limit, then return 1 (Expandable).
         0 otherwise (not Expandable). */
    int SymTable_isExpandable(SymTable_T oSymTable){
        unsigned int expand_num = oSymTable->count;

        if(expand_num == 65521 ){
            return 0;
        }

         return ((expand_num == 2) || (expand_num == 5) ||
           (expand_num == 2053) || (expand_num == 4093) ||
           (expand_num == 8191) || (expand_num == 16381) ||
           (expand_num == 32771));
    }


My implementation of the function SymTable_expand(...):

    /* This function expands the oSymTable, when it's needed. Returns 1 in success, 0 otherwise. */
    int SymTable_expand(SymTable_T oSymTable){
        unsigned int expand_num = oSymTable->count; /* The number of bindings in oSymTable if we put a new binding in it. */
        SymTable_T tmp_SymTable = NULL; /* The temporary SymTable. */
        struct node *traverse = NULL, *previous = NULL;
        int i;
        unsigned int old_buckets = current_buckets;
        unsigned int new_buckets = 0U;
        print(oSymTable);
        tmp_SymTable = SymTable_new(); /* Allocating memory for the temporary SymTable. */

        for(i = 0; i < old_buckets; i++){ /* Copying the hash table of oSymTable with the old number of buckets to a temporary hash table. */
            traverse = oSymTable->head[i];
            while(traverse != NULL){
                SymTable_putWithoutExpanding(tmp_SymTable, traverse->key, traverse->value);
                traverse = traverse->next;
            }
        }

        switch(expand_num){ /* Increase the number of bruckets. */
            case 509: 
                new_buckets = 1021;
                break;
            case 1021:
                new_buckets = 2053;
                break;
            case 2053:
                new_buckets = 4093;
                break;
            case 4093:
                new_buckets = 8191;
                break;
            case 8191:
                new_buckets = 16381;
                break;
            case 16381:
                new_buckets = 32771;
                break;
            default:
                printf("Maximum buckets.\n");
                SymTable_free(tmp_SymTable); /* Free the temporary SymTable. */
                return 0;
        }

        for(i = 0; i < old_buckets; i++){ /* Free the hash table of oSymTable with the old number of buckets. */
            traverse = oSymTable->head[i];
            while(traverse != NULL){
                previous = traverse;
                traverse = traverse->next;

                free(previous->key);
                previous->key = NULL;

                free(previous);
                previous = NULL;
            }
        }
        free(oSymTable->head);
        oSymTable->head = NULL;

        printf("Expanding the hash table to %u buckets.\n", new_buckets);
        oSymTable->head = malloc(new_buckets * sizeof(struct node)); /* Allocating memory for the new hash table with the new number of buckets. */
        printf("new buckets inside expand. %u\n", new_buckets);
        for(i = 0; i < new_buckets; i++){
            oSymTable->head[i] = NULL;
        }

        oSymTable->count = 0;

        for(i = 0; i < old_buckets; i++){ /* Copy the bindings from tmp_SymTable to oSymTable with the new bruckets. */
            traverse = tmp_SymTable->head[i];
            while(traverse != NULL){
                SymTable_putWithoutExpanding(oSymTable, traverse->key, traverse->value);
                traverse = traverse->next;
            }
        }

        current_buckets = old_buckets; 
        SymTable_free(tmp_SymTable); /* Free the temporary SymTable. */
        current_buckets = new_buckets;

        return 1;
    }


My implementation of the function SymTable_putWithoutExpanding(...) is exactly the same as my current SymTable_put.

I also modified some of the existing function like SymTable_put(...), at the end of this function I 
put these lines of code: 
 
    if(SymTable_isExpandable(oSymTable)){ /* If oSymTable is expandable, expand the hash table. */
        printf("Before Expanding: %u.\n", SymTable_getLength(oSymTable));
        SymTable_expand(oSymTable); /* Expand oSymTable. */
    }

Also, in each function, whenever it was using the constant BUCKETS, I replaced it with the global variable current_buckets.
