#include "semaphore.h"

int semd, shmd, fd;
union semun se;
struct sembuf sb;

int createSem(){
  semd = semget(SEMKEY, 1, IPC_CREAT | 0644);
  if (semd < 0){
    printf("%s\n", strerror(errno));
    return -1;
  }
  printf("semaphore created\n");

  semctl(semd, 0, SETVAL, se);
  shmd = shmget(SHKEY, sizeof(char *),IPC_CREAT | 0644);
  if (shmd < 0){
    printf("%s\n", strerror(errno));
    return -1;
  }
  printf("shared memory created\n");

  fd = open("file.txt", O_CREAT | O_RDWR, 0644);
  if (fd < 0){
    printf("%s\n", strerror(errno));
    return -1;
  }
  printf("file created\n");
  close(fd);
  return 0;
}

int removeSem(){
  semd = semget(SEMKEY, 1, 0);
  if (semd < 0){
    printf("%s\n", strerror(errno));
    return 1;
  }
  printf("Trying to get in\n");
  semop(semd,&sb, 1);
  shmd = shmget(SHKEY, 1, 0);
  if (shmd < 0){
    printf("%s\n", strerror(errno));
    return -1;
  }
  fd = open("file.txt", O_RDONLY);
  if (fd < 0){
    printf("%s\n", strerror(errno));
    return -1;
  }
  char buff[1000];
  buff[0] = '\0';
  read(fd, buff, 1000);
  if (strlen(buff) != 0){
    *(strrchr(buff, '\n') + 1) = '\0';
  }
  printf("Content: \n");
  printf("%s\n", buff);
  close(fd);
  shmctl(shmd, IPC_RMID, 0);
  printf("Shared memory removed\n");
  remove("file.txt");
  printf("File removed\n");
  semctl(semd, IPC_RMID, 0);
  printf("Semaphore removed\n");
  //printf("dummy");
  return 0;
}

int viewSem(){
  fd = open("file.txt", O_RDONLY);
  if (fd < 0){
    printf("%s\n", strerror(errno));
    return -1;
  }
  char buff[1000];
  buff[0] = '\0';
  read(fd, buff, 1000);
  if (strlen(buff) != 0){
    *(strrchr(buff, '\n') + 1) = '\0';
  }
  printf("The story so far:\n");
  printf("%s\n", buff);
  close(fd);
  //printf("dummy");
  return 0;
}

int main(int argc, char* argv[]){
  sb.sem_num = 0;
  sb.sem_op = -1;
  se.val = 1;
  if (argc > 1){
    if (strcmp(argv[1], "-c") == 0){
      createSem();
    }
    else if (strcmp(argv[1], "-r") == 0){
      removeSem();
    }
    else if (strcmp(argv[1], "-v") == 0){
      viewSem();
    }
  }
  return 0;
}
