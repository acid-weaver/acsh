#include "../include/builtins.h"
#include <stdio.h>

void loop(void) {
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    // input = read_line();
    // args = acsh_split_line(line);
    // status = acsh_execute(args);

    // free(line);
    // free(args);
  } while (status);
}

int main(int argc, char **argv) {
  loop();
  return 0;
}
