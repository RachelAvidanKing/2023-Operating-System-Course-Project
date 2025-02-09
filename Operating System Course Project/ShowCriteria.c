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
#define M 3

int main() {
    int fd_id, rbytes;
    char dest[BUFF_SZ] = "./Loan/Result/Criteria.txt";
    char buff[M];

    // If the file couldn't be opened, print an error message and return
    if ((fd_id = open(dest, O_RDONLY)) == -1)
    {
        perror("Request Not Found!\n");
        exit(1);
    }
    //If the reading from the file fails, print an error message and return
    if ((rbytes = read(fd_id, buff, M)) == -1)
    {
        perror("read 1\n");
        exit(1);
    }
    //Print the criteria for approving the loan
    printf("Min Rating %s\n", buff);

    return 0;
}
