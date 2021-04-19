#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "Rahman_tree.h"
#include "Bueno_list.h"
#include "Diop_path.h"
#include "Wu_exit.h"

// declare an array that will hold the commands
char *cmd_tokens[512];

// show info to the users
void showUserGuideline()
{
    printf("CSC 332 Operating Systems Final Project\n");
    printf("Run commands: tree, list, path, or exit\n");
    printf("Don't forget to press enter!\n");

}

// print out "(my_terminal)#"
void showUserPrompt()
{
    printf("(my_terminal)# ");
}

// divide input line into tokens
void parseCommand(char *input)
{
    int i = 0;
    char *token;

    // returns the first token
    token = strtok(input, "\n ");

    // keep adding tokens in the array while one of the
    // delimeters present in input
    while (token != NULL)
    {
        cmd_tokens[i] = token;       // add token to the array
        token = strtok(NULL, "\n "); // get the next token
        i++;
    }

    // end of the array
    cmd_tokens[i] = NULL;
}

// Execute a command
void executeCommand()
{
    int child_pid, status;
    // Create a new process
    child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0)
    { // child process created successfully
        // execute command
        status = execvp(cmd_tokens[0], cmd_tokens);
        if (status == -1)
        {
            printf("Command Execution Failed!\n");
            perror("Sorry, not a correct command!");
            exit(errno);
        }
    }
    else
    { // parent process
        // wait for child process
        waitpid(child_pid, &status, 0);
    }
}


int main(int argc, char *argv[])
{
    char *line = NULL;
    size_t len = 0;
    ssize_t lineSize = 0;

    showUserGuideline();

    // ask user for a command to type
    // execute the command when user presses Enter
    // Exit the program when the user types 'quit'
    while (1)
    {
        showUserPrompt();

        // read the user input from the console
        lineSize = getline(&line, &len, stdin);
        if (lineSize == -1)
        {
            perror("getline() error");
        }

        // check if the user input is empty
        if (strcmp(line, "\n") == 0)
        {
            perror("Please type in a command ");
            continue; // stay in the parent process/ while loop
        }

        // parse the input
        parseCommand(line);

        if (strcmp(cmd_tokens[0], "tree") == 0)
        {
            tree();
            continue; // stay in the parent process/ while loop
        }
        
        if (strcmp(cmd_tokens[0], "list") == 0)
        {
            printf("list!!!");
            list();
            continue; // stay in the parent process/ while loop
        }
        
        if (strcmp(cmd_tokens[0], "path") == 0)
        {
            printf("path!!!");
            continue; // stay in the parent process/ while loop
        }

        // if the user input is 'quit' then exit the program
        if (strcmp(cmd_tokens[0], "exit") == 0)
        {
            printf("Bye Bye!!\n");
//            exit(<#char (*commands)[1024]#>, <#int count#>);
            return 0;
        }

        // execute the command
        executeCommand();
    }

    // free the buffer
//    free(line);

    return 0;
}
