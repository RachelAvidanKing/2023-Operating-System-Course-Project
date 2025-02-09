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
#define ID 10

int main()
{
	/*
	Function does not receive anything or return anything.
	Funcion then starts a loop which will end with the entering of "LogOut" by user. Function reads how many arguments it has received
	and calls upon the appropriate process, while creating a son to fufill the required results.
	*/
	char buff[BUFF_SZ];
	char path[BUFF_SZ];
	char str[ID];
	char* token;
	const char t[2] = " ";
	int id, wid, status, flag;
	char *argv3[3] = {path, str, NULL};
	char *argv2[2] = {path, NULL};
	
	printf("ManagerShell>");
        fgets(buff, sizeof(buff), stdin);
        if (buff[strlen(buff) - 1] == '\n') {
        	buff[strlen(buff) - 1] = '\0';
        }
	
	while (strcmp(buff, "LogOut") != 0)
	{
		token = strtok(buff,t);
		strcpy(path,"./");
		strcat(path, token);
		flag = 2;
		if ((token = strtok(NULL, t)) != NULL){
			strcpy(str,token);
			flag = 3;
		}
		if ((token = strtok(NULL, t)) != NULL)
			flag = 4;
		if (flag == 2 || flag == 3){
			switch (id = fork()) 
			{//cases for the fork: for the son, for a problem and for the father.
				case -1:
					perror("fork");
					exit(1);
				case 0:
					if (flag == 2){
						execv(path, argv2);
						printf("ERROR!\n");
						exit(1);
					}
					else //if flag==3
					{
						execv(path, argv3);
						printf("ERROR!\n");
						exit(1);
					}
				default:
					break;
			}
			wid = wait(&status);
		}
		else
			printf("Not Supported!\n");
		printf("ManagerShell>");
	        fgets(buff, sizeof(buff), stdin);
        	if (buff[strlen(buff) - 1] == '\n') {
        		buff[strlen(buff) - 1] = '\0';
        	}
	}
	
	return 0;
}
