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
#include "SPI.h"

//******************************************************************************
// Variables
//******************************************************************************
#define _XTAL_FREQ 8000000
uint8_t conta = 0;

//******************************************************************************
//Portotipos de funciones
//******************************************************************************
void setup();

//******************************************************************************
// COdigo de interrupcion
//******************************************************************************
void __interrupt() isr(void){
    if(SSPIF == 1){
        spiWrite(conta);
        SSPIF = 0;
        //Mandarlo al SPI
    }
}
//******************************************************************************
// Ciclo principal
//******************************************************************************
void main(void){
    setup();
    //**************************************************************************
    // Loop principal
    //**************************************************************************
    while(1){
        if (PORTBbits.RB0 == 0){
            __delay_ms(100);
            if (PORTBbits.RB0 == 1){
                conta ++;
                PORTD = conta;
            }
        }
        if (PORTBbits.RB1 == 0){
            __delay_ms(100);
            if (PORTBbits.RB1 == 1){
                conta --;
                PORTD = conta;
            }
        }
    }
}
//******************************************************************************
// Configuración
//******************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    
    
    TRISB = 3;
    TRISD = 0;
    
    //Steo los puertos
    PORTB = 0;
    PORTD = 0;
    
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
   
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, 
            SPI_IDLE_2_ACTIVE);

}


