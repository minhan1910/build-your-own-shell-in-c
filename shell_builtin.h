#ifndef __SHELL_BUILD_IN__
#define __SHELL_BUILD_IN__

/*
  Function Declarations for builtin shell commands:
 */
int osh_cd(char **args);
int osh_help(char **args);
int osh_exit(char **args);
int osh_num_builtins();

extern *builtin_str[];
extern int (*builtin_func[])(char **);

#endif