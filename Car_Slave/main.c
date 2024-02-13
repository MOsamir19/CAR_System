
/*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*
 *==================******************************************================*/
 /*****************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"

#include "DIO_Interface.h"
#include "UART_Interface.h"
#include "SPI_Interface.h"
#include "SPI_Private.h"
#include "GIE_Interface.h"
#include "ADC_Interface.h"
#include "TMR0_Interface.h"
#include "TMR2_Interface.h"
#include "TIMER1_int.h"
#include "DOORS_MOVING_LIGHT.h"
#include "LCD_Interface.h"

#include"string.h"

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
//#include "avr/io.h"
//#undef  F_CPU
//#define F_CPU (16000000UL)




void SYSTEM_INIT(void);
void Display_Screen(void) ;
void SPI_ISR(void);

u8 arr[20]={0} ;
u8 STAT_Door1[15]="D1 Closed";
u8 STAT_Door2[15]="D2 Closed";
u8 STAT_Door3[15]="D3 Closed";
u8 STAT_Door4[15]="D4 Closed";
u8 STAT_MOVE [15] ="Car Stoped"  ;
u8 SPI_END =0 ;
u8 PWM_STF=0;
u8 PWM_STB=0 ;
u8 STAT_LIGHT_F[15]="0"  ;
u8 STAT_LIGHT_B[15]="0"  ;
u16 ADC_Data=0 ;
u16 ADC_Data_OLD=0 ;

int main()
{

	u8 error =1 ;

	SYSTEM_INIT();
	ADC_voidChannelSellect(0);
	while(1)
	{
		/*-----------------------------------*/
		/**** SPI data comes from spi isr ****/
		/*-----------------------------------*/


		/*------------------------*/
		/*ADC BLOCK _ LM35 Sensor */
		/*------------------------*/
		ADC_StartConversionBoling(&ADC_Data);
		if(ADC_Data_OLD != ADC_Data)
		{
			LCD_voidGoToXY(0,17);
			LCD_voidWriteString((u8*)"   ");
			LCD_voidGoToXY(0,17);
			LCD_voidWriteNumber(ADC_Data/2);
		}
		ADC_Data_OLD = ADC_Data ;
		/*---------------------------------*/

		/*SPI_END =1  its means that spi Received string */
		if (SPI_END ==1)
		{

			/*SPI_END change to 1  in spi ISR
			 * and when we go here must make it 0 in the first
			 */
			SPI_END=0 ;

			if (arr[0]=='M')/*Moving check*/
			{
				/*string check*/
				error =Select_Moving_Way(arr[1]) ;
			}

			else if (arr[0]=='D')/*Doors check*/
			{
				/*string check*/
				error =Select_Door(arr[1] ) ;
				
			}

			else if (arr[0]=='L')/*Light check*/
			{
				/*string check*/
				error =Light_Intensit(arr[1]) ;
			}

			if(error==1)
			{
				LCD_voidClear() ;
				LCD_voidGoToXY(0,0);
				LCD_voidWriteString((u8*)"TRY AGAIN");
				_delay_ms(100);
			}

			/*Display all car status*/
			Display_Screen();


		}/* related to cond --->i f (SPI_END ==1)*/





	}







	return 0 ;
}

/*****************************************************************/
void SYSTEM_INIT(void)
{


	SPI_voidInit();
	GIE_Enable();
	ADC_voidInit();
	Doors_init();
	LCD_voidInit();
	Moving_Init();
	TIMER0_VoidInit();
	TIMER2_VoidInit();
	M_TIMER1_voidPwm1Init();
	M_TIMER1_voidPwm1SetTop();

	SPI_voidSetCallBack(&SPI_ISR);
	ALL_Doors_Closed();
	Display_Screen();

}
/*****************************************************************/
void Display_Screen(void)
{
	LCD_voidGoToXY(0,0);
	LCD_voidWriteString((u8*)STAT_MOVE);

	LCD_voidGoToXY(0,15);
	LCD_voidWriteString((u8*)"T=");
	LCD_voidGoToXY(0,17);
	LCD_voidWriteString((u8*)"   ");
	LCD_voidGoToXY(0,17);
	LCD_voidWriteNumber(ADC_Data/2);

	LCD_voidGoToXY(1,0);
	LCD_voidWriteString((u8*)"L.F=     ");
	LCD_voidGoToXY(1,4);
	LCD_voidWriteString((u8*)STAT_LIGHT_F);
	LCD_voidWriteData('%');

	LCD_voidGoToXY(1,11);
	LCD_voidWriteString((u8*)"L.B=    ");
	LCD_voidGoToXY(1,15);
	LCD_voidWriteString((u8*)STAT_LIGHT_B);
	LCD_voidWriteData('%');


	//	LCD_voidGoToXY(1,16);
	//	LCD_voidWriteNumber(ADC_Data/2);


	LCD_voidGoToXY(2,0);
	LCD_voidWriteString((u8*)STAT_Door1);
	LCD_voidGoToXY(2,11);
	LCD_voidWriteString((u8*)STAT_Door2);
	LCD_voidGoToXY(3,0);
	LCD_voidWriteString((u8*)STAT_Door3);
	LCD_voidGoToXY(3,11);
	LCD_voidWriteString((u8*)STAT_Door4);

}
/*******************************************************/

void SPI_ISR(void)
{
	static u8 coun=0 ;
	u8 coun1 =0 ;

	/*------------------------------*/
	if(coun==0)
	{
		for(coun1=0 ; coun1!=20 ; coun1++)
		{
			arr[coun1]=0 ;
		}
	}

	/*------------------------------*/
	arr[coun]=SPDR_REG;
	/*------------------------------*/

	if(arr[coun] !='#')
	{
		coun++ ;

	}
	else {
		coun = 0 ;
		SPI_END  =1 ;
	}

	/*------------------------------*/
}



/*******************************************************/
