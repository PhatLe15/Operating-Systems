#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int done = 1;
bool exit_flag = false;

void sighandler(int sig){
  exit_flag = true;
}

void* thread1_handler(void *arg){
  while(1){
    pthread_mutex_lock(&lock); //aquire a lock
    if(done ==1 ){
      printf("thread 1: ping thread 2\n");
      done = 2;
      pthread_cond_signal(&cond1); //signal on the thread2
      pthread_cond_wait(&cond1, &lock);//wait for thread2 signal
      printf("thread 1: pong! thread 2 ping received\n");
    }
    pthread_mutex_unlock(&lock);
    if(exit_flag){
      exit(0);
    }
  }
  return NULL;
}

void* thread2_handler(void *arg){
  while(1){
    pthread_mutex_lock(&lock); //aquire a lock
    if(done ==2 ){
      printf("thread 2: pong! thread 1 ping received\n");
      printf("thread 2: ping thread 1\n");
      done = 1;
      pthread_cond_signal(&cond1);
    }
    pthread_mutex_unlock(&lock);
    if(exit_flag){
      exit(0);
    }
  }
  return NULL;
}


int main(){
  signal(SIGINT, sighandler);
  pthread_t thread1, thread2;

  //  while(1){
  pthread_create(&thread1, NULL, thread1_handler, NULL);
  pthread_create(&thread2, NULL, thread2_handler, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);


  //}
  return 0;
}
