#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#define BUFF_SZ 200
#define ID 10


int main(int argc, char* argv[])
{
	/*
	Function receives and int argc and a string array argv (full of the arguments received). Function does not return anything.
	Function checks if the id has been previously used . If so, function prints an error message and exits.
	If not, function will create a new id.txt file and ask user for information to fill said file, along with previously received
	arguments.
	*/
	srand(time(NULL));
	rand();
	int fd_id, fd_user, rbytes, wbytes, ran = (rand() % 10) + 1;
	char buff[BUFF_SZ];
	char str[ID+1];
	char dest[BUFF_SZ] = "./Loan/Request/";
	char* user = "./Loan/User.txt";
	char* id = argv[1];
	char* sum = argv[2];	
	
	strcat(dest, id);
	strcat(dest, ".txt"); //turn dest into "./Loan/Request/<ID>.txt"
	strcpy(str,id);
	strcat(str, "\n");	//turn str into "<ID>\n"
	
	if ((fd_user = open(user, O_RDONLY)) == -1)
	{
		perror("Error opening file User.txt\n");
		exit(1);
	}

	if ((rbytes = read(fd_user, buff, ID)) == -1)
	{
		perror("read 1\n");
		exit(1);
	}
	
	while (rbytes > 0)
	{
		if (strcmp(str,buff) == 0)
		{
			printf("Sorry! You already have a request\n");
			exit(1);
		}
		else
		{
			if ((rbytes = read(fd_user, buff, ID)) == -1)
			{
				perror("read 1\n");
				exit(1);
			}
		}
	}

	if ((fd_user = open(user, O_WRONLY)) == -1)
	{
		perror("Error opening file User.txt\n");
		exit(1);
	}

	lseek(fd_user, 0, SEEK_END);
	if ((wbytes = write(fd_user, str, strlen(str))) == -1)
	{
		perror("write 1\n");
		exit(1);
	}
	if ((fd_id = open(dest, O_WRONLY | O_CREAT, 0774)) == -1)
	{
		perror("open send\n");
		exit(1);
	}
	printf("User: %s", str);
	printf("Password: ");
	scanf("%s", dest);
	strcat(dest, "\n");
	printf("User Created//\n");

	if ((wbytes = write(fd_id, dest, strlen(dest))) == -1)
	{
		perror("read 1\n");
		exit(1);
	}

	printf("Insert Details:\n");
	printf("Name: ");
	scanf("%s", buff);
	strcpy(dest, "Name: ");
	strcat(dest,buff);
	strcat(dest, "\n");
	if ((wbytes = write(fd_id, dest, strlen(dest))) == -1)
	{
		perror("read 1\n");
		exit(1);
	}
	printf("SurName: ");
	scanf("%s", buff);
	strcpy(dest, "SurName: ");
	strcat(dest,buff);
	strcat(dest, "\n");
	if ((wbytes = write(fd_id, dest, strlen(dest))) == -1)
	{
		perror("read 1\n");
		exit(1);
	}

	printf("Age: ");
	scanf("%s", buff);
	strcpy(dest, "Age: ");
	strcat(dest,buff);
	strcat(dest, "\n");
	if ((wbytes = write(fd_id, dest, strlen(dest))) == -1)
	{
		perror("read 1\n");
		exit(1);
	}
	strcpy(dest,"Sum: ");
	strcat(dest, sum);
	strcat(dest, "\n");
	if ((wbytes = write(fd_id, dest, strlen(dest))) == -1)
	{
		perror("read 1\n");
		exit(1);
	}
	strcpy(dest,"Payments: ");
	strcat(dest, argv[3]);
	strcat(dest, "\n");
	if ((wbytes = write(fd_id, dest, strlen(dest))) == -1)
	{
		perror("read 1\n");
		exit(1);
	}
	sprintf(buff, "%d", ran);
	strcpy(dest,"Rating: ");
	strcat(dest, buff);
	strcat(dest, "/10\n");
	if ((wbytes = write(fd_id, dest, strlen(dest))) == -1)
	{
		perror("read 1\n");
		exit(1);
	}
	strcpy(dest,"Status: Waiting\n");
	if ((wbytes = write(fd_id, dest, strlen(dest))) == -1)
	{
		perror("read 1\n");
		exit(1);
	}
	printf("Request Saved!\n");
	return 0;
}
