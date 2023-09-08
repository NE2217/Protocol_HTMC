#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "HDLC_PROTOCOL.h"
#include "CRC.h"
//#include "Help_functions.h"

#include <iostream>
using namespace std;

// return values for function f_HDLC_unpack HdlcUnpack
#define HDLC_UNPACK_SUCCESS   0
#define OPEN_FLAG_NOT_FIND    1
#define HCS_NOT_VALID         2
#define CLOSE_FLAG_NOT_FIND   3
#define FCS_NOT_VALID         4

//struct t_HDLC_data_U Voltage = { 0 };
//struct t_HDLC_data_I Current = { 0 };
//struct t_HDLC_data_P Power = { 0 };

#define DATA_BUF_SIZE    100u
static uint8_t DataBuf[DATA_BUF_SIZE] = { 0 };
static uint16_t DataLen = 0;

void f_HDLC_Init(void)
{
	memset(DataBuf, 0, DATA_BUF_SIZE);
	DataLen = 0;
}
// -----------------------------------------------------------------------------
// TODO в название нужно делать соответствующее назначению функции CalcPackSize например
uint16_t f_HDLC_CalcPackSize(uint8_t* data, uint16_t data_len) { // рассчитывает длину входящего/исходящего сообщения
	uint16_t len = 1;
	uint16_t i = 1;

		if (*data == FLAG) {

			while ( (data[i] != FLAG) && (i < data_len) ) // TODO в функцию нужно передавать длину данных.Тогда ее можно вставить вместо 1000
													  // Ответ: 1000 добавлина для избежания зависания в бесконечном цикле, на случай если конечный флаг не будет обнаружен
			{
				len++;
				i++;
			}
			return len+1; 
		}
		return 0;
}
// -----------------------------------------------------------------------------
void f_HDLC_UunpackData(void)
{
	if (unpack_LLC(DataBuf) == 0)
	{
		t_LLC* llc = (t_LLC*)DataBuf;
		if (unpack_LLC_inf(&llc->tag) == 0)
		{
			t_LLC_inf* llc_inf = (t_LLC_inf*) &llc->tag;
			unpack_LLC_inf_response(&llc_inf->inf);
		}
	}
}
// -----------------------------------------------------------------------------
// TODO repack - перепаковать, больше подойдёт unpack - распаковать


