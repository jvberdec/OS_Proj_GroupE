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
    char cwd[256];
    int check;
    int change;

    // check for current directory error
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        perror("getcwd() error");

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

    // check for current directory error
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        perror("getcwd() error");
}
