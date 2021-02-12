#include <xc.h>
#include <pic16f887.h>
#include "USART.h"

void _baudios(void){
    SPBRG = 12; //9600 baudios para 8MHZ
}
//Configuracion dada en el datasheet
void config_txsta(void){
    TXSTAbits.CSRC = 0;
    TXSTAbits.TX9 = 0;
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 0;
    TXSTAbits.TRMT = 0;
    TXSTAbits.TX9D = 0;
}
//Configuracion dada en el datasheet
void config_rcsta(void){
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.SREN = 0;
    RCSTAbits.CREN = 1;
    RCREG = 0;  
}
//Extraido de https://electrosome.com/uart-pic-microcontroller-mplab-xc8/
void Write_USART(uint8_t a){
    while(!TRMT);
    TXREG=a;
}
void Write_USART_String(char *a){
    uint8_t i;
    for(i=0;a[i]!='\0';i++){
        Write_USART(a[i]);
    }
}
uint8_t Read_USART(){
  while(!RCIF);
  return RCREG;
} 