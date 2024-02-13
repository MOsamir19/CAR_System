/*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*
 *==================******************************************================*/
 /*****************************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


/******************************************************************/

enum ADC_PRSCALLER
{
	PRSCALLER_2   = 0b001 ,
	PRSCALLER_4   = 0b010 ,
	PRSCALLER_8   = 0b011 ,
	PRSCALLER_16  = 0b100 ,
	PRSCALLER_32  = 0b101 ,
	PRSCALLER_64  = 0b110 ,
	PRSCALLER_128 = 0b111
};

/******************************************************************/

enum ADC_VREFF
{
	AREF_INTERNAL_VREF_TURNED_Off = 0b00 ,
	AVCC                          = 0b01 ,
	INTERNAL_2_5V                 = 0b11

};



/******************************************************************/
enum ADC_EN
{
	D_EN = 0,
	EN   = 1
};

/******************************************************************/
enum TRIGGER_S
{
	  FREE_RUNNING_MODE            = 0b000      ,
	  ANALOG_COMPARATOR            = 0b001      ,
	  EXTERNAL_INTERRUPT_RUQUEST0  = 0b010      ,
	  TIMER0_COMPARE_MATCH         = 0b011      ,
	  TIMER0_OVERFLOW              = 0b100      ,
	  TIMER1_COMPARE_MATCHB        = 0b101      ,
	  TIMER1_OVERFLOW              = 0b110      ,
	  TIMER1_CAPTURE_EVENT         = 0b111
};

/******************************************************************/


#define RIGHT_DATA   0b0
#define LEFT_DATA    0b1


/******************************************************************/

#define ADCH       ( *((volatile u8*)0x025)  )
#define ADCL       ( *((volatile u8*)0x024)  )
#define ADC_DATA   ( *((volatile u16*)0x024) )

/******************************************************************/

typedef struct
{
	u8 MUX   : 5 ;
	u8 ADLAR : 1 ;
	u8 REFS  : 2 ;

}ADMUX;

#define ADMUX_REG ((volatile ADMUX*)0x27)


/******************************************************************/

typedef  struct
{
	u8 ADPS :3;
	u8 ADIE :1;
	u8 ADIF :1;
	u8 ADATE:1;
	u8 ADSC :1;
	u8 ADEN :1;


}ADCSRA;
#define ADCSRA_REG   ((volatile ADCSRA*)0x26)


/******************************************************************/

typedef  struct
{
	u8            :5;
	u8 SFIOR_ADTS :3;


}SFIOR;
#define SFIOR_REG   ((volatile SFIOR*)0x50)

/*Special FunctionIO Register –SFIOR*/



/******************************************************************/



#endif /* ADC_PRIVATE_H_ */
