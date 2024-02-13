/*
 * TMR0_Config.h
 *
 *  Created on: Nov 12, 2022
 *      Author: General
 */


#ifndef TMR0_CONFIG_H_
#define TMR0_CONFIG_H_


/***************************************************************************************/
#define  PRELOAD   0

/***************************************************************************************/

/*
 * NORMAL_MOOD
 * CTC_MOOD
 * PWM_MOOD
 * */
#define MOOD  PWM_MOOD
/***************************************************************************************/

/*
 * ISR_EN
 * ISR_DIS_EN
 */


#if (MOOD==CTC_MOOD) ||(MOOD==NORMAL_MOOD)
#define  ISR  ISR_EN
#endif


/***************************************************************************************/

/*
 * CLEAR_ON_COMPARE_MATCH
 * SET_ON_COMPARE_MATCH
 * OC0_TOGGEL
 * OC0_DISCONNECTED
 */

#if  MOOD == CTC_MOOD
#define CTC_COMPARE_MATCH     OC0_TOGGEL
#define  CTC_MOOD_VAL         249
#endif

/***************************************************************************************/

/*
 * CLEAR_ON_COMPARE_MATCH_SET_ON_TOP
 * SET_ON_COMPARE_MATCH_CLR_ON_TOP
 * OC0_DISCONNECTED
 */
#if     MOOD == PWM_MOOD
#define PWM_COMPARE_MATCH       CLEAR_ON_COMPARE_MATCH_SET_ON_TOP
#endif

/***************************************************************************************/
/*
 * No_PRESCALER
 * PRESCALER_8
 * PRESCALER_64
 * PRESCALER_256
 * PRESCALER_1024
 * */

#define PRESCALER   PRESCALER_1024

/***************************************************************************************/


#endif /* TMR0_CONFIG_H_ */
