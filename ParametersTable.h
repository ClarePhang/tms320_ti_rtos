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
Parameter_type ParametersTable[] =
{
	{&LedsState,	0,	0xFF,	READ_PARAMETER_FLAG | WRITE_PARAMETER_FLAG	},
	{&TestPrm, 		0, 	0xFFFF, READ_PARAMETER_FLAG | WRITE_PARAMETER_FLAG	},
};

// ���������� ����������
#define	ParametersCount (sizeof(ParametersTable)/sizeof(Parameter_type))

#endif /* PARAMETERSTABLE_H_ */
