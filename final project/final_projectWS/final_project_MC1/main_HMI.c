#include "main_HMI.h"
/*
 * global variables and configurations
 */
uint8 count1;
UART_ConfigType UART_Configurations={BIT_8,DISABLED,STOP_BIT1,9600};
Timer1_ConfigType timer1_Configurations_CTC={0,7812,PRESCALER1024, COMPARE};
int main(void)
{

	SREG |= (1<<7);//enable the global intr
	uint8 num1[5]={0},num2[5]={0},verifed=0,command=0;
	/*
	 * LCD &UART init and set call back
	 */
	LCD_init();
	UART_init(&UART_Configurations);
	Timer1_setCallBack(timer_count_CTC);

	while (verifed == 0)
	{
		LCD_clearScreen();
		LCD_displayString("Plz enter pass: ");
		LCD_moveCursor(1,0);
		creat_password(num1);//Receive the first pass
		_delay_ms(50);
		send_pass(num1);//send the first pass


		LCD_clearScreen();
		LCD_displayString("Enter same pass: ");
		LCD_moveCursor(1,0);

		creat_password(num2);//Receive the 2nd pass
		_delay_ms(50);
		send_pass(num2);//send the 2nd pass

		verifed = UART_recieveByte();//if the 2 passwords matched the verifed=1 if not verified=0
		_delay_ms(50);
	}

	_delay_ms(500);

	while(1)
	{
		/*
		 * The LCD will always display the main system option:
		 *
		 */
		main_options();

		command = KEYPAD_getPressedKey(); //takes the command form the keypad
		_delay_ms(50);
		UART_sendByte(command);
		_delay_ms(500);
		// Open Door = +
		if (command == '+')
		{

			LCD_clearScreen();
			LCD_displayString("Enter your pass: ");
			LCD_moveCursor(1,0);
			creat_password(num1);//take the pass
			_delay_ms(50);
			send_pass(num1);//Receive the password
			_delay_ms(500);
			verifed=0;
			verifed = UART_recieveByte();// if the password matched with the old one

			if (verifed)
			{
				main_choice1();
			}

			else
			{
				// if the 2 passwords do not match
				//receive the counter for the control
				uint8 falsecounter = UART_recieveByte();
				//  two passwords are not matched for the third consecutive time,
				if (falsecounter >= 3)
				{
					unmatched_pass();
					falsecounter=0;
				}

				else
				{

					LCD_clearScreen();
					LCD_displayString("Wrong Pass");
					_delay_ms(500);
				}

			}
		}

		if (command == '-')
		{


			LCD_clearScreen();
			LCD_displayString("Enter your pass: ");
			LCD_moveCursor(1,0);
			creat_password(num1);//take the pass
			_delay_ms(50);
			send_pass(num1);//send the pass
			_delay_ms(500);
			verifed=0;
			verifed = UART_recieveByte();// if the password matched with the old one


			if (verifed)
			{
				//change password
				LCD_clearScreen();
				LCD_displayString("Enter new pass: ");
				LCD_moveCursor(1,0);
				creat_password(num1);//enter new pass
				_delay_ms(50);
				send_pass(num1);//send new pass


				LCD_clearScreen();
				LCD_displayString("Enter same pass:");
				LCD_moveCursor(1,0);
				creat_password(num2);//re-enter new pass
				_delay_ms(50);
				send_pass(num2);//send the pass
				verifed=0;
				verifed = UART_recieveByte();
				if(verifed==0){
					//if the 2 passwords aren't matched
					LCD_clearScreen();
					LCD_displayString("Unmatched pass");
					LCD_moveCursor(1,0);
					LCD_displayString("Pass unchanged");
					_delay_ms(1500);
				}
				else{
					//if the 2 passwords are matched
					LCD_clearScreen();
					LCD_displayString("Password");
					LCD_moveCursor(1,0);
					LCD_displayString("changed");
					_delay_ms(1500);
				}
			}

			else
			{
				// if the 2 passwords do not match
				//receive the counter for the control
				uint8 falsecounter = UART_recieveByte();
				if (falsecounter >= 3)
				{
					unmatched_pass();
					falsecounter=0;
				}

				else
				{
					LCD_clearScreen();
					LCD_displayString("Wrong Pass");
					_delay_ms(500);
				}
			}
		}
	}
}

void creat_password(uint8 *num1)
{
	uint8 i=0;
//takes the numbers from the keypad
	for (i=0 ; i<6 ; ++i)
	{
		while ((KEYPAD_getPressedKey() != 13)  &&  (i==5)){};

		num1[i] = KEYPAD_getPressedKey();
		_delay_ms(600);
		LCD_displayCharacter('*');
	}
	_delay_ms(500);
}

void send_pass(uint8 *number)
{
	//send the password with UART
	uint8 i=0;
	for (i=0 ; i<5 ; i++)
	{
		UART_sendByte (number[i]);
	}
	_delay_ms(50);
}

void main_options(void)
{
	//display on the lcd
	LCD_clearScreen();
	LCD_displayString("+ : Open Door ");
	LCD_moveCursor(1,0);
	LCD_displayString("- : Change Pass");
}

void main_choice1(void)
{
	//set the init to start the timer
	Timer1_init(&timer1_Configurations_CTC);
	LCD_clearScreen();
	LCD_displayString("Door unlocking");

	while(count1<15);
	count1=0;
	LCD_clearScreen();
	LCD_displayString("Door opened");

	while(count1<3);
	count1=0;
	LCD_clearScreen();
	LCD_displayString("Door locking");

	while(count1<15);
	count1=0;

	Timer1_deInit();

}

void timer_count_CTC(void)
{
	count1++;
}

void unmatched_pass(void)
{
	Timer1_init(&timer1_Configurations_CTC);
	LCD_clearScreen();
	LCD_displayString ("ERROOOOOOR");//haramiiiiii

	while (count1 <60);
	count1=0;
	Timer1_deInit();
}
