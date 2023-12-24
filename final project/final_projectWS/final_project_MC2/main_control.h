#include "uart.h"
#include"util/delay.h"
#include "external_eeprom.h"
#include"twi.h"
#include"DC_Motor.h"
#include<avr/io.h>
#include"buzzer.h"
#include"timer1.h"


void recive_pass(uint8 *num);
uint8 check_numbers(uint8 *array1,uint8 *array2);
void rotate_motor(void);//open
void unmatched_pass(void);//false
void timer_count_CTC(void);//handler
void store_eeprom (uint8 *arr);//store
void read_eeprom(uint8 *arr);//read eeprom
