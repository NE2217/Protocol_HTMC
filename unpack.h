#pragma once
#ifndef REPACK
#define REPACK

#include <stdint.h>
#include "Help_functions.h"

//фазы
#define A				0
#define B				1
#define C				2
//вид энергии
#define AI				0//активная-импорт
#define AE				1//активная-экспорт
#define RI				2//реактивная-импорт
#define RE				3//реактивная-экспорт

uint8_t f_HDLC_unpack(uint8_t* pack, uint16_t len);

float f_GetVoltage(uint8_t phase);
float f_GetCurrent(uint8_t phase);
float f_GetPower(uint8_t phase);
float f_GetEnergy(uint8_t type);


void f_HDLC_Print_Pack(struct HDLC_get_pocket* pack);

#endif //REPACK
