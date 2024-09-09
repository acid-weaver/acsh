#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static void sig_int(int);

/**
 * main - Main entry point for our program
 * @argc: Argument count to the main
 * @argv: Pointer to array of argument values
 *
 * Return: O Always success
 */

int main(int argc, char **argv) {

  (void)argc, (void)argv;
  char *command_str = NULL;
  size_t command_str_allocated = 0;
  ssize_t command_len;

  pid_t pid;
  int status;

  // SIGNALS INIT
  if (signal(SIGINT, sig_int) == SIG_ERR)
    err_sys("Error to call signal.");

  // REPL
  do {
    write(STDOUT_FILENO, "$ ", 2);

    // INPUT
    command_len = getline(&command_str, &command_str_allocated, stdin);
    if (command_str[command_len - 1] == '\n')
      command_str[command_len - 1] = 0;

    // EXIT
    if (command_len == -1) { // EOF case
      break;
    }

    // RUN
    if ((pid = fork()) < 0) {
      err_sys("error to fork process!");
    } else if (pid == 0) {

      printf("-----|-----|-----\n"
             "NEW PROCESS\n"
             "\tPID: %lu\n"
             "\tcommand_str: %s\n"
             "\tcommand_str_allocated: %lu\n"
             "-----|-----|-----\n",
             (long)getpid(), command_str, command_str_allocated);
      exit(0);

    } else if ((pid = waitpid(pid, &status, 0)) < 0)
      err_sys("error to call waitpid");
  } while (1);

  // FINALLY
  free(command_str);
  write(STDOUT_FILENO, "\n-----|-----|-----|-----|-----|-----|-----", 42);
  return (0);
}

void sig_int(int signo) { printf("Interruption!\n"); }
