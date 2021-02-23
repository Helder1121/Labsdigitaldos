/*
 * File:   Temperatura.c
 * Author: Helder Ovalle
 *
 * Created on 21 de febrero de 2021, 06:20 PM
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
#include "ADC.h"
#include "SPI.h"

//******************************************************************************
// Variables
//******************************************************************************
#define _XTAL_FREQ 8000000
uint8_t ADC = 0;
float temp;
uint8_t volt, volt2;//variable para los voltajes en los pots
//******************************************************************************
//Portotipos de funciones
//******************************************************************************
void setup(void);
void semaf(uint8_t temp);
uint8_t adc_11(void);
//uint8_t adc_21(void);
//void Enviar_1(void);
//void Enviar_2(void);
//******************************************************************************
// COdigo de interrupcion
//******************************************************************************
void __interrupt() isr(void){
    if(SSPIF == 1){
        spiWrite(temp);
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
        adc_11();
        //ADC_2();
        ADC = adc_11();
        temp = (1.95*ADC);//COnversion para los grados
        semaf(temp);
    }        
}
void semaf(uint8_t temp){
    if (temp < 25){//Verde <25
        PORTD = 1;}
    else if (temp > 25 && temp < 36){//Amariillo para el rango de 25-36
        PORTD = 2;}
    else if (temp > 36){//Rojo para >36
        PORTD = 4;}
}
//******************************************************************************
// Configuración
//******************************************************************************
void setup(void){
    ANSEL = 0b00001000;
    ANSELH = 0;
    
    //TRISB = 0;
    TRISD = 0;
    //Steo el puerto
    PORTD = 0;
    PORTB = 0;
    
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
   
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, 
            SPI_IDLE_2_ACTIVE);

}

//******************************************************************************
// Funciones
//******************************************************************************
uint8_t adc_11(void){
    Canal_ADC(8);//canal 8
    //Configuracion bits ADCON0
    ADCON0bits.ADCS0 = 1;//Clock ADC conversion 
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADON = 1;//Habilitamos el ADC
    __delay_ms(0.25);//Para la conversion
    ADCON0bits.GO = 1;//Inicia la conversion
    while (ADCON0bits.GO == 1){
        //Conversion 
    }
    return ADRESH;
}
//uint8_t adc_21(void){
//    Canal_ADC(1);//Canal 1
//    //Configuracion bits ADCON0
//    ADCON0bits.ADCS0 = 1;//Clock ADC conversion 
//    ADCON0bits.ADCS1 = 0;
//    ADCON0bits.ADON = 1;//Habilitamos el ADC
//    __delay_ms(0.25);//Para la conversion
//    ADCON0bits.GO = 1;//Inicia la conversion
//    while (ADCON0bits.GO == 1){
//        volt2 = ((ADRESH * 150)/255); //Conversion de 0V-5V
//    }
//}
//void Enviar_1(void){//Envio de datos
//    TXREG = volt;
//    while (TXSTAbits.TRMT == 1){//Retorna y envia el voltaje a ADC1
//        return;
//    }
//}
//void Enviar_2(void){//Envio de datos
//    TXREG = volt2;
//    while (TXSTAbits.TRMT == 1){//Retorna y envia el voltaje a ADC2
//        return;
//    }
//}