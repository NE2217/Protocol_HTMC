#include <iostream>
#include <stdint.h>
#include <assert.h>
#include <string>
#include"LLC.h"

uint8_t f_pasword_pack(uint8_t* buf, uint16_t len, uint8_t* pasword,uint16_t len_password) {
	if (sizeof(t_LLC_pasword_pack) < len) return 1;//ïðåäîñòàâëåííî íåäîñòàòî÷íî ìåñòà
	t_LLC_pasword_pack* pack = (t_LLC_pasword_pack*)buf;
	pack->receiver = RECEIVER;
	pack->source = COMMAND;
	pack->ñîntrol = CONTROL;
	memcpy(pack->reserv_1, PASWORD_RESERV_1, sizeof(PASWORD_RESERV_1));
	memcpy(pack->pasword, pasword, len);
	memcpy(pack->reserv_2, PASWORD_RESERV_2, sizeof(PASWORD_RESERV_2));
}

uint8_t f_connect_pack(uint8_t* buf, uint16_t len, t_connect_data data) {
	if (sizeof(t_connect) > len) return 1; //ïðåäîñòàâëåííî íåäîñòàòî÷íî ìåñòà
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

uint8_t f_LLC_pack(uint8_t* data, uint16_t len, uint8_t param) {
	if (sizeof(t_LLC_inf_request_pack) > len) return 1; //Ã¯Ã°Ã¥Ã¤Ã®Ã±Ã²Ã Ã¢Ã«Ã¥Ã­Ã­Ã® Ã­Ã¥Ã¤Ã®Ã±Ã²Ã Ã²Ã®Ã·Ã­Ã® Ã¬Ã¥Ã±Ã²Ã 
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

	
/*
	switch (LAST_REQUEST)
	{
	case 1:
		for (int i = 0; i < LEN_OBIS; i++) {
			pack->param[i] = OBIS_VOLTAGE_A[i];
		}
		break;
	case 2:
		for (int i = 0; i < LEN_OBIS; i++) {
			pack->param[i] = OBIS_VOLTAGE_B[i];
		}
		break;
	case 3:
		for (int i = 0; i < LEN_OBIS; i++) {
			pack->param[i] = OBIS_VOLTAGE_C[i];
		}
		break;
	case 4:
		for (int i = 0; i < LEN_OBIS; i++) {
			pack->param[i] = OBIS_CURRENT_A[i];
		}
		break;
	case 5:
		for (int i = 0; i < LEN_OBIS; i++) {
			pack->param[i] = OBIS_CURRENT_B[i];
		}
		break;
	case 6:
		for (int i = 0; i < LEN_OBIS; i++) {
			pack->param[i] = OBIS_CURRENT_C[i];
		}
		break;
	case 7:
		for (int i = 0; i < LEN_OBIS; i++) {
			pack->param[i] = OBIS_POWER_A[i];
		}
		break;
	case 8:
		for (int i = 0; i < LEN_OBIS; i++) {
			pack->param[i] = OBIS_POWER_B[i];
		}
		break;
	case 9:
		for (int i = 0; i < LEN_OBIS; i++) {
			pack->param[i] = OBIS_POWER_C[i];
		}
		break;
	case 10:
		for (int i = 0; i < LEN_OBIS; i++) {
			pack->param[i] = OBIS_ENERGY_ACTIVE_IMPORT[i];
		}
		break;
	case 11:
		for (int i = 0; i < LEN_OBIS; i++) {
			pack->param[i] = OBIS_ENERGY_ACTIVE_EXPORT[i];
		}
		break;
	case 12:
		for (int i = 0; i < LEN_OBIS; i++) {
			pack->param[i] = OBIS_ENERGY_REACTIVE_IMPORT[i];
		}
		break;
	case 13:
		for (int i = 0; i < LEN_OBIS; i++) {
			pack->param[i] = OBIS_ENERGY_REACTIVE_EXPORT[i];
		}
		break;
	default:
		return 1;//Ã­Ã¥Ã¨Ã§Ã¢Ã¥Ã±Ã²Ã­Ã»Ã© Ã²Ã¨Ã¯ Ã¤Ã Ã­Ã­Ã»Ãµ
	}
	return 0;
*/
}
