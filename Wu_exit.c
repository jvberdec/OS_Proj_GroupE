#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void exit(char commands[1024][1024],int count)
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
		printf("\n Hit Return to exit Shell");
		getchar();
		// FILE *f = fopen("file.txt","w");
		// 	for (int i =0; i < count; i++)
		// 	{
		// 		fprintf(f,"%s\n",commands[i]);
		// 	}
		// 	fclose(f);
		printf("\n Shell have exited \n");
	}
}
