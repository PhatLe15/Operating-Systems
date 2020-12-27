#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void sighandler(int sig){
  printf("All zombies are dead\n");
}

int main(int argc, char *argv[]){
  int i;      //n zombies index
  pid_t pid;  //zombies id
  int opt;    //variable to handle option argument
  int n;      //n zombies
  
  while((opt=getopt(argc,argv,":n:"))!= -1){  // to handle -n option
    switch(opt){
    case 'n':
      n = atoi(optarg);
      printf("Chosen number of zombies: %s\n",optarg);
      break;
    case ':':
      printf("option need a value\n");
      break;
    case '?':
      printf("unknown option: %c\n",optopt);
      break;
    }
  }
 
  if(n<1){         // if no zombie
    printf("ERROR No zombie to create, please enter again\n");
  }

  for(i=0; i<n; i=i+1){
    pid = fork();  // create n zombies

    if(pid == 0){//child process
      printf("Zombie no.%d ID is: %d\n",i,getpid());//just to check if they are differnt child
      printf("Its parent id is %d\n\n",getppid());//check if they are from same parent
      exit(0);
      printf("zombie process not exited\n");// this will print if it wont exit
    }    
  }
  
  if(pid != 0){ //parent process
    signal(SIGCONT, sighandler);  //catch the kill signal
    pause();//wait for the kill signal before ending the process
  }
   return 0;
}
