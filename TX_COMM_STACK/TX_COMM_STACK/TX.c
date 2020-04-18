/*
 * TX.c
 *
 * Created: 04/08/2018 11:46:36
 *  Author: Mahmoud
 */ 
#include "TX.h"
#define MAX_BUFF_SIZE 100
static enum_tx_state comm_state=IDLE;  
static enum_tx_state

static ecore_u8 COMM_BUFFER[MAX_BUFF_SIZE];
static ecore_u8 BUFF_COUNTER;

static struct
{
	comm_cmommands_t command;
	ecore_u8 data_size;
	ecore_u8 *data_ptr;
	ecore_u8 data_checkSum;
}comm_frame_obj;
 
 void comm_cb()
 {
	 
	 if( (comm_state == SENDING_SIZE) ||(comm_state == SENDING_BYTE))
	 {
		 comm_state=SENDING_BYTE_DONE;
	 }
	 else if (comm_state ==SENDING_COMMAND)
	 {
		 comm_state = SENDING_SIZE;
	 }
	 else if (comm_state==SENDING_CS)
	 {
		 comm_state=IDLE;
	 } 
	 else
	 {
		 
	 }
	 
 }

enumtx_error_t comm_send(ecore_u8 * data_in,ecore_u8 BUFF_SIZE,comm_cmommands_t comm)
{
	enumtx_error_t ret_val=NO_ERRORS;
	if (comm_state == IDLE)
	{
			if ( (data_in != NULL) && (BUFF_SIZE <= MAX_BUFF_SIZE) )
			{
				comm_frame_obj.data_ptr=data_in;
				comm_frame_obj.data_size=BUFF_SIZE;
				comm_frame_obj.command=comm;
				comm_frame_obj.data_checkSum=0;
				comm_state=LOCKED;				
			} 
			else
			{
				ret_val=INVALID_PARAMS
			}
	} 
	else
	{
		ret_val=COMM_BUSY;
	}
	
	return ret_val;		
}
enumtx_error_t comm_dispatch()
{
	enumtx_error_t ret_val=NO_ERRORS;
	if (comm_state != IDLE)
	{
		if ( BUFF_COUNTER <= comm_frame_obj.data_size)
		{
					if(comm_state == SENDING_BYTE_DONE)
					{
						uart_send( *(comm_frame_obj.data_ptr+BUFF_COUNTER) );
						comm_frame_obj.data_checkSum+=*(comm_frame_obj.data_ptr);
						BUFF_COUNTER++;
						comm_state=SENDING_BYTE;
					}
					else if(comm_state == SENDING_SIZE)
					{
						uart_SEND(comm_frame_obj.data_size);
					}
					else if(comm_state == LOCKED)
					{
						uart_send((ecore_u8 )comm_frame_obj.command);

						comm_state =SENDING_COMMAND;
						
					}
					else
					{
						ret_val=INVALID_PARAMS;
					}
		} 
		else
		{
			if(comm_state == SENDING_BYTE_DONE)
			{
				uart_send(*(comm_frame_obj.data_checkSum));
				comm_state=SENDING_CS;
			}
				
		}

	}
	else
	{
		//donothing
	}
	
	return ret_val;
}

