
 /*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*
 *==================******************************************================*/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "TMR2_Interface.h"
#include "TMR2_Private.h"
#include "TMR2_Config.h"
#include "DIO_Interface.h"



/**********************************************************************************
 *********************************************************************************/

#if ISR2 ==ISR2_EN

//global pointer to fun
static void (*TIMER2_callBack)(void);

//call back fun
void TIMER2_voidSetCallBack(  void (*ptr_timer)(void) )
{

	if(ptr_timer!=NULL)
	{
		TIMER2_callBack=ptr_timer ;
	}
}


#if MOOD2== NORMAL2_MOOD
void __vector_5 () __attribute__  ((signal));
void __vector_5 ()
{

	TIMER2_callBack();

}

#elif MOOD2== CTC2_MOOD
void __vector_4 () __attribute__ ((signal));
void __vector_4 ()
{

	TIMER2_callBack();

}

#endif /*Related to  (#if MOOD== NORMAL_MOOD) and (#elif MOOD== CTC_MOOD)*/




#endif /*Related to  (#if ISR ==ISR_EN)*/
/**********************************************************************************
 *********************************************************************************/



/**********************************************************************************
 *********************************************************************************/
void TIMER2_VoidInit(void)
{

/**************************************/
#if MOOD2==NORMAL2_MOOD
/**************************************/
	TCCR2_REG->TCCR2_WGM00 = ZERO;
	TCCR2_REG->TCCR2_WGM01 = ZERO;
	TCNT2_REG=PRELOAD2;
	/*------------------------------------*/
#if ISR2 == ISR2_EN
	/*enabel  NORMAL_MOOD interrupt*/
	TIMSK2_REG->TIMSK2_TOIE0 = ONE ;
#endif /*Related to first (#if ISR ==ISR_EN)*/
	/*------------------------------------*/

/**************************************/
#elif  MOOD2==CTC2_MOOD
/**************************************/
	TCCR2_REG->TCCR2_WGM00 = ZERO;
	TCCR2_REG->TCCR2_WGM01 = ONE;
	TCNT2_REG = PRELOAD2;
	OCR2_REG  = CTC2_MOOD_VAL ;


	TCCR2_REG->TCCR2_COM = CTC2_COMPARE_MATCH;

	/*------------------------------------*/

#if ISR2 == ISR2_EN
	/*enabel  NORMAL_MOOD interrupt*/
	TIMSK2_REG->TIMSK2_OCIE0 = ONE ;
#endif /*Related to sec (#if ISR ==ISR_EN)*/
	/*------------------------------------*/


/**************************************/
#elif  MOOD2==PWM2_MOOD
/**************************************/
	DIO_voidSetPinDirection(PORTD_ID,PIN7,PIN_OUTPUT);
	TCCR2_REG->TCCR2_WGM00=1;
	TCCR2_REG->TCCR2_WGM01=1;

	TCCR2_REG->TCCR2_COM = PWM2_COMPARE_MATCH;


	/**************************************/
#endif /*Related to (#if MOOD==NORMAL_MOOD) and (#elif MOOD==CTC_MOOD) and (#elif MOOD==PWM_MOOD) */
	/**************************************/



}

/*****************************************************************************/
void TIMER2_VoidStop(void)
{
	TCCR2_REG->TCCR2_CS0=No2_FREQ;

}


/*****************************************************************************/
void TIMER2_VoidStart(void)
{

	TCCR2_REG->TCCR2_CS0=PRESCALER2;

}

/*****************************************************************************/
void TIMER2_VoidSetPreload(u8 copy_u8PRELOAD )
{

	TCNT2_REG=copy_u8PRELOAD;
}

/*****************************************************************************/

u8 TIMER2_VoidVal(void )
{

	return  TCNT2_REG ;
}

/*****************************************************************************/
void TIMER2_VoidSetPWMCompareMatch(u8 copy_u8Val )
{
#if PWM_COMPARE_MATCH == CLEAR_ON_COMPARE_MATCH_SET_ON_TOP
	//OCR2_REG =   ( ( (f32)copy_u8Val / 100 ) * (255) );
	  OCR2_REG =   ( ( (u32)copy_u8Val * 255 ) / (100) );

#elif PWM_COMPARE_MATCH == SET_ON_COMPARE_MATCH_CLR_ON_TOP
	//OCR2_REG = (255) - ( ( (f32)copy_u8Val / 100 ) * (255) ) ;
	  OCR2_REG = (255) - ( ( (u32)copy_u8Val * 255 ) / (100) ) ;
#endif
}

/*****************************************************************************/





