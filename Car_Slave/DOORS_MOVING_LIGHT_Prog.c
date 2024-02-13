

/******************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*/
/*=================******************************************=================*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "string.h"
#include "DOORS_MOVING_LIGHT.h"
#include "TIMER1_int.h"
#include "TMR0_Interface.h"
#include "TMR2_Interface.h"
#include "DIO_Interface.h"



/*----------------------------------------------*/
/* Important Data use it to display on lcd      */
/*----------------------------------------------*/
extern u8 arr[20];
extern u8 STAT_Door1[15] ;
extern u8 STAT_Door2[15] ;
extern u8 STAT_Door3[15] ;
extern u8 STAT_Door4[15] ;
extern u8 STAT_MOVE[15] ;
extern u8 PWM_STF;
extern u8 PWM_STB;
extern u8 STAT_LIGHT_F[15]  ;
extern u8 STAT_LIGHT_B[15]  ;
/******************************************************************/
void Doors_init(void )
{
	/*PIN A  B To Select Servo Motor*/
	DIO_voidSetPinDirection(PORTD_ID,PIN6,PIN_OUTPUT);
	DIO_voidSetPinDirection(PORTD_ID,PIN7,PIN_OUTPUT);

	DIO_voidSetPinDirection(PORTA_ID,PIN4,PIN_OUTPUT);
	DIO_voidSetPinDirection(PORTA_ID,PIN5,PIN_OUTPUT);
	DIO_voidSetPinDirection(PORTA_ID,PIN6,PIN_OUTPUT);
	DIO_voidSetPinDirection(PORTA_ID,PIN7,PIN_OUTPUT);


}

/******************************************************************/
u8 Select_Door(const u8 data)
{
	u8 select =0 ;
	switch(data)
	{
	/*-------------------------------------------*/
	case '1':

		if(strcmp((char*)arr,(char*)"D1OPEN#")==0)
		{
			strcpy((char*)STAT_Door1,(char*)"D1 Open  ");

			DIO_voidSetPinValue(PORTC_ID,PIN6,PIN_LOW);
			DIO_voidSetPinValue(PORTC_ID,PIN7,PIN_LOW);
			M_TIMER1_voidPwm1Start();
			M_TIMER1_voidPwm1SetDutyCycle(25);
			DIO_voidSetPinValue(PORTA_ID,PIN4,PIN_HIGH);

		}
		else if(strcmp((char*)arr,(char*)"D1CLOSE#")==0)
		{
			strcpy((char*)STAT_Door1,(char*)"D1 Closed");
			DIO_voidSetPinValue(PORTC_ID,PIN6,PIN_LOW);
			DIO_voidSetPinValue(PORTC_ID,PIN7,PIN_LOW);
			M_TIMER1_voidPwm1Start();
			M_TIMER1_voidPwm1SetDutyCycle(65);
			DIO_voidSetPinValue(PORTA_ID,PIN4,PIN_LOW);

		}
		else
		{
			select =1 ;
		}
		break ;
		/*-------------------------------------------*/
	case '2':

		if(strcmp((char*)arr,(char*)"D2OPEN#")==0)
		{
			strcpy((char*)STAT_Door2,(char*)"D2 Open  ");
			DIO_voidSetPinValue(PORTC_ID,PIN6,PIN_HIGH);
			DIO_voidSetPinValue(PORTC_ID,PIN7,PIN_LOW);
			M_TIMER1_voidPwm1Start();
			M_TIMER1_voidPwm1SetDutyCycle(25);
			DIO_voidSetPinValue(PORTA_ID,PIN5,PIN_HIGH);

		}
		else if(strcmp((char*)arr,(char*)"D2CLOSE#")==0)
		{
			strcpy((char*)STAT_Door2,(char*)"D2 Closed");
			DIO_voidSetPinValue(PORTC_ID,PIN6,PIN_HIGH);
			DIO_voidSetPinValue(PORTC_ID,PIN7,PIN_LOW);
			M_TIMER1_voidPwm1Start();
			M_TIMER1_voidPwm1SetDutyCycle(65);
			DIO_voidSetPinValue(PORTA_ID,PIN5,PIN_LOW);

		}
		else
		{
			select =1 ;
		}

		break ;
		/*-------------------------------------------*/
	case '3':

		if(strcmp((char*)arr,(char*)"D3OPEN#")==0)
		{
			strcpy((char*)STAT_Door3,(char*)"D3 Open  ");
			DIO_voidSetPinValue(PORTC_ID,PIN6,PIN_LOW);
			DIO_voidSetPinValue(PORTC_ID,PIN7,PIN_HIGH);

			M_TIMER1_voidPwm1Start();
			M_TIMER1_voidPwm1SetDutyCycle(25);

			DIO_voidSetPinValue(PORTA_ID,PIN6,PIN_HIGH);

		}
		else if(strcmp((char*)arr,(char*)"D3CLOSE#")==0)
		{
			strcpy((char*)STAT_Door3,(char*)"D3 Closed");
			DIO_voidSetPinValue(PORTC_ID,PIN6,PIN_LOW);
			DIO_voidSetPinValue(PORTC_ID,PIN7,PIN_HIGH);

			M_TIMER1_voidPwm1Start();
			M_TIMER1_voidPwm1SetDutyCycle(65);
			DIO_voidSetPinValue(PORTA_ID,PIN6,PIN_LOW);

		}
		else
		{
			select =1 ;
		}
		break ;

		/*-------------------------------------------*/
	case '4':

		if(strcmp((char*)arr,(char*)"D4OPEN#")==0)
		{
			strcpy((char*)STAT_Door4,(char*)"D4 Open  ");
			DIO_voidSetPinValue(PORTC_ID,PIN6,PIN_HIGH);
			DIO_voidSetPinValue(PORTC_ID,PIN7,PIN_HIGH);

			M_TIMER1_voidPwm1Start();
			M_TIMER1_voidPwm1SetDutyCycle(25);
			DIO_voidSetPinValue(PORTA_ID,PIN7,PIN_HIGH);

		}
		else if(strcmp((char*)arr,(char*)"D4CLOSE#")==0)
		{
			strcpy((char*)STAT_Door4,(char*)"D4 CLOSED");
			DIO_voidSetPinValue(PORTC_ID,PIN6,PIN_HIGH);
			DIO_voidSetPinValue(PORTC_ID,PIN7,PIN_HIGH);
			M_TIMER1_voidPwm1Start();
			M_TIMER1_voidPwm1SetDutyCycle(65);
			DIO_voidSetPinValue(PORTA_ID,PIN7,PIN_LOW);

		}
		else
		{
			select =1 ;
		}

		break ;
		/*-------------------------------------------*/

	default : select =1 ;
	break ;
	}

	return select ;
}


