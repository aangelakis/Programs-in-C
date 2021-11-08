/***************************************************
 *                                                              
 * file: among_us.c                                          
 *                                                             
 * @Author  Alexandros Angelakis                                                                 
 * @email   csd4334@csd.uoc.gr , angelakis@ics.forth.gr                             
 *                                                             
 * @brief   Implementation of among_us.h             
 *                                                               
 ***************************************************
 */

#include "among_us.h"

unsigned int primes_g[650] = {
                                 179,    181,    191,    193,    197,    199,    211,    223,    227,    229,
                                 233,    239,    241,    251,    257,    263,    269,    271,    277,    281,
                                 283,    293,    307,    311,    313,    317,    331,    337,    347,    349,
                                 353,    359,    367,    373,    379,    383,    389,    397,    401,    409,
                                 419,    421,    431,    433,    439,    443,    449,    457,    461,    463,
                                 467,    479,    487,    491,    499,    503,    509,    521,    523,    541,
                                 547,    557,    563,    569,    571,    577,    587,    593,    599,    601,
                                 607,    613,    617,    619,    631,    641,    643,    647,    653,    659,
                                 661,    673,    677,    683,    691,    701,    709,    719,    727,    733,
                                 739,    743,    751,    757,    761,    769,    773,    787,    797,    809,
                                 811,    821,    823,    827,    829,    839,    853,    857,    859,    863,
                                 877,    881,    883,    887,    907,    911,    919,    929,    937,    941,
                                 947,    953,    967,    971,    977,    983,    991,    997,   1009,   1013,
                                1019,   1021,   1031,   1033,   1039,   1049,   1051,   1061,   1063,   1069,
                                1087,   1091,   1093,   1097,   1103,   1109,   1117,   1123,   1129,   1151,
                                1153,   1163,   1171,   1181,   1187,   1193,   1201,   1213,   1217,   1223,
                                1229,   1231,   1237,   1249,   1259,   1277,   1279,   1283,   1289,   1291,
                                1297,   1301,   1303,   1307,   1319,   1321,   1327,   1361,   1367,   1373,
                                1381,   1399,   1409,   1423,   1427,   1429,   1433,   1439,   1447,   1451,
                                1453,   1459,   1471,   1481,   1483,   1487,   1489,   1493,   1499,   1511,
                                1523,   1531,   1543,   1549,   1553,   1559,   1567,   1571,   1579,   1583,
                                1597,   1601,   1607,   1609,   1613,   1619,   1621,   1627,   1637,   1657,
                                1663,   1667,   1669,   1693,   1697,   1699,   1709,   1721,   1723,   1733,
                                1741,   1747,   1753,   1759,   1777,   1783,   1787,   1789,   1801,   1811,
                                1823,   1831,   1847,   1861,   1867,   1871,   1873,   1877,   1879,   1889,
                                1901,   1907,   1913,   1931,   1933,   1949,   1951,   1973,   1979,   1987,
                                1993,   1997,   1999,   2003,   2011,   2017,   2027,   2029,   2039,   2053,
                                2063,   2069,   2081,   2083,   2087,   2089,   2099,   2111,   2113,   2129,
                                2131,   2137,   2141,   2143,   2153,   2161,   2179,   2203,   2207,   2213,
                                2221,   2237,   2239,   2243,   2251,   2267,   2269,   2273,   2281,   2287,
                                2293,   2297,   2309,   2311,   2333,   2339,   2341,   2347,   2351,   2357,
                                2371,   2377,   2381,   2383,   2389,   2393,   2399,   2411,   2417,   2423,
                                2437,   2441,   2447,   2459,   2467,   2473,   2477,   2503,   2521,   2531,
                                2539,   2543,   2549,   2551,   2557,   2579,   2591,   2593,   2609,   2617,
                                2621,   2633,   2647,   2657,   2659,   2663,   2671,   2677,   2683,   2687,
                                2689,   2693,   2699,   2707,   2711,   2713,   2719,   2729,   2731,   2741,
                                2749,   2753,   2767,   2777,   2789,   2791,   2797,   2801,   2803,   2819,
                                2833,   2837,   2843,   2851,   2857,   2861,   2879,   2887,   2897,   2903,
                                2909,   2917,   2927,   2939,   2953,   2957,   2963,   2969,   2971,   2999,
                                3001,   3011,   3019,   3023,   3037,   3041,   3049,   3061,   3067,   3079,
                                3083,   3089,   3109,   3119,   3121,   3137,   3163,   3167,   3169,   3181,
                                3187,   3191,   3203,   3209,   3217,   3221,   3229,   3251,   3253,   3257,
                                3259,   3271,   3299,   3301,   3307,   3313,   3319,   3323,   3329,   3331,
                                3343,   3347,   3359,   3361,   3371,   3373,   3389,   3391,   3407,   3413,
                                3433,   3449,   3457,   3461,   3463,   3467,   3469,   3491,   3499,   3511,
                                3517,   3527,   3529,   3533,   3539,   3541,   3547,   3557,   3559,   3571,
                                3581,   3583,   3593,   3607,   3613,   3617,   3623,   3631,   3637,   3643,
                                3659,   3671,   3673,   3677,   3691,   3697,   3701,   3709,   3719,   3727,
                                3733,   3739,   3761,   3767,   3769,   3779,   3793,   3797,   3803,   3821,
                                3823,   3833,   3847,   3851,   3853,   3863,   3877,   3881,   3889,   3907,
                                3911,   3917,   3919,   3923,   3929,   3931,   3943,   3947,   3967,   3989,
                                4001,   4003,   4007,   4013,   4019,   4021,   4027,   4049,   4051,   4057,
                                4073,   4079,   4091,   4093,   4099,   4111,   4127,   4129,   4133,   4139,
                                4153,   4157,   4159,   4177,   4201,   4211,   4217,   4219,   4229,   4231,
                                4241,   4243,   4253,   4259,   4261,   4271,   4273,   4283,   4289,   4297,
                                4327,   4337,   4339,   4349,   4357,   4363,   4373,   4391,   4397,   4409,
                                4421,   4423,   4441,   4447,   4451,   4457,   4463,   4481,   4483,   4493,
                                4507,   4513,   4517,   4519,   4523,   4547,   4549,   4561,   4567,   4583,
                                4591,   4597,   4603,   4621,   4637,   4639,   4643,   4649,   4651,   4657,
                                4663,   4673,   4679,   4691,   4703,   4721,   4723,   4729,   4733,   4751,
                                4759,   4783,   4787,   4789,   4793,   4799,   4801,   4813,   4817,   4831,
                                4861,   4871,   4877,   4889,   4903,   4909,   4919,   4931,   4933,   4937,
                                4943,   4951,   4957,   4967,   4969,   4973,   4987,   4993,   4999,   5003,
                                5009,   5011,   5021,   5023,   5039,   5051,   5059,   5077,   5081,   5087,
                                5099,   5101,   5107,   5113,   5119,   5147,   5153,   5167,   5171,   5179,
                            };

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize() {
    num_of_aliens = 0;
    num_of_crewmates = 0;
    eject_dont_print = 1;
    chain_dont_print = 1;
    players_dont_print = 1;
    register_player_dont_print = 1;
    pid_max_evidence = 0;
    max_evidence = -1;
    int i=0;
    srand(time(NULL));
    players_sentinel = (struct Player*)malloc(sizeof(struct Player));
	players_sentinel->pid = -1;
	players_sentinel->is_alien = 0;
	players_sentinel->evidence = 0;
	players_sentinel->tasks = NULL;
	players_sentinel->parrent = NULL;
	players_sentinel->lc = NULL;
	players_sentinel->rc = NULL;
	num_players = 0;
    while(primes_g[i] <= max_tid_g){
        i++;
    }
    p = primes_g[i];
    a = (rand()%(p))+1;
    b = (rand()%(p));
    general_tasks_ht.count = 0;
    general_tasks_ht.tasks = (struct HT_Task**)malloc(max_tasks_g*sizeof(struct HT_Task*));
    for(int i=0; i<max_tasks_g; i++){
        general_tasks_ht.tasks[i] = NULL;
    }
    completed_tasks_pq = (struct Completed_Tasks_PQ*)malloc(sizeof(struct Completed_Tasks_PQ));
    completed_tasks_pq->size  = 0;
    completed_tasks_pq->tasks = (struct HT_Task*)malloc(max_tasks_g*sizeof(struct HT_Task));
    return 1;
}

