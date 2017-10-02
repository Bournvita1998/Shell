#ifndef RUN_H
#define RUN_H

int cmds;
int count,position,position1,jobpid[100];
char array[1000][1000],jobname[100][100];
struct utsname unamedata;
char name[10000];
int namei;



char **splitline(char *line);
int execute();
int pinfo(char **args);
int ls(char **args);
int cd(char **args);
int pwd(char **args);
int redirect(char **args, int num);
int set(char **args,int num);	
int unset(char **args,int num);	
int piping(char **args,int input_pipe,int fl,int l,int r,int num);	
#endif
