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

int set(char **args, int num)
{
	if (args[1]==NULL || num>3)
	{perror("Inappropriate number of arguments for setenv");}
	else
	{
			if (args[2]==NULL)
			{setenv(args[1],"",1);}
			else
			{setenv(args[1],args[2],1);}
	}
	return 1;
}
