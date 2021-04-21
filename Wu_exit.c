#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void my_exit(char commands[1024][1024],int count)
{	//collects the last 4 commands
	int start = count;
	if(start < 4)
	{
		start = 0;
	}
	else
	{
		start = -4;
	}

	for (int i = start; i < count; i++)
	{
		printf("%d : %s\n", i + 1, commands[i]);
	}
	//creates a fork
	int pid = fork();

	if(pid < 0)
	{
		printf("Fork failed");
	}
	//child
	if(pid == 0)
	{
		char *args[3];
		args[0] = "ls";
		args[1] = "-l";
		args[2] = NULL;
		//executes ls and -l
		execvp(args[0],args);
		//prints error message if an error ocurred
		printf("Error");
	}
	//parent
	else if (pid >0)
	{
		wait(NULL);
		printf("\n -> Are you sure you want to exit? If yes, press ENTER.");
		getchar();
		 FILE *f = fopen("file.txt","w");
		 	for (int i =0; i < count; i++)
		 	{
		 		fprintf(f,"%s\n",commands[i]);
		 	}
		 	fclose(f);
        printf("SHELL EXITED \n");
        printf("By Group E: \n");
        printf("Group Leader/Shell: Julia Berdecia \n");
        printf("Tree: Muhammed Rahman \n");
        printf("List: Steven Bueno \n");
        printf("Path: David Diop \n");
        printf("Exit: Hui Wu \n");
	}
}
