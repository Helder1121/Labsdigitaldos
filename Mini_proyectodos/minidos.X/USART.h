/* 
 * File:   
 * Author: Helder Ovalle 
 * Comments:
 * Revision history: 
 */
#define _XTAL_FREQ  16000000

#define BaudRate    57800
#define TX_D        TRISC6
#define RX_D        TRISC7

//-----------[ Functions' Prototypes ]--------------

//---[ UART Routines ]---

void UART_TX_Init(void);
void UART_Write(unsigned char);
void UART_Write_String(char*);

