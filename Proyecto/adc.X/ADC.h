#ifndef __ADC_H
#define	__ADC_H
#include <xc.h> 
#include <stdint.h>

unsigned Canal_ADC(unsigned short x);
void config_ADC(void);
float ADC_1(void);
float ADC_2(void);
void Enviar_1(void);
void Enviar_2(void);

#endif	/* __ADC_H_ */