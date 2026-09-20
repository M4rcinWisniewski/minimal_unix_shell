#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../include/tokenize.h"

int main(void) {
  char *inputbuf = NULL;
  size_t buffsize = 0;
  int last_status = 0;
  // don't die on Ctrl-C
  struct sigaction sa = {0};
  sa.sa_handler = SIG_IGN;
  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGQUIT, &sa, NULL);

  while (1) {
    fputs("mysh> ", stdout);
    fflush(stdout);

    ssize_t length = getline(&inputbuf, &buffsize, stdin);
    if (length == -1) {
      if (feof(stdin)) {
        putchar('\n');
        break;
      }
      perror("getline");
      free(inputbuf);
      return 1;
    }

    char **tokens = tokenize_input(inputbuf);
    if (!tokens)
      continue;

    if (tokens[0] == NULL) {
      free(tokens);
      continue;
    }

    // --- execute ---
    pid_t pid = fork();
    if (pid < 0) {
      perror("fork");
      free(tokens);
      continue;
    }

    if (pid == 0) {
      // CHILD
      execvp(tokens[0], tokens);
      perror(tokens[0]);
      _exit(127);
    }

    // PARENT
    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
      last_status = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
      last_status = 128 + WTERMSIG(status);
    }

    free(tokens);
  }

  free(inputbuf);
  (void)last_status; // will be used once $? is implemented
  return 0;
}
