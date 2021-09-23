/**
 * @author Alexandros Angelakis csd4334@csd.uoc.gr , angelakis@ics.forth.gr 
 *
 * When an event is showing "failed" in the test files output
 * then: 1. malloc returns NULL
 * 	 2. the given player does not exist in the players list
 * 	 3. the given player does not have any other tasks in his tasks list
 * 	 4. in the F event, nobody wins
 */

#include "among_us.h"


/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 *
 * Time complexity: O(1)
 */
int initialize() {
    eject_dont_print = 1;
    TotalTasks = 0;
    tasks_head = (struct Head_GL*)malloc(sizeof(struct Head_GL));
    if(tasks_head == NULL){
        return 0;
    }
	tasks_head->head = NULL;
	tasks_head->tasks_count[0] = 0;
	tasks_head->tasks_count[1] = 0;
	tasks_head->tasks_count[2] = 0;
	players_head = (struct Players*)malloc(sizeof(struct Players));
	if(players_head == NULL){
        return 0;
	}
	players_head->tasks_head = NULL;
	players_head->tasks_sentinel = NULL;
	players_head->next = NULL;
	players_head->prev = NULL;
	players_head->evidence = -1;
	players_head->is_alien = -1;
	players_head->pid = -1;
	tasks_stack = (struct Head_Completed_Task_Stack*)malloc(sizeof(struct Head_Completed_Task_Stack));
	if(tasks_stack == NULL){
        return 0;
	}
	tasks_stack->count = 0;
	tasks_stack->head = NULL;
    return 1;
}

/**
 * @brief Register player
 *
 * @param pid The player's id
 *
 * @param is_alien The variable that decides if he is an alien or not
 * @return 1 on success
 *         0 on failure
 *
 * Time complexity: O(1)
 *
 * Event P
 */
int register_player(int pid,int is_alien) {
    struct Players *q;
    struct Tasks* sentinel;
    sentinel = (struct Tasks*)malloc(sizeof(struct Tasks));
    q = (struct Players*)malloc(sizeof(struct Players));
    if(q == NULL || sentinel == NULL){
        return 0;
    }
    sentinel->tid = -1;
    sentinel->difficulty = 0;
    sentinel->next = q->tasks_head;
    q->evidence = 0;
	q->is_alien = is_alien;
	q->pid = pid;
	q->tasks_head = sentinel;
	q->tasks_sentinel = sentinel;
	q->tasks_sentinel->next = q->tasks_head;

	if (players_head->next == NULL) {
		players_head->next = q;
		players_head->prev = q;
		q->prev = players_head;
		q->next = players_head;
	}
	else {
		q->next = players_head->next;
		players_head->next->prev = q;
		players_head->next = q;
		q->prev = players_head;
	}
	printf("P %d\n", pid);
	print_players2();
	printf("\nDONE\n");
    return 1;
}

/**
 * @brief Insert task in the general task list
 *
 * @param tid The task id
 *
 * @param difficulty The difficulty of the task
 *
 * @return 1 on success
 *         0 on failure
 *
 * Time Complexity: O(n) (where n is the number of tasks inside the General Task List)
 *                     because of the function insert_sorted() which has O(n) time complexity
 *
 * Event T
 */
