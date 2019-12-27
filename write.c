#include "semaphore.h"

int semd, shmd, fd;
struct sembuf sb;

int writeSem(){
  printf("trying to get in\n");
  semd = semget(KEY, 1, 0);
  if(semd < 0){
    printf("HERE ERROR: %s\n", strerror(errno));
    return 1;
  }
  semop(semd, &sb, 1);
  printf("trying to get in\n");
  shmd = shmget(KEY, sizeof(char *), 0);
  if(shmd < 0){
    printf("ERROR: %s\n", strerror(errno));
    return 1;
  }
  printf("trying to get in\n");
  fd = open("file.txt", O_WRONLY | O_APPEND);
  printf("trying to get in\n");

  char *last = shmat(shmd, 0, 0);

  printf("trying to get in\n");
  printf("Last addition: %s\n", last);
  char next[SIZE];
  printf("Your addition: ");
  fgets(next, SIZE, stdin);
  printf("\n");
  write(fd, next, strlen(next));
  close(fd);
  strcpy(last,next);
  shmdt(last);
  sb.sem_op = 1;
  semop(semd, &sbmd, 1);
  return 0;
}

int main(){
  sb.sem_num = 0;
  sb.sem_op = -1;
  writeSem();
  return 0;
}
