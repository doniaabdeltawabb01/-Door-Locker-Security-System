/*
 * DC_Motor.h
 *
 *  Created on: Oct 11, 2023
 *      Author: Donia
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include"std_types.h"
#include"gpio.h"
//defines
#define MOTOR_PORT_ID                PORTC_ID
#define MOTOR_PIN1_ID                PIN5_ID
#define MOTOR_PIN2_ID                PIN4_ID
#define SPEED_OFF                     0
#define SPEED_QAUR                   64
#define SPEED_HALF                   128
#define SPEED_SEMI_FULL              192
#define SPEED_FULL                   254
//Enum
typedef enum{
	STOP,A_CW,CW
}DcMotor_State ;
//Prototypes

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);



#endif /* DC_MOTOR_H_ */
