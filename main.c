#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "string_util.h"
#include "shell_builtin.h"

int osh_launch(char ** args);

int osh_execute(char ** args) {
    int i;

    if (args[0] == NULL) {
        return 1;
    }

    for (i = 0; i < osh_num_builtins(); ++i) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return osh_launch(args);
}
int osh_launch(char ** args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
    } else {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

void shell_loop() {
  char *line;
  char **args;
  int status;
  const char * delimiter = " ";
  int count;

  do {
    printf("osh> ");
    line = read_line();
    args = split_str(line, delimiter, &count);
    status = osh_execute(args);

    free(line);
    free(args);
  } while (status);
}

int main(int argc, char const *argv[])
{
    shell_loop();
    
    return EXIT_SUCCESS;
}





