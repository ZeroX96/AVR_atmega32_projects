/*
 * TX.h
 *
 * Created: 04/08/2018 11:46:51
 *  Author: Mahmoud
 */ 


#ifndef TX_H_
#define TX_H_
#include "common.h"

typedef enum
{	
	//
}comm_cmommands_t;

typedef enum
{
	NO_ERRORS=0,
	INVALID_PARAMS,
	COMM_BUSY,
	//
}enumtx_error_t;

typedef enum
{
	IDLE=0,				//0
	SENDING_SIZE,		//1
	SENDING_BYTE,		//2
	SENDING_BYTE_DONE,	//3
	LOCKED,				//4
	SENDING_COMMAND,
	SENDING_CS,
}enum_tx_state;

enumtx_error_t comm_send();
enumtx_error_t comm_dispatch();


#endif /* TX_H_ */