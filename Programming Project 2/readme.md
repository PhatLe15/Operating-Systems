# Introduction
The purpose of this project is to runs an infinite loop that sleep for intervals of 2 seconds. Furthermore, we will make use of different signals call.

## Requirements:
- Infinite loop for intervals of `2 seconds`.
- Send `SIGINT` signal to toggle print out the number of current interation:
  - Initially print out nothing. If `SIGINT` call, print out interation number. 
  - Keep printing out the interation. If `SIGINT` call, print out nothing. 
- Send `SIGURS1` to terminate the program with the `value 0` as exit status.

```c
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

bool SIGINTflag = false;
bool SIGUSR1flag = false;

void sighandler(int sig){
  if(sig == SIGINT){
    SIGINTflag = !SIGINTflag; //toggle debug flag
  }
  else if(sig == SIGUSR1){ //terminate process if use this signal
    SIGUSR1flag = true;
  }
  
}

int main(){
  //set signal catcher user interrupt handler
  signal(SIGINT,sighandler);
  signal(SIGUSR1,sighandler);

  int i = 0;
  while(1){
    i = i + 1; //iteration counter
    sleep(2);
    if(SIGINTflag) printf("Current interation: %u\n", i);// print iteration if debug flag is ON
    if(SIGUSR1flag) exit(0);// exit process
  }
  return 0;
}
```
