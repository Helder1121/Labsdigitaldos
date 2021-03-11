/*
 * File:   USART.c
 * Author: betov
 *
 * Created on 22 de febrero de 2021, 07:53 AM
 */
//Extraido de: 
//https://deepbluembedded.com/mpu6050-with-microchip-pic-accelerometer-gyroscope-interfacing-with-pic/
//y combinacion del proyecto pasado que tambien era de: 
////Extraido de https://electrosome.com/
#include <xc.h>
#include "USART.h"
//---------------[ UART Routines ]------------------
//--------------------------------------------------

void UART_TX_Init(void)
{
  BRGH  = 0;   // Set For High-Speed Baud Rate
  SPBRG = 12;  // Set The Baud Rate To Be 9600 bps
  //--[ Enable The Ascynchronous Serial Port ]--
  SYNC = 0;
  SPEN = 1;
  //--[ Set The RX-TX Pins to be in UART mode (not io) ]--
  TX_D = 1;
  RX_D = 1;
  TXEN = 1;  // Enable UART Transmission
}
//Labs pasados
void UART_Write(unsigned char data)
{
  while(!TRMT);
  TXREG = data;
}

void UART_Write_String(char* buf)
{
    int i=0;
    while(buf[i] != '\0')
        UART_Write(buf[i++]);
}