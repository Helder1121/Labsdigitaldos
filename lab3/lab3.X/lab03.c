/*
 * File:   lab03.c
 * Author: Helder Ovalle
 *
 * Created on 8 de febrero de 2021, 10:35 AM
 */
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
#pragma config BOREN = ON      // Brown Out Reset Selection bits (BOR disabled)
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
//Permite realizar los prints
#include <stdio.h>
#include <pic16f887.h>
#include "LCD.h"
#include "ADC.h"
#include "USART.h"
#define _XTAL_FREQ 8000000

//******************************************************************************
// Variables
//******************************************************************************
char data[16];
float volt, volt2;
char LecUSART = 0;
char entregado = 0;
uint8_t contador = 0;
//uint8_t valorADC1;
//uint8_t valorADC2;

//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void config_P();
float ADC_1(void);
float ADC_2(void);
void Enviar_1(void);
void Enviar_2(void);
float Volts_Bina(uint8_t b);

//Interrupcion del RCIF 
void __interrupt() ISR(){
    if (RCIF == 1){
        RCIF = 0;
        LecUSART = Read_USART();
        if(LecUSART=='+'){
            contador++;}
        else if(LecUSART=='-'){
            contador--;}
    }
}
//******************************************************************************
// Ciclo principal
//******************************************************************************
void main(void){
    config_P();
    config_ADC();
    _baudios();
    config_txsta();
    config_rcsta();
    Lcd_Init();
    LCD_Limpia();
//    Lcd_Set_Cursor(1, 1);
//    Lcd_Write_String("S1   S2   CONT");
    //Mensaje en la lcd primera fila 
//    valorADC1 = Canal_ADC(0);
//    valorADC2 = Canal_ADC(1);
//    volt = Volts_Bina(valorADC1);
//    volt2 = Volts_Bina(valorADC2);   
    //**************************************************************************
    // Loop principal
    //**************************************************************************
    while(1){
        LCD_Limpia();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("S1   S2   CONT ");
        //Lo que se muestra en la LCD en la primera fila
        ADC_1();
        ADC_2();
        sprintf(data, "%1.2f   %1.2f   %d" ,volt,volt2,contador);
        //Despliega en dos decimales el voltaje de 0V-5V
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_String(data);
        Write_USART_String("S1    S2    CONT");
        //Mensaje que se muestra en la terminal en la segunda linea
        Write_USART(13);
        Write_USART(10);
        //Saltar lineas
        Write_USART_String(data);
        Write_USART(13);
        Write_USART(10);
        //Saltar lineas
        if (RCIF == 1){
            entregado = RCREG;
            if(entregado == '+'){contador = contador +1;}
            if(entregado == '-'){contador = contador -1;}
        }
        __delay_ms(500);
    }
}
//******************************************************************************
// Configuración
//******************************************************************************
void config_P(){
    //Configuracion de los puertos
    TRISD = 0;
    TRISE = 0;
    TRISA = 3;
    //TRISCbits.TRISC7 = 1;
    //TRISCbits.TRISC6 = 0;
    ANSEL = 3;//Para los potenciometros
    ANSELH = 0;
    //Steo los puertos
    PORTD = 0;
    PORTE = 0;
    PORTC = 0;
    //Interrupcion
//    INTCONbits.PEIE = 1;
//    PIE1bits.RCIE = 1;
//    PIR1bits.RCIF = 0;
//    INTCONbits.GIE = 1;
}
//******************************************************************************
// Funciones
//******************************************************************************
float ADC_1(void){
    Canal_ADC(0);//canal 0
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADON = 1;
    __delay_ms(0.25);
    ADCON0bits.GO = 1;//Inicia la conversion
    while (ADCON0bits.GO == 1){
        volt = ((ADRESH * 5.0)/255);//Conversion de 0V-5V
    }
}
float ADC_2(void){
    Canal_ADC(1);//Canal 1
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADON = 1;
    __delay_ms(0.25);
    ADCON0bits.GO = 1;//Inicia la conversion
    while (ADCON0bits.GO == 1){
        volt2 = ((ADRESH * 5.0)/255); //Conversion de 0V-5V
    }
}
void Enviar_1(void){//Envio de datos
    TXREG = volt;
    while (TXSTAbits.TRMT == 1){//Retorna y envia el voltaje a ADC1
        return;
    }
}
void Enviar_2(void){//Envio de datos
    TXREG = volt2;
    while (TXSTAbits.TRMT == 1){//Retorna y envia el voltaje a ADC2
        return;
    }
}

//float Volts_Bini(uint8_t b){
//    return b*0.0196;
//}