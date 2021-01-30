/*
 * File:   lab1.c
 * Author: Helder Ovalle
 *
 * Created on 30 de enero de 2021, 02:55 PM
 */

//******************************************************************************
// Importaci�n de librer�as
//******************************************************************************

#include <xc.h>

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
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
// Palabra de configuraci�n
//******************************************************************************

//******************************************************************************
// Variables
//******************************************************************************

//******************************************************************************
// Prototipos de funciones
//******************************************************************************

//******************************************************************************
// Ciclo principal
//******************************************************************************
void main(void) {
    return;
}
    //**************************************************************************
    // Loop principal
    //**************************************************************************

//******************************************************************************
// Configuraci�n
//******************************************************************************

//******************************************************************************
// Funciones
//******************************************************************************


