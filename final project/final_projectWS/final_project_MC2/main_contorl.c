/*
 * main_contorl.c
 *
 *  Created on: Oct 31, 2023
 *      Author: Donia
 */

#include"main_control.h"

uint16 count1;
uint8 falsecounter;
UART_ConfigType UART_Configurations={BIT_8,DISABLED,STOP_BIT1,9600};
TWI_ConfigType TWI_Configurations={ADDRESS,BIT_RATE};
Timer1_ConfigType timer1_Configurations_CTC={0,7812,PRESCALER1024, COMPARE};

int main(void)
{
	SREG|=(1<<7);//Global interrupt enable

	/* Initialize the TWI/I2C Driver */
	TWI_init(&TWI_Configurations);
	Buzzer_init();
	DcMotor_Init();
	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_init(&UART_Configurations);

	uint8 num1[5]={0},num2[5]={0},verifed=0,command=0;

	Timer1_setCallBack(timer_count_CTC);

	while(verifed==0)
	{
		recive_pass(num1);//Receive the 1st pass
		recive_pass(num2);//Receive the 1st pass
		verifed=check_numbers(num1,num2);//compare the 2 pass
		UART_sendByte(verifed);//send the 2 pass are matched or not
		_delay_ms(500);
	}
//if matched it will be saved in eeprom
	store_eeprom(num1);

	while(1)
	{
		//main options
		uint8 pass[5]={0};
		command = UART_recieveByte();//receive option 1 or 2
		_delay_ms(500);

		//read the saved password from eeprom
		read_eeprom(pass);
		//option 1
		if (command == '+')
		{
			recive_pass(num1);//receive the entered pass
			verifed = 0;
			verifed=check_numbers(num1,pass);//compare it with saved one

			if (verifed)
			{
				//if the 2 passwords are matched
				falsecounter=0;
				UART_sendByte(1);
				_delay_ms(500);
				rotate_motor();//open door
			}

			else
			{
				//if 2 passwords unmatched
				UART_sendByte(0);
				_delay_ms(500);
				falsecounter++;
				UART_sendByte(falsecounter);//send the counter to HMI
				_delay_ms(500);
				if (falsecounter >= 3)
				{
					//If the two passwords are not matched for the third consecutive time,
					falsecounter=0;
					unmatched_pass();//buzzer on
				}
			}
		}
		//option 2
		else if(command=='-'){

			recive_pass(num1);//receive the pass from HMI
			verifed = 0;
			verifed=check_numbers(num1,pass);//compare it with saved
			UART_sendByte(verifed);
			_delay_ms(500);
			if(verifed)
			{
				//change password
				falsecounter=0;
				recive_pass(num1);//take 1st pass
				recive_pass(num2);//take 2nd pass
				verifed=check_numbers(num1,num2);//check password matched
				UART_sendByte(verifed);

				if(verifed)
				{
					//if matched save it to eeprom
					store_eeprom(num1);
				}
			}
			else
			{
				//if the 2 passwords unmatched
				falsecounter++;
				UART_sendByte(falsecounter);//send the counter to HMI
				if (falsecounter >= 3)
				{
					unmatched_pass();//buzzer on
					falsecounter=0;
				}
			}

		}
	}
}




void recive_pass(uint8 *num)
{
	//recive the password by UART
	uint8 i=0;

	for (i=0 ; i<5 ; i++)
	{
		num[i]=UART_recieveByte();

	}
	_delay_ms(200);
}
uint8 check_numbers(uint8 *array1,uint8 *array2)
{
	//check if the 2 passwords are the same
	uint8 i=0;
	for (i=0 ; i<5 ; i++)
	{
		if (array1[i] != array2[i])
		{
			return 0;
		}
	}
	return 1;
}


void rotate_motor(void)
{
	//open the door
	Timer1_init(&timer1_Configurations_CTC);//timer on
	DcMotor_Rotate(CW, SPEED_FULL );
	while(count1<15);
	count1=0;
	DcMotor_Rotate(STOP,SPEED_OFF);
	while(count1<3);
	count1=0;
	DcMotor_Rotate(A_CW, SPEED_FULL );
	while(count1<15);
	count1=0;
	DcMotor_Rotate(STOP,SPEED_OFF);
	Timer1_deInit();
}


void unmatched_pass(void)
{
	Timer1_init(&timer1_Configurations_CTC);//timer on
	Buzzer_on();
	while (count1 <60);
	Buzzer_off();
	count1=0;
	Timer1_deInit();//timer off
}


void timer_count_CTC(void)
{
	count1++;
}

void store_eeprom (uint8 *arr)
{
	for(int j=0;j<5;j++)
	{
		EEPROM_writeByte(0X0211 + j,arr[j]);
		_delay_ms(100);
	}
}


void read_eeprom(uint8 *arr)
{
	for(int j=0;j<5;j++)
	{
		EEPROM_readByte(0x0211 + j, &arr[j]);
		_delay_ms(100);
	}
}

