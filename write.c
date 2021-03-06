#include "semaphore.h"

int semd, shmd, fd;
struct sembuf sb;

int writeSem(){
  printf("trying to get in\n");
  semd = semget(SEMKEY, 1, 0);
  if(semd < 0){
    printf("%s\n", strerror(errno));
    return -1;
  }
  semop(semd, &sb, 1);
  shmd = shmget(SHKEY, sizeof(char *), 0);
  if(shmd < 0){
    printf("%s\n", strerror(errno));
    return -1;
  }
  fd = open("file.txt", O_WRONLY | O_APPEND);
  char *last = shmat(shmd, 0, 0);
  printf("Last addition: %s\n", last);
  char next[1000];
  printf("Your addition: ");
  fgets(next, 1000, stdin);
  printf("%s\n",next);
  write(fd, next, strlen(next));
  close(fd);
  strcpy(last,next);
  shmdt(last);
  sb.sem_op = 1;
  semop(semd, &sb, 1);
  return 0;
}

int main(){
  sb.sem_num = 0;
  sb.sem_op = -1;
  writeSem();
  return 0;
}
