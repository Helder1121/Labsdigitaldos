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
#include "LCD.h"
#include "USART.h"

//******************************************************************************
// Variables
//******************************************************************************
#define _XTAL_FREQ 8000000
uint8_t cont = 0;
uint8_t ADC1 = 0;
uint8_t ADC2 = 0;
float v1,temp;
char data[20];
//******************************************************************************
//Portotipos de funciones
//******************************************************************************
void setup(void);
void contador(void);
void ADC_lectura(void);
float temperatura(void);
//******************************************************************************
// Ciclo principal
//******************************************************************************
void main(void){
    setup();
    
    _baudios();
    config_txsta();
    config_rcsta();
    Lcd_Init();
    LCD_Limpia();
    //**************************************************************************
    // Loop principal
    //**************************************************************************
    while(1){
        contador();
        ADC_lectura();
        //temperatura();
        LCD_Limpia();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("S1   CONT   S3");
        
//        v1 = ADC1*0.0196;
        temp = temperatura();
        sprintf(data, "%1.0f   %d   %3.0f" ,v1,cont,temp);
        
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String(data);
        
        Write_USART_String("S1   CONT   S3");
        Write_USART(13);
        Write_USART(10);
        
        Write_USART_String(data);
        Write_USART(13);
        Write_USART(10);
        __delay_ms(500);
    }
}

void ADC_lectura(void){
    PORTCbits.RC0 = 0;       //Slave Select
    __delay_ms(1);
       
    spiWrite(1);
    v1 = spiRead();
       
    __delay_ms(1);
    PORTCbits.RC0 = 1;       //Slave Deselect 
    __delay_ms(1);
}    
    
void contador(void){
    PORTCbits.RC1 = 0;
    __delay_ms(1);
       
    spiWrite(1);
    cont = spiRead();
       
    __delay_ms(1);
    PORTCbits.RC1 = 1; 
    __delay_ms(1);
}   

float temperatura(void){
    PORTCbits.RC2 = 0;
    __delay_ms(1);
       
    spiWrite(1);
    temp = spiRead();
       
    __delay_ms(1);
    PORTCbits.RC2 = 1; 
    __delay_ms(1);
    return temp;
}

//******************************************************************************
// Configuración
//******************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    TRISE = 0;
    TRISD = 0;
    //Steo los puertos
    PORTE = 0;
    PORTD = 0;
    PORTB = 0;
    
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    PORTCbits.RC0 = 1;
    PORTCbits.RC1 = 1;
    PORTCbits.RC2 = 1;
    PORTCbits.RC7 = 1;

    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, 
        SPI_IDLE_2_ACTIVE);
}


