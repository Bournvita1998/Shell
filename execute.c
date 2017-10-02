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

int execute()
{
	int i;
	for (i=0;i<cmds;i++)
	{
		int redir = 0;
		char *args[10000];
		char *token;
		int l = 0,num;
		token = strtok(array[i]," ");
		while(token != NULL)
		{
			args[l++]=token;
			token = strtok(NULL," ");
		}
		args[l] = NULL;
		// printf("%d\n", l);
		// for (i=0;i<l;i++)
		// {printf("%s\n", args[i]);}
		num = l;

		if (args[0]==NULL)
		{return 1;}
		else
		{
			int bg = 0;
			int *status;
			pid_t pid;
			int pos=0;
			int last=0;
			int pipe_loc[999];
			for (int j=0;j<num;j++)
			{
				if (args[j][0]==124)
				{
					// printf("hi\n");
					pipe_loc[pos++]=j;
					args[j]=NULL;
				}
			}
			pipe_loc[pos++]=num;
			// for (int j=0;j<num;j++)
			// {
			// 	if (args[j][0]==60 || args[j][0]==62)
			// 	{redir = 1; break;}
			// }
			// printf("%d\n",pos );
			if(pos!=1)
			{
				int in=dup(0);
				int out=dup(1);
				int l=0,z=-1;
				// printf("he\n");
				args[num-1][strlen(args[num-1])-1]=0;
				args[num]=NULL;
				for(i=0;i<pos;i++){
					int r=pipe_loc[i];
					z=piping(&args[l],z,pos-1-i,l,r,r-l);
					l=r+1;
				}
				dup2(out,1);
				close(out);
			}
			else
			if (redir==1)
			{redirect(args,num);}
			else
			{
				if (args[0][0]==113 && args[0][1]==117 && args[0][2]==105 && args[0][3]==116)
				{return 0;}
				else if (args[0][0]==99 && args[0][1]==100)
				{cd(args);}
				else if (args[0][0]==112 && args[0][1]==119 && args[0][2]==100)
				{pwd(args);}
				else if (args[0][0]==108 && args[0][1]==115)
				{ls(args);}
				else if (args[0][0]==115 && args[0][1]==101 && args[0][2]==116 && args[0][3]==101 && args[0][4]==110 && args[0][5]==118)
				{set(args,num);}
				else if (args[0][0]==117 && args[0][1]==110 && args[0][2]==115 && args[0][3]==101 && args[0][4]==116 && args[0][5]==101 && args[0][6]==110 && args[0][7]==118)
				{unset(args,num);}
				else if (args[0][0]==101 && args[0][1]==99 && args[0][2]==104 && args[0][3]==111)
				{
					if (args[1][0]==36)
					{
						args[1][strlen(args[1])-1] = 0;
						char name[1000];
						char * value;
						strncpy(name,&args[1][1],strlen(args[1])-1);
						name[strlen(args[1])-1] = '\0';
						// printf("%s\n", name);
						value = getenv(name);
						if (value==NULL)
						{perror("This environment variable does not exist.");}
						else
						{
							// value[strlen(value)-1] = 0;
							printf("%s\n", value);
						}
					}
					else
					{
						int var;
						char str[100000]={0};
						if (num==2)
						{strcat(str,args[1]);}
						else
						{
							for (var=1;var<num-1;var++)
							{
								strcat(str,args[var]);
								strcat(str," ");
							}
							strcat(str,args[num-1]);
						}
						strcat(str,"\0");
						printf("%s",str);
					}
					return 1;
				}
				else if (args[0][0]==112 && args[0][1]==105 && args[0][2]==110 && args[0][3]==102 && args[0][4]==111)
				{pinfo(args);}
				else if (args[0][0]==107 && args[0][1]==106 && args[0][2]==111 && args[0][3]==98)
				{
					kill(jobpid[(int)args[1][0]-1],(int)args[2][0]);
				}
				else if (args[0][0]==106 && args[0][1]==111 && args[0][2]==98 && args[0][3]==115)
				{
					// printf("%d\n", position);
					// printf("2%d\n", jobpid[0]);
					int k = 0;
					while(k<position)
					{
						printf("[");
						printf("%d", k+1);
						printf("]     ");
						printf("%s", jobname[k]);
						printf("[");
						printf("%d", jobpid[k]);
						printf("]");
						printf("\n");
						k++;
					}	
				}
				else
				{
					int r=0;
					if (args[1]==NULL)
					{bg = 0;}
					else if (*args[1]==38)
					{
						bg = 1;
						strcpy(jobname[position++],args[0]);
						// printf("%d\n", position);
					}
					int status;	
					if (bg==0)
					{
						args[num-1][strlen(args[num-1])-1] = 0;
						args[num]=NULL;
						// printf("%d %s\n", strlen(args[0]),args[0]);
						// printf("%d %s\n", strlen(args[1]),args[1]);
						pid = fork();
						if(pid==0)
						{
							if(execvp(args[0],args)<0)
							{r = 1; printf("%s : Command doesn't exist\n", args[0]);}
						}
						else
						{wait(NULL);}
						if (r!=1)
						{
							printf("%s with process id: %d exited normally\n",args[0],pid);
						}					
					}	
					else
					{
						pid = fork();
						if (bg!=0 && pid==0)
						{
							// jobpid[position1++] = getpid();
							// printf("%d\n", k);
							// printf("%d\n", jobpid[0]);
							// printf("hello\n");
							int pidd = fork();

							if(pidd == 0){							
								execvp(args[0],args);
								exit(0);
							}
						}
						else
						{
							int k = pid;
								// printf("%d\n", k);
							jobpid[position1++] = k;
							// printf("%d\n", jobpid[0]);
						}
					}
				}
			}

		}
	}
}
