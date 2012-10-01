/**
 *	@file LibNetWork.c
 *  @brief AR commands processing, manage video stream reception,
 *	 photo reception and essential navdata demux
 *  @date 28/09/2012
 *  @author maxime.maitre@parrot.com
**/

#ifndef _LIB_NET_WORK_H_
#define _LIB_NET_WORK_H_

//include :

#include <stdio.h> //!!sup 
#include <stdlib.h> //!!sup 
//#include <LibSAL.h>
#include "../Includes/LibNetWork.h"


/**
 *	@brief buffer of the acknowledged commandes
**/
AR_CMD_ACK* globalBufCmdAck;
/**
 *	@brief nomber of the date in the buffer of the acknowledged commandes
**/
int globalBufCmdAckNbData;




/*****************************************
 * 
 * 			implementation :
 *
******************************************/

/**
 *  @brief init the buffer of acknowledge commande
*/
void bufCmdAckInit()
{
	printf("bufCmdAckInit \n");
	
	globalBufCmdAckNbData = 0;
	globalBufCmdAck = malloc( sizeof(AR_CMD_ACK) * BUFFER_CMD_SIZE );

}

/**
 *	@brief 
**/
int sendCmdWithAck(AR_CMD_ACK* cmd)
{
	static int buffIndexInput = 0;
	int error = 1; //!!
	AR_CMD_ACK* buffPointor = NULL;
	
	printf("sendCmdWithAck \n");

	if( globalBufCmdAckNbData < BUFFER_CMD_SIZE)
	{
		buffPointor = globalBufCmdAck + (buffIndexInput % BUFFER_CMD_SIZE);
		++buffIndexInput;
		++globalBufCmdAckNbData;
		
		buffPointor->CMDType = cmd->CMDType;
		
		error = 0; //!!
	}

	return error;
}

/**
 *  @brief puch a commande acknowledged
*/
void bufferPush()
{
	static int buffIndexOutput = 0;
	AR_CMD_ACK* buffPointor = NULL;
	
	if( globalBufCmdAckNbData > 0)
	{
		buffPointor = globalBufCmdAck + (buffIndexOutput % BUFFER_CMD_SIZE);
		++buffIndexOutput;
		--globalBufCmdAckNbData;
		printf("data : %d \n", buffPointor->CMDType); //!! sup
	}
}



/**
 *  @brief send piloting command
*/
void sendCmd(AR_CMD_ACK* cmd)
{
	
}

#endif // _LIB_NET_WORK_H_
