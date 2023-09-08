#pragma once
#ifndef REPACK
#define REPACK

#include <stdint.h>
#include "Help_functions.h"
#include "HDLC_PROTOCOL.h"
//����
#define A				0
#define B				1
#define C				2
//��� �������
#define AI				0//��������-������
#define AE				1//��������-�������
#define RI				2//����������-������
#define RE				3//����������-�������

uint8_t f_HDLC_unpack(uint8_t* pack, uint16_t len);

float f_GetVoltage(uint8_t phase);
float f_GetCurrent(uint8_t phase);
float f_GetPower(uint8_t phase);
float f_GetEnergy(uint8_t type);


//void f_HDLC_Print_Pack(HDLC_get_pocket* pack, uint16_t len);

#endif //REPACK
