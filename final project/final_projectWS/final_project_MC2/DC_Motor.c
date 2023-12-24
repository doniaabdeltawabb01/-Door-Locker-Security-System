/*
 * DC_Motor.c
 *
 *  Created on: Oct 11, 2023
 *      Author: Donia
 */
#include"DC_Motor.h"
#include<avr/io.h>
#include"gpio.h"
#include"pwm.h"

void DcMotor_Init(void){
	//set up the motor pins direction
	GPIO_setupPinDirection(MOTOR_PORT_ID,MOTOR_PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID,MOTOR_PIN2_ID,PIN_OUTPUT);
	/*Stop the motor at first*/
	GPIO_writePin (MOTOR_PORT_ID,MOTOR_PIN1_ID,LOGIC_LOW);
	GPIO_writePin (MOTOR_PORT_ID,MOTOR_PIN2_ID,LOGIC_LOW);

}
void DcMotor_Rotate(DcMotor_State state,uint8 speed){

	if (state == STOP)
	{
		/*Stop the motor*/
		GPIO_writePin (MOTOR_PORT_ID,MOTOR_PIN1_ID,LOGIC_LOW);
		GPIO_writePin (MOTOR_PORT_ID,MOTOR_PIN2_ID,LOGIC_LOW);
	}

	else if (state == CW)
	{
		/*Rotate Clockwise*/
		GPIO_writePin (MOTOR_PORT_ID,MOTOR_PIN1_ID,LOGIC_LOW);
		GPIO_writePin (MOTOR_PORT_ID,MOTOR_PIN2_ID,LOGIC_HIGH);
	}

	else if (state == A_CW)
	{
		/*Rotate AntiClockwise*/
		GPIO_writePin (MOTOR_PORT_ID,MOTOR_PIN1_ID,LOGIC_HIGH);
		GPIO_writePin (MOTOR_PORT_ID,MOTOR_PIN2_ID,LOGIC_LOW);
	}
	PWM_Timer0_Start(speed);//set the speed by the timer


}
