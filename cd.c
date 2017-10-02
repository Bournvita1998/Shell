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


int cd(char **args)
{
	if (args[1]==NULL)
	{
		fprintf(stderr, "expected an argument for \"cd\"\n");
	}
	else
	{
		char dot[999];
		{
			char lstr[1111];
			int i=0;
			name[namei]='/';
			namei++;
			while(args[1][i] != '\n' && args[0][3]!='.' && args[0][4]!='.')
			{
				lstr[i] = args[1][i];
				name[namei]=lstr[i];
				namei++;
				i++;
			}
			lstr[i] = '\0';

			if(args[0][3]=='.' && args[0][4]=='.' && namei>1)
			{
				int i=0,j;

				while(args[1][i] != '\n')
				{
					lstr[i] = args[1][i];
					i++;
				}
				lstr[i] = '\0';

				namei--;
				for(i=namei-1;i>=0;i--)
				{
					if(name[i]!='/')
						namei--;
					else
					{
						//int j;
						//printf("updated path is ------- ");
						//for(j=0;j<namei;j++)
						//	printf("%c",name[j]);
						//printf("\n");
						break;
					}
				}
			}

			int x = chdir(lstr);
		}
	}
	return 1;
}

