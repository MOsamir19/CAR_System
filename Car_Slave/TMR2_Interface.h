/*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*
 *==================******************************************================*/


#ifndef TMR2_INTERFACE_H_
#define TMR2_INTERFACE_H_



void TIMER2_VoidInit(void);
void TIMER2_VoidStop(void);
void TIMER2_VoidStart(void);
void TIMER2_VoidSetPreload(u8 copy_u8PRELOAD );
u8 TIMER2_VoidVal(void );




//void TIMER0_Void(u8 copy_u8PRELOAD );
void TIMER2_VoidSetPWMCompareMatch(u8 copy_u8Val );

void TIMER2_voidSetCallBack(  void (*ptr_timer)(void) );




#endif /* TMR0_INTERFACE_H_ */
