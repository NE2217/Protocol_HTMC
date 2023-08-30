#pragma once
#ifndef REPACK
#define REPACK

#include <stdint.h>

uint8_t f_HDLC_repack(uint8_t* pack, uint16_t len);
//void f_HDLC_repackData(uint8_t* buf, uint16_t len);
struct HDLC_data_U f_GetVoltage();
struct HDLC_data_I f_GetCurrent();
struct HDLC_data_P f_GetPower();
uint16_t f_HDLC_packSize(uint8_t* data);

void f_HDLC_Print(struct HDLC_get_pocket* pack);
void f_HDLC_RepackData(void);
#endif //REPACK