/*******************************************************/


void ALL_Doors_Closed(void)
{
	M_TIMER1_voidPwm1Start();
	DIO_voidSetPinValue(PORTC_ID,PIN6,PIN_LOW);
	DIO_voidSetPinValue(PORTC_ID,PIN7,PIN_LOW);
	M_TIMER1_voidPwm1SetDutyCycle(65);
	_delay_ms(50);
	DIO_voidSetPinValue(PORTC_ID,PIN6,PIN_HIGH);
	DIO_voidSetPinValue(PORTC_ID,PIN7,PIN_LOW);
	M_TIMER1_voidPwm1SetDutyCycle(65);
	_delay_ms(50);
	DIO_voidSetPinValue(PORTC_ID,PIN6,PIN_LOW);
	DIO_voidSetPinValue(PORTC_ID,PIN7,PIN_HIGH);
	M_TIMER1_voidPwm1SetDutyCycle(65);
	_delay_ms(50);
	DIO_voidSetPinValue(PORTC_ID,PIN6,PIN_HIGH);
	DIO_voidSetPinValue(PORTC_ID,PIN7,PIN_HIGH);
	M_TIMER1_voidPwm1SetDutyCycle(65);
	_delay_ms(50);
	M_TIMER1_voidPwm1Stop();
}




void Moving_Init(void)
{
	/*Motor _ speed*/
	DIO_voidSetPinDirection(PORTD_ID,PIN0,PIN_OUTPUT);
	DIO_voidSetPinDirection(PORTD_ID,PIN1,PIN_OUTPUT);
	DIO_voidSetPinDirection(PORTD_ID,PIN2,PIN_OUTPUT);
	DIO_voidSetPinDirection(PORTD_ID,PIN3,PIN_OUTPUT);
}

