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

int pinfo(char **args)
{
	if (args[1]==NULL)
	{
		long long int x = (long long int)getpid();
		printf("pid -- %lld\n",x);

		char file[1000];
		sprintf(file,"/proc/self/stat");
		FILE *f = fopen(file,"r");
		int status1;
		char state,status2[1000];
		fscanf(f,"%d %s %c",&status1,status2,&state);
		printf("Process Status -- ");
		printf("%c\n",state);	
		fclose(f);

		long long int mem;
		FILE *f1 = fopen("/proc/self/statm","r");
		fscanf(f1,"%lld",&mem);
		printf("memory -- ");
		printf("%lld\n",mem);
		fclose(f1);

		char tmp[1000],loc[1000];
		strcpy(tmp,"/proc/self/exe");
		int len = readlink(tmp,loc,sizeof(loc));
		loc[len] = '\n';	
		printf("Executable Path -- %s",loc);

	}

	else 
	{
		printf("pid -- %s",args[1]);
		char file[1000],file1[1000];
		args[1][strlen(args[1])-1] = 0;
		sprintf(file,"/proc/%s/stat",args[1]);
		FILE *f = fopen(file,"r");
		int status1;
		char state,status2[1000];
		fscanf(f,"%d %s %c",&status1,status2,&state);
		printf("Process Status -- ");
		printf("%c\n",state);	
		fclose(f);

		long long int mem;
		sprintf(file1,"/proc/%s/statm",args[1]);
		FILE *f1 = fopen(file1,"r");
		fscanf(f1,"%lld",&mem);
		printf("memory -- ");
		printf("%lld\n",mem);
		fclose(f1);

		char tmpr[1000],tmp[1000],loc[1000]={0};
		strcpy(tmpr,"/proc/");
		strcat(tmpr,args[1]);
		strcat(tmpr,"/exe");
		//printf("%s\n", tmpr);
		//strcpy(tmp,tmpr);
		int len = readlink(tmpr,loc,sizeof(loc));
		loc[len] = '\n';	
		printf("Executable Path -- %s",loc);
	}
	return 1;
}
