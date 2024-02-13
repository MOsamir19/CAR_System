/*
 * TIMER1_private.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef TIMER1_TIMER1_PRIVATE_H_
#define TIMER1_TIMER1_PRIVATE_H_

#define TCCR1A_REG   *((volatile u8 *)0x4F)
#define WGM10         0
#define WGM11         1
#define COM1A0        6
#define COM1A1        7

#define TCCR1B_REG   *((volatile u8 *)0x4E)
#define WGM12         3
#define WGM13         4
#define CS10          0
#define CS11          1
#define CS12          2


#define OCR1A_REG    *((volatile u16 *)0x4A)
#define ICR1_REG     *((volatile u16 *)0x46)



#endif /* TIMER1_TIMER1_PRIVATE_H_ */
