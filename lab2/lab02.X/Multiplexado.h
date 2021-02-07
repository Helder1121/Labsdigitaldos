/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __Multiplexado_H_
#define	__Multiplexado_H_
#include <xc.h> // include processor files - each processor file is guarded.  

void Multiplexado(uint8_t num);

void Multiplexado(uint8_t num){
    TRISC = 0;
    PORTC = 0;
    switch (num){
        case 0:
            PORTC = 0x3F;
            break;
        case 1:
            PORTC = 0x06;
            break;
        case 2:
            PORTC = 0x5B;
            break;
        case 3:
            PORTC = 0x4F;
            break;
        case 4:
            PORTC = 0x66;
            break;
        case 5:
            PORTC = 0x6D;
            break;
        case 6:
            PORTC = 0x7D;
            break;
        case 7:
            PORTC = 0x07;
            break;
        case 8:
            PORTC = 0x7F;
            break;
        case 9:
            PORTC = 0x6F;
            break;
        case 10:
            PORTC = 0x77;
            break;
        case 11:
            PORTC = 0x1F;
            break;
        case 12:
            PORTC = 0x4E;
            break;
        case 13:
            PORTC = 0x3D;
            break;
        case 14:
            PORTC = 0x4F;
            break;
        case 15:
            PORTC = 0x47;
            break;
//Siguiente display
        case 128:
            PORTC = 0x06;
            break;
        case 64:
            PORTC = 0x5B;
            break;
        case 192:
            PORTC = 0x4F;
            break;
        case 32:
            PORTC = 0x66;
            break;
        case 160:
            PORTC = 0x6D;
            break;
        case 96:
            PORTC = 0x7D;
            break;
        case 224:
            PORTC = 0x07;
            break;
        case 16:
            PORTC = 0x7F;
            break;
        case 144:
            PORTC = 0x6F;
            break;
        case 80:
            PORTC = 0x77;
            break;
        case 208:
            PORTC = 0x1F;
            break;
        case 48:
            PORTC = 0x4E;
            break;
        case 176:
            PORTC = 0x3D;
            break;
        case 112:
            PORTC = 0x4F;
            break;
        case 240:
            PORTC = 0x47;
            break;
        default:
            PORTC = 0x3F;
            break;
    }
}
#endif	/* __Multiplexado_H_ */

