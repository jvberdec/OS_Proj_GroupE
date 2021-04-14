#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>      
#include <sys/wait.h> 

int main(){
  system("clear");
  FILE *new_fp;
  new_fp = fopen("t1.txt", "w+");
  int link[2];
  pid_t pid;
  char foo[4096];

  if (pipe(link)==-1)
    printf("error in pipe \n");

  if ((pid = fork()) == -1)
    printf("error in fork\n");

  if(pid == 0) {

    dup2 (link[1], 1);
    close(link[0]);
    close(link[1]);
    char *list_comm = "ls";
    char *new_args[] = {list_comm,"-l", NULL};
    execvp(list_comm,new_args);
    printf("exec\n");

  } else {

    close(link[1]);
    int nbytes = read(link[0], foo, sizeof(foo));
    fprintf(new_fp,"%s",foo);
    printf("%.*s\n", nbytes, foo);
    wait(NULL);

  }
  rename("t1.txt", "tree.txt");
  fclose(new_fp);
  return 0;
}
