/**
 *	@file main.h
 *  @brief Test
 *  @date 05/18/2012
 *  @author maxime.maitre@parrot.com
**/

#include <stdio.h> 
#include <stdlib.h> 
#include <libSAL/print.h>
#include <libSAL/thread.h>

#include <libNetwork/common.h>
#include <libNetwork/inOutBuffer.h>
#include <libNetwork/sender.h>
#include <libNetwork/receiver.h>
#include <libNetwork/network.h>

#include <unistd.h>

#include "Includes/networkDef.h"

#include <signal.h>

#include <termios.h>
 
 
  
#define MILLISECOND 1000

typedef struct printThread // pass uint32_t
{
	network_inOutBuffer_t* pOutBuffChar;
	network_inOutBuffer_t* pOutBuffIntAck;
	int alive;
	
}printThread;

void* printBuff(void* data);
 
 
 
struct termios initial_settings, new_settings;
 
void setupNonBlockingTerm ()
{
  new_settings = initial_settings;
  new_settings.c_lflag &= ~ICANON;
  new_settings.c_lflag &= ~ECHO;
 
  tcsetattr(0, TCSANOW, &new_settings);
}

void fixTerminal (int sig)
{
	tcsetattr(0, TCSANOW, &initial_settings);
	
	exit (0);
}

