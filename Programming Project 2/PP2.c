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
