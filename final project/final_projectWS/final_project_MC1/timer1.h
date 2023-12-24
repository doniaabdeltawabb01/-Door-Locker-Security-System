/*
 * timer1.h
 *
 *  Created on: Oct 28, 2023
 *      Author: Donia
 */

#ifndef TIMER1_H_
#define TIMER1_H_
#include"std_types.h"

/*
 * defines
 */

#define TIMER1_CTC          1
#define TIMER1_OVERFLOW    0

/*enum to set the sturct*/
typedef enum
{
	NORMAL , COMPARE
} Timer1_Mode;
typedef enum{
	NO_CLK,PRESCALER1,PRESCALER8,PRESCALER64,PRESCALER256,PRESCALER1024,FALLING,RISING
}Timer1_Prescaler;
/*
 * struct to the init
 */
typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;
/*******************************Function prototypes*************/
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));



#endif /* TIMER1_H_ */
