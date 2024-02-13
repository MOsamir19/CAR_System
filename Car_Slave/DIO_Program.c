

 /*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*
 *==================******************************************================*
 /*****************************************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_Interface.h"
#include"DIO_Private.h"



void DIO_voidSetPortDirection(u8 Copy_u8portID,u8 Copy_u8PortDir )
{
	switch(Copy_u8portID)
	{
	case PORTA_ID :   DDRA_REG= Copy_u8PortDir ; break ;
	case PORTB_ID :   DDRB_REG= Copy_u8PortDir ; break ;
	case PORTC_ID :   DDRC_REG= Copy_u8PortDir ; break ;
	case PORTD_ID :   DDRD_REG= Copy_u8PortDir ; break ;

	}
}


void DIO_voidSetPortValue(u8 Copy_u8PortID,u8 Copy_u8PortVal )

{

	switch(Copy_u8PortID)
	{

	case PORTA_ID :   PORTA_REG= Copy_u8PortVal ; break ;
	case PORTB_ID :   PORTB_REG= Copy_u8PortVal ; break ;
	case PORTC_ID :   PORTC_REG= Copy_u8PortVal ; break ;
	case PORTD_ID :   PORTD_REG= Copy_u8PortVal ; break ;

	}
}






void	DIO_voidSetPinDirection(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinDir)
{
	if(Copy_u8PinID>=PIN0 &&Copy_u8PinID<=PIN7)
	{
		if(Copy_u8PinDir==PIN_OUTPUT)//Output
		{
			switch(Copy_u8PortID)
			{
			case PORTA_ID:    SET_BIT(DDRA_REG,Copy_u8PinID); break;
			case PORTB_ID:    SET_BIT(DDRB_REG,Copy_u8PinID); break;
			case PORTC_ID:    SET_BIT(DDRC_REG,Copy_u8PinID); break;
			case PORTD_ID:    SET_BIT(DDRD_REG,Copy_u8PinID); break;

			default:   break;

			}
		}
		else if(Copy_u8PinDir==PIN_INPUT)//Input
		{
			switch(Copy_u8PortID)
			{
			case PORTA_ID:   CLR_BIT(DDRA_REG,Copy_u8PinID); break;
			case PORTB_ID:   CLR_BIT(DDRB_REG,Copy_u8PinID); break;
			case PORTC_ID:   CLR_BIT(DDRC_REG,Copy_u8PinID); break;
			case PORTD_ID:   CLR_BIT(DDRD_REG,Copy_u8PinID); break;
			default:   break;
			}
		}
	}

}
void    DIO_voidSetPinValue(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinValue)
{
	if(Copy_u8PinID>=PIN0&&Copy_u8PinID<=PIN7)
	{
		if(Copy_u8PinValue==PIN_HIGH)//High
		{

			switch(Copy_u8PortID)
			{
			case PORTA_ID :    SET_BIT(PORTA_REG,Copy_u8PinID); break;
			case PORTB_ID :    SET_BIT(PORTB_REG,Copy_u8PinID); break;
			case PORTC_ID :    SET_BIT(PORTC_REG,Copy_u8PinID); break;
			case PORTD_ID :    SET_BIT(PORTD_REG,Copy_u8PinID); break;

			}
		}
		else if(Copy_u8PinValue==PIN_LOW)//Low
		{
			switch(Copy_u8PortID)
			{
			case PORTA_ID : CLR_BIT(PORTA_REG,Copy_u8PinID); break ;
			case PORTB_ID : CLR_BIT(PORTB_REG,Copy_u8PinID); break ;
			case PORTC_ID : CLR_BIT(PORTC_REG,Copy_u8PinID) ;break ;
			case PORTD_ID : CLR_BIT(PORTD_REG,Copy_u8PinID) ;break ;

			}
		}
	}
}

u8 DIO_voidGetBitValue(u8 copy_u8PortID , u8 Copy_u8PinID )
{

	u8 Local_PinVal ;

	if( Copy_u8PinID>=PIN0 && Copy_u8PinID<=PIN7 )
	{
		switch(copy_u8PortID)
		{

		case PORTA_ID : Local_PinVal=GET_BIT(PINA_REG,Copy_u8PinID)   ; break ;
		case PORTB_ID : Local_PinVal=GET_BIT(PINB_REG,Copy_u8PinID)   ; break ;

		case PORTC_ID : Local_PinVal=GET_BIT(PINC_REG,Copy_u8PinID)   ; break ;

		case PORTD_ID : Local_PinVal=GET_BIT(PIND_REG,Copy_u8PinID)   ; break ;

		}
	}

	return Local_PinVal ;

}

/*
void DIO_voidGetPinValue(u8 copy_u8PortID , u8 copy_PinID ,u8 *copy_u8PinVal )
{


	switch(copy_u8PortID)
	{

	case PORTA_ID : *copy_u8PinVal=GET_BIT(PINA_REG,copy_PinID)   ; break ;
	case PORTB_ID : *copy_u8PinVal=GET_BIT(PINB_REG,copy_PinID)   ; break ;

	case PORTC_ID : *copy_u8PinVal=GET_BIT(PINC_REG,copy_PinID)   ; break ;

	case PORTD_ID : *copy_u8PinVal=GET_BIT(PIND_REG,copy_PinID)   ; break ;

	}


}
 */

void DIO_voidToggelPin(u8 copy_u8PortID,u8 Copy_u8PinID)
{

	if( Copy_u8PinID>=PIN0 && Copy_u8PinID<=PIN7)
		{

	switch (copy_u8PortID)
	{
	case PORTA_ID :  TOG_BIT(PORTA_REG,Copy_u8PinID) ; break ;
	case PORTB_ID :  TOG_BIT(PORTB_REG,Copy_u8PinID) ; break ;
	case PORTC_ID :  TOG_BIT(PORTC_REG,Copy_u8PinID) ; break ;
	case PORTD_ID :  TOG_BIT(PORTD_REG,Copy_u8PinID) ; break ;
	}

	}
}





