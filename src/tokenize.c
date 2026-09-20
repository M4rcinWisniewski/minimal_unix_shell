#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char **tokenize_input(char *inputbuf) {
  size_t cap = 8;
  size_t count = 0;

  char **tokens = malloc(cap * sizeof(char *));
  if (!tokens) {
    perror("malloc");
    return NULL;
  }

  char *saveptr = NULL;
  char *token = strtok_r(inputbuf, " \t\n", &saveptr);
  while (token != NULL) {
    if (count + 1 >= cap) {
      cap *= 2;
      char **tmp = realloc(tokens, cap * sizeof(char *));
      if (!tmp) {
        perror("realloc");
        free(tokens);
        return NULL;
      }
      tokens = tmp;
    }
    tokens[count++] = token;
    token = strtok_r(NULL, " \t\n", &saveptr);
  }
  tokens[count] = NULL;
  return tokens;
}
