/*
 * File:   contador.c
 * Author: Helder Ovalle
 *
 * Created on 21 de febrero de 2021, 01:36 PM
 */
//Basados en la implementación de comunicación SPI de Pablo 
//******************************************************************************
// Palabra de configuración
//******************************************************************************
// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

//******************************************************************************
// Importación de librerías
//******************************************************************************
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "SPI.h"

//******************************************************************************
// Variables
//******************************************************************************
#define _XTAL_FREQ 8000000
//uint8_t  = 0;

//******************************************************************************
//Portotipos de funciones
//******************************************************************************
void setup();

//******************************************************************************
// Ciclo principal
//******************************************************************************
void main(void){
    setup();
    //**************************************************************************
    // Loop principal
    //**************************************************************************
    while(1){
        PORTCbits.RC2 = 0;       //Slave Select
        __delay_ms(1);
       
        spiWrite(1);
        PORTB = spiRead();
       
        __delay_ms(1);
         PORTCbits.RC2 = 1;       //Slave Deselect 
      
        __delay_ms(1);
        PORTCbits.RC1 = 0;
        __delay_ms(1);
       
        spiWrite(1);
        PORTD = spiRead();
       
        __delay_ms(1);
        PORTCbits.RC1 = 1; 
        __delay_ms(1);
    }
    return;
}    

//******************************************************************************
// Configuración
//******************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    
    TRISE = 0;
    TRISD = 0;
    //Steo los puertos
    PORTE = 0;
    PORTD = 0;
    
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    //PORTCbits.RC0 = 1;
    PORTCbits.RC1 = 1;
    PORTCbits.RC2 = 1;
    
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, 
            SPI_IDLE_2_ACTIVE);

}


