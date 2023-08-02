//open existing semaphore created by semaphore.c; create child process. Parent and child try to run
//forever concurrenty; both parent and child try to decrease both semaphore values one at a time.
//once both semaphore values are decreased (when both become zero), child process prints "child is
//"in critical section" and parent prints "parent in critical section"; parent and child try to inc
//semaphore values one at a time; child count a number for each loop. when count becomes 100, child
//sends signal to parent which causes the parent to terminate; after parent terminates, child
//removes the semaphore and terminates itself

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

int buffer[BUFSIZE];
int counter;

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void down(int semid, int index){
    struct sembuf buf = {index, -1 , 0};
    semop(semid, &buf, 1);
}

void up(int semid, int index){
    struct sembuf buf = {index, 1, 0};
    semop(semid, &buf, 1);
}

void* producer(void* arg){
    printf("Starting procedure\n");
    int semid = (int) arg;
    int item, spot;
    while(1){
        while(semctl(semid,MUTEX,GETVAL) == 0)
            sleep(1);
        item = rand()%1000;
        down(semid, EMPTY);
        down(semid, MUTEX);
        spot = semctl(semid, FULL, GETVAL);
        buffer[spot] = item;
        int i=0;
        for(i=0;i<BUFSIZE; i++){
            printf("buffer[%d] = %d\n", i,buffer[i]);
        }
        up(semid, MUTEX);
        up(semid, FULL);
        sleep(1);
    }
}

void* consumer(void* arg){
    printf("Starting consumer\n");
    int semid = (int) arg;
    int item, spot;
    while(1){
        while(semctl(semid,MUTEX,GETVAL) == 0)
            sleep(1);
        down(semid, FULL);
        down(semid, MUTEX);
        spot = semctl(semid, FULL, GETVAL);
        item = buffer[spot];
        printf("Consumer used %d\n",item);
        buffer[spot-1]=0;
        up(semid, MUTEX);
        up(semid, EMPTY);
        sleep(2);
    }
}



int main(int argc, char** argv){
    key_t key;
    union semun arg;
    int semid;
    pthread_t p,c;
    if((key=ftok("semaphore.c", 'A'))<0){
        perror("ftok error");
        exit(1);
    }
    if((semid=semget(key,3,0666|IPC_CREAT))<0){
        perror("semget error");
        exit(2);
    }
    arg.val = 1;
    semctl(semid, MUTEX, SETVAL, arg);
    arg.val = 0;
    semctl(semid, FULL, SETVAL, arg);
    arg.val = BUFSIZE;
    semctl(semid, EMPTY, SETVAL, arg);

    pthread_create(&p, NULL, producer, (void*)semid);
    pthread_create(&c, NULL, consumer, (void*)semid);

    pthread_join(p, NULL);
    pthread_join(c, NULL);
    exit(0);
}
