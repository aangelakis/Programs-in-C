/*
  Alexandros Angelakis
  csd4334@csd.uoc.gr
  assignment1 - hy345
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define DEBUG 0 

size_t SIZE = 1024;
size_t MAX_COMMAND = 100;

int **pipefd;

/* Struct for every command from input. */
typedef struct command {
  char *command; /* The command. */
  char **args;   /* The arguments of the command. */
  int action;    /* 1 for pipe, 2 for '>' , 3 for '<' , 4 for ">>" and 0 for
                    nothing. */
  int args_length;
  char *file_output;
  char *file_input;
} cmd;

/* printing the prompt */
void prompt();

/* Storing the input of the user. Returns 0 if no input is given or 1 if a
 * command/commands is/are given. */
int read_input(char *);

/* We tokenize the spaces of the input to find every command */
cmd *tokenize(char *, int *);

/* The function that execute the commands. */
void execute_commands(cmd *, int, int);

/* Initializes the pipes of the input. */
void initialize_pipes(int);

int main(int argc, char *argv[]) {

  char input[SIZE];
  int i = 0;
  int length = 0;
  int pipes;
  cmd *commands;

  while (1) {

    /* Show the prompt of the user. */
    prompt();

    pipes = 0;
    /* If no input given, then continue to the next loop. */
    if (read_input(input) == 0) {
      continue;
    }

    /* Tokenize the input and store the commands found in a pointer of struct
     * cmd. */
    commands = tokenize(input, &length);

    /* Finding the number of pipes from the input. */
    for (i = 0; i < length; i++) {
      if (commands[i].action == 1) {
        pipes++;
      }
    }

    /* Allocating memory for the pipe of each command that has one. */
    initialize_pipes(pipes);

    printf("length of commands: %d\n", length);
    printf("pipes: %d\n", pipes);

    if (DEBUG) {
      int j;
      for (i = 0; i < length; i++) {
        printf("%s ", commands[i].command);
        j = 0;
        if (commands[i].args[j] == NULL) {
          printf("with no arguments\n");
        }
        while (commands[i].args[j] != NULL) {
          printf("with arguments: %s\n", commands[i].args[j]);
          j++;
        }
      }
    }

    if (strcmp(commands[0].command, "exit") == 0) {
      exit(0);
    }
    /* else if (strcmp(commands[0].command, "cd") == 0) {
      chdir(commands[0].args[0]);
    } */
    else {
      /* For each command found, execute it one by one. */
      for (i = 0; i < length; i++) {
        execute_commands(commands, i, length);
      }
    }
  }

  return 0;
}

/* Execute commands one by one. */
void execute_commands(cmd *command, int index, int length) {
  int i;
  int j = 0;
  char *excvp_args[50];
  int pipeline = 0;
  FILE *file;
  int fd;

  /* Storing the current command with its arguments in a new array of char
   * pointers for the execvp function. */
  excvp_args[0] = (char *)malloc(50 * sizeof(char));
  strcpy(excvp_args[0], command[index].command);

  i = 1;
  while (command[index].args[j] != NULL) {
    excvp_args[i] = (char *)malloc(50 * sizeof(char));
    strcpy(excvp_args[i], command[index].args[j]);
    i++;
    j++;
  }

  /* execvp needs the array of pointers to be terminated by a NULL pointer. */
  excvp_args[i] = NULL;

  if (DEBUG) {
    i = 0;
    while (command[index].args[i] != NULL) {
      printf("arguments: %s\n", command[index].args[i]);
      i++;
    }
  }

  /* If the command is cd then just use chdir() and return. */
  if (strcmp(command[index].command, "cd") == 0) {
    chdir(excvp_args[1]);
    return;
  }

  /* If you are not the last command and you have a pipe. */
  if ((index != length - 1) && command[index].action == 1) {
    pipeline = 1;
    pipe(pipefd[index]);
  }

  pid_t pid = fork();

  if (pid == -1) {
    printf("\nFailed forking child..");
    return;
  } else if (pid == 0) {

    /* If we have a '>' */
    if (command[index].action == 2) {

      file = fopen(command[index].file_output, "w+");

      fd = fileno(file);

      if (fd == -1) {
        printf("Couldn't open file\n");
        exit(-1);
      }
      dup2(fd, 1);
      fclose(file);
    }

    /* If we have a '<' */
    if (command[index].action == 3) {

      file = fopen(command[index].file_input, "r");

      fd = fileno(file);

      if (fd == -1) {
        printf("Couldn't open file\n");
        exit(-1);
      }
      dup2(fd, 0);
      fclose(file);
    }

    if(command[index].action == 4){

      file = fopen(command[index].file_output, "a");

      fd = fileno(file);

      if(fd == -1){
        printf("Couldn't open file\n");
        exit(-1);
      }
      dup2(fd, 1);
      fclose(file);
    }

    /* If we have pipes */
    if (pipeline) {
      dup2(pipefd[index][1], STDOUT_FILENO);
    }

    if (index > 0 && (command[index - 1].action == 1)) {
      dup2(pipefd[index - 1][0], STDIN_FILENO);
    }

    /* Execute the command */
    execvp(excvp_args[0], excvp_args);

    printf("Could not execute command..\n");
    exit(0);

  } else {

    /* Close all the pipes */
    if ((index != length - 1) && command[index].action == 1) {
      close(pipefd[index][1]);
    }

    if (index > 0 && (command[index - 1].action == 1)) {
      close(pipefd[index - 1][0]);
    }

    wait(NULL);
  }
  return;
}

