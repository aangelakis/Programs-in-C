/**************************************************
 *                                                *
 * file: among_us.h                               *
 *                                                *
 *                                                *
 * @Author  Skerdi Basha                          *
 * @Version 1-12-2020                             *
 * @email   sbash@csd.uoc.gr                      *
 *                                                *
 * @brief   Header file for the needs of CS-240   *
 * project 2020, with the structures and function *
 * prototypes                                     *
 *                                                *
 **************************************************
 */

#ifndef __AMONG_US_H_
#define __AMONG_US_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

/**
 * Structure defining a node of the players double linked tree
 * tree
 */
struct Player
{
    int pid;                        /*Player's identifier*/
    int is_alien;                   /*Alien flag*/
    int evidence;                   /*Amount of evidence*/
    struct Player *parrent;         /*Pointer to the parent node*/
    struct Player *lc;              /*Pointer to the left child node*/
    struct Player *rc;              /*Pointer to the right child node*/
    struct Task *tasks;             /*Pointer to the head of player's task tree*/
};

/**
 * Structure defining a node of the tasks sorted tree
 */
struct Task
{
    int tid;                        /*Task's identifier*/
    int difficulty;                 /*Task's difficulty*/
    int lcnt;                       /*Node's left child's node counter*/
    struct Task *lc;                /*Pointer to the left child node*/
    struct Task *rc;                /*Pointer to the right child node*/
};

struct HT_Task
{
    int tid;                        /*Task's identifier*/
    int difficulty;                 /*Task's difficulty*/
    struct HT_Task *next;           /*Pointer to the next node*/
};

struct General_Tasks_HT
{
    int count;                      /*Count of tasks*/
    struct HT_Task **tasks;         /*General tasks hash table*/
};

struct Completed_Tasks_PQ
{
    int size;                       /*Count of completed tasks*/
    struct HT_Task* tasks;         /*Completed tasks priority queue*/
};

unsigned int max_tasks_g; /* Max number of tasks */
unsigned int max_tid_g;   /* Max task tid */
unsigned int a,b,p;     /* Variables for the universal hashing */
unsigned int num_players;
unsigned int count;
struct Player *inorder_player;
int eject_dont_print;
int chain_dont_print;
int players_dont_print;
int register_player_dont_print;
int pid_max_evidence;
int max_evidence;
int num_of_aliens;
int num_of_crewmates;
/* Primes for your universal hashing implementation */
extern unsigned int primes_g[650];

/* Global variable, pointer to the head of the players tree */
struct Player *players_tree;

/* Global variable, pointer to the head of the tasks tree */
struct General_Tasks_HT general_tasks_ht;

/* Global variable, pointer to the top of the completed task's priority queue */
struct Completed_Tasks_PQ *completed_tasks_pq;

/* Global variable, pointer to the sentinel of the players tree */
struct Player* players_sentinel;

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize();

/**
 * @brief Register Player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid, int is_alien);

/**
 * @brief Insert Task in the general task hash table
 *
 * @param tid The task id
 *
 * @param difficulty The difficulty of the task
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_task(int tid, int difficulty);

/**
 * @brief Distribute Tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks();

/**
 * @brief Implement Task
 *
 * @param pid The player's id
 *
 * @param tid The task's tid
 *
 * @return 1 on success
 *         0 on failure
 */
int implement_task(int pid, int tid);

/**
 * @brief Eject Player
 *
 * @param pid_1 The ejected player's id
 *
 * @param pid_2 The crewmates id
 *
 * @return 1 on success
 *         0 on failure
 */
int eject_player(int pid_1, int pid_2);

/**
 * @brief Witness Eject Player
 *
 * @param pid_1 The ejected player's id
 *
 * @param pid_2 The crewmate's pid
 *
 * @param pid_a The alien's pid
 *
 * @param number_of_witnesses The number of witnesses
 *
 * @return 1 on success
 *         0 on failure
 */
int witness_eject(int pid_1, int pid_2, int pid_a, int number_of_witnesses);

/**
 * @brief Sabotage
 *
 * @param number_of_tasks The number of tasks to be sabotaged
 *
 * @param pid The player's id
 *
 * @return 1 on success
 *         0 on failure
 */
int sabotage(int number_of_tasks, int pid);

/**
 * @brief Vote
 *
 * @param pid_1 The suspicious player's id
 *
 * @param pid_2 The crewmate's pid
 *
 * @param vote_evidence The vote's evidence
 *
 * @return 1 on success
 *         0 on failure
 */
int vote(int pid_1, int pid_2, int vote_evidence);

/**
 * @brief Give Away Work
 *
 * @param pid_1 The existing crewmate's id
 *
 * @param pid_2 The new crewmate's pid
 *
 * @return 1 on success
 *         0 on failure
 */
int give_work(int pid_1, int pid_2);

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int terminate();

/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players();

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks();

/**
 * @brief Print Priority Queue
 *
 * @return 1 on success
 *         0 on failure
 */
int print_pq();

/**
 * @brief Print Players & Task tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_tree();

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int free_all(void);

/**
 * @brief function that helps with the event X
 */
void print_players_2(struct Player*);

void print_double_tree2(struct Player*);

void print_tasks_tree(struct Task*);

void print_double_tree_evidence();

void print_double_tree3(struct Player*);

void player_insert_tasks_tree(struct Player*, struct HT_Task*);
/**
 * @brief the class of the hash functions
 */
int hash_function(int);

void player_find_inorder(struct Player*, int);

struct Player* search_player(int);

void search_player_evidence(struct Player*);

struct Task* search_tasks_tree(struct Task*, int);

void tasks_tree_delete(struct Task**, struct Task*);

struct Task* inorder_successor_tasks(struct Task*, struct Task*);

struct Player* inorder_successor_players(struct Player*);

struct Player* inorder_predecessor_players(struct Player*);

void player_delete(struct Player*);

void delete_priority_queue();

void heapify_delete(int);

void insert_priority_queue(struct Task*);

void heapify_insert(int);

int number_of_tasks_in_player(struct Task*);

int tree2array(struct Task*, int, struct Task*);

struct Task* merge_arrays(struct Task*, struct Task*, int, int);

struct Task* merged_arr_to_tree(struct Task*, int, int);

void find_num_of_aliens_crewmates(struct Player*);

void split_tree_in_half(struct Task*, struct Task**, struct Task**, int);

struct Player* max_player();

struct Player* min_player();

#endif /* __AMONG_US_H_ */
