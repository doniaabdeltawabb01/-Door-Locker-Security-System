/*
 * buzzer.c
 *
 *  Created on: Oct 30, 2023
 *      Author: Donia
 */
#include "buzzer.h"
/*
 * ⮚ Setup the direction for the buzzer pin as output pin through the
GPIO driver.
⮚ Turn off the buzzer through the GPIO.
 */
 void Buzzer_init(){
	 /*
	  * SET THE pin as output
	  */
	 GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
	 /*
	  * TURN OFF the buzzer
	  */
	 GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);

 }
 void Buzzer_on(void){
	 /*
	  * TURN ON the buzzer
	  */
	 GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);

 }
 void Buzzer_off(void){
	 /*
	  * TURN OFF the buzzer
	  */
	 	 GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);

 }
