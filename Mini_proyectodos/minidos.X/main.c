/*
 * File:   main.c
 * Author: Helder Ovalle
 *
 * Created on 8 de marzo de 2021, 10:53 AM
 */

//******************************************************************************
// Palabra de configuración
//******************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR21V   // Brown-out Reset Selection bit (Brown-out Reset set to 2.1V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

//******************************************************************************
// Importación de librerías
//******************************************************************************
#include <xc.h>
#include <stdio.h>
//#include "config.h"
#include "USART.h"
#include "MPU.h"
#include "I2c.h"
//******************************************************************************
// Variables
//******************************************************************************
#define _XTAL_FREQ 8000000
//******************************************************************************
// Ciclo principal
//******************************************************************************
void main(void){
       
    UART_TX_Init();
    TRISD2 = 0;    // LED Indicador
    TRISB = 0;     // Leds conectadas para demostrar la variable ay
    ANSELH = 0;
    
    MPU6050_Init();
    //**************************************************************************
    // Loop principal
    //**************************************************************************
    while(1)
	{
        RD2 = ~RD2;  // Blink LED verde
        MPU6050_Read();
        __delay_ms(50);
    }
    return;
}
//Se hizo con oscilador externo al inicio pero no era tan establa y mejor se 
//hizo con uno interno.