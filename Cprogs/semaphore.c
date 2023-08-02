//Create a semaphore with two members by using ley value key=ftok(".", 'K'). Initiate both member of
//semaphore with value 1

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/msg.h>
#include<pthread.h>

#define BUFSIZE 10
#define MUTEX 0
#define EMPTY 2
#define FULL 1

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(int argc, char** argv){
    key_t key;
    union semun arg;
    int semid;
    pthread_t p,c;
    if((key=ftok(".", 'K'))<0){
        perror("ftok error");
        exit(1);
    }
    if((semid=semget(key,2,0666|IPC_CREAT))<0){
        perror("semget error");
        exit(2);
    }
    arg.val = 1;
    semctl(semid, 1, SETVAL, arg);
    semctl(semid, 0, SETVAL, arg);
    exit(0);
}
