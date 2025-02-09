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


int main(int argc, char* argv[])
{
	//Checks if the amount of parameters received is correct
	if (argc != 2){
		printf("Wrong Paramaters!\n");
		exit(1);
	}
	srand(time(NULL));
	rand();
	int wbytes, ran, file, number;
	char ran_string[BUFF_SZ];
	char dest[BUFF_SZ] = "./Loan/Result/Criteria.txt";
	char* num = argv[1];
	
	number = strtol(num, (char **)NULL, 10); //Turn the string into a number
	ran = (rand() % 10) + 1;   //Random number draw up to 10
	//Check if the number that came out is between the number received and the number 10, if not grilled again
	while ((ran < number) || (ran > 11)) {
		ran = (rand() % 10) + 1;
	}
	sprintf(ran_string, "%2.d", ran); //Turn a number into a string and store it in ran_string

	// If the file couldn't be opened for reading and writing, print an error message and return
	if ((file = open(dest, O_RDWR)) == -1)
	{
		perror("Error opening file Criteria.txt\n");
		exit(1);
	}
	//If the writing to a file failed, print an error message and return
	if ((wbytes = write(file, ran_string, strlen(ran_string))) == -1)
	{
		perror("write 1\n");
		exit(1);
	}

	return 0;
}
