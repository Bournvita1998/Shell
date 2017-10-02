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

char **splitline(char *line)
{
	// count = 0;
	// char **words = malloc(100000 * sizeof(char*));
	// char *token;
	int i=0,ind=0,j=0,k;

	for (k=0;k<strlen(line);k++)
	{
		if (line[k]==';')
		{array[j][ind] = 0;
			j++;ind=0;}
		else
		{array[j][ind++] = line[k];}
		array[j][ind] = 0;	
	}
	cmds = j+1;
	// for (k=0;k<cmds;k++)
	// {printf("%s ", array[k]);}

}