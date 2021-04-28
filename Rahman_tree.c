#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

// this method checks for error while opening a file
void checkFileOpenError(int fd)
{
    if (fd == -1)
    {
        // print which type of error occurred
        printf("Error Number: %s\n", strerror(errno));
        perror("Opening of the file is failed\n");
    }
}

// this method checks for error while creating a directory
void checkMakeDirError(int result)
{
    if (result == -1)
    {
        // print which type of error occurred
        printf("Error Number: %s\n", strerror(errno));
        perror("Unable to create directory.\n");
    }
}

// tree() creates a directory dir0, changes the working directory to dir0
// and inside dir0 creates three files: t1.txt, t2.txt, t3.txt and a directory dir1
void tree()
{
    // the maximum permitted size of file paths
    int path_max = 256;
    // contains the path
    char cwd[path_max];
    int dir_result1, dir_result2;
    int change_dir;

    // check for current directory error
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
    }

    // create a directory in the current location
    dir_result1 = mkdir("./dir0", 0777);
    checkMakeDirError(dir_result1);

    // change the current working directory(cwd) to ./dir0
    // on successful creation of ./dir0
    if (dir_result1 == 0)
    {
        change_dir = chdir("./dir0");
    }

    // create other files and diretories inside the changed directory
    if (dir_result1 == 0 && change_dir == 0)
    {
        int fd1, fd2, fd3;
        // create the file if it does not exist in the directory and open it
        fd1 = open("./t1.txt", O_RDWR | O_CREAT, 0777);
        checkFileOpenError(fd1);

        fd2 = open("./t2.txt", O_RDWR | O_CREAT, 0777);
        checkFileOpenError(fd2);

        fd3 = open("./t3.txt", O_RDWR | O_CREAT, 0777);
        checkFileOpenError(fd3);

        // create the directory dir1
        dir_result2 = mkdir("./dir1", 0777);
        checkMakeDirError(dir_result2);

        // close the files
        close(fd1);
        close(fd2);
        close(fd3);
    }

    // check for current directory error
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
    }
}

