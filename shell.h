#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


extern char **gArgs;
extern char **cmds;
extern char *env_vars[100];
extern char *program_name;
extern int status;
extern int cmd_count;

extern char **environ;


/*Handlers*/
void handle_shell(void);
int handle_piped_shell(void);
void init_global_vars(char *pname);

void handle_unsetenv(void);
void handle_setenv(void);
void handle_exit(void);
void handle_cd(void);

void interrupt_handler(void);
void signal_handler(int signal_number);

/*Utils*/
int _strlen(char *s);
void str_append(char *from, char *to, int start);
int _strcmp(char *s1, char *s2);
int nonexact_strcmp(char *s1, char *s2);
int contains(char *s, char c);

int str_to_int(char *s);
int count_words(char *s);
void remove_char(char *buff, int index);
int cp_line(char *buff, char *line);
void *_realloc(void *ptr, int old_size, int new_size);

int _intlen(long int num, int base);
void int_to_str(long int num, char *new_num, int len, int sign);


/*Cycle functions*/
void alloc_err(void);
int handled_read(int fd, void *buff, size_t n);
int handled_write(int fd, void *buff, size_t n);
int read_whole(char *buff, int start, int *q, int *dq, int arrow);
int handle_quote(char c, int *q, int *dq);
int handle_status(int val);
int get_path(char *paths, char *path);

void free_args(void);
void free_all(void);
void free_env(void);
void free_cmds(void);

int fill_args(int count, char *buffer);
void process_args(void);
int fill_cmds(char *buff);
int _getline(char *buffer);

/*Command functions*/
void exe_command(void);
void exe_ncommand(void);
void command_process(char *buffer);
void exe_path(void);

int command_to_path(char *buff);

/*Env related functions*/
void handle_env(void);

char *_getenv(char *name, int val_only);
int _getenvIndex(char *name);
void _setenv(char *name, char *value);
void realloc_environ(char *var, int op);

void alloc_new_var(char *new_var);

void custom_perror(char *msg);
/* void write_env(char **environ);*/

#endif
