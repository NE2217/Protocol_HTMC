#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include "HDLC_PROTOCOL.h"

#include <assert.h>

using namespace std;

control format_read(uint8_t form) {
	control control = {NULL};

	if (form & 1 == 0) {
		control.R = form >> 5;
		control.P = form & 1 << 3;
		control.S = (form >> 1) & 7;//(номер посланного кадра) сдвиг влево на 1 и маскирование 3 последних битов
	}
	if (form & 1 << 1 == 0) {
		control.R = form >> 5;//номер принимаемого кадра
		control.P = form & 1 << 3;//бит опроса окончания
		switch (form & 0xF)
		{
			case RR :
				control.comand = RR;
				break;
			case RNR :
				control.comand = RNR;
				break;
			case REJ :
				control.comand = REJ;
				break;
			case SREJ:
				control.comand = SREJ;
				break;
		}
	}
	else {
		control.P = form & 1 << 3;//бит опроса окончания
		switch (form)
		{
			case UI:
				control.comand = UI;
				break;
			case SNRM:
				control.comand = SNRM;
				break;
			case DISC:
				control.comand = DISC;
				break;
			case UP:
				control.comand = UP;
				break;
			case UA:
				control.comand = UA;
				break;
			case TEST:
				control.comand = TEST;
				break;
			case SIM:
				control.comand = SIM;
				break;
			case FRMR:
				control.comand = FRMR;
				break;
			case DM:
				control.comand = DM;
				break;
			case RSET:
				control.comand = RSET;
				break;
			case CF:
				control.comand = CF;
				break;
			case SNRME:
				control.comand = SNRME;
				break;
			case SABM:
				control.comand = SABM;
				break;
			case XID:
				control.comand = XID;
				break;
			case SABME:
				control.comand = SABME;
				break;
		}
	}

	return control;
}