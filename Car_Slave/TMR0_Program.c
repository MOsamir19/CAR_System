

 /*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*
 *==================******************************************================*/



#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "DIO_Interface.h"

#include "TMR0_Interface.h"
#include "TMR0_Private.h"
#include "TMR0_Config.h"



/**********************************************************************************
 *********************************************************************************/

#if ISR ==ISR_EN

//global pointer to fun
static void (*TIMER0_callBack)(void);

//call back fun
void TIMER_voidSetCallBack(  void (*ptr_timer)(void) )
{

	if(ptr_timer!=NULL)
	{
		TIMER0_callBack=ptr_timer ;
	}
}


#if MOOD== NORMAL_MOOD
void __vector_11 () __attribute__  ((signal));
void __vector_11 ()
{

	TIMER0_callBack();

}

#elif MOOD== CTC_MOOD
void __vector_10 () __attribute__ ((signal));
void __vector_10 ()
{

	TIMER0_callBack();

}

#endif /*Related to  (#if MOOD== NORMAL_MOOD) and (#elif MOOD== CTC_MOOD)*/




#endif /*Related to  (#if ISR ==ISR_EN)*/
/**********************************************************************************
 *********************************************************************************/



/**********************************************************************************
 *********************************************************************************/
void TIMER0_VoidInit(void)
{

/**************************************/
#if MOOD==NORMAL_MOOD
/**************************************/
	TCCR0_REG->TCCR0_WGM00 = ZERO;
	TCCR0_REG->TCCR0_WGM01 = ZERO;
	TCNT0_REG=PRELOAD;
	/*------------------------------------*/
#if ISR == ISR_EN
	/*enabel  NORMAL_MOOD interrupt*/
	TIMSK_REG->TIMSK_TOIE0 = ONE ;
#endif /*Related to first (#if ISR ==ISR_EN)*/
	/*------------------------------------*/

/**************************************/
#elif  MOOD==CTC_MOOD
/**************************************/
	TCCR0_REG->TCCR0_WGM00 = ZERO;
	TCCR0_REG->TCCR0_WGM01 = ONE;
	TCNT0_REG = PRELOAD;
	OCR0_REG  = CTC_MOOD_VAL ;


	TCCR0_REG->TCCR0_COM = CTC_COMPARE_MATCH;

	/*------------------------------------*/

#if ISR == ISR_EN
	/*enabel  NORMAL_MOOD interrupt*/
	TIMSK_REG->TIMSK_OCIE0 = ONE ;
#endif /*Related to sec (#if ISR ==ISR_EN)*/
	/*------------------------------------*/


/**************************************/
#elif  MOOD==PWM_MOOD
/**************************************/
	DIO_voidSetPinDirection(PORTB_ID,PIN3,PIN_OUTPUT);
	TCCR0_REG->TCCR0_WGM00=1;
	TCCR0_REG->TCCR0_WGM01=1;

	TCCR0_REG->TCCR0_COM = PWM_COMPARE_MATCH;


	/**************************************/
#endif /*Related to (#if MOOD==NORMAL_MOOD) and (#elif MOOD==CTC_MOOD) and (#elif MOOD==PWM_MOOD) */
	/**************************************/



}

/*****************************************************************************/
void TIMER0_VoidStop(void)
{
	TCCR0_REG->TCCR0_CS0=No_FREQ;

}


/*****************************************************************************/
void TIMER0_VoidStart(void)
{

	TCCR0_REG->TCCR0_CS0=PRESCALER;

}

/*****************************************************************************/
void TIMER0_VoidSetPreload(u8 copy_u8PRELOAD )
{

	TCNT0_REG=copy_u8PRELOAD;
}

/*****************************************************************************/

u8 TIMER0_VoidVal(void )
{

	return  TCNT0_REG ;
}

/*****************************************************************************/
void TIMER0_VoidSetPWMCompareMatch(u8 copy_u8Val )
{
#if PWM_COMPARE_MATCH == CLEAR_ON_COMPARE_MATCH_SET_ON_TOP
	//OCR0_REG =   ( ( (f32)copy_u8Val / 100 ) * (255) );
	  OCR0_REG =   ( ( (u32)copy_u8Val * 255 ) / (100) );

#elif PWM_COMPARE_MATCH == SET_ON_COMPARE_MATCH_CLR_ON_TOP
	//OCR0_REG = (255) - ( ( (f32)copy_u8Val / 100 ) * (255) ) ;
	  OCR0_REG = (255) - ( ( (u32)copy_u8Val * 255 ) / (100) ) ;
#endif
}

/*****************************************************************************/


/*
 * watch dog timer IN TIMER_1
 */
void WDT_VoidEnabel(void )
{

	//SET_BIT(WDTCR_,3);
	WDTCR_REG->WDTCR_WDE=1;
}

void WDT_VoidDisEnabel(void )
{
//	WDTCR_==(1<<4)|(1<<3);
//	WDTCR_=0 ;

WDTCR_REG->WDTCR=(1<<4)|(1<<3);
WDTCR_REG->WDTCR_WDE=0;
}
void WDT_VoidSleep(u8 sleep_time )
{

	//WDTCR_=(WDTCR_&0xF8) |sleep_time ;

	WDTCR_REG->WDTCR_WDP=sleep_time;

}


