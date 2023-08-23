#pragma once
#ifndef PACK
#define PACK
#include <stdlib.h>
#include <stdint.h>

void f_HDLC_pack(uint8_t* buf, uint16_t len);//запаковка пакета данных
uint16_t f_HDLC_packData(void* data);//запаковка информационной части

#endif //PACK