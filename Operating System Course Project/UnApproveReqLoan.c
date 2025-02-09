#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUFF_SZ 200
#define M 8


int main(int argc, char* argv[])
{
	//Checks if the amount of parameters received is correct
	if (argc != 2) {
		printf("Error not enough arguments!\n");
		exit(1);
	}
	int fd_id, rbytes, wbytes, length = 0, len1, len2, id_fork, wid, status;
	char* id = argv[1];
	char* token;
	char dest[BUFF_SZ] = "./Loan/Request/";
	char destinationFolder[BUFF_SZ] = "./Loan/Result/Unapproved/";
	char buff[BUFF_SZ];
	const char s[2] = "\n";
	const char t[2] = " ";
	char *arguments[4]={"mv",dest, destinationFolder, NULL};  //Moving the file to the Unapproved folder
	
	strcat(dest, id);       //Thread the id to the path
	strcat(dest, ".txt");   //Chains to the end .txt
	// If the file couldn't be opened for reading and writing, print an error message and return
	if ((fd_id = open(dest, O_RDWR)) == -1)
	{
		printf("Request Not Found!\n");
		exit(1);
	}
	//If the reading from the file fails, print an error message and return
	if ((rbytes = read(fd_id, buff, BUFF_SZ)) == -1)
	{
		perror("read 1\n");
		exit(1);
	}
	//To get to a location in the file that lists the status of the request
	length = strlen(buff);
	token = strtok(buff, s); 
	for (int i = 1; i < M; i++) {
		if (token != NULL)
		{
			token = strtok(NULL, s);
		}
	}
	len1 = strlen(token);
	token = strtok(token, t);
	len2 = strlen(token);
	length -= len1 - len2;
	lseek(fd_id, length, SEEK_SET);
	if ((wbytes = write(fd_id, "UnApproved", strlen("UnApproved"))) == -1)  //Update the loan status and if the update fails, return an appropriate message
	{
		perror("write 1\n");
		exit(1);
	}
	
	switch (id_fork = fork()) 
		{//cases for the fork: for the son, for a problem and for the father.
			case -1:
				perror("fork");
				exit(1);
			case 0:
				execvp(arguments[0], arguments);  //Moving the file to the Unapproved folder
				printf("ERROR!\n");
				exit(1);
			default:
				break;
		}
	wid = wait(&status);
	printf("Request UnApproved.\n");
	return 0;
}
