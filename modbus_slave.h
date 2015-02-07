/*
 * modbus_slave.h
 *
 *  Created on: 04 ���. 2014 �.
 *      Author: salnikov
 */

#ifndef MODBUS_SLAVE_H_
#define MODBUS_SLAVE_H_

#include "DSP2802x_Device.h"

enum {
	MODBUS_FUNCTION_ERROR = 1,
	MODBUS_ADDRESS_ERROR,
	MODBUS_DATA_VALUE_ERROR
};

/**
 * ���������� Modbus �������
 * @return len - ����� ������
 *         0 - ������� �� ���� ��� CRC �� ������
 */
Uint16 modbus_func(Uint16 *Buffer, Uint16 len, Uint16 ModbusAddress);

/**
 * ��������� ������� �� ������
 * @return len - ����� ������
 */
Uint16 modbus_0x03_func(Uint16 *Buffer, Uint16 len);

/**
 * ��������� ������� �� ������
 * @return len - ����� ������
 */
Uint16 modbus_0x06_func(Uint16 *Buffer, Uint16 len);

/**
 * ��������� ������ � �������
 * ��������� ����� � ������� �� ������
 * @return 3 - ����� ������� ������ �� ������
 */
Uint16 modbus_error(Uint16 *Buffer, Uint16 err);
#endif /* MODBUS_SLAVE_H_ */
