/*
 * adc.h
 *
 *  Created on: 14 ����� 2015 �.
 *      Author: lamazavr
 */

#ifndef ADC_H_
#define ADC_H_

#include <xdc/cfg/global.h>


void init_adc();

void adc_isr(UArg arg);



#endif /* ADC_H_ */
