#include "semaphore.h"

int semd, shmd, fd;
union semun se;
struct sembuf sb;

int createSem(){
  semd = semget(KEY, 1, IPC_CREAT | 0644);
  if (semd < 0){
    printf("%s\n", strerror(errno));
    return 1;
  }
  printf("semaphore created\n");

  semctl(semd, 0, SETVAL, se);
  shmd = shmget(KEY, sizeof(char *),IPC_CREAT | 0644);
  if (shmd < 0){
    printf("%s\n", strerror(errno));
    return 1;
  }
  printf("shared memory created\n");

  fd = open("file.txt", O_CREAT | O_RDWR, 0644);
  if (fd < 0){
    printf("%s\n", strerror(errno));
    return 1;
  }
  printf("file created\n");
  close(fd);
  return 0;
}

void removeSem(){
  semd = semget(KEY, 1, 0);

  semop(semd,&sb, 1);

  shmd = shmget(KEY, 1, 0);
  fd = open("file.txt", O_RDONLY);

  char buff[SIZE];
  buff[0] = '\0';
  read(fd, buff, SIZE);
  if (strlen(buff) != 0){
    *(strrchr(buff, '\n') + 1) = '\0';
  }
  close(fd);
  shmctl(shmd, IPC_RMID, 0);

  semctl(semd, IPC_RMID, 0);

  remove("file.txt");
  printf("dummy");
}

void viewSem(){
  fd = open("file.txt", O_RDONLY);
  char buff[SIZE];
  buff[0] = '\0';
  read(fd, buff, SIZE);
  close(fd);
  printf("dummy");
}

int main(int argc, char* argv[]){
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
