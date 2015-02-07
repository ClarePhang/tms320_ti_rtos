/*
 * modbus_slave.c
 *
 *  Created on: 04 ���. 2014 �.
 *      Author: salnikov
 */
#include "modbus_slave.h"
#include "crc16.h"
#include "ParametersTable.h"

Uint16 modbus_func(Uint16 *Buffer, Uint16 len, Uint16 ModbusAddress)
{
	Uint16 tmp;

	// �������� ������ ���� ��� ����������
	if (*Buffer != ModbusAddress)
		return 0;

	// ��������� ���������� �������
	if (Crc16(Buffer,len) != 0)
		return 0;

	// ���������� �������
	switch (Buffer[1])
	{
		// ������
		case 0x03:
			len = modbus_0x03_func(Buffer, len);
		break;

		// ������
		case 0x06:
			len = modbus_0x06_func(Buffer, len);
		break;

		default:
			len = modbus_error(Buffer,MODBUS_FUNCTION_ERROR);
	}
	// ��������� � ������� CRC
	tmp = Crc16(Buffer,len);
	Buffer[len] = tmp & 0xFF;
	Buffer[len+1] = tmp >> 8;

	return len+2;
}

Uint16 modbus_0x03_func(Uint16 *Buffer, Uint16 len)
{
	Uint16 Addr, size, tmp, s_tmp;
	const Parameter_type *parameter;

	Addr = (Buffer[2] << 8) | Buffer[3];
	size = (Buffer[4] << 8) | Buffer[5];

	// �������� ����������� ������
	if (Addr > ParametersCount)
		return modbus_error(Buffer, MODBUS_ADDRESS_ERROR);

	parameter = &ParametersTable[Addr];

	// �������� ���������� ��������
	if (parameter->Flags.bit.r != 1)
		return modbus_error(Buffer, MODBUS_DATA_VALUE_ERROR);


	// ������ � ����� Uart ���������� ����������
	Buffer[2] = size;
	s_tmp = size;
	Buffer += 3;
	for (; size>0; size--, Buffer+=2, Addr++)
	{
		tmp = *ParametersTable[Addr].Addr;
		*Buffer = tmp >> 8;
		Buffer[1] = tmp & 0xFF;
	}
	// ���������� ����� �������
	// ����� + ������� + ���������� ������ + ������
	return (3 + s_tmp*2);
}

Uint16 modbus_0x06_func(Uint16 *Buffer, Uint16 len)
{
	Uint16 Addr, Value;
	const Parameter_type *parameter;

	Addr = (Buffer[2] << 8) | Buffer[3];
	Value = (Buffer[4] << 8) | Buffer[5];

	// �������� ����������� ������
	if (Addr > ParametersCount)
		return modbus_error(Buffer, MODBUS_ADDRESS_ERROR);

	parameter = &ParametersTable[Addr];

	// �������� ����������� �������� ��� ������
	if (parameter->Flags.bit.w == 1)
	{
		// ��������� �������
		if (Value >= parameter->LowerLimit && Value <= parameter->UpperLimit)
		{
			// ����������
			*(parameter->Addr) = Value;
		}
		else return modbus_error(Buffer, MODBUS_DATA_VALUE_ERROR);
	}
	else return modbus_error(Buffer, MODBUS_DATA_VALUE_ERROR);

	// ����� - ����� �������
	return 6;
}

Uint16 modbus_error(Uint16 *Buffer, Uint16 err)
{
	Buffer[1] |= 0x80;
	Buffer[2] = err;

	return 3;
}

