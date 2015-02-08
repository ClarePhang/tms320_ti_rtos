/*
 * drv8301.c
 *
 *  Created on: 16 ���. 2014 �.
 *      Author: lamazavr
 */

#include "drv8301.h"
#include "DSP2802x_Examples.h"

#include <ti/sysbios/knl/Task.h>
#include <xdc/cfg/global.h>

Void drv8301_task(UArg a0, UArg a1)
{
	drv8301_init();
	drv8301_gate_reset();

	while(1)
	{
		//TODO: parse for errors of drv8301
		Task_sleep(100);
	}
}

Uint16 drv8301_send_cmd(Uint16 addr, Uint16 data, Uint16 rw)
{
	DRV_8301_DATA_SEND sdata;  // send data

	sdata.bit.w0 = rw; // read5
	sdata.bit.addr = addr;
	sdata.bit.data = data;

	// Transmit data
	SpiaRegs.SPITXBUF = sdata.all;
	// Wait until data is received
	while(SpiaRegs.SPIFFRX.bit.RXFFST !=1) { }
	// Check against sent data
	return SpiaRegs.SPIRXBUF;
}

void drv8301_init()
{
	// ��������� ������ GPIO6 - EN_GATE
	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;	// as gpio pin
	GpioCtrlRegs.GPADIR.bit.GPIO6 = 1; 	// output
	EDIS;

	// ������������� EN_GATE
	__DRV8301_EN_GATE_SET;
	DELAY_US(10000);

	// ����������� spi
	drv8301_spi_init();

	// reset drv8301 to initial state
	//drv8301_gate_reset();
	//DELAY_US(10000);

	DRV_8301_REG1_DATA reg;
	reg.all = 0;
	reg.bit.PWM_MODE = 1;
	reg.bit.OC_ADJ_SET = 20;
	reg.bit.OC_MODE = 3;

	// set over current report only mode
	drv8301_send_cmd(0x02, reg.all, __DRV8301_WRITE);

	DRV_8301_REG2_DATA reg2;
	reg2.all = 0;
	reg2.bit.OC_TOFF = 1;
	reg2.bit.GAIN = 3;

	drv8301_send_cmd(0x03, reg2.all, __DRV8301_WRITE);
}

void drv8301_spi_init()
{
	InitSpiaGpio();

	SpiaRegs.SPICCR.all = 0x000F;	             // Reset on, rising edge,
	SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;

	//SpiaRegs.SPICTL.all = 0x0006;    		     // Enable master mode, normal phase,
                                                 // enable talk, and SPI int disabled.
	SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;
	SpiaRegs.SPICTL.bit.CLK_PHASE = 0;
	SpiaRegs.SPICTL.bit.TALK = 1;
	SpiaRegs.SPICTL.bit.SPIINTENA = 0;

	SpiaRegs.SPIBRR = 0x007F;
    //SpiaRegs.SPICCR.all = 0x008F;		         // Relinquish SPI from Reset
	SpiaRegs.SPICCR.bit.SPISWRESET = 1;
	SpiaRegs.SPICCR.bit.SPICHAR = 0xF;  //16-bit char bits

//    SpiaRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission

	// ��������� ��������� FIFO
	SpiaRegs.SPIFFTX.all=0xE040;
	SpiaRegs.SPIFFRX.all=0x2044;
	SpiaRegs.SPIFFCT.all=0x0;
}

inline void drv8301_gate_reset()
{
	drv8301_send_cmd(2,4,0);
}

void InitSpiaGpio()
{

   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pull-up on GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pull-up on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pull-up on GPIO19 (SPISTEA)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

/* Configure SPI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SPI functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA

    EDIS;
}

void drv8301_pwm_mode_set(Uint16 mode)
{
	if (mode == 1)
		drv8301_send_cmd(__DRV8301_CONTROL_REG1, 0x08, __DRV8301_WRITE);
	else if (mode == 0)
		drv8301_send_cmd(__DRV8301_CONTROL_REG1, 0x00, __DRV8301_WRITE);
}


