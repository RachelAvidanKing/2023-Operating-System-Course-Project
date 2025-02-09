#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


int main() {
	int cunter, file1, rbytes;
	char buffer[10]; //10 characters because in the id has 9 digits plus \0

	file1 = open("./Loan/User.txt", O_RDONLY);
	// If the file couldn't be opened, print an error message and return
	if (file1 == -1) {
		perror("There is an error with the File1\n");
		exit(1);
	}
	//Sum up the amount of applications submitted
	while (rbytes = read(file1, buffer, 10) > 0) {
		cunter++;
	}
	//If reading from the file failed
	if (rbytes == -1) {
		perror("read 1\n");
		exit(1);
	}
	printf("%d\n",cunter);
	//Close files descriptors
	close(file1);
	return 0;
}
