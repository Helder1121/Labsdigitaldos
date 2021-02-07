/*
 * File:   lab2.c
 * Author: Helder Ovalle
 *
 * Created on 31 de enero de 2021, 10:24 PM
 */

//******************************************************************************
// Importación de librerías
//******************************************************************************
#include <xc.h>
//#include <stdint.h>
#include "ADC.h"
#include "Multiplexado.h"
#define _XTAL_FREQ  4000000 //Delay
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
// Variables
//******************************************************************************
int Contador = 0; //Incremento
int conta = 0;
int banders = 0; 
//valor asignando 
unsigned int valor_adc;
//Nibbles
unsigned int val_high;
unsigned int val_low;

//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void Config_P(void);
void Config_Int(void);
void Banderas(void);
void Sep_Nb(void);
void Display(void);

//******************************************************************************
// Interrupcion
//******************************************************************************
void __interrupt() isr(void){
    //Interrupccion puerto B
    if (INTCONbits.RBIF){
        INTCONbits.RBIF = 0;
        if (PORTBbits.RB0 == 1){
            //Utilice delay en vez de antirebote
            __delay_ms(200);
        }
        //Delay para el puerto RB0
        if (PORTBbits.RB0 == 0){
            Contador++; //Incrementa el contador
            PORTD = Contador;
            __delay_ms(200);
        }
                if (PORTBbits.RB1 == 1){
            __delay_ms(200);
    }
            if (PORTBbits.RB1 == 0){
            Contador--; //Decrementa el contador 
            PORTD = Contador;
            __delay_ms(200);
            }
    }
    
    if (PIR1bits.ADIF) {
        PIR1bits.ADIF = 0;
        
        ADC_READ(8); //Canal 8
        //Comienzo de la conversion del ADC
        __delay_ms(2);
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO !=0){
            //Mientras Go sea diferente de 0 se deplegara en Adresh 
            //el valor del ADC
            valor_adc = ADRESH;
            Display();
        }
    }
    //Configuracion del TMR0
    if (TMR0IF){
        TMR0IF = 0;
        TMR0 = 4; //0.5 MS
        conta++;
    }
}
//******************************************************************************
// Ciclo principal
//******************************************************************************
void main(void) {
    Config_P();
    Config_Int();
    ADC_INIT();
    ADC_INTERRUPCION();
    //**************************************************************************
    // Loop principal
    //**************************************************************************
    while (1) {
        if (conta >= 1){ 
            conta = 0; 
            //Limpiara la var si en dado caso es >=1 
            Banderas();
        }
        //Función de la alarma 
        Sep_Nb();//Separacion de los nibbles 
        if (ADRESH >= PORTD) { //Se prendera el led cuando se mayor 
            PORTEbits.RE0 = 1;
        
        } else { // de lo contrario estara apagado 
            PORTEbits.RE0 = 0;
        }
    }
    //return;
}
        
//******************************************************************************
// Configuración
//******************************************************************************
void Config_P(void){
    TRISD = 0;
    TRISB = 0b00000111;
    TRISA = 0;
    TRISE = 0;
    //Todos estanran como salida menos loas tres de RB0.RB1 Y RB2
    ANSEL = 0;
    ANSELH = 0b00000000; 
    //Unicamente el canal8 
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    //Steo los puertos
}
//******************************************************************************
// Funciones
//******************************************************************************
void Config_Int(void){
    TMR0 = 4;
    OPTION_REG = 0b10000001;//TMR0 1:4
    INTCON = 0b10101001; //Habilitos los GIE
    IOCB = 0b00000011;
}

void Display(void){
    PORTE = 0;//steo el puerto E
    if (banders == 0){
        Multiplexado(val_low);
        PORTEbits.RE1 = 1;
    } else if (banders == 1){
        Multiplexado(val_high);
        PORTEbits.RE2 = 1;
        //Se asignan el valor a cada uno de los puertoE
    }
}

void Banderas(void){
    if (banders == 1){
        banders = 0;
    } else if (banders == 0){
        banders = 1;
    }
    //Apagamos y encedemos las banderas para el multiplexado 
}

void Sep_Nb(void){
    val_low = (0b11110000 & valor_adc) >> 4;
    val_high = (0b00001111 & valor_adc) << 4;
    //https://www.geeksforgeeks.org/swap-two-nibbles-byte/ utilice esta pagina 
    //de ejemplo para realizar la separacion de nibbles
}