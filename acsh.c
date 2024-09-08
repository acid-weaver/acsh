// #include "acsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Main entry point for our program
 * @argc: Argument count to the main
 * @argv: Pointer to array of argument values
 *
 * Return: O Always success
 */

int main(int argc, char **argv) {

  (void)argc, (void)argv;
  char *command = NULL;
  size_t command_len = 0;
  ssize_t output;

  do {
    write(STDOUT_FILENO, "$ ", 2);

    // INPUT
    output = getline(&command, &command_len, stdin);

    // EXIT
    if (output == -1) { // EOF case
      break;
    }

    // DEBUG
    printf("DEBUG MESSAGE.\n\tline=%s\n", command);
  } while (1);

  // FINALLY
  free(command);
  write(STDOUT_FILENO, "\n-----|-----|-----|-----|-----|-----|-----", 42);
  return (0);
}
