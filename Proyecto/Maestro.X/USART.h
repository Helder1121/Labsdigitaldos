#ifndef __UART_H_
#define	__UART_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void _baudios(void);
void config_txsta(void);
void config_rcsta(void);
uint8_t Read_USART();
void Write_USART_String(char *a);
void Write_USART(uint8_t a);
#endif	/* __UART_H_ */