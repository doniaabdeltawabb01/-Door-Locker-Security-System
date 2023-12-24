/*
 * main_HMI.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Donia
 */

#ifndef MAIN_HMI_H_
#define MAIN_HMI_H_
/*
 * includes
 */

#include"lcd.h"
#include"keypad.h"
#include"gpio.h"
#include"timer1.h"
#include"uart.h"
#include<avr/io.h>
#include"util/delay.h"
/*
 * prototypes
 */

void creat_password(uint8 *num1);
void send_pass(uint8 *number); //send
void main_options(void); // options
void main_choice1(void);
void timer_count_CTC(void); //handler
void unmatched_pass(void); // false

#endif /* MAIN_HMI_H_ */
