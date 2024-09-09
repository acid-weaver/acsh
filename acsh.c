#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
// #include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void sig_int(int);
char *get_command_path(char *file_name);

/**
 * main - Main entry point for our program
 * @argc: Argument count to the main
 * @argv: Pointer to array of argument values
 *
 * Return: O Always success
 */

int main(int argc, char **argv) {

  (void)argc, (void)argv;
  char *command_path, *command_str = NULL;
  size_t command_str_allocated = 0;
  ssize_t command_len;

  char *token;
  char **arguments;

  pid_t pid;
  int status, i;

  // SIGNALS INIT
  if (signal(SIGINT, sig_int) == SIG_ERR)
    err_sys("Error to call signal.");

  // REPL
  do {
    write(STDOUT_FILENO, "$ ", 2);

    // INPUT
    command_len = getline(&command_str, &command_str_allocated, stdin);
    // if (command_str[command_len - 1] == '\n')
    // command_str[command_len - 1] = 0;

    token = strtok(command_str, " \n");
    arguments = malloc(sizeof(char *) * 1024);
    i = 0;
    while (token) {
      arguments[i] = token;
      token = strtok(NULL, " \n");
      i++;
    }
    arguments[i] = NULL;

    command_path = get_command_path(arguments[0]);

    // EXIT
    if (command_len == -1) { // EOF case
      break;
    }

    // RUN
    if ((pid = fork()) < 0) {
      err_sys("error to fork process!");
    } else if (pid == 0) {

      if (execve(command_path, arguments, NULL) == -1) {
        err_sys("Error to execute command");
      }
      printf("-----|-----|-----\n"
             "NEW CHILD PROCESS\n"
             "\tPID: %lu\n"
             "\tcommand_str: %s\n"
             "\tcommand_len: %lu\n"
             "\tcommand_str_allocated: %lu\n"
             "-----|-----|-----\n",
             (long)getpid(), command_str, command_len, command_str_allocated);
      exit(0);

    } else if ((pid = waitpid(pid, &status, 0)) < 0)
      err_sys("Error to call waitpid");
  } while (1);

  // FINALLY
  free(command_str);
  write(STDOUT_FILENO, "\n-----|-----|-----|-----|-----|-----|-----", 42);
  return (0);
}

char *get_command_path(char *file_name) {
  char *path = getenv("PATH");
  char *token;
  struct stat file_path;
  char *path_buffer = NULL;

  if (!path) {
    perror("PATH not found");
  }

  token = strtok(path, ":");

  while (token) {
    if (path_buffer) {
      free(path_buffer);
      path_buffer = NULL;
    }
    path_buffer = malloc(sizeof(token) + sizeof(file_name) + sizeof(char) * 2);
    if (!path_buffer) {
      perror("Error: malloc failed");
      exit(EXIT_FAILURE);
    }
    strcpy(path_buffer, token);
    strcat(path_buffer, "/");
    strcat(path_buffer, file_name);
    strcat(path_buffer, "\0");

    if (stat(path_buffer, &file_path) == 0 && access(path_buffer, X_OK) == 0) {
      // free(path);
      return (path_buffer);
    }
    token = strtok(NULL, ":");
  }

  // FINALLY
  // free(path);
  if (path_buffer)
    free(path_buffer);

  perror("Absolute path not found");
  return (NULL);
}

void sig_int(int signo) { printf("Interruption!\n"); }
