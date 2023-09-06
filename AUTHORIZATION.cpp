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
		return 1; //нет ответа
	}
	else {
		disconect = TIMEOUT;
		if (!(memcmp(buf, get, get_l))) {
			return 0; //ответ совпал
		}
		else {

			return 2; //ответ НЕ совпал
		}
	}
}

bool authorization(uint8_t* buf, uint16_t buf_l) {
	
	ConfigCOM();
	uint8_t SG = 0;

//1 вопрос/ответ
	SG = SendGet(send_1, get_1, buf, sizeof(send_1),sizeof(get_1), buf_l);
	switch (SG) {
	case 0:
		cout << "Ответ 1 совпал" << endl;
		break;
	case 1:
		cout << "НЕТ 1 ответа" << endl;
		return false;
		break;
	case 2:
		cout << "Ответ 1 НЕ совпал" << endl;
		return false;
		break;
	}

//2 вопрос/ответ
	SG = SendGet(send_2, get_2, buf, sizeof(send_2), sizeof(get_2), buf_l);
	switch (SG) {
	case 0:
		cout << "Ответ 2 совпал" << endl;
		break;
	case 1:
		cout << "НЕТ 2 ответа" << endl;
		return false;
		break;
	case 2:
		cout << "Ответ 2 НЕ совпал" << endl;
		return false;
		break;
	}
//3 вопрос/ответ
	SG = SendGet(send_3, get_3, buf, sizeof(send_3), sizeof(get_3), buf_l);
	switch (SG) {
	case 0:
		cout << "Ответ 3 совпал" << endl;
		break;
	case 1:
		cout << "НЕТ 3 ответа" << endl;
		return false;
		break;
	case 2:
		cout << "Ответ 3 НЕ совпал" << endl;
		return false;
		break;
	}

//4 вопрос/ответ
	SG = SendGet(send_4, get_4, buf, sizeof(send_4), sizeof(get_4), buf_l);
	switch (SG) {
	case 0:
		cout << "Ответ 4 совпал" << endl;
		break;
	case 1:
		cout << "НЕТ 4 ответа" << endl;
		return false;
		break;
	case 2:
		cout << "Ответ 4 НЕ совпал" << endl;
		return false;
		break;
	}

//5 вопрос/ответ
	SG = SendGet(send_5, get_5, buf, sizeof(send_5), sizeof(get_5), buf_l);
	switch (SG) {
	case 0:
		cout << "Ответ 5 совпал" << endl;
		break;
	case 1:
		cout << "НЕТ 5 ответа" << endl;
		return false;
		break;
	case 2:
		cout << "Ответ 5 НЕ совпал" << endl;
		return false;
		break;
	}
}