#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>


void tree()
{
    // look at stat for checking if the directory exists
    struct stat st = {0};
    char cwd[256];
    int check;
    int change;

    // printing current working directory
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        perror("getcwd() error");
    else
        printf("current working directory is: %s\n", cwd);

    // check if the directory "./dir0" exists in the working directory
    if (stat("./dir0", &st) == -1)
    {
        // create a directory in the current location
        check = mkdir("./dir0", 0777);

        // changing the current working directory(cwd) to ./dir0
        change = chdir("./dir0");

        // create other files and diretories inside the changed directory
        if (!check && change == 0)
        {
            // create the file if it does not exist in the directory and open it in read only mode.
            open("./t1.txt", O_RDWR | O_CREAT, 0777);
            open("./t2.txt", O_RDWR | O_CREAT, 0777);
            open("./t3.txt", O_RDWR | O_CREAT, 0777);
            mkdir("./dir1", 0777);
        }
    }

    // printing current working directory
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        perror("getcwd() error");
    else
        printf("current working directory is: %s\n", cwd);
}
