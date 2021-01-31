/*
 * File:   lab1.c
 * Author: Helder Ovalle
 *
 * Created on 30 de enero de 2021, 02:55 PM
 */

//******************************************************************************
// Importación de librerías
//******************************************************************************

#include <xc.h>

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
// Palabra de configuración
//******************************************************************************

//******************************************************************************
// Variables
//******************************************************************************

#define _XTAL_FREQ  8000000
#define LED_ROJO PORTEbits.RE0
#define LED_AMARILLO PORTEbits.RE1
#define LED_VERDE PORTEbits.RE2

unsigned char check = 0;
unsigned int J1 = 0;
unsigned int J2 = 0;

//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void semaforo(void);
void setup(void);
//******************************************************************************
// Ciclo principal
//******************************************************************************
void main(void) {
    


    //**************************************************************************
    // Loop principal
    //**************************************************************************
    setup();
    while (1) {
    
        if (PORTAbits.RA0 == 0){
            __delay_ms(50);
            if (PORTAbits.RA0 == 1) { 
            semaforo();
            }
        }
    }
}
//******************************************************************************
// Configuración
//******************************************************************************
void setup(void){
    TRISE = 0;
    PORTE = 0;
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0b00000111;
    PORTA = 0;
    TRISC = 0;
    PORTC = 0;
    TRISD = 0;
    PORTD = 0;
}

//******************************************************************************
// Funciones
//******************************************************************************
void semaforo(void) {
    //PORTC = 0;
    //PORTD = 0;
    LED_ROJO = 1;
    __delay_ms(500);
    LED_ROJO = 0;
    LED_AMARILLO = 1;
    __delay_ms(500);
    LED_AMARILLO = 0;
    LED_VERDE = 1;
    __delay_ms(500);
    LED_VERDE = 0; 
    //check = 1;
}

void avance(void) {
    while (check == 1){
        if (PORTAbits.RA1 == 0){
            __delay_ms(50);
            if(PORTAbits.RA1 == 1) {
                if (PORTC == 0){
                    J1 = 0b00000001;
                    PORTC = J1;
            }
            if (PORTC != 0){
                J1 = J1*2;
                PORTC = J1;
            }
            if (PORTCbits.RC7 == 1){
                check = 0;
            }
        }
    }
        if (PORTAbits.RA2 == 0){
            __delay_ms(50);
            if(PORTAbits.RA2 == 1) {
                if (PORTD == 0){
                    J2 = 0b00000001;
                    PORTD = J2;
            }
            if (PORTD != 0){
                J2 = J2*2;
                PORTD = J2;
            }
            if (PORTDbits.RD7 == 1){
                check = 0;
            }
            }
        }
    }
}
