#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUFF_SZ 200
#define M 8

int main(int argc, char* argv[])
{
	/*
	Function receives and int argc and a string array argv (full of the arguments received). Function does not return anything.
	Function checks if the requested txt file exists in the correct directory. If so, it then checks if the username and password
	are correct. If so, function prompts user if signeture and password (once more) and then changes the status of the request to
	approved and changed the txt file into a read only file.
	*/
	int fd_id, rbytes, wbytes, len1, len2, length;
	char* id = argv[1];
	char* str = argv[1];
	char* password = argv[2];
	char svdPwd[BUFF_SZ];
	char dest[BUFF_SZ] = "./Loan/Result/Approved/";
	char buff[BUFF_SZ];
	const char s[2] = "\n";
	const char t[2] = " ";
	char* token;
	
	strcat(dest, str);
	strcat(dest, ".txt");
	
	if ((fd_id = open(dest, O_RDONLY)) == -1)
	{
		printf("No approved request!\n");
		exit(1);
	}
	
	
	if ((rbytes = read(fd_id, buff, BUFF_SZ)) == -1)
	{
		perror("read 1\n");
		exit(1);
	}
	length = strlen(buff);
	token = strtok(buff, s);
	strcpy(svdPwd, token);
	if (strcmp(password, token) != 0) {
		printf("Wrong Password\n");
		exit(1);
	}
	
	for (int i = 1; i < M; i++) {
		if (token != NULL)
		{
			token = strtok(NULL, s);
			if (i != M-1)
				printf("%s\n", token);
		}
	}

	len1 = strlen(token);
	token = strtok(token, t);
	len2 = strlen(token);
	length = length - (len1 - len2);
	printf("Please type Approve: ");
	scanf("%s", buff);
	if (&buff[strlen(buff)] == "\n")
		buff[strlen(buff)-1] = '\0';
	if (strcmp("Approve", buff) != 0)
	{
		printf("You did not approve!\n");
		exit(1);
	}
	printf("Password: ");
	scanf("%s", buff);
	while (strcmp(svdPwd, buff) != 0) {
		printf("Wrong Password\n");
		printf("Password: ");
		scanf("%s", buff);
	}
	printf("Good Luck!!\n");
	if ((fd_id = open(dest, O_WRONLY)) == -1)
	{
		perror("open fileID\n");
		exit(1);
	}
	
	lseek(fd_id, length, SEEK_SET);
	if ((wbytes = write(fd_id, "Approved", strlen("Approved"))) == -1)
	{
		perror("write 1\n");
		exit(1);
	}
	
	if (chmod(dest, S_IRGRP | S_IROTH | S_IRUSR) != 0)
	{
		perror("open send\n");
		exit(1);
	}
	
	return 0;
}
