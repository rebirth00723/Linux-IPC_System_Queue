#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include </usr/include/asm/errno.h>
typedef struct  {
  char caName[20];
  char caIdNo[10];
  char cGender;
  int iAge;
  char caPhone[12];
} stDefStudent;

typedef struct{
	long lMsgType;
	stDefStudent stStudent;
} stDefMsg;


int main(int iArgc, char **caArgv){
	key_t key;
	int iMsgId;
	stDefStudent stStudent;	

	if(iArgc < 2){
		printf("RecvQ <key>\n");
		return 0;
	}else{
		key = atoi(caArgv[1]);
	}

	iMsgId = msgget(key, IPC_CREAT|0666);
	if(iMsgId < 0){
		perror("msgget error\n");
		exit(-1);
	}	

	printf("Recv...\n");
	
	stDefMsg stMsg;
	int iRc;

	iRc = msgrcv(iMsgId, &stMsg, sizeof(stDefStudent), 0, IPC_NOWAIT);
	if(iRc < 0){
		perror("msgrcv error.\n");
		exit(-1);
	}

	stStudent = stMsg.stStudent;
	printf("Data:{%s,%s,%c,%d,%s}\n", 
		stStudent.caName, stStudent.caIdNo, stStudent.cGender, stStudent.iAge, stStudent.caPhone);
	return 0;
	
}
