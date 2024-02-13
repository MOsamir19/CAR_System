/*
 * TIMER1.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "TIMER1_int.h"
#include "TIMER1_private.h"
#include "TIMER1_config.h"



void M_TIMER1_voidPwm1Init(void)
{
	/* to enable output circuit for PD5 pin */

	DIO_voidSetPinDirection(PORTD_ID,PIN5,PIN_OUTPUT);

	/* to select mode 14 in table 47 */
	CLR_BIT(TCCR1A_REG,WGM10);
	SET_BIT(TCCR1A_REG,WGM11);
	SET_BIT(TCCR1B_REG,WGM12);
	SET_BIT(TCCR1B_REG,WGM13);

	/* to select non inverting mode */
	SET_BIT(TCCR1A_REG,COM1A1);
	CLR_BIT(TCCR1A_REG,COM1A0);
}
void M_TIMER1_voidPwm1SetTop(void)
{
	//to make TIMER at 20ms top  when PRESCALER = 256  at  8M F
	ICR1_REG=625;
}
void M_TIMER1_voidPwm1SetDutyCycle(u16 Copy_u8DutyCycle)
{
	// pass num between 25 and 65
	OCR1A_REG=Copy_u8DutyCycle ;

}
void M_TIMER1_voidPwm1Start(void)
{
#if   TIMER1_PRESCALER   ==   1024
	SET_BIT(TCCR1B_REG,CS10);
	CLR_BIT(TCCR1B_REG,CS11);
	SET_BIT(TCCR1B_REG,CS12);
#elif TIMER1_PRESCALER   ==   256
	CLR_BIT(TCCR1B_REG,CS10);
	CLR_BIT(TCCR1B_REG,CS11);
	SET_BIT(TCCR1B_REG,CS12);
#endif
}
void M_TIMER1_voidPwm1Stop(void)
{
	CLR_BIT(TCCR1B_REG,CS10);
	CLR_BIT(TCCR1B_REG,CS11);
	CLR_BIT(TCCR1B_REG,CS12);
}
