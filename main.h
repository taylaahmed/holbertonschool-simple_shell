#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int execve_wait(char **args);
int main(void);
char *read_line(void);
void looping(void);
char **split_line(char *input);
int execve_wait(char **args);
void find_path(char *command);
char *get_path(void);
int compare_string(const char *env_path, const char *path);

#endif
