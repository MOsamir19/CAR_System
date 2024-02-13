
/*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*
 *==================******************************************================*
 /*****************************************************************************/


/*--------------------------------------------------------------------------------------------*/
/*   INCLUDES   */
/*--------------------------------------------------------------------------------------------*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "UART_Config.h"
#include "UART_Interface.h"
#include "UART_Private.h"
#include "LCD_Interface.h"


/*--------------------------------------------------------------------------------------------*/
/*   FUNCTION BODY   */
/*--------------------------------------------------------------------------------------------*/
void UART_VoidInit(void)
{

	//u8 UCSRC_Data =0;
	UCSRC_REG_Data DATA ;
	DIO_voidSetPinDirection(PORTD_ID,PIN0,PIN_INPUT);
	DIO_voidSetPinDirection(PORTD_ID,PIN1,PIN_OUTPUT);

	/*   TO SELECT BAUD RATE   */
	UBRRL_REG = ( (u32)(F_OSC * 1000000) /((u32)16 * UART_BAUD_RATE)) - 1 ;

	DATA.UCSRC_UPM =UART_PARITY_MODE ;
	DATA.UCSRC_UCPOL=UART_NUM_STOP_BIT ;

	/***********************************************/

	/***********************************************/

	/* TO SELECT CHARACTER SIZE -> 8 BITS */
	DATA.UCSRC_UCSZ=0b11 ;
	UCSRB_REG->UCSRB_UCSZ2=0b0 ;


	/***** Write data in UCSRC_REG in one time ***********/
	DATA.UCSRC_URSEL=ONE ;
	UCSRC_REG  = DATA.BYTE ;

	/* TO ENABLE RX CIRCUIT */
	UCSRB_REG->UCSRB_RXEN =ONE  ;


	/* TO ENABLE TX CIRCUIT */
	UCSRB_REG->UCSRB_TXEN =ONE  ;

}

/*--------------------------------------------------------------------------------------------*/
/*   FUNCTION BODY   */
/*--------------------------------------------------------------------------------------------*/
UART_ERROR UART_VoidSendChar(u8 Copy_U8_Data)
{
	/* while(GET_BIT(UCSRA_REG,UCSRA_UDRE_BIT) ==0);
			UDR_REG = Copy_U8_Data; */
	u32 Local_U32_Counter = 0;
	UART_ERROR Send_check_ERROR=UART_NO_ERROR ;

	while(Local_U32_Counter <= UART_POLLING_TIME)
	{
		Local_U32_Counter++;
		if( (UCSRA_REG->UCSRA_UDRE) == UART_FINISHED_TRANSMITTING)
		{
			UDR_REG = Copy_U8_Data;
			break;
		}
	}
	if(Local_U32_Counter == UART_POLLING_TIME)
	{
		Send_check_ERROR=UART_TIME_OUT_ERROR ;
	}

	return  Send_check_ERROR ;


}
void UART_VoidSendString(u8* PO_U8_Data)
{
	u8 count=0 ;

	while(PO_U8_Data[count] !='\0')
	{
		UART_VoidSendChar(PO_U8_Data[count]);
		count ++ ;
	}


}

void UART_VoidReceiveString(u8* PO_U8_Data)
{
	s8 count= -1 ;

	u8 c=0 ;
	for( ; c!=20 ; c++)
	{
		PO_U8_Data[c]=0 ;
	}
	do
	{
		count ++ ;
		UART_U8ReceiveChar(&PO_U8_Data[count]);

	}while(PO_U8_Data[count] !='#');



}

/*------------------------------------------------------------------------------------*/
/*   FUNCTION BODY                                                                    */
/*------------------------------------------------------------------------------------*/

UART_ERROR UART_U8ReceiveChar(u8 *copy_p8_Data )
{
	UART_ERROR Send_check_ERROR=UART_NO_ERROR ;
	while( (UCSRA_REG->UCSRA_RXC) == ZERO);

	*copy_p8_Data= UDR_REG ;
	return Send_check_ERROR;

	/*
	u32 Local_U32_Counter = 0;
	UART_ERROR Send_check_ERROR=UART_NO_ERROR ;

			while(Local_U32_Counter < UART_POLLING_TIME)
			{
				Local_U32_Counter++;
				if( (UCSRA_REG->UCSRA_RXC) == UART_FINISHED_TRANSMITTING)
				{
	               *copy_p8_Data= UDR_REG ;
					break;
				}
			}
			if(Local_U32_Counter == UART_POLLING_TIME)
			{
				Send_check_ERROR=UART_TIME_OUT_ERROR ;
			}

			return  Send_check_ERROR ;
	 */


}


