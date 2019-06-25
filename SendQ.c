#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
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

	if(iArgc < 7){
		printf("SendQ <key> <name> <IdNo> <M/F> <Age> <Phone>\n");
		return 0;
	}else{
		key = atoi(caArgv[1]);
	}

	iMsgId = msgget(key, IPC_CREAT|0666);
	if(iMsgId < 0){
		perror("msgget error\n");
		exit(-1);
	}	

	printf("Sending...\n");

	memcpy(stStudent.caName , caArgv[2], strlen(caArgv[2]));
	memcpy(stStudent.caIdNo, caArgv[3], strlen(caArgv[3]));
	stStudent.cGender = caArgv[4][0];
	stStudent.iAge = atoi(caArgv[5]);
	memcpy(stStudent.caPhone, caArgv[6], strlen(caArgv[6]));

	stDefMsg stMsg;
	stMsg.lMsgType = 666;
	memcpy(&stMsg.stStudent, &stStudent, sizeof(stDefStudent));
 	
	int iRc;
	iRc = msgsnd(iMsgId, &stMsg, sizeof(stDefStudent), 0);
	if(iRc < 0){
		perror("msgsnd error.\n");
		exit(-1);
	}
	
	printf("Sended.\t{%s,%s,%c,%d,%s}\n", caArgv[2], caArgv[3], caArgv[4][0], atoi(caArgv[5]), caArgv[6]);
	printf("The structure size is : %d\n", sizeof(stDefStudent));
	return 0;
	
}
