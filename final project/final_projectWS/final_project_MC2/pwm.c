/*
 * pwm.c
 *
 *  Created on: Oct 14, 2023
 *      Author: Donia
 */
#include<avr/io.h>
#include"gpio.h"
#include"pwm.h"
//timer init
void PWM_Timer0_Start(uint8 set_duty_cycle){

	TCNT0 = 0; //Set Timer Initial value
	OCR0  = set_duty_cycle;
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,LOGIC_HIGH);//set PB3/OC0 as output pin
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
