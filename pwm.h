/*
 * pwm.h
 *
 *  Created on: 17 ���. 2014 �.
 *      Author: lamazavr
 */

#ifndef PWM_H_
#define PWM_H_

#include "DSP2802x_Device.h"
#include "DSP2802x_EPwm_defines.h"

//timer period on 60MHz for 4kHz PWM
#define PWM_TIMER_PRD 15000

/**
 * ��������� ������� GPIO0-5 ��� PWM
 */
void pwm_gpio_init();

void pwm_init();

void pwm1_init();
void pwm2_init();
void pwm3_init();

void pwm1_dead_band_configure();

static volatile Uint16 duty = 0;

void pwm_debug();

void pwm1_interrupt_init();

void pwm_it_enable();
void pwm_it_disable();

#pragma CODE_SECTION(epwm1_timer_isr, "ramfuncs");
interrupt void epwm1_timer_isr();

#endif /* PWM_H_ */