/******************************************************************/
u8 Select_Moving_Way(u8 copy_data)
{
	u8 select =0 ;

	switch(copy_data)
	{
	case 'F' :
		if(strcmp((char*)arr,(char*)"MF#")==0)
		{

			strcpy((char*)STAT_MOVE,(char*)"Moving Forward");

			DIO_voidSetPinValue(PORTD_ID,PIN0,PIN_HIGH);
			DIO_voidSetPinValue(PORTD_ID,PIN1,PIN_LOW);

			DIO_voidSetPinValue(PORTD_ID,PIN2,PIN_HIGH);
			DIO_voidSetPinValue(PORTD_ID,PIN3,PIN_LOW);
		}
		else
		{
			select =1 ;
		}
		break ;

		/*--------------------------------------------------------*/
	case 'R' :
		if(strcmp((char*)arr,(char*)"MR#")==0)
		{
			strcpy((char*)STAT_MOVE,(char*)"Moving Right  ");


			DIO_voidSetPinValue(PORTD_ID,PIN0,PIN_LOW);
			DIO_voidSetPinValue(PORTD_ID,PIN1,PIN_LOW);

			DIO_voidSetPinValue(PORTD_ID,PIN2,PIN_HIGH);
			DIO_voidSetPinValue(PORTD_ID,PIN3,PIN_LOW);
		}
		else
		{
			select =1 ;
		}
		break ;
		/*--------------------------------------------------------*/
	case 'B' :
		if(strcmp((char*)arr,(char*)"MB#")==0)
		{
			strcpy((char*)STAT_MOVE,(char*)"Moving Back   ");


			DIO_voidSetPinValue(PORTD_ID,PIN0,PIN_LOW);
			DIO_voidSetPinValue(PORTD_ID,PIN1,PIN_HIGH);

			DIO_voidSetPinValue(PORTD_ID,PIN2,PIN_LOW);
			DIO_voidSetPinValue(PORTD_ID,PIN3,PIN_HIGH);
		}
		else
		{
			select =1 ;
		}
		break ;

		/*--------------------------------------------------------*/
	case 'L' :
		if(strcmp((char*)arr,(char*)"ML#")==0)
		{
			strcpy((char*)STAT_MOVE,(char*)"Moving Left   ");

			DIO_voidSetPinValue(PORTD_ID,PIN0,PIN_HIGH);
			DIO_voidSetPinValue(PORTD_ID,PIN1,PIN_LOW);

			DIO_voidSetPinValue(PORTD_ID,PIN2,PIN_LOW);
			DIO_voidSetPinValue(PORTD_ID,PIN3,PIN_LOW);
		}
		else
		{
			select =1 ;
		}
		break ;
		/*--------------------------------------------------------*/
	case 'S' :
		if(strcmp((char*)arr,(char*)"MS#")==0)
		{
			strcpy((char*)STAT_MOVE,(char*)"Car Stoped    ");


			DIO_voidSetPinValue(PORTD_ID,PIN0,PIN_LOW);
			DIO_voidSetPinValue(PORTD_ID,PIN1,PIN_LOW);

			DIO_voidSetPinValue(PORTD_ID,PIN2,PIN_LOW);
			DIO_voidSetPinValue(PORTD_ID,PIN3,PIN_LOW);
		}
		break ;

	default :
		select =1 ;
		break ;
	}


	return select  ;
}

/*******************************************************/

u8 Light_Intensit(u8 copy_data)
{
	u8 select =0 ;

	switch(copy_data)
	{
	case 'F' :
		if(strcmp((char*)arr,(char*)"LFI#")==0)
		{
			if (PWM_STF>=0 && PWM_STF<=90)
			{

				PWM_STF +=10 ;
			}


			TIMER0_VoidStart();
			TIMER0_VoidSetPWMCompareMatch(PWM_STF);
		}
		else if(strcmp((char*)arr,(char*)"LFD#")==0)
		{
			if (PWM_STF>=0 && PWM_STF<=90)
			{

				PWM_STF -=10 ;
			}
			TIMER0_VoidStart();
			TIMER0_VoidSetPWMCompareMatch(PWM_STF);
		}
		else
		{
			select =1 ;
		}
		break ;

		/*--------------------------------------------------------*/
	case 'B' :
		if(strcmp((char*)arr,(char*)"LBI#")==0)
		{
			if (PWM_STB>=0 && PWM_STB<=90)
			{

				PWM_STB +=10 ;
			}


			TIMER2_VoidStart();
			TIMER2_VoidSetPWMCompareMatch(PWM_STB);
		}
		else if(strcmp((char*)arr,(char*)"LBD#")==0)
		{
			if (PWM_STB>=0 && PWM_STB<=90)
			{

				PWM_STB -=10 ;
			}
			TIMER2_VoidStart();
			TIMER2_VoidSetPWMCompareMatch(PWM_STB);
		}
		else
		{
			select =1 ;
		}
		break ;
		/*--------------------------------------------------------*/
	default :
		select =1 ;
		break ;
	}

	//TIMER0_VoidStart();
	sprintf(STAT_LIGHT_F, "%d", PWM_STF);
	sprintf(STAT_LIGHT_B, "%d", PWM_STB);

	return select  ;
}

/*******************************************************/

