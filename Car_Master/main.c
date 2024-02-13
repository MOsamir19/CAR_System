/*
 * main.c
 *
 *  Created on: Sep 25, 2022
 *      Author: General
 */




#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "UART_Interface.h"
#include "SPI_Interface.h"







int main()
{

	u8 data=0 ;

	UART_VoidInit();
	SPI_voidInit();


	while(1)
	{

	UART_U8ReceiveChar(&data);
	SPI_VoidSendChar(data);


	}


	return 0 ;
}



