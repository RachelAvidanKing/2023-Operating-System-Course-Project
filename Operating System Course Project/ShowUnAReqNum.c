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
#include <dirent.h>


int main() {
    DIR *directory;        // Pointer to directory stream
    struct dirent *entry;  // Pointer to directory entry
    int filecounter = 0;    // Counter for files

    // Open the directory
    directory = opendir("./Loan/Result/Unapproved");

    // If the directory couldn't be opened, print an error message and return
    if (directory == NULL) {
        perror("Unable to open directory");
        exit(1);
    }

    //Sum up the number of rejected requests
    while ((entry = readdir(directory)) != NULL) {
    	if (entry->d_type == DT_REG)
            filecounter++;
        }

    // Close the directory
    closedir(directory);

    // Print the total number of files in the directory
    printf("%d\n", filecounter);

    return 0;
}
