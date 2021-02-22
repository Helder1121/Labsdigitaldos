/*
 * File:   ADC.c
 * Author: Helder Ovalle 
 *
 * Created on 21 de febrero de 2021, 02:32 PM
 */

#include <xc.h> 
#include <stdint.h>
#include "ADC.h"
#define _XTAL_FREQ 8000000

float volt, volt2;//variable para los voltajes en los pots

void config_ADC(void){
    ADCON1 = 0b00000000;//Justificado a la izquierda 
}

unsigned Canal_ADC(unsigned short x){ //Fosc/8,datasheet
    switch(x){
        //Canal analogico
        case 0:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;//Canal00
            break;
        case 1:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;//Canal1
            break;
        case 2:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;//Canal2
            break;
        case 3:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;//Canal3
            break;
        case 4:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;//Canal4
            break;
        case 5:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;//Canal5
            break;
        case 6:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;//Canal6
            break;
        case 7:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;//Canal7
            break;
        case 8:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;//Canal8
            break;
        case 9:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;//Canal9
            break;
        case 10:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;//Canal10
            break;
        case 11:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;//Canal11
            break; 
        case 12:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;//Canal12
            break;
        case 13:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;//Canal13
            break;
        case 14:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;//CVref
            break;
        case 15:
            ADCON0bits.CHS3 = 1;
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;//Fixed Ref
            break; 
        default:
            ADCON0bits.CHS3 = 0;
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;//Canal 0
            break;           
    }
}

float ADC_1(void){
    Canal_ADC(0);//canal 0
    //Configuracion bits ADCON0
    ADCON0bits.ADCS0 = 1;//Clock ADC conversion 
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADON = 1;//Habilitamos el ADC
    __delay_ms(0.25);//Para la conversion
    ADCON0bits.GO = 1;//Inicia la conversion
    while (ADCON0bits.GO == 1){
        volt = ((ADRESH * 5.0)/255);//Conversion de 0V-5V
    }
}
float ADC_2(void){
    Canal_ADC(1);//Canal 1
    //Configuracion bits ADCON0
    ADCON0bits.ADCS0 = 1;//Clock ADC conversion 
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADON = 1;//Habilitamos el ADC
    __delay_ms(0.25);//Para la conversion
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