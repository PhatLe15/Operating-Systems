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

