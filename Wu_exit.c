#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void my_exit(char commands[1024][50],int count)
{	//collects the last 4 commands
	printf("Printing the last 4 commands used \n");
	int start = count;
	// if start is less then 4, initializes it to 0
	if(start < 4)
	{
		start = 0;
	}
	else
	{
		//gets the last 4 commands
		start -= 4;
	}

	for (int i = start; i < count; i++)
	{
		// prints the last commands in a list, since start will get 4 commands, only a list of 4 elements will be printed
		printf("%d : %s\n", i + 1, commands[i]);
	}
	//creates a fork
	int pid = fork();

	//error checking
	if(pid < 0)
	{	
		printf("Fork failed");
	}
	//child
	if(pid == 0)
	{
		//defines args
		char *args[3];
		//will execute ls
		args[0] = "ls";
		//will execute -l
		args[1] = "-l";
		//end of the array
		args[2] = NULL;
		//executes ls and -l
		execvp(args[0],args);
		//prints error message if an error ocurred
		printf("Error");
	}
	//parent
	else if (pid >0)
	{
		//waits for the child to finish
		wait(NULL);
		printf("\n -> Are you sure you want to exit? If yes, press ENTER.");
		// requires you to press enter/return to continue
		getchar();
		
		
	//closing statements	
        printf("SHELL EXITED \n");
        printf("By Group E: \n");
        printf("Group Leader/Shell: Julia Berdecia \n");
        printf("Tree: Muhammed Rahman \n");
        printf("List: Steven Bueno \n");
        printf("Path: David Diop \n");
        printf("Exit: Hui Wu \n");
	}
}
