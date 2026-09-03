#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

char *read_line(void);
char **split_line(char *input);
int execve_wait(char *path, char **args, char *name);
char *find_path(char *command);
char *get_path(void);
void print_enviroment(void);
/*int compare_string(const char *env_path, const char *path); */

#endif