/* Initializes the pipes of the input. */
void initialize_pipes(int pipes) {
  int i;
  pipefd = (int **)malloc(pipes * sizeof(int *));
  for (i = 0; i < pipes; i++) {
    pipefd[i] = (int *)malloc(2 * sizeof(int));
  }
}

/* We tokenize the input to find every command */
cmd *tokenize(char *input, int *length) {
  char *token = strtok(input, " ");
  cmd *commands = (cmd *)malloc(SIZE * sizeof(cmd));
  int current_command = 0, current_arg = 0;

  int command_found =
      0; /* Boolean variable that indicates the a command is found and helps us
with the arguments with no '-' next to them (just spaces).*/

  /* If the input has as first character '-' or ';' then do nothing. */
  if (token[0] == '-' || token[0] == ';' || token[0] == '|' ||
      token[0] == '>' || token[0] == '<') {
    printf("Wrong input given\n");
    return NULL;
  }

  while (token != NULL) {

    /* If the first character of the current token has '-' then it's an argument
     * of the current command. */
    if (token[0] == '-') {

      commands[current_command].args[current_arg] =
          (char *)malloc(MAX_COMMAND * sizeof(char));
      strcpy(commands[current_command].args[current_arg], token);
      current_arg++;
      commands[current_command].args_length = current_arg;
      /* If we encounter a pipe. */
    } else if (token[0] == '|') {
      commands[current_command].action = 1;
      commands[current_command].args_length = current_arg;
      current_command++;
      command_found = 0;
      current_arg = 0;
      /* If we encounter a redirection. */
    } else if (strcmp(token, ">>") == 0) {
      commands[current_command].file_output =
          (char *)malloc(MAX_COMMAND * sizeof(char));
      commands[current_command].action = 4;
      token = strtok(NULL, " ");
      strcpy(commands[current_command].file_output, token);
      command_found = 0;
      current_arg = 0;
    } else if (token[0] == '>') {
      commands[current_command].file_output =
          (char *)malloc(MAX_COMMAND * sizeof(char));
      commands[current_command].action = 2;
      token = strtok(NULL, " ");
      strcpy(commands[current_command].file_output, token);

      // current_command++;
      command_found = 0;
      current_arg = 0;
    } else if (token[0] == '<') {
      commands[current_command].file_input =
          (char *)malloc(MAX_COMMAND * sizeof(char));
      commands[current_command].action = 3;
      token = strtok(NULL, " ");
      strcpy(commands[current_command].file_input, token);
      command_found = 0;
      current_arg = 0;
    }
    /* If we have found a command and its argument(s) have spaces and not '-'
       then store them as arguments. */
    else if (command_found == 1 && token[0] != ';') {
      commands[current_command].args[current_arg] =
          (char *)malloc(MAX_COMMAND * sizeof(char));
      strcpy(commands[current_command].args[current_arg], token);
      current_arg++;
      commands[current_command].args_length = current_arg;
    }
    /* If we find in our input ';' then go find the next command. */
    else if (token[0] == ';') {
      commands[current_command].args_length = current_arg;
      current_command++;
      commands[current_command].action = 0;
      current_arg = 0;
      command_found = 0;
    } else {
      /* We have a command. Allocate memory for the command and its arguments.
       */
      int i;
      command_found = 1;
      commands[current_command].command =
          (char *)malloc(MAX_COMMAND * sizeof(char));
      commands[current_command].args =
          (char **)malloc(MAX_COMMAND * sizeof(char *));
      commands[current_command].action = 0;

      /* Making a valid string. */
      for (i = 0; i < MAX_COMMAND; i++) {
        commands[current_command].command[i] = '\0';
      }

      strcpy(commands[current_command].command, token);
    }

    token = strtok(NULL, " ");
  }

  *length = current_command + 1;

  return commands;
}

/* Storing the input of the user. Returns 0 if no input is given or 1 if a
 * command/commands is/are given. */
int read_input(char *input) {
  int c, i;
  int index = 0, counter = 0;

  while ((c = getchar()) != '\n') {
    input[index] = c;
    index++;
  }

  input[index] = '\0';

  for (i = 0; i < index; i++) {
    if (input[i] == ' ')
      counter++;
  }

  // printf("%s\n",input);
  if (counter == index)
    return 0;
  if (index == 0)
    return 0;
  return 1;
}

/* printing the prompt */
void prompt() {
  char dir[SIZE];
  char *user;

  user = getlogin();

  getcwd(dir, SIZE);

  printf("%s", user);
  printf("@cs345sh");
  printf("%s", dir);
  printf("$ ");
}