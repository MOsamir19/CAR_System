
/*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*
 *==================******************************************================*/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "SPI_Interface.h"
#include "SPI_config.h"
#include "SPI_Private.h"
#include "LCD_Interface.h"
/********************************************************************************************/


//global pointer to fun
static void (*SPI_callBack)(void);

//call back fun
void SPI_voidSetCallBack(  void (*ptr_spi)(void) )
{

	if(ptr_spi!=NULL)
	{
		SPI_callBack=ptr_spi ;
	}
}

/********************************************************/

void __vector_12 () __attribute__  ((signal));
void __vector_12 ()
{
	if(SPI_callBack!=NULL)
	{
		SPI_callBack();
	}

}

/********************************************************/

void SPI_voidInit(void)
{
#if   SPI_MODE   ==   SPI_MASTER_MODE
	//MASTER_MODE
	SET_BIT(SPCR_REG,SPCRMSTR);

	//Freq
	SET_BIT(SPCR_REG,SPCR_SPR0);
	SET_BIT(SPCR_REG,SPCR_SPR1);


	DIO_voidSetPinDirection(PORTB_ID,PIN4,PIN_OUTPUT);
	DIO_voidSetPinDirection(PORTB_ID,PIN5,PIN_OUTPUT);
	DIO_voidSetPinDirection(PORTB_ID,PIN6,PIN_INPUT);
	DIO_voidSetPinDirection(PORTB_ID,PIN7,PIN_OUTPUT);


#elif SPI_MODE   ==   SPI_SLAVE_MODE
	//SLAVE_MODE
	CLR_BIT(SPCR_REG,SPCR_MSTR);

	DIO_voidSetPinDirection(PORTB_ID,PIN4,PIN_INPUT);
	DIO_voidSetPinDirection(PORTB_ID,PIN5,PIN_INPUT);
	DIO_voidSetPinDirection(PORTB_ID,PIN6,PIN_OUTPUT);
	DIO_voidSetPinDirection(PORTB_ID,PIN7,PIN_INPUT);

#endif

	SET_BIT(SPCR_REG,SPCR_SPIE);
	/* to send from LSB first */
	SET_BIT(SPCR_REG,SPCR_DORD);
	/* to enable spi circuit */
	SET_BIT(SPCR_REG,SPCR_SPE);
}

/********************************************************************************************/
u8   SPI_voidTransiver(u8 Copy_u8Data)
{
	u8 data =0;
	SPDR_REG = Copy_u8Data;

	while(GET_BIT(SPSR_REG,SPSR_SPIF) == 0);

	data=SPDR_REG;
	return data;
}
/***************************************************************************/
u8 SPI_voidReceiveChar(u8 *Copy_u8Data)
{
	u8 error = 0 ;
	//while(GET_BIT(SPSR_REG,SPSR_SPIF) == 0);
	if(GET_BIT(SPSR_REG,SPSR_SPIF) == 1)
	{
		*Copy_u8Data=SPDR_REG;
	}
	else
	{
		error =1 ;
	}

	return error ;

}
/***************************************************************************/
void SPI_VoidSendChar(u8 Copy_u8Data)
{
	//while(GET_BIT(SPSR_REG,SPSR_SPIF) == 0);
	SPDR_REG = Copy_u8Data;
}

/***************************************************************************/
u8 SPI_voidReceiveStr(u8 *arr)
{
	u8 coun1 =0 ;
	static u8 coun=255 ;
	u8 error=0 ;
	u8 END=0 ;

	if(coun==255)
	{


		for(coun1=0 ; coun1!=20 ; coun1++)
		{
			arr[coun1]=0 ;
		}
	}
	do
	{
		coun++ ;
		error=SPI_voidReceiveChar(&arr[coun]);


		if(error==1)
		{
			coun-- ;
			error = 1 ;
			break ;
		}

	}while(arr[coun]!='#');



	if(arr[coun] =='#')
	{

		coun = 255 ;
		END =1 ;
	}

	return END ;

}
/***************************************************************************/



