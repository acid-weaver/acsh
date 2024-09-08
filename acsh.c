#include "apue.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  char line[MAXLINE];

  do {
    printf("$ ");

    // INPUT
    // EXIT
    if (scanf("%s", line) == EOF || strcmp(line, "exit") == 0) {
      break;
    }

    // DEBUG
    printf("DEBUG MESSAGE.\n\tline=%s\n", line);
  } while (1);

  // FINALLY
  printf("\n-----|-----|-----|-----|-----|-----|-----");
  return 0;
}
