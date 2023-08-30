#include <stdlib.h>
#include <stdint.h>
#include "HDLC_PROTOCOL.h"
#include "CRC.h"
#include "Help_functions.h"

#include <iostream>
using namespace std;

struct HDLC_data_U Voltage = { NULL };
struct HDLC_data_I Current = { NULL };
struct HDLC_data_P Power = { NULL };

uint8_t dataBuf[100] = { NULL };
uint16_t dataLen = { NULL };

uint16_t f_HDLC_packSize(uint8_t* data) {	
	uint16_t len = 1;
	uint16_t i = 1;

		if (*data == FLAG) {

			while ( (data[i] != FLAG) && i<1000)
			{
				len++;
				i++;
			}
			return len+1; 
		}
}

uint8_t f_HDLC_repack(uint8_t* pack, uint16_t len)//������ � ������
 {
	HDLC_get_pocket get_pack = { NULL };
	uint8_t *data = NULL;
	//HDLC_pocket_begin* p_pack_1 = (HDLC_pocket_begin*)pack;

	get_pack.begin = (HDLC_pocket_begin*)pack;

	if (get_pack.begin->flag_open == FLAG) {
	
		/*
		if (p_pack_1->control.win.type_1 & 1) {
			if (p_pack_1->control.win.type_2 & 1) {
				*inf_type = 1;//U-������
			}
			else{
				*inf_type = 2;//S-������
			}

		}
		else { 
			*inf_type = 3;//I-������
		}
		*/
	}
	else{
		
		return 1;
	}

	if (get_pack.begin->HCS != f_crc16(&pack[1], 8)) {
		//cout << hex << (int)get_pack.begin->HCS << " = CRC = " << (int)f_crc16(&pack[1], 8) << dec << endl;
		return 2;
	}

	get_pack.end = (HDLC_pocket_end*)(&pack[f_HDLC_packSize(pack) - 3]);
	
	format form = { NULL };
	form.point = svipe((uint8_t*)&get_pack.begin->format.point, 2);
	/*
	cout << "������ � ������� = " << (int)form.point << endl;
	cout << "��� � ������� = " << (int)form.form.typ << endl;
	cout << "S � ������� = " << (int)form.form.S << endl;
	cout << "������ � ������� = " << (int)form.form.size << endl;
	cout << "������ ��������� = " << (int)(f_HDLC_packSize(pack) - 2) << endl;
	*/
	if (form.form.size == f_HDLC_packSize(pack) - 2) {
		cout << "������ �������" << endl;
	}
	else{ cout << "������ �� �������" << endl; }

	if ( get_pack.end->FCS == f_crc16(&pack[1], (f_HDLC_packSize(pack) - 4)) ){
		
		if (get_pack.end-> flag_close != FLAG)
		{
			return 3;
		}
	}
	else {
	
		return 4;
	}
		for (uint8_t i = 0; i < (f_HDLC_packSize(pack) - 6); i++) {
			dataBuf[i] = *(&get_pack.begin->data + i);
		}
		dataLen = (f_HDLC_packSize(pack) - 6);
	return 0;
}

/*void f_HDLC_repackData(uint8_t* buf, uint16_t len) {
	switch (*buf){	
	case 'U': 
		Voltage = *(HDLC_data_U*)buf;
		return;
	case 'I':
		Current = *(HDLC_data_I*)buf;
		return;
	case 'P':
		Power = *(HDLC_data_P*)buf;
		return;
	}
}
*/

struct HDLC_data_U f_GetVoltage() {
	return Voltage;
}

struct HDLC_data_I f_GetCurrent() {
	return Current;
}

struct HDLC_data_P f_GetPower() {
	return Power;
}

void f_HDLC_Print(struct HDLC_get_pocket* pack) {
	uint16_t i = NULL;

	cout << "���� =		   " << (int)pack->begin->flag_open << endl;
	cout << "����� =		   " << (int)pack->begin->DA_SA[1] << endl;
	cout << "���������� =	   " << (int)pack->begin->control << endl;
	cout << "����������" << endl;
	for (uint16_t i = 0; i < ((f_HDLC_packSize(&(pack->begin->data)))-5); i++) {
		cout << "	" << (int)i << "		 = " << (int) *(&(pack->begin->data) + i) << endl;
	}
	cout << "CRC =		   " << (int)pack->end->FCS << endl;
	cout << "���� =		   " << (int)pack->end->flag_close << endl << endl;

}

void f_HDLC_RepackData(void) {

	for (uint16_t i = 0; i < dataLen; i++) {
		cout << "0x" << hex << (int)dataBuf[i] << dec << ", ";
		if((i+1)%10==0){ cout << endl; }
	}
}
