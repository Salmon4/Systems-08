#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SEM_KEY 24602
#define SH_KEY 24601

union semun{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *__buf;
};

int main(int argc, char* argv[]){
  if (argc > 1){
    if (strcmp(argv[1], "-c") == 0){
      create()
    }
    else if (strcmp(argv[1], "-r") == 0){
      read()
    }
    else if (strcmp(argv[1], "-v") == 0){
      view()
    }
  }
  return 0;
}

void create(){
  int send = semget(SEM_KEY,1,IPC_CREAT | 0644);

  union semun se;
  semctl(send, 0, SETVAL, se);
  
  shmd = shmget(SH_KET,1,IPC_CREAT | 0644);

  fd = open("file.txt", O_CREAT | O_RDWR, 0644);
}

void read(){

}

void view(){

}
