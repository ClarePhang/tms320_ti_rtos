/*
 * ParametersTable.h
 *
 *  Created on: 04 ���. 2014 �.
 *      Author: salnikov
 */

#ifndef PARAMETERSTABLE_H_
#define PARAMETERSTABLE_H_

#include "parameters.h"

// �������� ������� ����������
const Parameter_type ParametersTable[] =
{
	{&system.Fref,				0, 	0xFFFF, READ_PARAMETER_FLAG | WRITE_PARAMETER_FLAG	},
	{&system.LastFault,			0, 	0xFFFF, READ_PARAMETER_FLAG							},
	{&system.Status,			0, 	0xFFFF, READ_PARAMETER_FLAG  						},
	{&system.current.PhaseA,	0, 	0xFFFF, READ_PARAMETER_FLAG  						},
	{&system.current.PhaseB,	0, 	0xFFFF, READ_PARAMETER_FLAG  						},
	{&system.current.PhaseC,	0, 	0xFFFF, READ_PARAMETER_FLAG  						},
	{&system.Udc,				0, 	0xFFFF, READ_PARAMETER_FLAG  						},
	{&system.voltage.PhaseA,	0, 	0xFFFF, READ_PARAMETER_FLAG  						},
	{&system.voltage.PhaseB,	0, 	0xFFFF, READ_PARAMETER_FLAG  						},
	{&system.voltage.PhaseC,	0, 	0xFFFF, READ_PARAMETER_FLAG  						},
};

// ���������� ����������
#define	ParametersCount (sizeof(ParametersTable)/sizeof(Parameter_type))

#endif /* PARAMETERSTABLE_H_ */
