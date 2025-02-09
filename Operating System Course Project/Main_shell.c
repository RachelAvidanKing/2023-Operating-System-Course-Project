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
#include <time.h>
#define BUFF_SZ 200
#define ID 10
#define MAX 20

int main()
{
	/*
	Function does not receive anything or return anything.
	Function calls upon a new processes to create new directories and txt files.
	Function uses randrange in order to initialize Criteria.txt.
	Funcion then starts a loop which will end with the entering of "exit" by user. Function reads how many arguments it has received
	and calls upon the appropriate process, while creating a son to fufill the required results.
	*/
	char name[BUFF_SZ] = "Loan";
	char *arg1[3]={"mkdir",name, NULL};
	char *arg2[3]={"touch",name, NULL};
	char buff[BUFF_SZ];
	char path[BUFF_SZ];
	char strID[ID];
	char pass[MAX];
	char str[MAX];
	char* token;
	const char t[2] = " ";
	int id_fork, id, wid, status, ran, wbytes, flag;
	char *argv5[5] = {path, strID, pass, str, NULL};
	char *argv4[4] = {path, strID, pass, NULL};
	
	switch (id_fork = fork()) //creating Loan directory
		{//cases for the fork: for the son, for a problem and for the father.
			case -1:
				perror("fork");
				exit(1);
			case 0:
				execvp(arg1[0], arg1);
				printf("ERROR!\n");
				exit(1);
			default:
				break;
		}
	wid = wait(&status);
	
	strcat(name, "/Result");
	switch (id_fork = fork()) //creating Result directory
		{//cases for the fork: for the son, for a problem and for the father.
			case -1:
				perror("fork");
				exit(1);
			case 0:
				execvp(arg1[0], arg1);
				printf("ERROR!\n");
				exit(1);
			default:
				break;
		}
	wid = wait(&status);
	
	strcat(name, "/Approved");
	switch (id_fork = fork()) //creating Approved directory
		{//cases for the fork: for the son, for a problem and for the father.
			case -1:
				perror("fork");
				exit(1);
			case 0:
				execvp(arg1[0], arg1);
				printf("ERROR!\n");
				exit(1);
			default:
				break;
		}
	wid = wait(&status);
	
	strcpy(name,"Loan/Result/Unapproved");
	switch (id_fork = fork()) //creating Unapproved directory
		{//cases for the fork: for the son, for a problem and for the father.
			case -1:
				perror("fork");
				exit(1);
			case 0:
				execvp(arg1[0], arg1);
				printf("ERROR!\n");
				exit(1);
			default:
				break;
		}
	wid = wait(&status);
	
	strcpy(name,"Loan/Request");
	switch (id_fork = fork()) //creating Request directory
		{//cases for the fork: for the son, for a problem and for the father.
			case -1:
				perror("fork");
				exit(1);
			case 0:
				execvp(arg1[0], arg1);
				printf("ERROR!\n");
				exit(1);
			default:
				break;
		}
	wid = wait(&status);
	
	strcpy(name,"Loan/User.txt");
	switch (id_fork = fork()) //creating User.txt
		{//cases for the fork: for the son, for a problem and for the father.
			case -1:
				perror("fork");
				exit(1);
			case 0:
				execvp(arg2[0], arg2);
				printf("ERROR!\n");
				exit(1);
			default:
				break;
		}
	wid = wait(&status);
	
	strcpy(name,"Loan/Result/Criteria.txt");
	switch (id_fork = fork()) //creating Request directory
		{//cases for the fork: for the son, for a problem and for the father.
			case -1:
				perror("fork");
				exit(1);
			case 0:
				execvp(arg2[0], arg2);
				printf("ERROR!\n");
				exit(1);
			default:
				break;
		}
	wid = wait(&status);
	
	srand(time(NULL));
	rand();
	ran = (rand() % 10) + 1;
	sprintf(buff, "%d", ran);
	if ((id = open("./Loan/Result/Criteria.txt", O_RDWR)) == -1)
	{
		perror("Error opening file Criteria.txt\n");
		exit(1);
	}

	if ((wbytes = write(id, buff, strlen(buff))) == -1)
	{
		perror("write 1\n");
		exit(1);
	}
	
	printf("MainShell>");
        fgets(buff, sizeof(buff), stdin);
        if (buff[strlen(buff) - 1] == '\n') {
        	buff[strlen(buff) - 1] = '\0';
        }
	
	while (strcmp(buff, "exit") != 0)
	{
		token = strtok(buff,t);
		strcpy(path,"./");
		strcat(path, token);
		flag = 2;
		if ((token = strtok(NULL, t)) != NULL){
			strcpy(strID,token);
			flag = 3;
			}
		if ((token = strtok(NULL, t)) != NULL){
			strcpy(pass,token);
			flag = 4;
			}
		if ((token = strtok(NULL, t)) != NULL){
			strcpy(str,token);
			flag = 5;
			}
		if ((token = strtok(NULL, t)) != NULL)
			flag = 6;
		if (flag == 4 || flag == 5)
		{
			switch (id = fork()) 
			{//cases for the fork: for the son, for a problem and for the father.
				case -1:
					perror("fork");
					exit(1);
				case 0:
					if (flag == 5)
					{
						execv(path, argv5);
						printf("Not Supported\n");
						exit(1);
					}
					else //if (flag == 4)
					{
						execv(path, argv4);
						printf("Not Supported\n");
						exit(1);
					}
				default:
					break;
			}
			wid = wait(&status);
		}
		else
			printf("Not Supported!\n");
		printf("MainShell>");
	        fgets(buff, sizeof(buff), stdin);
        	if (buff[strlen(buff) - 1] == '\n') {
        		buff[strlen(buff) - 1] = '\0';
        	}
	}
	printf("Goodbye\n");
	
	return 0;
}
