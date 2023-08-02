//Get two intger values from the shared memory which is created by msgQrcv.c; calculate the sum of 
//the integers and display them on the screen; shmemsum.c will keep running until no more new data
//in shared memory
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<errno.h>
#include<sys/msg.h>

#define NOT_READY -1
#define FILLED 0
#define TAKEN 1
#define GO 2
#define STOP 3

struct ints{
    int num1, num2;
};
struct Memory{
    int status;
    int gostop;
    struct ints data;
};


int main(int argc, char** argv){
    key_t key;
    if((key = ftok(".", 'B')) == -1){
        perror("ftok() error");
        exit(1);
    }
    int shmid;
    if((shmid = shmget(key, sizeof(struct Memory), 0)) == -1){
        perror("shmget error");
        exit(4);
    }


    struct Memory *shm = (struct Memory*)shmat(shmid, NULL, 0);
    while(shm->gostop == GO){
        while(shm->status == FILLED){
            if(shm->gostop == STOP)
                break;
            
            printf("The sum of %d and %d is %d", shm->data.num1, shm->data.num2, (shm->data.num1+shm->data.num2));
            shm->status=TAKEN;
        }
    }
    shmdt((void*)shm);
    exit(0);
}
