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


int ls(char **args)
{
	if (args[1]==NULL)
	{
		DIR *direc;
		char cur[100000];
		struct dirent *file;
		getcwd(cur,sizeof(cur));
		direc = opendir(cur);
		while((file = readdir(direc)) != NULL)
		{
			if (file->d_name[0] != '.')
			{
				printf("%s\n", file->d_name);
			}
		}
		closedir(direc);		
	}

	else if ((args[1][0]==45 && args[1][1]==97 && args[1][2]==108) || (args[1][0]==45 && args[1][1]==108 && args[1][2]==97))
	{
		DIR *dp;
		char cur[100000];
		struct dirent *dirp;
		getcwd(cur,sizeof(cur));
		char path[100000];
		if ((dp=opendir(cur)) == NULL)
		{printf("cant open file\n");}
		else
		{
			while((dirp=readdir(dp)) != NULL)
			{
				strcpy(path,cur);
				strcat(path,"/");
				strcat(path,dirp->d_name);
				struct stat filestat;
				struct stat attr;
				struct tm clock;
				struct group *grp;
				struct passwd *pwd;
				register gid_t gid = getgid();
				register uid_t uid = getuid();

				grp = getgrgid(gid);
				pwd = getpwuid(uid);

				stat(path,&filestat);
				stat(path,&attr);

				time_t t = attr.st_mtime;
				localtime_r(&t,&clock);
				char date[100];
				strftime(date,sizeof(date),"%c",&clock);
				printf( (S_ISDIR(filestat.st_mode)) ? "d" : "-");
				printf( (filestat.st_mode & S_IRUSR) ? "r" : "-");
				printf( (filestat.st_mode & S_IWUSR) ? "w" : "-");	
				printf( (filestat.st_mode & S_IXUSR) ? "x" : "-");
				printf( (filestat.st_mode & S_IRGRP) ? "r" : "-");
				printf( (filestat.st_mode & S_IWGRP) ? "w" : "-");
				printf( (filestat.st_mode & S_IXGRP) ? "x" : "-");
				printf( (filestat.st_mode & S_IROTH) ? "r" : "-");
				printf( (filestat.st_mode & S_IWOTH) ? "w" : "-");
				printf( (filestat.st_mode & S_IXOTH) ? "x" : "-");
				printf(" ");
				printf("%d", (int)filestat.st_nlink);
				printf(" ");
				printf("%s", pwd->pw_name);
				printf(" ");
				printf("%s", grp->gr_name);
				printf(" ");
				printf("%d",(int)filestat.st_size);			
				printf(" ");
				printf("%s ", date);
				printf("%s", dirp->d_name);
				printf("\n");	

			}
		}		
	}

	else if (args[1][0]==45 && args[1][1]==108)
	{
		DIR *dp;
		char cur[100000];
		struct dirent *dirp;
		getcwd(cur,sizeof(cur));
		char path[100000];
		if ((dp=opendir(cur)) == NULL)
		{printf("cant open file\n");}
		else
		{
			while((dirp=readdir(dp)) != NULL)
			{
				if (dirp->d_name[0] != '.')
				{
					strcpy(path,cur);
					strcat(path,"/");
					strcat(path,dirp->d_name);
					struct stat filestat;
					struct stat attr;
					struct tm clock;
					struct group *grp;
					struct passwd *pwd;
					register gid_t gid = getgid();
					register uid_t uid = getuid();

					grp = getgrgid(gid);
					pwd = getpwuid(uid);

					stat(path,&filestat);
					stat(path,&attr);

					time_t t = attr.st_mtime;
					localtime_r(&t,&clock);
					char date[100];
					strftime(date,sizeof(date),"%c",&clock);
					printf( (S_ISDIR(filestat.st_mode)) ? "d" : "-");
					printf( (filestat.st_mode & S_IRUSR) ? "r" : "-");
					printf( (filestat.st_mode & S_IWUSR) ? "w" : "-");	
					printf( (filestat.st_mode & S_IXUSR) ? "x" : "-");
					printf( (filestat.st_mode & S_IRGRP) ? "r" : "-");
					printf( (filestat.st_mode & S_IWGRP) ? "w" : "-");
					printf( (filestat.st_mode & S_IXGRP) ? "x" : "-");
					printf( (filestat.st_mode & S_IROTH) ? "r" : "-");
					printf( (filestat.st_mode & S_IWOTH) ? "w" : "-");
					printf( (filestat.st_mode & S_IXOTH) ? "x" : "-");
					printf(" ");
					printf("%d", (int)filestat.st_nlink);
					printf(" ");
					printf("%s", pwd->pw_name);
					printf(" ");
					printf("%s", grp->gr_name);
					printf(" ");
					printf("%d",(int)filestat.st_size);			
					printf(" ");
					printf("%s ", date);
					printf("%s", dirp->d_name);
					printf("\n");	
				}

			}
		}
	}

	else if (args[1][0]==45 && args[1][1]==97)
	{
		DIR *direc;
		char cur[100000];
		struct dirent *file;
		if (args[2]==NULL)
		{
			getcwd(cur,sizeof(cur));
			direc = opendir(cur);
			while((file = readdir(direc)) != NULL)
			{
				printf("%s\n", file->d_name);
			}
			closedir(direc);
		}
		else
		{
			direc = opendir(args[2]);
			while((file = readdir(direc)) != NULL)
			{
				printf("%s\n", file->d_name);
			}	
			closedir(direc);
		}
	}

	return 1;

}