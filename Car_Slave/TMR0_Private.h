#ifndef _TMR0_REG_H
#define _TMR0_REG_H

/************************************************************************************/
//#define------> for #if cases
#define NORMAL_MOOD  1
#define CTC_MOOD     2
#define PWM_MOOD     3


/************************************************************************************/

#define  ISR_EN       1
#define  ISR_DIS_EN   2


/************************************************************************************/

#define  OC0_ON       1
#define  OC0_OFF      2

/************************************************************************************/

/*
 * OC0_PWM_STAT
 * */
#define  CLEAR_ON_COMPARE_MATCH_SET_ON_TOP   0b10
#define  SET_ON_COMPARE_MATCH_CLR_ON_TOP     0b11


/************************************************************************************/


enum OC0_CTC_STAT
{
	OC0_DISCONNECTED        = 0b00   ,
	OC0_TOGGEL              = 0b01   ,
	CLEAR_ON_COMPARE_MATCH  = 0b10   ,
	SET_ON_COMPARE_MATCH    = 0b11
};

/************************************************************************************/



/************************************************************************************/

enum  PRESCALER
{
	No_FREQ        =  0b000 ,
	No_PRESCALER   =  0b001 ,
	PRESCALER_8    =  0b010 ,
	PRESCALER_64   =  0b011 ,
	PRESCALER_256  =  0b100 ,
	PRESCALER_1024 =  0b101
};


/************************************************************************************/

/*
 * Timer/Counter 0 Control Register
 */

typedef struct
{
	u8 TCCR0_CS0     :3 ;
	u8 TCCR0_WGM01   :1 ;
	u8 TCCR0_COM     :2 ;
	u8 TCCR0_WGM00   :1 ;
	u8 TCCR0_FOC0    :1 ;
}TCCR0;


#define TCCR0_REG  ((volatile TCCR0*) 0x53)

/************************************************************************************/

/*
#define TCCR0_  *((volatile u8*) 0x53)
#define FOC0   (0x07)
#define WGM00  (0x06)
#define COM01  (0x05)
#define COM00  (0x04)
#define WGM01  (0x03)
#define CS02   (0x02)
#define CS01   (0x01)
#define CS00   (0x00)

 */

/************************************************************************************/


/*
 * Timer/Counter 0 Register
 */
#define TCNT0_REG  (*( (volatile u8 *) 0x52))
/************************************************************************************/

/*
 * Timer/Counter 0 Output Compare Register
 */
#define OCR0_REG   (*( (volatile u8 *) 0x5C))
/************************************************************************************/

/*
 * Timer/Counter 0 Interrupt Mask Register
 */
//#define TIMSK_REG  (*( (volatile u8 *) 0x59))
///* Bits from 7 : 2 are not used in this module */
//#define TIMSK_OCIE0  (0x01)
//#define TIMSK_TOIE0  (0x00)
typedef struct
{
	u8 TIMSK_TOIE0    :1 ;
	u8 TIMSK_OCIE0    :1 ;

} TIMSK;

#define TIMSK_REG  ((volatile TIMSK*) 0x59)

/************************************************************************************/

/*
 * Timer/Counter 0 Interrupt Flag Register
 */
#define TIFR   (*( (volatile u8 *) 0x58))
/* Bits from 7 : 2 are not used in this module */
#define TIFR_OCF0   (0x01)
#define TIFR_TOV0   (0x00)

/************************************************************************************/


typedef union
{
	struct
	{
		    u8 WDTCR_WDP   :3 ;
			u8 WDTCR_WDE   :1 ;
			u8 WDTCR_WDTOE :1 ;
	};

	   u8 WDTCR ;


}  WDTCR;


#define WDTCR_REG  ((volatile WDTCR*) 0x41)
//#define WDTCR_  *((volatile u8*) 0x41)
/************************************************************************************/



#endif /* _TMR0_REG_H */
