# Introduction
The purpose of this project is to create a pipe and forks a child process.

# Requirements:
- On the parent side of the pipe, the parent must sends the message in this format `"I am your daddy! and my name is <parent ID>\n"`.
- After receiving the message, the child prints it to its stdout verbatim.
- The parent then blocks the reading on the pipe.
- Next, the child writes back to its parent through the pipe stating '"Daddy, my name is <child ID>"`.
- The parent then writes the receives message to its stdout.
  - Additionally, make sure parent wait on child and not to create orphans or zombies processes.

```c
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define BUFFER_SIZE 40

int main(){
  int exit_status = 0;
  int fd1[2], fd2[2];
  pid_t pid;
  char buffer[BUFFER_SIZE];

  //create the pipe
  if(pipe(fd1)==-1||pipe(fd2)==-1){
    fprintf(stderr, "pipe failed");
    return 1;
  }

  pid = fork();

  if(pid <0){ //error occur
    fprintf(stderr,"fork failed");
    return 1;
  }

  if(pid == 0){//child
    close(fd1[1]);//parent-> child
    
    read(fd1[0],buffer,sizeof(buffer));//read parent message
    printf("%s", buffer);// print out parent's message

    close(fd2[0]);//child-> parent
    dprintf(fd2[1],"Daddy, my name is %d\n", getpid());

  }
  else{//parent
    close(fd1[0]);//parent->child
    dprintf(fd1[1],"I am your daddy! and my name is %d\n", getpid());
   
    close(fd2[1]);//child-> parent
    read(fd2[0],buffer,sizeof(buffer));//read child message
    fprintf(stdout,"%s", buffer);// print out child's message
     
    wait(&exit_status);
   
  }
  return 0;
}  
```
