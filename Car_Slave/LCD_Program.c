

 /*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*/



#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "avr/delay.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_private.h"
#include "LCD_Config.h"




/***********************************************************************************/
void LCD_voidInit(void)
{
	/* Delay 30ms to ensure the initialization of the LCD driver */
	_delay_ms(30);

	/* Set Control pins as output */
	DIO_voidSetPinDirection(RS_PORT,RS_PIN,PIN_OUTPUT);
	// DIO_voidSetPinDirection(RW_PORT,RW_PIN,PIN_OUTPUT);
	DIO_voidSetPinDirection(EN_PORT, EN_PIN,PIN_OUTPUT);

	/* Set Data Port Direction as output */
	DIO_voidSetPinDirection(D4_PORT,D4_PIN,PIN_OUTPUT);
	DIO_voidSetPinDirection(D5_PORT,D5_PIN,PIN_OUTPUT);
	DIO_voidSetPinDirection(D6_PORT,D6_PIN,PIN_OUTPUT);
	DIO_voidSetPinDirection(D7_PORT,D7_PIN,PIN_OUTPUT);

	/* Return Home */
	LCD_voidWriteCommand(RETURN_HOME );

	/* Configure as 4-bit data mode*/
	LCD_voidWriteCommand(FUNCTION_SET_4BIT_2LINES_5X7_DOTS);

	/*Display ON OFF Control */
	LCD_voidWriteCommand(DISPLAY_ON_CURSOR_OFF);

	/* Clear Display */
	LCD_voidWriteCommand(DISPLAY_CLEAR);

	/*ENTRY MODE*/
	LCD_voidWriteCommand(ENTRY_MODE_SET);

}
/***********************************************************************************/

static void LCD_voidWriteBitsToSend(u8 copy_u8Byte)
{



	/*prepare 4 bits MSB to send */
	DIO_voidSetPinValue(D7_PORT,D7_PIN,  GET_BIT(copy_u8Byte,PIN7)  ) ;
	DIO_voidSetPinValue(D6_PORT,D6_PIN, GET_BIT(copy_u8Byte,PIN6) );
	DIO_voidSetPinValue(D5_PORT,D5_PIN, GET_BIT(copy_u8Byte,PIN5) );
	DIO_voidSetPinValue(D4_PORT,D4_PIN, GET_BIT(copy_u8Byte,PIN4) );

	/* open EN--> make it high --- then after 2m close EN -->make it low*/
	DIO_voidSetPinValue(EN_PORT,EN_PIN, PIN_HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(EN_PORT,EN_PIN, PIN_LOW);


	/*prepare 4 bits LSB to send */
	DIO_voidSetPinValue(D7_PORT,D7_PIN, GET_BIT(copy_u8Byte,PIN3) );
	DIO_voidSetPinValue(D6_PORT,D6_PIN, GET_BIT(copy_u8Byte,PIN2) );
	DIO_voidSetPinValue(D5_PORT,D5_PIN, GET_BIT(copy_u8Byte,PIN1) );
	DIO_voidSetPinValue(D4_PORT,D4_PIN, GET_BIT(copy_u8Byte,PIN0) );

	/* open EN--> make it high --- then after 2m -- close EN -->make it low*/
	DIO_voidSetPinValue(EN_PORT,EN_PIN, PIN_HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(EN_PORT,EN_PIN, PIN_LOW);




}



/***********************************************************************************/
void LCD_voidWriteData(u8 copy_u8data)
{
	/*Set RS to HIGH */
	DIO_voidSetPinValue(RS_PORT,RS_PIN,PIN_HIGH);

	LCD_voidWriteBitsToSend(copy_u8data);
}


/***********************************************************************************/

void LCD_voidWriteCommand(u8 copy_u8Command)
{
	/*Set RS to low */
	DIO_voidSetPinValue(RS_PORT,RS_PIN,PIN_LOW);


	LCD_voidWriteBitsToSend(copy_u8Command);
}

/***********************************************************************************/



void LCD_voidWriteString(u8 * copy_str)
{

	u16 i= ZERO;
	while(copy_str[i] != '\0')
	{
		LCD_voidWriteData(copy_str[i]);
		i++;
	}
}


/***********************************************************************************/
void LCD_voidGoToXY(u8 copy_u8row,u8 copy_u8col)
{
	/* 0x00 --> address row 0
	 * 0x40 --> address row 1
	 * 0x14 --> address row 2
	 * 0x54 --> address row 3
	 * copy_u8col --> col num
	 * */
	u8 rows_address[4]={0x00,0x40,0x14,0x54};

	u8 local_address=( rows_address[copy_u8row]  + copy_u8col ) + SET_DDRAM_ADDRESS ;

	LCD_voidWriteCommand(local_address) ;

}

/***********************************************************************************/

/*
void LCD_voidGoToXY(u8 copy_u8row,u8 copy_u8col)
{

	u8 local_address ;
	switch(copy_u8row)
	{
	case 0 : local_address =0x00+copy_u8col ;
	break ;

	case 1 : local_address =copy_u8col+0x40 ;
	break ;

	case 2 : local_address =copy_u8col+0x14 ;
	break ;

	case 3 : local_address =copy_u8col+0x54 ;
	break ;

    default : break ;
	}
	LCD_voidWriteCommand(local_address+SET_DDRAM_ADDRESS) ;

}
 */
/***********************************************************************************/

void LCD_voidClear(void)
{
	LCD_voidWriteCommand( DISPLAY_CLEAR);

}

/***********************************************************************************/

void LCD_voidWriteNumber( u32 Copy_u8num )

{
	u32 LOCAL_NUMBER=Copy_u8num ;
	u8 LOCAL_ARR[10]   ;
	u8 i=ZERO ;


	do
	{
		LOCAL_ARR[i]= ( (LOCAL_NUMBER%10)+'0' );
		LOCAL_NUMBER=LOCAL_NUMBER/10 ;
		i++ ;
	}
	while(LOCAL_NUMBER!=ZERO);


	for(;i>0;i--)
	{
		LCD_voidWriteData(LOCAL_ARR[i-ONE]);
	}



}

/***********************************************************************************/

void LCD_voidWriteSpecialCharToCGRAM(u8 *copy_u8data , u8 copy_u8ByteNum )

{
	u8 Local_u8CGramAddrss ;
	u8 counter=ZERO ;

	Local_u8CGramAddrss = ( (copy_u8ByteNum * EIGHT)+SET_CGRAM_ADDRESS ) ;

	LCD_voidWriteCommand( Local_u8CGramAddrss  ) ;


	for(counter=ZERO;counter<EIGHT;counter++)
	{
		LCD_voidWriteData(copy_u8data[counter]);
	}

}

/***********************************************************************************/

void LCD_voidDisplaySpecialChar(u8 copy_u8ByteNum )
{

	LCD_voidWriteData(copy_u8ByteNum);

}


// Online C compiler to run C program online
