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


int main(int argc, char const *argv[])
{
	int sta = 1;
	uname(&unamedata);

	while(sta!=0)
	{
		char *line = NULL;
		ssize_t buffer = 0;
		printf("<%s@%s:~",getenv("USER"),unamedata.sysname);

		int i;
		for(i=0;i<namei;i++)
			printf("%c",name[i]);
		printf(">");

		getline(&line,&buffer,stdin);
		splitline(line);	
		sta = execute();

		free(line);
		// free(args);
	}


	return 0;
}
