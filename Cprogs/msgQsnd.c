//create a msg queue by using ket value key = ftok(".", 'B'); Keep receiving two integer
//values from the command line until end of data (ctrl+D); do not need to validate data; send each
//message to the msg queue
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/msg.h>

//declare a msgbuf stucture called msgbuf
typedef struct MSGBUF{
	long type;
	int one, two;
}MsgBuf;

int main(int argc, char *argv[]){
	key_t key;
	if((key = ftok(".", 'B')) == -1){
		perror("ftok() error");
		exit(1);
	}

	int msgqid;
	if((msgqid = msgget(key, 0644 | IPC_CREAT)) == -1){
		perror("msgget() error");
		exit(2);
	}

	MsgBuf buf;
	buf.type = 1;
	char* input = (char*) calloc(256, sizeof(int));

	printf("Input two ints\n");

	while(fgets(input, 256, stdin), !feof(stdin)){
		if(sscanf(input, "%d%d", &buf.one, &buf.two) != 2){
			printf("bbot input not ints");
			continue;
		}
		if(msgsnd(msgqid, (MsgBuf*) &buf, sizeof(buf), 0) == -1){
			perror("msgsnd() error");
			exit(3);
		}
		printf("Enter two integers\n");
	}
	
	if(msgctl(msgqid, IPC_RMID, NULL) == -1){
		perror("msgctl() error");
		exit(4);
	}
	exit(0);
}
