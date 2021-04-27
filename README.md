# [CSC 332] Operating Systems Final Project
Spring 2021

We created our own command shell program using C.

Group Leader (Shell) - Julia Berdecía
Tree - Mohammed Rahman
List - Steven Bueno
Path - David Diop
Exit - Hui Wu

  <img src = 'https://github.com/jvberdec/OS_Proj_GroupE/blob/dev-1/shell_demo.gif/>

Project Description

1. shell*: the environment that will execute the rest of nee command. the shell won’t terminate
unless the exit command gets executed. The shell displays a different command prompt (i.e.
something other than $ and >).
2. tree*: this new command will create a directory and call it Dir0. Then it will change the working
directory to Dir0, and create three empty text files namely; t1.txt, t2.txt,and t3.txt, and one empty
directory , called Dir1,inside it.
3. list*: this new command will clear the terminal screen and print a detailed list of all content of
the current directory (similar to ls -l) to the terminal and t1.txt. Finally, it will change the name of
text file to tree.txt.
4. path*: this new command will print the path of the current directory to the terminal and t2.txt,
and change the name of text file to path-info.txt. Concatenate the content of tree.txt and path.txt
into t3.txt and change the last to log.txt. Finally, delete tree and path text files
5. exit*: this new command will print a list the last 4 commands to the terminal, a detailed list of all
content of the current directory (similar to ls -l). Finally, it will wait for the user to hit the “return”
key to terminate the shell and return the control to the original shell program on your machine
