#include <iostream>
#include <stdint.h>
#include <assert.h>
#include <string>
#include"LLC.h"


//передача пароля
#define PASSWORD					"12345678"

const /*static*/ uint8_t PASWORD_RESERV_1[] = { 0x60, 0x36, 0xA1, 0x09, 0x06, 0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x01, 0x8A, 0x02, 0x07, 0x80, 0x8B,
0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x02, 0x01, 0xAC, 0x0A, 0x80, 0x08 };
const /*static*/ uint8_t PASWORD_RESERV_2[] = { 0xBE, 0x10, 0x04, 0x0E, 0x01, 0x00, 0x00, 0x00, 0x06, 0x5F, 0x1F, 0x04, 0x00, 0xFF, 0xFF, 0xFF, 0x08, 0x00 };
const /*static*/ uint8_t PASWORD_RESPONSE[] = { 0xE6, 0xE7, 0x00, 0x61, 0x29,
	0xA1, 0x09, 0x06, 0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x01, 0xA2, 0x03, 0x02, 0x01, 0x00,
	0xA3, 0x05, 0xA1, 0x03, 0x02, 0x01, 0x00, 0xBE, 0x10, 0x04, 0x0E, 0x08, 0x00, 0x06, 0x5F, 0x1F,
	0x04, 0x00, 0x00, 0x10, 0x15, 0x04, 0x00, 0x00, 0x07 };

//OBIS-коды
const /*static*/ uint8_t OBIS_VOLTAGE_A[] = { 1,0,32,7,0,255 };//LAST_REQUEST =  1
const /*static*/ uint8_t OBIS_VOLTAGE_B[] = { 1,0,52,7,0,255 };//LAST_REQUEST =  2
const /*static*/ uint8_t OBIS_VOLTAGE_C[] = { 1,0,72,7,0,255 };//LAST_REQUEST =  3

const /*static*/ uint8_t OBIS_CURRENT_A[] = { 1,0,31,7,0,255 };//LAST_REQUEST =  4
const /*static*/ uint8_t OBIS_CURRENT_B[] = { 1,0,51,7,0,255 };//LAST_REQUEST =  5
const /*static*/ uint8_t OBIS_CURRENT_C[] = { 1,0,71,7,0,255 };//LAST_REQUEST =  6
//полная мощьность по фазам
const /*static*/ uint8_t OBIS_POWER_A[] = { 1,0,29,7,0,255 };//LAST_REQUEST =  7
const /*static*/ uint8_t OBIS_POWER_B[] = { 1,0,49,7,0,255 };//LAST_REQUEST =  8
const /*static*/ uint8_t OBIS_POWER_C[] = { 1,0,69,7,0,255 };//LAST_REQUEST =  9

const /*static*/ uint8_t OBIS_ENERGY_ACTIVE_IMPORT[] = { 1,0,1,8,0,255 };//LAST_REQUEST =  10
const /*static*/ uint8_t OBIS_ENERGY_ACTIVE_EXPORT[] = { 1,0,2,8,0,255 };//LAST_REQUEST =  11
const /*static*/ uint8_t OBIS_ENERGY_REACTIVE_IMPORT[] = { 1,0,3,8,0,255 };//LAST_REQUEST =  12
const /*static*/ uint8_t OBIS_ENERGY_REACTIVE_EXPORT[] = { 1,0,4,8,0,255 };//LAST_REQUEST =  13

const /*static*/ uint8_t* OBIS[] = { OBIS_VOLTAGE_A, OBIS_VOLTAGE_B, OBIS_VOLTAGE_C, OBIS_CURRENT_A, OBIS_CURRENT_B, OBIS_CURRENT_C,
							OBIS_POWER_A, OBIS_POWER_B, OBIS_POWER_C, OBIS_ENERGY_ACTIVE_IMPORT, OBIS_ENERGY_ACTIVE_EXPORT,
							OBIS_ENERGY_REACTIVE_IMPORT, OBIS_ENERGY_REACTIVE_EXPORT };

uint8_t f_pasword_pack(uint8_t* buf, uint16_t len, uint8_t* pasword,uint16_t len_password)
{
	if (sizeof(t_LLC_pasword_pack) < len)
		return 1;//�������������� ������������ �����
	t_LLC_pasword_pack* pack = (t_LLC_pasword_pack*)buf;

	pack->receiver = RECEIVER;
	pack->source = COMMAND;
	pack->control = CONTROL;
	memcpy(pack->reserv_1, PASWORD_RESERV_1, sizeof(PASWORD_RESERV_1));
	memcpy(pack->pasword, pasword, len);
	memcpy(pack->reserv_2, PASWORD_RESERV_2, sizeof(PASWORD_RESERV_2));

	return 0;
}

uint8_t f_connect_pack(uint8_t* buf, uint16_t len, t_connect_data data) {
	if (sizeof(t_connect) > len) return 1; //�������������� ������������ �����
	t_connect* connect = (t_connect*)buf;
	connect->group_id = GROUP_ID;
	connect->len_group_id = data.max_cadr_reception_len+data.max_cadr_transmission_len+data.max_window_reception_len+data.max_window_transmission_len+ID_SIZE;
	connect->max_cadr_reception.ID = MAX_CADR_RECEPTION_ID;
	connect->max_cadr_reception.data = data.max_cadr_reception_data;
	connect->max_cadr_reception.len = data.max_cadr_reception_len;
	connect->max_cadr_transmission.ID = MAX_CADR_TRANSMISSION_ID;
	connect->max_cadr_transmission.data = data.max_cadr_transmission_data;
	connect->max_cadr_transmission.len = data.max_cadr_transmission_len;
	connect->max_window_reception.ID = MAX_WINDOW_RECEPTION_ID;
	connect->max_window_reception.data = data.max_window_reception_data;
	connect->max_window_reception.len= data.max_window_reception_len;
	connect->max_window_transmission.ID = MAX_WINDOW_TRANSMISSION_ID;
	connect->max_window_transmission.data = data.max_window_transmission_data;
	connect->max_window_transmission.len = data.max_window_transmission_len;
	return 0;
}

uint8_t f_LLC_pack(uint8_t* data, uint16_t len, uint8_t param)
{
	if (sizeof(t_LLC_inf_request_pack) > len)
		return 1; //ïðåäîñòàâëåííî íåäîñòàòî÷íî ìåñòà

	t_LLC_inf_request_pack* pack = (t_LLC_inf_request_pack*)data;

	pack->receiver = RECEIVER;
	pack->source = COMMAND;
	pack->control = CONTROL;
	pack->tag = GET_request;
	pack->reserv[0] = { RES_0 };
	pack->reserv[1] = { RES_1 };
	pack->reserv[2] = { RES_2 };
	pack->clas = CLASS;
	memcpy(pack->param, OBIS[param], LEN_OBIS);
	pack->atr = ATRIBUT;

	LAST_REQUEST = param;

	return 0;
}
