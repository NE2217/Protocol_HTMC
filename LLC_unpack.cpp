#include <iostream>
#include <stdint.h>
#include <assert.h>
#include"LLC.h"
//#include"h_LLC_unpack.h"

//Хранение значений
t_param_inf voltage_A = { 0 };
t_param_inf voltage_B = { 0 };
t_param_inf voltage_C = { 0 };

t_param_inf current_A = { 0 };
t_param_inf current_B = { 0 };
t_param_inf current_C = { 0 };
//полная мощьность по фазам
t_param_inf power_A = { 0 };
t_param_inf power_B = { 0 };
t_param_inf power_C = { 0 };

t_param_inf energy_active_import = { 0 };
t_param_inf energy_active_export = { 0 };
t_param_inf energy_reactive_import = { 0 };
t_param_inf energy_reactive_export = { 0 };

extern uint8_t LAST_REQUEST=0;

uint8_t unpack_LLC(uint8_t* data) {
	t_LLC* llc = (t_LLC*)data;
	if (llc->receiver == RECEIVER) {
		if (llc->control == RECEIVER)
		{
			switch (llc->source) {
			case COMMAND:
				return 3; //получен запрос
			case RESULT:
				return 0;
			default:
				return 4; //получатель не совпал
			}
		}
		else return 2; //контрольный байт не совпал	
	}
	else return 1; //отправитель не совпал
}

uint8_t unpack_LLC_inf(uint8_t* data) {
	t_LLC_inf* llc_inf = (t_LLC_inf*)data;
	switch(llc_inf->tag) {
	case GET_request:
		return 1; //получен запрос
	case GET_response:
		return 0; //получен ответ на запрос		
	default: return 2; //тэг не совпал
	}
}

uint8_t unpack_LLC_inf_response(uint8_t* data) {
	t_LLC_inf_response* llc_inf_response = (t_LLC_inf_response*)data;
	switch (LAST_REQUEST)
	{
	case 1:
		voltage_A.type=llc_inf_response->type;
		for (uint8_t i = 0; i < LEN_FLOAT32; i++) {
			voltage_A.data[i] = *(&llc_inf_response->data + i);
		}
		break;
	case 2:
		voltage_B.type = llc_inf_response->type;
		for (uint8_t i = 0; i < LEN_FLOAT32; i++) {
			voltage_B.data[i] = *(&llc_inf_response->data + i);
		}
		break;
	case 3:
		voltage_C.type = llc_inf_response->type;
		for (uint8_t i = 0; i < LEN_FLOAT32; i++) {
			voltage_C.data[i] = *(&llc_inf_response->data + i);
		}
		break;
	case 4:
		current_A.type = llc_inf_response->type;
		for (uint8_t i = 0; i < LEN_FLOAT32; i++) {
			current_A.data[i] = *(&llc_inf_response->data + i);
		}
		break;
	case 5:
		current_B.type = llc_inf_response->type;
		for (uint8_t i = 0; i < LEN_FLOAT32; i++) {
			current_B.data[i] = *(&llc_inf_response->data + i);
		}
		break;
	case 6:
		current_C.type = llc_inf_response->type;
		for (uint8_t i = 0; i < LEN_FLOAT32; i++) {
			current_C.data[i] = *(&llc_inf_response->data + i);
		}
		break;
	case 7:
		power_A.type = llc_inf_response->type;
		for (uint8_t i = 0; i < LEN_FLOAT32; i++) {
			power_A.data[i] = *(&llc_inf_response->data + i);
		}
		break;
	case 8:
		power_B.type = llc_inf_response->type;
		for (uint8_t i = 0; i < LEN_FLOAT32; i++) {
			power_B.data[i] = *(&llc_inf_response->data + i);
		}
		break;
	case 9:
		power_C.type = llc_inf_response->type;
		for (uint8_t i = 0; i < LEN_FLOAT32; i++) {
			power_C.data[i] = *(&llc_inf_response->data + i);
		}
		break;
	case 10:
		energy_active_import.type = llc_inf_response->type;
		for (uint8_t i = 0; i < LEN_FLOAT32; i++) {
			energy_active_import.data[i] = *(&llc_inf_response->data + i);
		}
		break;
	case 11:
		energy_active_export.type = llc_inf_response->type;
		for (uint8_t i = 0; i < LEN_FLOAT32; i++) {
			energy_active_export.data[i] = *(&llc_inf_response->data + i);
		}
		break;
	case 12:
		energy_reactive_import.type = llc_inf_response->type;
		for (uint8_t i = 0; i < LEN_FLOAT32; i++) {
			energy_reactive_import.data[i] = *(&llc_inf_response->data + i);
		}
		break;
	case 13:
		energy_reactive_export.type = llc_inf_response->type;
		for (uint8_t i = 0; i < LEN_FLOAT32; i++) {
			energy_reactive_export.data[i] = *(&llc_inf_response->data + i);
		}
		break;
	default:
		return 1;//неизвестный тип данных
	}
	return 0;
}


 
