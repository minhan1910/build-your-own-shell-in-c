#include <stdio.h>
#include <unistd.h>
#include "shell_builtin.h"

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[])(char **) = {
    &osh_cd,
    &osh_help,
    &osh_exit,
};

int osh_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

int osh_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "osh: expected arguments to \"cd\"");
        return -1;
    }

    if (chdir(args[1]) != 0)
    {
        perror("chdir failed");
        return -1;
    }

    return 0;
}

int osh_help(char **args)
{
    int i;
    printf("Minh An's OSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < osh_num_builtins(); ++i)
    {
        printf("    %s\n", builtin_str[i]);
    }
}

int osh_exit(char **args)
{
    return 0;
}