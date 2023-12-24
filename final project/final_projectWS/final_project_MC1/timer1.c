/*
 * timer1.c
 *
 *  Created on: Oct 29, 2023
 *      Author: Donia
 */

#include"timer1.h"
#include"common_macros.h"
#include<avr/io.h>
#include <avr/interrupt.h>
#include"std_types.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

#if(TIMER1_CTC==1)
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
#elif (TIMER1_OVERFLOW ==1)
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
#endif
/*Timer1_init
 *Description
⮚ Function to initialize the Timer driver
Inputs: pointer to the configuration structure with type
Timer1_ConfigType
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr){

	/*FOC1A/FOC1B bits are only active when the WGM13:0 bits specifies a non-PWM mode
	 */
	SET_BIT(TCCR1A,FOC1A); /* for non-PWM mode */
	SET_BIT(TCCR1A,FOC1B);



/*
 * to get the mode we have 2 bits in TCCR1A and 2 bits in TCCR1B so the number give has 4 bits
 * FOR TCCR1A 0011 & MODE GIVEN
 * FOR TCCR1B 1100 & MODE GIVEN and move to the left 3
 * FOR TCCR1B GIVEN THE prescaler
 * TCNT1 take the initial value
 * OCR1A and OCR1B IS THE COMPARE VALUE IN THE COMAPRE REGISTER
 * For TIMSK We have 2 compare match interrupt and 1 for the overflow
 */

	TCCR1B=(Config_Ptr->prescaler);
	TCNT1=(Config_Ptr->initial_value);

	if( (Config_Ptr -> mode) == NORMAL )
	{
		/* Enable interrupts for overflow mode */
		SET_BIT(TIMSK,TOIE1);
		/* Enable overflow flag */
		SET_BIT(TIFR,TOV1);
	}
	else if ( (Config_Ptr -> mode) == COMPARE )
	{
		SET_BIT(TCCR1B,WGM12);
		OCR1A = Config_Ptr ->compare_value;
		SET_BIT(TIMSK,OCIE1A); /* enable interrupts for CTC mode */
		SET_BIT(TIFR,OCF1A); /* enable CTC flag */
	}
	/*
	 * don't forget the global interrupt*/


}
/*Timer1_deInit
 * ● Description
⮚ Function to disable the Timer1.
 */
void Timer1_deInit(void){
	/*
	 * To stop the TIMER
	 */
	TCCR1B&=~(1<<CS12)&~(1<<CS10)&~(1<<CS11);
}
/*Timer1_setCallBack
 *Description
⮚ Function to set the Call Back function address.
Inputs: pointer to Call Back function.
 */
void Timer1_setCallBack(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
		g_callBackPtr = a_ptr;
}
