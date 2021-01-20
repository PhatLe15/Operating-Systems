# Introduction
The purpose of this project is to get familiar with the creation and uses of child and parent processes.

The `child` process is required to:
[] Print out its ID and new line.
[] Calls **pause()** system call.
[] Once return from pause system call, exit with code 5.

The `parent` process is required to:
[] Wait for the child process.
[] Print out ID of child process.
[] Print out exit status with the format: `"childpid=%d,exutstatus=%d\n"`

Additionally, create a signal handler function and observe the changes. 

```c
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

void sighandler(int s){
}
int main()
{
        signal(SIGINT,sighandler);// nothing happen whether or not I added this line
        pid_t pid;
	int status;

	pid = fork(); //fork to create a child process

	if(pid == 0){ //child process
		printf("The child pid is: %d\n",getpid()); //print out its id
		pause(); 
		exit(5);  //exit with code 5
	}
	else{//parent process
	        pid = wait(&status);// read child id when child exit
		printf("childid=%d,exitstatus:%d\n", pid, WEXITSTATUS(status));
	}
	return 0;

}
```