/**
 * @brief Register Player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 */
int register_player(int pid, int is_alien) {
    struct Player* q, * pq = NULL;
	struct Player *newPlayer;
	if (players_tree == NULL) {
        q = (struct Player*)malloc(sizeof(struct Player));
		players_tree = (struct Player*)malloc(sizeof(struct Player));
		q->evidence = 0;
		q->is_alien = is_alien;
		q->lc = players_sentinel;
		q->rc = players_sentinel;
		q->parrent = NULL;
		q->pid = pid;
		q->tasks = NULL;
		players_tree = q;
	}
	else {
		q = players_tree;
		while (q != players_sentinel) {
			if (q->pid == pid) {
                printf("FAIL\n");
				return 0;
			}
			pq = q;
			if (pid < q->pid) {
				q = q->lc;
			}
			else {
				q = q->rc;
			}
		}
		newPlayer = (struct Player*)malloc(sizeof(struct Player));
		newPlayer->pid = pid;
		newPlayer->evidence = 0;
		newPlayer->is_alien = is_alien;
		newPlayer->parrent = pq;
		newPlayer->lc = players_sentinel;
		newPlayer->rc = players_sentinel;
		newPlayer->tasks = NULL;
		if (pid < pq->pid) {
			pq->lc = newPlayer;
		}
		else {
			pq->rc = newPlayer;
		}
	}
	num_players++;
	if(register_player_dont_print == 1){
        printf("P <%d><%d>\n", pid, is_alien);
        print_players();
        printf("\nDONE\n");
	}
    register_player_dont_print = 3;
    return 1;
}

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
int insert_task(int tid, int difficulty) {
    struct HT_Task *newTask = (struct HT_Task*)malloc(sizeof(struct HT_Task));
    struct HT_Task  *q;
    int index;
    newTask->tid = tid;
    newTask->difficulty = difficulty;
    newTask->next = NULL;
    index = hash_function(tid);
    if(general_tasks_ht.tasks[index] == NULL){
        general_tasks_ht.tasks[index] = newTask;
    }
    else{
        q = general_tasks_ht.tasks[index];
        while(q->next != NULL){
            q = q->next;
        }
        q->next = newTask;
    }
    general_tasks_ht.count++;
    printf("T <%d><%d>\n", tid, difficulty);
    chain_dont_print = 1;
    print_tasks();
    chain_dont_print = 2;
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Distribute Tasks to the players
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks() {
    struct Player *player = NULL;
    struct HT_Task *q;
    int i, chain = 0, tmp = general_tasks_ht.count;
    q = general_tasks_ht.tasks[chain];
    for(i=0; i < tmp; i++){
        if(q == NULL){
            chain++;
            i--;
            q = general_tasks_ht.tasks[chain];
        }
        else{
            count = 0;
            player_find_inorder(players_tree, (i%num_players)+1);
            player = inorder_player;
            if(player->is_alien == 0){
                player_insert_tasks_tree(player, q);
                q = q->next;
            }
            else{
                tmp++;
            }
        }
    }

    printf("D\n");
    players_dont_print = 1;
    print_double_tree();
    players_dont_print = 6;
    printf("\nDONE\n");
    return 1;
}

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
int implement_task(int pid, int tid) {
    struct Player* player;
    struct Task* task;
    player = search_player(pid);
    task = search_tasks_tree(player->tasks, tid);
    if(player == NULL){
        return 0;
    }
    if(task == NULL){
        return 0;
    }
    tasks_tree_delete(&player->tasks, task);
    insert_priority_queue(task);
    printf("I <%d><%d>\n", pid, tid);
    players_dont_print = 2;
    print_double_tree();
    players_dont_print = 6;
    printf("DONE\n");
    return 1;
}


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
int eject_player(int pid_1, int pid_2) {
    int n_pid_1, n_pid_2;
    struct Task *arr1, *arr2, *merged_arr;
    struct Player* p1, *p2;
    p1 = search_player(pid_1);
    p2 = search_player(pid_2);
    if(p1 == NULL){
        printf("Player with pid: %d not found in players' tree!\n", pid_1);
        return 0;
    }
    if(p2 == NULL){
        printf("Player with pid: %d not found in players' tree!\n", pid_2);
        return 0;
    }
    n_pid_1 = number_of_tasks_in_player(p1->tasks);
    n_pid_2 = number_of_tasks_in_player(p2->tasks);
    arr1 = (struct Task*)malloc(sizeof(struct Task)*(n_pid_1));
    arr2 = (struct Task*)malloc(sizeof(struct Task)*(n_pid_2));
    tree2array(p1->tasks, 0, arr1);
    tree2array(p2->tasks, 0, arr2);
    merged_arr = merge_arrays(arr1, arr2, n_pid_1, n_pid_2);
    p2->tasks = merged_arr_to_tree(merged_arr, 0, n_pid_1+n_pid_2-1);
    player_delete(p1);
    if(eject_dont_print !=2 && eject_dont_print != 3){
        printf("E <%d><%d>\n", pid_1, pid_2);
        players_dont_print = 3;
        print_double_tree();
        players_dont_print = 6;
        printf("DONE\n");
        eject_dont_print = 1;
    }
    return 1;
}

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
int witness_eject(int pid_1, int pid_2, int pid_a, int number_of_witnesses){
    struct Player* p_a;
    eject_dont_print = 2;
    eject_player(pid_1, pid_2);
    eject_dont_print = 1;
    p_a = search_player(pid_a);
    if(p_a == NULL){
        return 0;
    }
    p_a->evidence += number_of_witnesses;

    printf("W <%d><%d><%d><%d>\n", pid_1, pid_2, pid_a, number_of_witnesses);
    print_double_tree_evidence();
    printf("DONE\n");
    return 1;
}

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
int sabotage(int number_of_tasks, int pid) {
    struct Player *player;
    struct Player *p;
    struct Player *max, *min;
    struct HT_Task *tmp;
    int i, num = number_of_tasks;
    if(number_of_tasks > completed_tasks_pq->size){
        return 0;
    }
    player = search_player(pid);
    p = player;
    max = max_player();
    min = min_player();
    for(i = 0; i < number_of_tasks/2; i++){
        if(p == min)
            p = max;
        else
            p = inorder_predecessor_players(p);
    }

    print_pq();
    while(number_of_tasks > 0){
        tmp = (struct HT_Task*)malloc(sizeof(struct HT_Task));
        tmp->difficulty = completed_tasks_pq->tasks[0].difficulty;
        tmp->tid = completed_tasks_pq->tasks[0].tid;
       if(p->is_alien == 1){
            if(p == max)
                p = min;
            else
                p = inorder_successor_players(p);
        }
        else{
            player_insert_tasks_tree(p, tmp);
            delete_priority_queue();
            number_of_tasks--;
            if(p == max)
                p = min;
            else
                p = inorder_successor_players(p);
        }
    }
    print_pq();
    printf("S <%d><%d>\n", num, pid);
    players_dont_print = 4;
    print_double_tree();
    players_dont_print = 6;
    printf("DONE\n");
    return 1;
}

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
int vote(int pid_1, int pid_2, int vote_evidence) {
    struct Player *p1;
    p1 = search_player(pid_1);
    p1->evidence += vote_evidence;
    search_player_evidence(players_tree);
    eject_dont_print = 3;
    eject_player(pid_max_evidence, pid_2);
    eject_dont_print = 1;
    max_evidence = -1;
    printf("V <%d><%d><%d>\n", pid_1, pid_2, vote_evidence);
    print_double_tree_evidence();
    printf("DONE\n");
    return 1;
}

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
int give_work(int pid_1, int pid_2) {
    struct Player *p1, *p2;
    struct Task* p1_root = NULL, *p2_root  = NULL;
    int tasks_p1;
    register_player_dont_print = 2;
    register_player(pid_2,0);
    register_player_dont_print = 1;
    p2 = search_player(pid_2);
    p1 = search_player(pid_1);
    if(p2 == NULL){
        return 0;
    }
    if(p1 == NULL){
        return 0;
    }
    tasks_p1 = number_of_tasks_in_player(p1->tasks);
    split_tree_in_half(p1->tasks,&p1_root, &p2_root, tasks_p1/2);
    p1->tasks = p1_root;
    p2->tasks = p2_root;
    printf("G <%d><%d>\n", pid_1, pid_2);
    players_dont_print = 5;
    print_double_tree();
    players_dont_print = 6;
    printf("DONE\n");
    return 1;
}

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 */
int terminate() {
    find_num_of_aliens_crewmates(players_tree);
    printf("F\n");
    if(num_of_aliens > num_of_crewmates)
        printf("\tAliens win.\n");
    else if(num_of_aliens == 0 || completed_tasks_pq->size == general_tasks_ht.count)
        printf("\tCrewmates win.\n");
    printf("DONE\n");
    return 1;
}

/**
 * @brief Print Players
 *
 * @return 1 on success
 *         0 on failure
 */
int print_players() {
    struct Player* q = players_tree;
    if(register_player_dont_print == 3)
        printf("X\n");
    printf("\tPlayers = ");
    print_players_2(q);
    if(register_player_dont_print == 3)
        printf("\nDONE\n");
    register_player_dont_print = 1;
    return 1;
}

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks() {
    int i;
    struct HT_Task *q;
    if(chain_dont_print == 2)
        printf("Y\n");
    for(i=0; i<max_tasks_g; i++){
        printf("\tChain %d: ", i);
        q = general_tasks_ht.tasks[i];
        while(q != NULL){
            if(q->next == NULL){
                printf("<%d,%d>",q->tid, q->difficulty);
            }
            else{
                printf("<%d,%d>,",q->tid, q->difficulty);
            }
            q = q->next;
        }
        printf("\n");
    }
    if(chain_dont_print == 2)
        printf("DONE\n");
    return 1;
}

/**
 * @brief Print Priority Queue
 *
 * @return 1 on success
 *         0 on failure
 */
int print_pq() {
    int i;
    printf("Z\n \tCompleted Tasks = ");
    for(i = 0; i < (completed_tasks_pq->size); i++){
        printf(" <%d,%d>", completed_tasks_pq->tasks[i].tid, completed_tasks_pq->tasks[i].difficulty);
    }
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Print Players & Task tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_tree() {
    struct Player* q = players_tree;
    if(players_dont_print == 6)
        printf("U\n");
    print_double_tree2(q);
    if(players_dont_print == 6)
    printf("DONE\n");
    return 1;
}

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */

int free_all(void) {
    return 1;
}

/* FROM THIS POINT I HAVE MINE FUNCTIONS   */

void find_num_of_aliens_crewmates(struct Player *q){
    if(q == players_sentinel)
        return;
    if(q->is_alien == 1)
        num_of_aliens++;
    else
        num_of_crewmates++;
    find_num_of_aliens_crewmates(q->lc);
    find_num_of_aliens_crewmates(q->rc);
}

void player_find_inorder(struct Player* q, int i){
    if(q == players_sentinel){
        return ;
    }
    if(count <= i){
        player_find_inorder(q->lc, i);
        count++;
        if(count == i){
            inorder_player = q;
        }
        player_find_inorder(q->rc, i);
    }
}

void player_insert_tasks_tree(struct Player* player, struct HT_Task *task){
    struct Task *newTask = (struct Task*)malloc(sizeof(struct Task));
    struct Task *q, *pq;
    newTask->difficulty = task->difficulty;
    newTask->tid = task->tid;
    newTask->lcnt = 0;
    newTask->rc = NULL;
    newTask->lc = NULL;
    if(player->tasks == NULL){
        player->tasks = newTask;
    }
    else{
        q = player->tasks;
        while(q != NULL){
            pq = q;
            if(task->tid < q->tid){
                q->lcnt++;
                q = q->lc;
            }
            else{
                q = q->rc;
            }
        }
        if(task->tid < pq->tid){
            pq->lc = newTask;
        }
        else{
            pq->rc = newTask;
        }
    }
}
 void print_double_tree_evidence(){
    struct Player* q = players_tree;
    print_double_tree3(q);
 }

 void print_double_tree3(struct Player* q){
     if(q == players_sentinel){
        return;
    }
    print_double_tree3(q->lc);
    printf("\t<Player%d,%d> = ", q->pid, q->evidence);
    print_tasks_tree(q->tasks);
    printf("\n");
    print_double_tree3(q->rc);

 }
void print_double_tree2(struct Player* q){
    if(q == players_sentinel){
        return;
    }
    print_double_tree2(q->lc);
    printf("\tPlayer%d = ", q->pid);
    print_tasks_tree(q->tasks);
    printf("\n");
    print_double_tree2(q->rc);
}

void print_tasks_tree(struct Task *q){
    if(q == NULL){
        return;
    }
    print_tasks_tree(q->lc);
    printf("<%d,%d>", q->tid, q->difficulty);
    print_tasks_tree(q->rc);
}

void print_players_2(struct Player *q) {
	if (q == players_sentinel) {
		return;
	}
	print_players_2(q->lc);
	printf("<%d:%d>", q->pid, q->is_alien);
	print_players_2(q->rc);
}

struct Player* search_player(int pid){
    struct Player* q = players_tree;
    players_sentinel->pid = pid;
    while(pid != q->pid){
        if(pid < q->pid){
            q = q->lc;
        }
        else{
            q = q->rc;
        }
    }
    if(q != players_sentinel){
        return q;
    }
    else{
        return NULL;
    }
}

void search_player_evidence(struct Player *q){
    if(q == players_sentinel)
        return ;
    if(q->evidence > max_evidence){
        pid_max_evidence = q->pid;
        max_evidence = q->evidence;
    }
    search_player_evidence(q->lc);
    search_player_evidence(q->rc);
}

struct Task* search_tasks_tree(struct Task* task, int tid){
    struct Task* q = task;
    while(q != NULL && tid != q->tid){
        if(tid < q->tid){
            q = q->lc;
        }
        else{
            q = q->rc;
        }
    }
    if(q != NULL){
        return q;
    }
    else{
        return NULL;
    }
}

void tasks_tree_delete(struct Task** root, struct Task* z){
   struct Task *temp;
   if((*root) == NULL)
        return;
   else if(z->tid < (*root)->tid){
        (*root)->lcnt--;
        tasks_tree_delete(&(*root)->lc, z);
   }
   else if(z->tid > (*root)->tid)
        tasks_tree_delete(&(*root)->rc,z);
   else{
        if((*root)->lc == NULL && (*root)->rc == NULL)
                (*root) = NULL;
        else if((*root)->lc == NULL){
            temp = (*root);
            (*root) = (*root)->rc;
            temp = NULL;
        }
        else if((*root)->rc == NULL){
            temp = (*root);
            (*root) = (*root)->lc;
            temp = NULL;
        }
        else{
            temp = inorder_successor_tasks((*root), z);
            (*root)->tid = temp->tid;
            tasks_tree_delete(&(*root)->rc, temp);
        }
   }
}

void player_delete(struct Player* z){
    struct Player *y, *x;
    if(z->lc == players_sentinel || z->rc == players_sentinel)
        y = z;
    else
        y = inorder_successor_players(z);

    if(y->lc != players_sentinel)
        x = y->lc;
    else
        x = y->rc;

    if(x != players_sentinel)
        x->parrent = y->parrent;

    if(y->parrent == NULL)
        players_tree = x;
    else if(y == y->parrent->lc)
        y->parrent->lc = x;
    else
        y->parrent->rc = x;

    if(y != z){
        z->evidence = y->evidence;
        z->is_alien = y->is_alien;
        z->pid = y->pid;
        z->tasks = y->tasks;
    }

}

struct Player* inorder_predecessor_players(struct Player* player){
    struct Player* q = players_tree, *prev = NULL;
    struct Player *predecessor;
    if(player->lc != players_sentinel){
        q = player->lc;
        while(q != players_sentinel){
            prev = q;
            q = q->rc;
        }
        return prev;
    }
    while(q != players_sentinel){
        if(q->pid >= player->pid)
            q = q->lc;
        else{
            predecessor = q;
            q = q->rc;
        }
    }
    return predecessor;
}


struct Player* inorder_successor_players(struct Player* player){
    struct Player *q = players_tree;
    struct Player *successor;

    while(q != players_sentinel){
        if(player->pid < q->pid){
            successor = q;
            q = q->lc;
        }
        else
            q = q->rc;
    }
    return successor;
}

struct Task* inorder_successor_tasks(struct Task* head, struct Task* task){
    struct Task* q = head;
    struct Task* successor;
    while(q != NULL){
        if(task->tid < q->tid){
            successor = q;
            q = q->lc;
        }
        else{
            q = q->rc;

        }
    }
    return successor;
}

void delete_priority_queue(){
    struct HT_Task toDelete;
    toDelete = completed_tasks_pq->tasks[completed_tasks_pq->size - 1];
    completed_tasks_pq->tasks[0] = toDelete;
    completed_tasks_pq->size--;
    heapify_delete(0);
}

void heapify_delete(int i){
    int left_child = 2*i + 1, right_child = 2*i + 2, largest_node = i;
    struct HT_Task tmp;
    if(left_child < completed_tasks_pq->size && completed_tasks_pq->tasks[left_child].difficulty > completed_tasks_pq->tasks[largest_node].difficulty)
        largest_node = left_child;

    if(right_child < completed_tasks_pq->size && completed_tasks_pq->tasks[right_child].difficulty > completed_tasks_pq->tasks[largest_node].difficulty)
        largest_node = right_child;

    if(largest_node != i){
        tmp = completed_tasks_pq->tasks[i];
        completed_tasks_pq->tasks[i] = completed_tasks_pq->tasks[largest_node];
        completed_tasks_pq->tasks[largest_node] = tmp;
         heapify_delete(largest_node);
    }
}

void insert_priority_queue(struct Task* task){
    struct HT_Task *newTask = (struct HT_Task*)malloc(sizeof(struct HT_Task));
    if(completed_tasks_pq->size == max_tasks_g)
        return;
    newTask->difficulty = task->difficulty;
    newTask->tid = task->tid;
    newTask->next = NULL;
    completed_tasks_pq->size++;
    completed_tasks_pq->tasks[completed_tasks_pq->size - 1] = *newTask;
    heapify_insert(completed_tasks_pq->size - 1);
}

void heapify_insert(int i){
    int parent = (i - 1) / 2;
    struct HT_Task tmp;
    if(parent < 0)
        return;
    else{
        if(completed_tasks_pq->tasks[i].difficulty > completed_tasks_pq->tasks[parent].difficulty){
                tmp = completed_tasks_pq->tasks[i];
                completed_tasks_pq->tasks[i] = completed_tasks_pq->tasks[parent];
                completed_tasks_pq->tasks[parent] = tmp;
                heapify_insert(parent);
        }
    }
}

int number_of_tasks_in_player(struct Task* root){
    struct Task *q = root;
    int sum = 0;
    while(q != NULL){
        sum  += q->lcnt + 1;
        q = q->rc;
    }
    return sum;
}

int tree2array(struct Task* root, int i, struct Task *arr){
    if(root == NULL)
        return i;
    if(root->lc != NULL)
        i = tree2array(root->lc, i, arr);
    arr[i].tid = root->tid;
    arr[i].difficulty = root->difficulty;
    i++;
    if(root->rc != NULL)
        i = tree2array(root->rc,i, arr);
    return i;
}

struct Task* merge_arrays(struct Task* arr1, struct Task* arr2, int n1, int n2){
    int i1 = 0, i2 = 0, i = 0;
    struct Task* newarr;
    newarr = (struct Task*)malloc((n1+n2)*sizeof(struct Task));
    while(i1 < n1 && i2 < n2){
        if(arr1[i1].tid < arr2[i2].tid){
            newarr[i++] = arr1[i1++];
        }
        else{
            newarr[i++] = arr2[i2++];
        }
    }
    while(i1 < n1)
        newarr[i++] = arr1[i1++];

    while(i2 < n2)
        newarr[i++] = arr2[i2++];

    return newarr;

}

struct Task* merged_arr_to_tree(struct Task* arr, int left, int right){
    struct Task* q;
    int mid;
    if(right < left)
        return NULL;
    mid = (right+left)/2;
    q = (struct Task*)malloc(sizeof(struct Task));
    q->tid = arr[mid].tid;
    q->difficulty = arr[mid].difficulty;
    q->lcnt = mid-left;
    q->lc = merged_arr_to_tree(arr, left, mid-1);
    q->rc = merged_arr_to_tree(arr,mid+1, right);
    return q;
}

void split_tree_in_half(struct Task* root, struct Task **p1_root, struct Task **p2_root, int k){
    struct Task *q = root, *prev = NULL;

    if(q == root && k < q->lcnt){
        (*p1_root) = q;
        q->lcnt = q->lcnt - k;
        prev = q;
        q = q->lc;
    }
    else if(q == root && k == q->lcnt){
        (*p2_root) = q->lc;
        q->lc = NULL;
        (*p1_root) = q;
        (*p1_root)->lcnt = 0;
        k = k - q->lcnt - 1;
    }
    else if(q == root && k > q->lcnt){
        (*p2_root) = q;
        k = k - q->lcnt - 1;
        prev = q;
        q = q->rc;
        (*p1_root) = q;
        if(k == 0)
            prev->rc = NULL;
    }

    while(k > 0){
        if(k < q->lcnt + 1 ){
            prev = q;
            q->lcnt = q->lcnt - k;
            q = q->lc;
        }
        else if(k > q->lcnt + 1){
            if((*p2_root != NULL)){
                k = k - q->lcnt - 1;
                prev = q;
                q = q->rc;
            }
            else{
            (*p2_root) = q;
            k = k - q->lcnt - 1;
            prev = q;
            q = q->rc;
            }
        }
        else{
            if((*p2_root) == root){
                (*p1_root) = q->rc;
                q->rc = NULL;
                k = k - q->lcnt - 1;
            }
            else{
                if(prev == root){
                    prev = q;
                    q = q->rc;
                }
                else if(prev->lcnt != 0){
                    prev->lc = NULL;
                    k = k - q->lcnt - 1;
                }
                else if((*p2_root) == NULL){
                       (*p2_root) = q;
                       prev->rc = NULL;
                       k = k - q->lcnt -1;
                }
                else{
                    (*p1_root)->lc = q->rc;
                    q->rc = NULL;
                    k = k - q->lcnt -1;
                }
            }
        }
    }

    if((*p2_root) == NULL)
        (*p2_root) = q;
}

struct Player* max_player(){
    struct Player *q = players_tree;
    while(q->rc != players_sentinel){
        q = q->rc;
    }
    return q;
}

struct Player* min_player(){
    struct Player *q = players_tree;
    while(q->lc != players_sentinel){
        q = q->lc;
    }
    return q;
}


int hash_function(int tid){
    return ((a*tid + b) % p) % max_tasks_g;
}

int main() {
    scanf("%d %d", &max_tasks_g, &max_tid_g);
    initialize();
	register_player(69, 0);
	register_player(12, 0);
	register_player(68, 0);
	register_player(21, 1);
	register_player(79, 0);
	register_player(14, 0);
	register_player(25, 0);
	register_player(37, 0);
	register_player(28, 1);
	register_player(6,0);
    insert_task(124,3);
    insert_task(164,3);
    insert_task(4,1);
    insert_task(86,1);
    insert_task(62,3);
    insert_task(82,3);
    insert_task(212,1);
    insert_task(193,3);
    insert_task(53,2);
    insert_task(66,1);
    insert_task(33,3);
    insert_task(65,2);
    insert_task(142,3);
    insert_task(94,1);
    insert_task(12,2);
    insert_task(171,3);
    insert_task(218,3);
    insert_task(19,3);
    insert_task(37,1);
    insert_task(26,3);
    insert_task(143,2);
    distribute_tasks();
    implement_task(68, 193);
    implement_task(68, 33);
    implement_task(68, 65);
    implement_task(68, 66);
    implement_task(68, 164);
    implement_task(68, 4);
    implement_task(68, 37);
    implement_task(68, 171);
    implement_task(68, 12);
    implement_task(68, 142);
    implement_task(68, 143);
    implement_task(68, 82);
    implement_task(68, 19);
    implement_task(68, 212);
    implement_task(68, 53);
    implement_task(68, 86);
    implement_task(68, 218);
    implement_task(68, 26);
    implement_task(68, 124);
    implement_task(68, 62);
    implement_task(68, 94);
    implement_task(69, 193);
    implement_task(69, 33);
    implement_task(69, 65);
    implement_task(69, 66);
    implement_task(69, 164);
    implement_task(69, 4);
    implement_task(69, 37);
    implement_task(69, 171);
    implement_task(69, 12);
    implement_task(69, 142);
    implement_task(69, 143);
    implement_task(69, 82);
    implement_task(69, 19);
    implement_task(69, 212);
    implement_task(69, 53);
    implement_task(69, 86);
    implement_task(69, 218);
    implement_task(69, 26);
    implement_task(69, 124);
    implement_task(69, 62);
    implement_task(69, 94);
    implement_task(37, 193);
    implement_task(37, 33);
    implement_task(37, 65);
    implement_task(37, 66);
    implement_task(37, 164);
    implement_task(37, 4);
    implement_task(37, 37);
    implement_task(37, 171);
    implement_task(37, 12);
    implement_task(37, 142);
    implement_task(37, 143);
    implement_task(37, 82);
    implement_task(37, 19);
    implement_task(37, 212);
    implement_task(37, 53);
    implement_task(37, 86);
    implement_task(37, 218);
    implement_task(37, 26);
    implement_task(37, 124);
    implement_task(37, 62);
    implement_task(37, 94);
    eject_player(68,14);
    witness_eject(37,14,28,6);
    vote(14,6,2);
    give_work(25,15);
  //  sabotage(7,14);
    eject_player(79,25);
    implement_task(6, 193);
    implement_task(6, 33);
    implement_task(6, 65);
    implement_task(6, 66);
    implement_task(6, 164);
    implement_task(6, 4);
    implement_task(6, 37);
    implement_task(6, 171);
    implement_task(6, 12);
    implement_task(6, 142);
    implement_task(6, 143);
    implement_task(6, 82);
    implement_task(6, 19);
    implement_task(6, 212);
    implement_task(6, 53);
    implement_task(6, 86);
    implement_task(6, 218);
    implement_task(6, 26);
    implement_task(6, 124);
    implement_task(6, 62);
    implement_task(6, 94);
    implement_task(25, 193);
    implement_task(25, 33);
    implement_task(25, 65);
    implement_task(25, 66);
    implement_task(25, 164);
    implement_task(25, 4);
    implement_task(25, 37);
    implement_task(25, 171);
    implement_task(25, 12);
    implement_task(25, 142);
    implement_task(25, 143);
    implement_task(25, 82);
    implement_task(25, 19);
    implement_task(25, 212);
    implement_task(25, 53);
    implement_task(25, 86);
    implement_task(25, 218);
    implement_task(25, 26);
    implement_task(25, 124);
    implement_task(25, 62);
    implement_task(25, 94);
    vote(21,6,3);
    print_players();
    terminate();
    return 0;
}
