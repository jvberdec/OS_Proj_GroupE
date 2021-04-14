#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

// declare an array that will hold the commands
char *cmd_tokens[512];

// show info to the users
void showUserGuideline()
{
    printf("This is a simple terminal interpreter.\n");
    printf("1. Please, type your command:\n");
    printf("2. Press enter to run the command: \n");
    printf("3. Type 'exit' to exit the program: \n");
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

        // if the user input is 'quit' then exit the program
        if (strcmp(cmd_tokens[0], "exit") == 0)
        {
            printf("Bye Bye!!\n");
            return 0;
        }

        // execute the command
        executeCommand();
    }

    // free the buffer
    free(line);

    return 0;
}
