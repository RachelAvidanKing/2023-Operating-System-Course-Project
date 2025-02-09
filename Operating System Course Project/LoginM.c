#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFF_SZ 200
#define M 8

int main(int argc, char* argv[])
{
	/*
	Function receives and int argc and a string array argv (full of the arguments received). Function does not return anything.
	Function checks if the username and password are correct. If so, function calls upon another process (it's own son) and splits
	off into "Manager_shell" until Manager_shell finishes and returns.
	*/
	int fd_mg, id, wid, status, rbytes, flag=0;
	char buff[BUFF_SZ];
	char str[BUFF_SZ];
	char* spare;
	char* acount = argv[1];
	char* password = argv[2];
	char* dest = "./Manager_pass.txt";
	char* path = "./Manager_shell";
	char* token;
	char* tk2;
	const char s[2] = "\n";
	const char t[2] = " ";

	if ((fd_mg = open(dest, O_RDONLY)) == -1)
	{
		perror("open file Manager_pass\n");
		exit(1);
	}
	if ((rbytes = read(fd_mg, buff, BUFF_SZ)) == -1)
	{
		perror("read 1\n");
		exit(1);
	}
	while (rbytes > 0)
	{
		token = strtok(buff, s);
		while (token != NULL)
		{
			strcpy(str,token);
			spare = str;
			tk2 = strsep(&spare, t);
			if (strcmp(acount, tk2) == 0)
			{
				tk2 = strsep(&spare, t);
				if (strcmp(password, tk2) == 0)
				{
					switch (id = fork()) 
					{//cases for the fork: for the son, for a problem and for the father.
						case -1:
							perror("fork");
							exit(1);
						case 0:
							execl(path, "Manager_shell", NULL);
							printf("ERROR!\n");
							exit(1);
						default:
							break;
					}
					wid = wait(&status);	//wait for fork to finish (successfully)
					flag = 1;
					break;
				}
			}
			else
			{
				token = strtok(NULL, s);
			}
		}
		if (flag == 1)//if already returned from son process, exit loop
			break;
		if ((rbytes = read(fd_mg, buff, BUFF_SZ)) == -1)
		{
			perror("read 1\n");
			exit(1);
		}
		
	}
	if (flag == 0)
		printf("No such manager/password combination exists\n");
	return 0;
}