int main(int argc, char *argv[])
{
	tcgetattr(0,&initial_settings);	
	signal (SIGINT, fixTerminal);
		
	network_t* pNetwork1= NULL;
	
	char netType = 0;
	
	char cmdType = 0;
	char chData = 0;
	
	int intData = 0;
	
	char IpAddress[16];
	int scanfReturn = 0;
	int bindError = -1;
	int connectError = -1;
	
	printThread printThread1;
	
	network_inOutBuffer_t* pInputBuffChar = NULL;
	network_inOutBuffer_t* pInputBuffIntAck = NULL;
	
	sal_thread_t thread_send1;
	sal_thread_t thread_recv1;
	sal_thread_t thread_printBuff;
	
	network_paramNewInOutBuffer_t paramNetwork1[5];
	
	//--- network 1 ---
	
	// input ID_CHAR_DATA int
	paramNetwork1[0].id = ID_CHAR_DATA;
	paramNetwork1[0].dataType = CMD_TYPE_DATA;
	paramNetwork1[0].sendingWaitTime = 3;
	paramNetwork1[0].ackTimeoutMs = 10;//not used
	paramNetwork1[0].nbOfRetry = 5;//not used
	paramNetwork1[0].buffSize = 1;
	paramNetwork1[0].buffCellSize = sizeof(char);
	paramNetwork1[0].overwriting = 1;
	
	// input ID_INT_DATA_WITH_ACK char
	paramNetwork1[1].id = ID_INT_DATA_WITH_ACK;
	paramNetwork1[1].dataType = CMD_TYPE_DATA_WITH_ACK;
	paramNetwork1[1].sendingWaitTime = 2;
	paramNetwork1[1].ackTimeoutMs = 10;
	paramNetwork1[1].nbOfRetry = -1 /*5*/;
	paramNetwork1[1].buffSize = 5;
	paramNetwork1[1].buffCellSize = sizeof(int);
	paramNetwork1[1].overwriting = 0;
	
	// input ID_KEEP_ALIVE char
	paramNetwork1[2].id = ID_KEEP_ALIVE;
	paramNetwork1[2].dataType = CMD_TYPE_KEEP_ALIVE;
	paramNetwork1[2].sendingWaitTime = 100;
	paramNetwork1[2].ackTimeoutMs = 10;//not used
	paramNetwork1[2].nbOfRetry = 5;//not used
	paramNetwork1[2].buffSize = 1;
	paramNetwork1[2].buffCellSize = sizeof(int);
	paramNetwork1[2].overwriting = 1;
	
	//  ID_CHAR_DATA_2 int
	paramNetwork1[3].id = ID_CHAR_DATA_2;
	paramNetwork1[3].dataType = CMD_TYPE_DATA;
	paramNetwork1[3].sendingWaitTime = 3;
	paramNetwork1[3].ackTimeoutMs = 10;//not used
	paramNetwork1[3].nbOfRetry = 5;//not used
	paramNetwork1[3].buffSize = 1;
	paramNetwork1[3].buffCellSize = sizeof(char);
	paramNetwork1[3].overwriting = 1;
	
	//  ID_INT_DATA_WITH_ACK_2 char
	paramNetwork1[4].id = ID_INT_DATA_WITH_ACK_2;
	paramNetwork1[4].dataType = CMD_TYPE_DATA_WITH_ACK;
	paramNetwork1[4].sendingWaitTime = 2;
	paramNetwork1[4].ackTimeoutMs = 10;
	paramNetwork1[4].nbOfRetry = -1 /*5*/;
	paramNetwork1[4].buffSize = 5;
	paramNetwork1[4].buffCellSize = sizeof(int);
	paramNetwork1[4].overwriting = 0;		
				
	printf("\n ~~ This soft sends data and repeater ack ~~ \n \n");
	
	while(netType == 0)
	{
		sal_print(PRINT_WARNING,"type 1 or 2 ? : ");
		scanfReturn = scanf("%c",&netType);
		
		switch(netType)
		{
			case '1':
				pNetwork1 = newNetwork( 256, 256, 2, 2/*3*/,
							paramNetwork1[3], paramNetwork1[4],
							paramNetwork1[0], paramNetwork1[1]/*, paramNetwork1[2]*/);
									
				printThread1.pOutBuffChar = inOutBufferWithId(	pNetwork1->ppTabOutput, pNetwork1->numOfOutput, ID_CHAR_DATA_2);
				printThread1.pOutBuffIntAck = inOutBufferWithId(	pNetwork1->ppTabOutput, pNetwork1->numOfOutput, ID_INT_DATA_WITH_ACK_2);
				
				pInputBuffChar  = inOutBufferWithId(	pNetwork1->ppTabInput, pNetwork1->numOfInput, ID_CHAR_DATA);
				pInputBuffIntAck = inOutBufferWithId(	pNetwork1->ppTabInput, pNetwork1->numOfInput, ID_INT_DATA_WITH_ACK);
				
			break;
			
			case '2':
				pNetwork1 = newNetwork( 256, 256, 2, 2,
							paramNetwork1[0], paramNetwork1[1],
							paramNetwork1[3], paramNetwork1[4]);
				printThread1.pOutBuffChar = inOutBufferWithId(	pNetwork1->ppTabOutput, pNetwork1->numOfOutput, ID_CHAR_DATA);
				printThread1.pOutBuffIntAck = inOutBufferWithId(	pNetwork1->ppTabOutput, pNetwork1->numOfOutput, ID_INT_DATA_WITH_ACK);
				
				pInputBuffChar  = inOutBufferWithId(	pNetwork1->ppTabInput, pNetwork1->numOfInput, ID_CHAR_DATA_2);
				pInputBuffIntAck = inOutBufferWithId(	pNetwork1->ppTabInput, pNetwork1->numOfInput, ID_INT_DATA_WITH_ACK_2);
			break;
			
			default:
				cmdType = 0;
			break;
		}
	}	
	
	while(scanfReturn != 1 || bindError != 0 || connectError != 0)
	{
		sal_print(PRINT_WARNING,"repeater IP address ? : ");
		scanfReturn = scanf("%s",IpAddress);
		
		if(bindError != 0)
		{
			if(netType == '1')
			{
				bindError = receiverBind(pNetwork1->pReceiver, 5552, 10);
			}
			else
			{
				bindError = receiverBind(pNetwork1->pReceiver, 5551, 10);
			}
		}
		
		if(connectError != 0)
		{
			if(netType == '1')
			{
				connectError = senderConnection(pNetwork1->pSender,IpAddress, 5551);
			}
			else
			{
				connectError = senderConnection(pNetwork1->pSender,IpAddress, 5552);
			}
		}
		
		printf("	- Sender connect error: %d \n", connectError );			
		printf("	- Receiver Bind  error: %d \n", bindError );
		printf("\n");
	}
	
	while ( ((chData = getchar()) != '\n') && chData != EOF)
	{
	};
	
	printThread1.alive=1;
	
	sal_thread_create(&thread_printBuff, (sal_thread_routine) printBuff, &printThread1 );
	sal_thread_create(&(thread_recv1), (sal_thread_routine) runReceivingThread, pNetwork1->pReceiver);
	sal_thread_create(&thread_send1, (sal_thread_routine) runSendingThread, pNetwork1->pSender);
	
	chData = 0;
	
	setupNonBlockingTerm ();
	
	while(cmdType != '0')
	{
		printf("press: 	1 - send char \n \
	2 - send int acknowledged \n \
	0 - quit \n");
	
		//scanfReturn = scanf("%d",&cmdType);
		
		cmdType = (char) getchar();
		
		switch(cmdType)
		{
			case '0' : 
				printf("wait ... \n");
			break;
			
			case '1' :
				++chData;
				printf("send char data :%d \n",chData);
				//scanfReturn = scanf("%c", &chData);
				//printf("\n");
				
				ringBuffPushBack(pInputBuffChar->pBuffer, &chData);
				
			break;
			
			case '2' :
				++intData;
				printf("int data acknowledged :%d \n",intData);
				//scanfReturn = scanf("%d", &intData);
				printf("\n");
										
				if( ringBuffPushBack(pInputBuffIntAck->pBuffer, &intData) )
				{
					printf("buffer fulll \n");
				}
				
			break;
				
			default:
				cmdType = -1;
			break;
		}
	}
	
	//stop all therad
	printThread1.alive = 0;
	stopSender(pNetwork1->pSender);
	stopReceiver(pNetwork1->pReceiver);
	
	//kill all thread
	
	sal_thread_join(&(thread_send1), NULL);
	sal_thread_join(&(thread_recv1), NULL);
	sal_thread_join(&(thread_printBuff), NULL);

	//delete
	deleteNetwork( &pNetwork1 );
	
	printf("end\n");

	fixTerminal (0);

	return 0;
}

void* printBuff(void* data)
{
	char chData = 0;
	int intData = 0;
	
	printThread* pprintThread1 = (printThread*) data;
	
	while(pprintThread1->alive)
	{
		usleep(MILLISECOND);
	

		while( !ringBuffPopFront(pprintThread1->pOutBuffChar->pBuffer, &chData) )
		{
			printf("- char :%d \n",chData);
		}
		
		while( !ringBuffPopFront(pprintThread1->pOutBuffIntAck->pBuffer, &intData) )
		{
			printf("- int ack :%d \n",intData);
		}
	}
	
	return NULL;
}