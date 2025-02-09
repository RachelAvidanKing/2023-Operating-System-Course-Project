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
#define M 7


int main(int argc, char* argv[])
{
	//Checks if the amount of parameters received is correct
	if (argc != 2) {
		printf("Error not enough arguments!\n");
		exit(1);
	}

	int fd_id, rbytes;
	char* id = argv[1];
	char* token;
	char dest[BUFF_SZ] = "./Loan/Request/";
	char id_txt[BUFF_SZ];
	char buff[BUFF_SZ];
	const char s[2] = "\n";

	strcat(dest, id); //Thread the id to the path
	strcat(dest, ".txt"); //Chains to the end .txt

	// If the file couldn't be opened, print an error message and return
	if ((fd_id = open(dest, O_RDONLY)) == -1)
	{
		perror("Request Not Found!\n");
		exit(1);
	}
	//If the reading from the file fails, print an error message and return
	if ((rbytes = read(fd_id, buff, BUFF_SZ)) == -1)
	{
		perror("read 1\n");
		exit(1);
	}

	//Displays the information of the relevant id request
	token = strtok(buff, s);
	for (int i = 1; i < M; i++) {
		if (token != NULL)
		{
			token = strtok(NULL, s);
			printf("%s\n", token);
		}
	}

	return 0;
}
