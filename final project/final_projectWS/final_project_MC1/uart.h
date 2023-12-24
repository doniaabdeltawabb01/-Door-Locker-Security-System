#ifndef UART_H_
#define UART_H_

#include "std_types.h"
typedef enum {
	DISABLED,RESERVED,EVEN_PARITY,ODD_PARITY
}UART_PARITY;
typedef enum {
	STOP_BIT1,STOP_BIT2
}UART_STOPBIT;
typedef enum{
	BIT_5,BIT_6,BIT_7,BIT_8,RESEVED1,RESEVED2,RESEVED3,BIT_9
}UART_BITDATA;
typedef uint32 UART_BaudRate;
typedef struct{
	UART_BITDATA bit_data;
	UART_PARITY parity;
	UART_STOPBIT stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;
//prototypes
void UART_init(const UART_ConfigType *Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */









