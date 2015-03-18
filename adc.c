/*
 * adc.c
 *
 *  Created on: 14 ����� 2015 �.
 *      Author: lamazavr
 */
#include "DSP2802x_Device.h"
#include "adc.h"
#include "system.h"

//TODO: remove this after parameters set/get functions implementation
extern System_t system;

void init_adc()
{
	//chanels map
	// Ia_FB - B1
	// Ib_FB - B3
	// Ic_FB - B7

	// Va_FB - A3
	// Vb_FB - A1
	// Vc_FB - A0

	// DC_FB - A7

	InitAdc();

	PieCtrlRegs.PIEIER1.bit.INTx1 = 1;	// Enable INT 1.1 in the PIE
	IER |= M_INT1; 						// Enable CPU Interrupt 1
	EINT;          						// Enable Global interrupt INTM
	ERTM;          						// Enable Global realtime interrupt DBGM

	// Configure ADC
	EALLOW;
	AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 1;	//ADCINT1 trips after AdcResults latch
	AdcRegs.INTSEL1N2.bit.INT1E     = 1;	//Enabled ADCINT1
	AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;	//Disable ADCINT1 Continuous mode
	AdcRegs.INTSEL1N2.bit.INT1SEL	= 1;	//setup EOC1 to trigger ADCINT1 to fire

	//current measurements sources
	AdcRegs.ADCSOC0CTL.bit.CHSEL 	= 0x0B;
	AdcRegs.ADCSOC1CTL.bit.CHSEL 	= 0x09;
	AdcRegs.ADCSOC2CTL.bit.CHSEL 	= 0x08;

	//TODO: add voltage measurements sources and triggers for them

	AdcRegs.ADCSOC0CTL.bit.TRIGSEL 	= 5;	//set SOC0 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL 	= 5;	//set SOC1 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1
	AdcRegs.ADCSOC0CTL.bit.ACQPS 	= 6;	//set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	AdcRegs.ADCSOC1CTL.bit.ACQPS 	= 6;	//set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
	EDIS;

}

#pragma CODE_SECTION(adc_isr, "ramfuncs");
void adc_isr(UArg arg)
{
	//TODO: create some filter here
	system.voltage.PhaseA = AdcResult.ADCRESULT0;
	system.voltage.PhaseB = AdcResult.ADCRESULT1;

	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;		//Clear ADCINT1 flag reinitialize for next SOC
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
}
