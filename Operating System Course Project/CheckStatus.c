#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#define BUFF_SZ 200
#define M 8


int main(int argc, char* argv[])
{
	/*
	Function receives and int argc and a string array argv (full of the arguments received). Function does not return anything.
	Function checks if the username and password are correct. If so, function searches for the status of the request and prints it
	onto the screen.
	*/

	int fd_id, rbytes, wbytes;
	char* id = argv[1];
	char* str = argv[1];
	char* password = argv[2];
	char dest1[BUFF_SZ] = "./Loan/Request/";
	char dest2[BUFF_SZ] = "./Loan/Result/Approved/";
	char dest3[BUFF_SZ] = "./Loan/Result/Unapproved/";
	char buff[BUFF_SZ];
	const char s[2] = "\n";
	char* token;

	strcat(dest1, str);
	strcat(dest1, ".txt");
	
	if ((fd_id = open(dest1, O_RDONLY)) == -1)
	{
		strcat(dest2, str);
		strcat(dest2, ".txt");
		if ((fd_id = open(dest2, O_RDONLY)) == -1)
		{
			strcat(dest3, str);
			strcat(dest3, ".txt");
			if ((fd_id = open(dest3, O_RDONLY)) == -1){
				printf("No such file found\n");
				exit(1);
				}
		}
	}
	
	if ((rbytes = read(fd_id, buff, BUFF_SZ)) == -1)
	{
		perror("read 1\n");
		exit(1);
	}
	token = strtok(buff, s);
	if (strcmp(password, token) != 0) {
		printf("Wrong Password\n");
		exit(1);
	}
	
	for (int i = 1; i < M; i++) {
		if (token != NULL)
			token = strtok(NULL,s);
	}

	printf("%s\n", token);
	return 0;
}
