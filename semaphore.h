#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <unistd.h>

#define SEMKEY 24601
#define SHKEY 24602

union semun {
  int val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short *array;  /* Array for GETALL, SETALL */
  struct seminfo *__buf;  /* Buffer for IPC_INFO
                              (Linux-specific) */
};

int writeSem();
int createSem();
int removeSem();
int viewSem();
