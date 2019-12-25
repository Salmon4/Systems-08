#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

union semun{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *__buf;
};

int main(int argc, char* argv[]){
  if (argc > 1){
    if (-c){
      create
    }
    else if (-r){
      read
    }
    else if (-v){
      view
    }
  }
  return 0;
}