int insert_task(int tid,int difficulty) {
	TotalTasks++;
	struct Tasks* q;
	q = (struct Tasks*)malloc(sizeof(struct Tasks));
	if (q == NULL) {
		return 0;
	}
	q->tid = tid;
	q->difficulty = difficulty;
  	insert_sorted(q);
	switch (q->difficulty) {
	case 1:
		tasks_head->tasks_count[0]++;
		break;
	case 2:
		tasks_head->tasks_count[1]++;
		break;
	case 3:
		tasks_head->tasks_count[2]++;
		break;
	}
	printf("T %d\n", tid);
    print_tasks2();
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Distribute tasks to the players
 *
 * Event D
 *
 * Time Complexity: O(m), where m is the total number of tasks in the general tasks list
 *
 * @return 1 on success
 *         0 on failure
 */
int distribute_tasks() {
    struct Players* q = players_head->next;
    struct Tasks* tasks = tasks_head->head; /* Pointer to head of general task list */
    struct Tasks* new_node_players_tasks; /* Pointer to help us add tasks to each player */
    while(tasks != NULL){
        new_node_players_tasks = (struct Tasks*)malloc(sizeof(struct Tasks));
        if(new_node_players_tasks == NULL){
            return 0;
        }
        if(q->is_alien == 1 || q == players_head){
            q = q->next;
        }
        else{
            if(q->tasks_head == q->tasks_sentinel){
                new_node_players_tasks->tid = tasks->tid;
                new_node_players_tasks->difficulty = tasks->difficulty;
                new_node_players_tasks->next = q->tasks_sentinel;
                q->tasks_head = new_node_players_tasks;
                q->tasks_sentinel->next = new_node_players_tasks;
                tasks = tasks->next;
                q = q->next;
            }
            else{
                new_node_players_tasks->tid = tasks->tid;
                new_node_players_tasks->difficulty = tasks->difficulty;
                q->tasks_sentinel->next->next = new_node_players_tasks;
                new_node_players_tasks->next = q->tasks_sentinel;
                q->tasks_sentinel->next = new_node_players_tasks;
                tasks = tasks->next;
                q = q->next;
            }
        }
   }
    printf("D\n");
    print_double_list2();
    printf("\nDONE\n");
    return 1;
}

/**
 * @brief Implement Task
 *
 * @param pid The player's id
 *
 * @param difficulty The task's difficulty
 *
 * @return 1 on success
 *         0 on failure
 *
 * Time complexity: O(n + m), where m is the number of tasks the given player has in his
 *                          tasks list and n is the number of players in the players' list.
 *
 * Event I
 */
int implement_task(int pid, int difficulty) {
    struct Players* q = NULL;
	struct Tasks* find_task_with_difficulty = NULL;
	struct Tasks* find_task_with_difficulty_previous = NULL;
	q = search_player(pid);
	if (q == NULL) {
		printf("The player with pid: %d does not exist\n", pid);
		return 0 ;
	}
    	if(q->tasks_head == q->tasks_sentinel){
		printf("The player with pid: %d does not have any other tasks to implement\n", pid);
		return 0;
	}
	find_task_with_difficulty = q->tasks_head;
	while ((find_task_with_difficulty->next != q->tasks_sentinel) && (find_task_with_difficulty->difficulty != difficulty)) {
		find_task_with_difficulty_previous = find_task_with_difficulty;
		find_task_with_difficulty = find_task_with_difficulty->next;
	}

	if (find_task_with_difficulty->difficulty != 0) {
		if (find_task_with_difficulty->next == q->tasks_sentinel && find_task_with_difficulty_previous == NULL) {
			q->tasks_head = find_task_with_difficulty->next;
			find_task_with_difficulty->next = NULL;
			q->tasks_sentinel->next = q->tasks_head;
			push(find_task_with_difficulty);

		}
		else if (find_task_with_difficulty->next == q->tasks_sentinel && find_task_with_difficulty_previous != NULL) {
			find_task_with_difficulty_previous->next = find_task_with_difficulty->next;
			find_task_with_difficulty->next = NULL;
			q->tasks_sentinel->next = find_task_with_difficulty_previous;
			push(find_task_with_difficulty  );
		}
		else {
			if (find_task_with_difficulty == q->tasks_head) {
				q->tasks_head = q->tasks_head->next;
				find_task_with_difficulty->next = NULL;
			}
			else {
				find_task_with_difficulty_previous->next = find_task_with_difficulty->next;
				find_task_with_difficulty->next = NULL;
				q->tasks_sentinel->next = find_task_with_difficulty_previous;
			}
			push(find_task_with_difficulty);
		}
	}
	printf("I %d %d\n", pid, difficulty);
	print_double_list2();
	printf("DONE\n");
    return 1;
}

/**
 * @brief Eject Player
 *
 * @param pid The ejected player's id
 *
 * @return 1 on success
 *         0 on failure
 *
 * Time complexity: O(n1+n2+2*n), where n1 is the number of tasks the given player has in
 *                                  his tasks list, n2 is the number of tasks the player with
 *                                  the least tasks has in his tasks list and n is the number of
 *                                  players in the players list.
 *
 * Event E
 */
int eject_player(int pid) {
    struct Players* q = NULL;
	struct Players* find_player_with_least_tasks;
	struct Players* found_player_with_least_tasks = NULL;
	struct Tasks* head_tasks_least = NULL;
	int counter;
	int min = 1000;
	q = search_player(pid);
	if (q == NULL) {
		if(eject_dont_print !=2 && eject_dont_print !=3)
			printf("The player with pid: %d does not exist\n", pid);
		return 0;
	}
	else {
		if (q->prev == players_head) {
			players_head->next = q->next;
			q->next->prev = players_head;
			q->next = NULL;
			q->prev = NULL;
		}
		else {
			q->prev->next = q->next;
			q->next->prev = q->prev;
			q->next = NULL;
			q->prev = NULL;
		}
		find_player_with_least_tasks = players_head->next;
		while (find_player_with_least_tasks != players_head) {
			if(find_player_with_least_tasks->is_alien == 1){
				find_player_with_least_tasks = find_player_with_least_tasks->next;
			}
			else {
				counter = 0;
				head_tasks_least = find_player_with_least_tasks->tasks_head;
				while (head_tasks_least != find_player_with_least_tasks->tasks_sentinel) {
					counter++;
					head_tasks_least = head_tasks_least->next;
				}
				if (counter < min) {
					min = counter;
					found_player_with_least_tasks = find_player_with_least_tasks;
				}
				find_player_with_least_tasks = find_player_with_least_tasks->next;
			}
		}
		merge_tasks_list(&q, &found_player_with_least_tasks);
		}

	
   if(eject_dont_print !=2 && eject_dont_print !=3){
        printf("E %d\n", pid);
        print_double_list2();
        printf("DONE\n");
        eject_dont_print = 1;
   }
   return 1;
}

/**
 * @brief Witness Eject Player
 *
 * @param pid_a The alien's pid
 *
 * @param pid The crewmate's pid
 *
 * @param number_of_witnesses The number of witnesses
 *
 * @return 1 on success
 *         0 on failure
 *
 * Time complexity: O(n1+n2+2*n), where n1 is the number of tasks the given player has in
 *                               his tasks list, n2 is the number of tasks the player with
 *                               the least tasks has in his tasks list and n is the number of
 *                               players in the players list.
 *
 * Event W
 */
int witness_eject(int pid, int pid_a, int number_of_witnesses){
	struct Players* q = NULL;
	int i;
	eject_dont_print = 2;
	i = eject_player(pid);
	eject_dont_print = 1;
	q = search_player(pid_a);
	if (q == NULL || i == 0) {
		printf("The player with pid: %d does not exist\n", pid);
		return 0;
	}
	else {
		q->evidence += number_of_witnesses;
	}
	printf("W %d %d %d\n", pid, pid_a, number_of_witnesses);
	print_players_with_evidence();
	printf("DONE\n");
    return 1;
}


/**
 * @brief Sabbotage
 *
 * @param pid The player's id
 *
 * @param number_of_tasks The number of tasks to be popped
 *
 * @return 1 on success
 *         0 on failure
 *
 * Time complexity: O(2*n + number_of_tasks), where n is the number of players
 *                                               in the players' list and number_of_tasks
 *                                               is the numbers of tasks to be popped.
 *
 * Event S
 */
int sabbotage(int pid, int number_of_tasks) {
    struct Players* q = NULL;
	struct Tasks* sab = NULL;
	int i;
	int temp = number_of_tasks;
		q = search_player(pid);
		if (q == NULL) {
			printf("The player with pid: %d does not exist\n", pid);
			return 0;
		}
		else {
			for (i = 0; i < (number_of_tasks / 2); i++) {
				q = q->prev;
			}
			while (number_of_tasks != 0) {
				if (q == players_head || q->is_alien == 1) {
					q = q->next;
				}
				else {
					sab = pop();
					if(sab == NULL){
					       break;
					}
					insert_sorted_players_list(&q->tasks_head, sab);
					number_of_tasks--;
					q = q->next;
				}
			}
		}
	printf("S %d %d\n", temp,pid);
	print_double_list2();
	printf("DONE\n");
    return 1;
}


/**
 * @brief Vote
 *
 * @param pid The player's id
 *
 * @param vote_evidence The vote's evidence
 *
 * @return 1 on success
 *         0 on failure
 *
 * Time complexity: O(3*n+n1+n2), where n1 is the number of tasks the given player has in
 *                               his tasks list, n2 is the number of tasks the player with
 *                               the least tasks has in his tasks list and n is the number of
 *                               players in the players list.
 *
 * Event V
 */
int vote(int pid, int vote_evidence) {
    struct Players* q = NULL;
    struct Players* most_evidence = players_head->next;
    struct Players* found_most_evidence = NULL;
	int max = -1;
	q = search_player(pid);
	if(q == NULL){
	   printf("The player with pid: %d does not exist\n", pid);	
	   return 0;
	}
	q->evidence += vote_evidence;
	while (most_evidence != players_head) {
		if (most_evidence->evidence > max) {
			max = most_evidence->evidence;
			found_most_evidence = most_evidence;
		}
		most_evidence = most_evidence->next;
	}
	if (found_most_evidence->is_alien == 1) {
		found_most_evidence->next->prev = found_most_evidence->prev;
		found_most_evidence->prev->next = found_most_evidence->next;
		found_most_evidence->next = NULL;
		found_most_evidence->prev = NULL;
	}
	else {
		eject_dont_print = 3;
		eject_player(found_most_evidence->pid);
		eject_dont_print = 1;
	}
	printf("V %d %d\n", pid, vote_evidence);
	print_players_with_evidence();
	printf("DONE\n");
    return 1;
}


/**
 * @brief Give Away Work
 *
 * @return 1 on success
 *         0 on failure
 *
 * Time complexity: O(max+n2+n*m), where max is the max tasks a player has, n2 is the number
 *                                      of tasks the Player with the least tasks have, n is the number
 *                                      of players in the players' list and m is the number of tasks the
 *                                      current player has in the while loop.
 *
 * Event G
 */
int give_work() {
    struct Players* pmax = NULL;
	struct Players* pmin = NULL;
	struct Players* q = players_head->next;
	struct Tasks* qtasks = NULL;
	int count;
	int max = -1;
	int min = 1000;
	while (q != players_head) {
		if (q->is_alien == 1)
			q = q->next;
		else {
			count = 0;
			qtasks = q->tasks_head;
			while (qtasks != q->tasks_sentinel) {
				count++;
				qtasks = qtasks->next;
			}
			if (count < min) {
				min = count;
				pmin = q;
			}
			if (count > max) {
				max = count;
				pmax = q;
			}
			q = q->next;
		}
	}
	if (pmax->pid != pmin->pid)
		merge_max_with_least(&pmax, &pmin, max);
    printf("G\n");
    print_double_list2();
    printf("DONE\n");
    return 1;
}

/**
 * @brief Terminate
 *
 * @return 1 on success
 *         0 on failure
 *
 * Time complexity: O(n), where n is the number of players in the player's list.
 *
 * Event F
 */
int terminate() {
    struct Players* q = players_head->next;
	int count_aliens = 0;
	int count_crewmates = 0;
	while (q != players_head) {
		if (q->is_alien == 1)
			count_aliens++;
		else
			count_crewmates++;
		q = q->next;
	}
	printf("F\n");
	if (count_aliens > count_crewmates) {
		printf("\tAliens win.\n");
	}else if (count_aliens == 0 || tasks_stack->count == TotalTasks) {
		printf("\tCrewmates win.\n");
	}
	else{
		printf("Nobody won.\n");
//		printf("DONE\n");
		return 0;
	}
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
    struct Players* q = players_head->next;
    printf("X\n");
    printf("\tPlayers = ");
	while (q != players_head) {
        printf("<%d:%d> ", q->pid, q->is_alien);
		q = q->next;
	}
	printf("\nDONE\n");
    return 1;
}

/**
 * @brief Print Tasks
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tasks() {
	struct Tasks* q = tasks_head->head;
	printf("Y\n");
	printf("\tList_Tasks = ");
	while (q != NULL) {
		printf("<%d,%d> ", q->tid, q->difficulty);
		q = q->next;
	}
	printf("\nDONE\n");
    return 1;
}

/**
 * @brief Print Stack
 *
 * @return 1 on success
 *         0 on failure
 */
int print_stack() {
    struct Tasks* q = tasks_stack->head;
    printf("Z\n");
    printf("\tStack_Tasks = ");
	while (q != NULL) {
		printf("<%d,%d> ", q->tid, q->difficulty);
		q = q->next;
	}
	printf("\nDONE\n");
    return 1;
}

/**
 * @brief Print Players & Task List
 *
 * @return 1 on success
 *         0 on failure
 */
int print_double_list() {
    struct Players* q = players_head->next;
    struct Tasks* print;
    printf("U\n");
    while(q != players_head){
        print = q->tasks_head;
        printf("Player_%d = ", q->pid);
        if(q->is_alien == 0){
            while(print != q->tasks_sentinel){
                printf("<%d,%d>  ", print->tid, print->difficulty);
                print = print->next;
            }
        }else{
            printf("<%d,%d>", print->tid, print->difficulty);
        }
		q = q->next;
		printf("\n");
    }
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

// From this point till the end, these are mine functions that I made to help me solve this project.

/**
 * @brief Print Players for the event P
 *
 */
void print_players2(){
    struct Players* q = players_head->next;
    printf("\tPlayers = ");
	while (q != players_head) {
        printf("<%d:%d> ", q->pid, q->is_alien);
		q = q->next;
	}
}

/**
 * @brief Print Tasks for the event T
 *
 */
void print_tasks2(){
	struct Tasks* q = tasks_head->head;
	printf("\tTasks = ");
	while (q != NULL) {
		printf("<%d,%d> ", q->tid, q->difficulty);
		q = q->next;
	}
}

/**
 * @brief Print Players and Tasks for the events D, I, E, S, G.
 *
 */
void print_double_list2(){
    struct Players* q = players_head->next;
    struct Tasks* print;
    while(q != players_head){
        print = q->tasks_head;
        printf("Player_%d = ", q->pid);
        if(q->is_alien == 0){
            while(print != q->tasks_sentinel){
                printf("<%d,%d>  ", print->tid, print->difficulty);
                print = print->next;
            }
        }else{
            printf("<%d,%d>", print->tid, print->difficulty);
        }
		q = q->next;
		printf("\n");
    }
}

/**
 * @brief Print Players and Tasks for the events W, V
 *
 */
void print_players_with_evidence(){
    struct Players* q = players_head->next;
    struct Tasks* print;
    while(q != players_head){
        print = q->tasks_head;
        printf("<Player_%d, %d> = ", q->pid, q->evidence);
        if(q->is_alien == 0){
            while(print != q->tasks_sentinel){
                printf("<%d,%d>  ", print->tid, print->difficulty);
                print = print->next;
            }
        }else{
            printf("<%d,%d>", print->tid, print->difficulty);
        }
		q = q->next;
		printf("\n");
    }

}

/**
 *@brief Checking if the General Task List is empty
 *
 * @return 1 if it's empty
 *           0 if it's not empty
 */
bool isEmptyTasksList() {
	if (tasks_head->head == NULL){
		return 1;
	}
	else{
		return 0;
	}
}

/**
 * @brief When we have an event give away work, this is the function
 *          that is merging the half of the tasks that have the least difficulty
 *          from the player with the most tasks, to the player
 *          with the least tasks, and then removing those tasks from the
 *          first player.
 *
 * Time complexity: O(max + n2), where max is the number of max nodes that
 *                     are going to merge to the player with the least tasks and
 *                     n2 is the number of tasks the Player with the least tasks have.
 */
void merge_max_with_least(struct Players** pmax, struct Players** pmin, int max){
    struct Tasks* pmax_tasks = (*pmax)->tasks_head;
	struct Tasks* pmin_tasks = (*pmin)->tasks_head;
	struct Tasks* pmin_tasks_prev = NULL;
	struct Tasks* max_pointer = (*pmax)->tasks_head;
	struct Tasks* temp = NULL;
	int i;
	for (i = 0; i < (max / 2) - 1; i++) {
		max_pointer = max_pointer->next;
	}
	while (pmax_tasks != max_pointer->next) {
		if (pmin_tasks != (*pmin)->tasks_sentinel) {
			if (pmax_tasks->difficulty <= pmin_tasks->difficulty) {
				temp = (struct Tasks*)malloc(sizeof(struct Tasks));
				temp->difficulty = pmax_tasks->difficulty;
				temp->tid = pmax_tasks->tid;
				if (pmin_tasks_prev == NULL) {
					temp->next = pmin_tasks;
					(*pmin)->tasks_head = temp;
					pmin_tasks_prev = temp;
				}
				else {
					temp->next = pmin_tasks;
					pmin_tasks_prev->next = temp;
					pmin_tasks_prev = pmin_tasks_prev->next;
				}

				if ((max / 2) - 1 < 0) {
					(*pmax)->tasks_head = (*pmax)->tasks_sentinel;
					(*pmax)->tasks_sentinel->next = (*pmax)->tasks_head;
					pmax_tasks = pmax_tasks->next;
					max_pointer->next = NULL;

				}
				else {
					(*pmax)->tasks_head = (*pmax)->tasks_head->next;
					pmax_tasks->next = NULL;
					pmax_tasks = (*pmax)->tasks_head;
				}

				if (max_pointer->next == NULL)
					break;
			}
			else {
				pmin_tasks_prev = pmin_tasks;
				pmin_tasks = pmin_tasks->next;
			}
		}
		else {
			temp = (struct Tasks*)malloc(sizeof(struct Tasks));
			temp->difficulty = pmax_tasks->difficulty;
			temp->tid = pmax_tasks->tid;
			if (pmin_tasks_prev == NULL) {
				temp->next = (*pmin)->tasks_sentinel;
				(*pmin)->tasks_head = temp;
				(*pmin)->tasks_sentinel->next = temp;
				pmin_tasks_prev = temp;
			}
			else {
				temp->next = (*pmin)->tasks_sentinel;
				pmin_tasks_prev->next = temp;
				(*pmin)->tasks_sentinel->next = temp;
				pmin_tasks_prev = pmin_tasks_prev->next;
			}

			if ((max / 2) - 1 < 0) {
				(*pmax)->tasks_head = (*pmax)->tasks_sentinel;
				(*pmax)->tasks_sentinel->next = (*pmax)->tasks_head;
				pmax_tasks = pmax_tasks->next;
				max_pointer->next = NULL;

			}
			else {
				(*pmax)->tasks_head = (*pmax)->tasks_head->next;
				pmax_tasks->next = NULL;
				pmax_tasks = (*pmax)->tasks_head;
			}

			if (max_pointer->next == NULL)
				break;
		}
	}
}


/**
 * @brief Merging together the lists of the ejected player and the
 *          player with the least tasks
 *
 * Time Complexity: O(n1+n2) , where n1 is the number of tasks of the
 *                     ejected player and n2 is the number of tasks of the
 *                     player with the least tasks.
 */
void merge_tasks_list(struct Players** ejected_player, struct Players** player_with_least_tasks) {
    struct Tasks* q_ejected = (*ejected_player)->tasks_head;
	struct Tasks* q_least = (*player_with_least_tasks)->tasks_head;
	struct Tasks* pq_least = NULL;
	struct Tasks* temp = NULL;
	while (q_ejected != (*ejected_player)->tasks_sentinel) {
		if (q_least != (*player_with_least_tasks)->tasks_sentinel) {
			if (q_ejected->difficulty <= q_least->difficulty) {
				temp = (struct Tasks*)malloc(sizeof(struct Tasks));
				temp->difficulty = q_ejected->difficulty;
				temp->tid = q_ejected->tid;
				if (pq_least == NULL) {
					temp->next = q_least;
					(*player_with_least_tasks)->tasks_head = temp;
					pq_least = temp;
				}
				else {
					temp->next = q_least;
					pq_least->next = temp;
					pq_least = pq_least->next;
				}
				q_ejected = q_ejected->next;
			}
			else if (q_ejected->difficulty > q_least->difficulty) {
				pq_least = q_least;
				q_least = q_least->next;
			}
		}
		else {
			temp = (struct Tasks*)malloc(sizeof(struct Tasks));
			temp->difficulty = q_ejected->difficulty;
			temp->tid = q_ejected->tid;
			if (pq_least == NULL) {
				temp->next = (*player_with_least_tasks)->tasks_sentinel;
				(*player_with_least_tasks)->tasks_head = temp;
				(*player_with_least_tasks)->tasks_sentinel->next = temp;
				pq_least = temp;
			}
			else {
				temp->next = q_least;
				pq_least->next = temp;
				(*player_with_least_tasks)->tasks_sentinel->next = temp;
				pq_least = pq_least->next;
			}
			q_ejected = q_ejected->next;
		}
	}
}

/**
 * @brief Inserting the given node into the right position so the list is sorted
 *
 * Time Complexity: O(n), where n is the number of tasks in the general tasks list.
 */
void insert_sorted(struct Tasks* new_node) {
	struct Tasks* q;

	if (isEmptyTasksList() || tasks_head->head->difficulty >= new_node->difficulty) {
		new_node->next = tasks_head->head;
		tasks_head->head = new_node;
	}
	else {
		q = tasks_head->head;
		while (q->next != NULL && q->next->difficulty < new_node->difficulty) {
			q = q->next;
		}
		new_node->next = q->next;
		q->next = new_node;
	}
}

/**
 * @brief This function is inserting the node from the top of the stack into the
 *          given player.
 *
 * Time complexity: O(n), where n is the number of tasks the given player has in
 *                          his tasks list.
 */
void insert_sorted_players_list(struct Tasks**temp_head, struct Tasks* new_node){
    struct Tasks* q = (*temp_head);
	struct Tasks* pq = NULL;
	if ((*temp_head)->difficulty == 0) {
		new_node->next = (*temp_head);
		(*temp_head) = new_node;
		new_node->next->next = new_node;
	}
	else {
		while (q->difficulty != 0 && q->difficulty < new_node->difficulty) {
			pq = q;
			q = q->next;
		}
		if (q->difficulty == 0) {
			new_node->next = q;
			q->next->next = new_node;
			q->next = new_node;
		}
		else {
			if (pq == NULL) {
				new_node->next = q;
				(*temp_head) = new_node;
			}
			else {
				pq->next = new_node;
				new_node->next = q;
			}
		}
	}
}

/**
 * @brief Searching for the player with the given pid
 *
 * Time Complexity: O(n) , n = number of players in the players' list
 */
struct Players* search_player(int pid) {
	struct Players* q = players_head->next;
	while (q != players_head) {
		if (q->pid == pid) {
			return q;
		}
		q = q->next;
	}
	return NULL;
}

bool isEmptyStack() {
	if (tasks_stack->head == NULL)
		return 1;
	else
		return 0;
}

struct Tasks* top() {
	if (isEmptyStack()) {
		printf("Stack is empty!\n");
		return NULL;
	}
	else {
		return tasks_stack->head;
	}

}

void push(struct Tasks* newq) {
	struct Tasks* q;
	q = (struct Tasks*)malloc(sizeof(struct Tasks));
	q->difficulty = newq->difficulty;
	q->tid = newq->tid;
	q->next = tasks_stack->head;
	tasks_stack->head = q;
	tasks_stack->count++;
}

struct Tasks* pop() {
	struct Tasks* temp, *popped;
	if (isEmptyStack()) {
		printf("Stack is empty!\n");
		return NULL;
	}
	else {
		temp = tasks_stack->head;
		popped = top();
		tasks_stack->head = tasks_stack->head->next;
		temp->next = NULL;
		tasks_stack->count--;
		return popped;
	}
}
