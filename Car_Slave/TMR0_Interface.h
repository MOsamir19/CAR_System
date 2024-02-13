/*
 * TMR0_Interface.h
 *
 *  Created on: Nov 12, 2022
 *      Author: General
 */

#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_

void TIMER0_VoidInit(void);
void TIMER0_VoidStop(void);
void TIMER0_VoidStart(void);
void TIMER0_VoidSetPreload(u8 copy_u8PRELOAD );
u8 TIMER0_VoidVal(void );



//void TIMER0_Void(u8 copy_u8PRELOAD );
void TIMER0_VoidSetPWMCompareMatch(u8 copy_u8Val );

void TIMER_voidSetCallBack(  void (*ptr_timer)(void) );


void WDT_VoidEnabel(void );
void WDT_VoidDisEnabel(void );
void WDT_VoidSleep(u8 sleep_time );

#endif /* TMR0_INTERFACE_H_ */
