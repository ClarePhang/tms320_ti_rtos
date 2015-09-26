/*
 * parameters.h
 *
 *  Created on: 04 ���. 2014 �.
 *      Author: salnikov
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "DSP2802x_Device.h"
#include "system.h"

extern System_t system;

enum Parameters_flag {
	READ_PARAMETER_FLAG	= 1,
	WRITE_PARAMETER_FLAG = 2
};

// ��������� ������
typedef struct {
	Uint16 r:1;		// ��������� ������
	Uint16 w:1;		// ��������� ������
}Flags_type;

union FlagsUnion {
	Uint16 all;
	Flags_type bit;
};

// ��������� ���������
typedef struct {
	Uint16 *Addr;			// ��������� �� ��������
	Uint16 LowerLimit;		// ������ ������
	Uint16 UpperLimit;		// ������� ������
	union FlagsUnion Flags;	// �����
}Parameter_type;


extern const Parameter_type ParametersTable[];



#endif /* PARAMETERS_H_ */
