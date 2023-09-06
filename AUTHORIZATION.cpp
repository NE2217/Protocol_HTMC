#include <stdint.h>
#include <Windows.h>
#include "SerialPort.h"
#include "AUTHORIZATION.h"
#include "Help_functions.h"

#define TIMEOUT 10

using namespace std;

uint8_t SendGet(void* send, void* get, uint8_t* buf, uint16_t send_l, uint16_t get_l, uint16_t buf_l ) {
	uint16_t i = 0;
	uint16_t disconect = TIMEOUT;

	WriteCOM(send, send_l);
	while (i < get_l && disconect > 0) {
		if (ReadCOM(&buf[i])) {
			i++;
			disconect = TIMEOUT;
		}
		else disconect--;
	}

	if (disconect == 0) {
		return 1; //��� ������
	}
	else {
		disconect = TIMEOUT;
		if (!(memcmp(buf, get, get_l))) {
			return 0; //����� ������
		}
		else {

			return 2; //����� �� ������
		}
	}
}

bool authorization(uint8_t* buf, uint16_t buf_l) {
	
	ConfigCOM();
	uint8_t SG = 0;

//1 ������/�����
	SG = SendGet(send_1, get_1, buf, sizeof(send_1),sizeof(get_1), buf_l);
	switch (SG) {
	case 0:
		cout << "����� 1 ������" << endl;
		break;
	case 1:
		cout << "��� 1 ������" << endl;
		return false;
		break;
	case 2:
		cout << "����� 1 �� ������" << endl;
		return false;
		break;
	}

//2 ������/�����
	SG = SendGet(send_2, get_2, buf, sizeof(send_2), sizeof(get_2), buf_l);
	switch (SG) {
	case 0:
		cout << "����� 2 ������" << endl;
		break;
	case 1:
		cout << "��� 2 ������" << endl;
		return false;
		break;
	case 2:
		cout << "����� 2 �� ������" << endl;
		return false;
		break;
	}
//3 ������/�����
	SG = SendGet(send_3, get_3, buf, sizeof(send_3), sizeof(get_3), buf_l);
	switch (SG) {
	case 0:
		cout << "����� 3 ������" << endl;
		break;
	case 1:
		cout << "��� 3 ������" << endl;
		return false;
		break;
	case 2:
		cout << "����� 3 �� ������" << endl;
		return false;
		break;
	}

//4 ������/�����
	SG = SendGet(send_4, get_4, buf, sizeof(send_4), sizeof(get_4), buf_l);
	switch (SG) {
	case 0:
		cout << "����� 4 ������" << endl;
		break;
	case 1:
		cout << "��� 4 ������" << endl;
		return false;
		break;
	case 2:
		cout << "����� 4 �� ������" << endl;
		return false;
		break;
	}

//5 ������/�����
	SG = SendGet(send_5, get_5, buf, sizeof(send_5), sizeof(get_5), buf_l);
	switch (SG) {
	case 0:
		cout << "����� 5 ������" << endl;
		break;
	case 1:
		cout << "��� 5 ������" << endl;
		return false;
		break;
	case 2:
		cout << "����� 5 �� ������" << endl;
		return false;
		break;
	}
}