uint8_t f_HDLC_unpack(uint8_t* pack, uint16_t len) // Размер в байтах
 {
	t_HDLC_get_packet get_pack = { 0 };
	uint8_t pack_size = 0;
	// TODO не используется. нужно убрать
	//HDLC_pocket_begin* p_pack_1 = (HDLC_pocket_begin*)pack;

	get_pack.begin = (t_HDLC_packet_begin*)pack; // TODO можно было сразу объявить указатель типа HDLC_pocket_begin без HDLC_get_pocket

	if (get_pack.begin->flag_open != FLAG)
		return OPEN_FLAG_NOT_FIND; //необнаружен открывающий флаг

	pack_size = f_HDLC_CalcPackSize(pack, len);

	/*
		if (p_pack_1->control.win.type_1 & 1) {
			if (p_pack_1->control.win.type_2 & 1) {
				*inf_type = 1;//U-формат
			}
			else{
				*inf_type = 2;//S-формат
			}

		}
		else { 
			*inf_type = 3;//I-формат
		}
		*/
//	}
//	else{
//
//		return 1; //необнаружен открывающий флаг
//	}

//	if (get_pack.begin->HCS != f_crc16((uint8_t*)&get_pack.begin->format, HEADER_LEN) ) { // TODO
	if (get_pack.begin->HCS != f_crc16(&pack[1], HEADER_LEN) ) {
		//cout << hex << (int)get_pack.begin->HCS << " = CRC = " << (int)f_crc16(&pack[1], 8) << dec << endl;
		return HCS_NOT_VALID; // HCS не совпал
	}

	get_pack.end = (t_HDLC_packet_end*)(&pack[pack_size - sizeof(t_HDLC_packet_end)]);
	
	t_format form; //? TODO не нужно делать  = { NULL }. И объяви указатель которуму укажешь на адрес
	form.point = swap((uint8_t*)&get_pack.begin->format.point, 2);
	/*
	cout << "формат в посылке = " << (int)form.point << endl;
	cout << "тип в посылке = " << (int)form.form.typ << endl;
	cout << "S в посылке = " << (int)form.form.S << endl; 
	cout << "длинна в посылке = " << (int)form.form.size << endl;
	cout << "длинна посчитана = " << (int)(f_HDLC_packSize(pack) - 2) << endl;
	*/ 
	if (form.form.size == (pack_size - 2) ) {
		cout << "длинна совпала" << endl;
	}
	else{ cout << "длинна НЕ совпала" << endl; }

	if ( get_pack.end->FCS == f_crc16((uint8_t*)&get_pack.begin->format, (pack_size - 4)) ){
		
		if (get_pack.end->flag_close != FLAG)
		{
			return CLOSE_FLAG_NOT_FIND;
		}
	}
	else {
	
		return 4;
	}
	DataLen = (pack_size - 6);
	for (uint8_t i = 0; i < DataLen; i++)
	{
		DataBuf[i] = *(&get_pack.begin->data + i); // TODO memcopy
	}
	f_HDLC_UunpackData();

	return 0;
}
// -----------------------------------------------------------------------------
void f_HDLC_Print_Pack(t_HDLC_get_packet* pack, uint16_t len) // TODO print чего? нужно дать более подробное имя
{
	cout << "флаг =		   " << (int)pack->begin->flag_open << endl;
	cout << "адрес =		   " << (int)pack->begin->DA_SA[1] << endl;
	cout << "управление =	   " << (int)pack->begin->control << endl;
	cout << "информация" << endl;

	for (uint16_t i = 0; i < ((f_HDLC_CalcPackSize(&(pack->begin->data), len))-5); i++) {
		cout << "	" << (int)i << "		 = " << (int) *(&(pack->begin->data) + i) << endl;
	}

	cout << "CRC =		   " << (int)pack->end->FCS << endl;
	cout << "флаг =		   " << (int)pack->end->flag_close << endl << endl;

}//3

// -----------------------------------------------------------------------------
float f_GetVoltage(uint8_t phase)
{
	float Voltage = 0;

	switch (phase)
	{
		case A:
			Voltage = (float)*voltage_A.data;
			break;
		case B:
			Voltage = (float)*voltage_B.data;
			break;
		case C:
			Voltage = (float)*voltage_C.data;
			break;
		default:
	//		Voltage = 0;
			break;
	}

	return Voltage;
}
// -----------------------------------------------------------------------------
float f_GetCurrent(uint8_t phase)
{
	float Current = 0;

	switch (phase)
	{
		case A:
			Current = (float)*current_A.data;
			break;
		case B:
			Current = (float)*current_B.data;
			break;
		case C:
			Current = (float)*current_C.data;
			break;
		default:
//			Current = &ERROR;
			break;
	}
	return Current;
}
// -----------------------------------------------------------------------------
float f_GetPower(uint8_t phase) {
	float Power = 0;

	switch (phase)
	{
		case A:
			Power = (float)*power_A.data;
			break;
		case B:
			Power = (float)*power_B.data;
			break;
		case C:
			Power = (float)*power_C.data;
			break;
		default:
//			Power = &ERROR;
			break;
	}
	return Power;
}
// -----------------------------------------------------------------------------
float f_GetEnergy(uint8_t type)
{
	float Energy = 0;

	switch (type)
	{
		case AI:
			Energy = (float)*energy_active_import.data;
			break;
		case AE:
			Energy = (float)*energy_active_export.data;
			break;
		case RI:
			Energy = (float)*energy_reactive_import.data;
			break;
		case RE:
			Energy = (float)*energy_reactive_export.data;
			break;

		default:
	//		Energy = &ERROR;
			break;
	}

	return Energy;
}
// -----------------------------------------------------------------------------
