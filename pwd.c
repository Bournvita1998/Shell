#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include "run.h"

int pwd(char **args)
{
	char cwd[100000];
	if (getcwd(cwd,sizeof(cwd)) != NULL)
	{fprintf(stdout, "%s\n", cwd);}
	else
	{perror("getcwd() error");}
	return 1;
}