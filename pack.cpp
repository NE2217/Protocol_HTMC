#include <stdlib.h>
#include <stdint.h>
#include "HDLC_PROTOCOL.h"
#include "CRC.h"

//void f_datatupe(unsigned int data[10]) {
//	return;
//}


/*
void f_HDLC_pack(uint8_t* buf, uint16_t len, uint8_t data, uint8_t len_data)//Размер в байтах
{
	HDLC_get_pocket* p_pack = (HDLC_get_pocket*)buf;

	p_pack->begin->flag_open = FLAG;
	p_pack->begin->DA_SA = ;
	p_pack->begin->control = CONTROL;
	p_pack->begin. = CONTROL;
	p_pack->addr = 21;
	p_pack->control = 112;

	for (uint8_t i = 0; i < 10; i++) {
		p_pack->data[i] = (i + 1) * 5;
	}
	p_pack->CRC = f_crc16(p_pack->data, 10);
	p_pack->flag_close = FLAG;

	return;
}
*/

uint16_t f_HDLC_packData(void* data) {
	
	uint8_t* param = (uint8_t*)data;

	switch (*param) {
	case 'U':
		return sizeof(t_HDLC_data_U);	
	case 'I':
		return sizeof(t_HDLC_data_I);
	case 'P':
		return sizeof(t_HDLC_data_P);	
	}
}