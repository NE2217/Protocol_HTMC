#include <iostream>
#include <stdint.h>
#include <assert.h>
#include"LLC.h"

uint8_t f_LLC_pack(uint8_t* data, uint16_t len, uint8_t param) {
	if (sizeof(t_LLC_inf_request_pack) > len) return 1; //предоставленно недостаточно места
	t_LLC_inf_request_pack* pack = (t_LLC_inf_request_pack*)data;
	pack->receiver = RECEIVER;
	pack->source = COMMAND;
	pack->соntrol = CONTROL;
	pack->tag = GET_request;
	pack->reserv[0] = { RES_0 };
	pack->reserv[1] = { RES_1 };
	pack->reserv[2] = { RES_2 };
	pack->clas = CLASS;
	pack->atr = ATRIBUT;

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
		return 1;//неизвестный тип данных
	}
	return 0;
}