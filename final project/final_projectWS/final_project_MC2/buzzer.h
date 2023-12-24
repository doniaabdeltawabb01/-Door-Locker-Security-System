/*
 * buzzer.h
 *
 *  Created on: Oct 30, 2023
 *      Author: Donia
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include"gpio.h"

#define BUZZER_PORT_ID       PORTB_ID
#define BUZZER_PIN_ID          PIN0_ID

/*
 * Prototypes
 */
 void Buzzer_init();
 void Buzzer_on(void);
 void Buzzer_off(void);


#endif /* BUZZER_H_ */
