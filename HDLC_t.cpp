#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h> 
#include <stdint.h>
#include <iostream>
#include "HDLC_PROTOCOL.h"

#include "AUTHORIZATION.h"
//#include "Help_functions.h"

using namespace std;

//void* A[3];

uint8_t buf_regist[100], pack_b[100], buf[100] = { 0 }; // TODO NULL - это для указателей. Нужно {0}
uint8_t TTT[] = { 0xA2, 0x08, 0x03, 0x21, 0x21, 0x53 };
uint8_t AAA[] = { 0xA2, 0x08, 0x03, 0x21, 0x21, 0x53 };
uint8_t buf_test[] = {0x7E, 0xA0, 0x23, 0x00, 0x02, 0x44, 0xC9,
0x61, 0x93, 0x44, 0x0B, 0x81, 0x80, 0x14, 0x05, 0x02,
0x04, 0x00, 0x06, 0x02, 0x04, 0x00, 0x07, 0x04, 0x00, 0x00, 0x00, 0x01, 0x08,
0x04, 0x00, 0x00, 0x00, 0x01, 0x72, 0xE3, 0x7E};
uint8_t buf_test_1[] = { 0x7E, 0xA0, 0x23, 0x61, 0x00, 0x02, 0x44, 0xC9,
0x73, 0xD9, 0xB6, 0x81, 0x80, 0x14, 0x05, 0x02, 0x04, 0x00, 0x06, 0x02, 0x04, 0x00, 0x07, 0x04,
0x00, 0x00, 0x00, 0x01, 0x08, 0x04, 0x00, 0x00, 0x00, 0x01, 0x72, 0xE3, 0x7E};
uint8_t buf_test_2[] = { 0x7E, 0xA0, 0x4F, 0x00, 0x02, 0x44, 0xC9, 0x61, 0x10, 0xC8, 0xA8, 0xE6, 0xE6,
0x00, 0x60, 0x3E, 0xA1, 0x09, 0x06, 0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x01, 0x8A, 0x02, 0x07,
0x80, 0x8B, 0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x02, 0x02, 0xAC, 0x12, 0x80, 0x10, 0x30, 0x31, 0x32,
0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0xBE, 0x10, 0x04, 0x0E,
0x01, 0x00, 0x00, 0x00, 0x06, 0x5F, 0x1F, 0x04, 0x00, 0xFF, 0xFF, 0xFF,0x08, 0x00, 0x3D, 0x69, 0x7E };
uint8_t buf_test_3[] = { 0x7E, 0xA0, 0x5B, 0x61, 0x00, 0x02, 0x44, 0xC9, 0x30, 0xE6, 0x09, 0xE6,
0xE7, 0x00, 0x61, 0x4A, 0xA1, 0x09, 0x06, 0x07, 0x60, 0x85, 0x74, 0x05,
0x08, 0x01, 0x01, 0xA2, 0x03, 0x02, 0x01, 0x00, 0xA3, 0x05, 0xA1, 0x03, 0x02,
0x01, 0x0E, 0x88, 0x02, 0x07, 0x80, 0x89, 0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x02, 0x02,
0xAA, 0x12, 0x80, 0x10, 0x36, 0x6F, 0x58, 0x70, 0x50, 0x39, 0x3E, 0x56, 0x65, 0x4D, 0x79,
0x34, 0x65, 0x5C, 0x4E, 0x72, 0xBE, 0x10, 0x04, 0x0E, 0x08, 0x00, 0x06, 0x5F,
0x1F, 0x04, 0x00, 0x00, 0x18, 0x1D, 0x04, 0x00, 0x00, 0x07, 0x0E, 0xDA, 0x7E };
uint8_t inf=0;


uint8_t reqest_1[] = {0x7E, 0xA0, 0x23, 0x00, 0x02, 0x44, 0xC9, 0x41, 0x93, 0x77, 0x28, 0x81, 0x80, 0x14, 0x05, 0x02,
	0x04, 0x00, 0x06, 0x02, 0x04, 0x00, 0x07, 0x04, 0x00, 0x00, 0x00, 0x01, 0x08, 0x04, 0x00, 0x00,
	0x00, 0x01, 0x72, 0xE3, 0x7E };

uint8_t response_1[] = { 0x7E, 0xA0, 0x23, 0x41, 0x00, 0x02, 0x44, 0xC9, 0x73, 0xB9, 0x33, 0x81, 0x80, 0x14, 0x05, 0x02,
	0x04, 0x00, 0x06, 0x02, 0x04, 0x00, 0x07, 0x04, 0x00, 0x00, 0x00, 0x01, 0x08, 0x04, 0x00, 0x00,
	0x00, 0x01, 0x72, 0xE3, 0x7E };

uint8_t reqest_2[] = { 0x7E, 0xA0, 0x47, 0x00, 0x02, 0x44, 0xC9, 0x41, 0x10, 0x17, 0x55, 0xE6, 0xE6, 0x00, 0x60, 0x36,
	0xA1, 0x09, 0x06, 0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x01, 0x8A, 0x02, 0x07, 0x80, 0x8B,
	0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x02, 0x01, 0xAC, 0x0A, 0x80, 0x08, 0x31, 0x32, 0x33, 0x34,
	0x35, 0x36, 0x37, 0x38, 0xBE, 0x10, 0x04, 0x0E, 0x01, 0x00, 0x00, 0x00, 0x06, 0x5F, 0x1F, 0x04,
	0x00, 0xFF, 0xFF, 0xFF, 0x08, 0x00, 0xD5, 0x24, 0x7E };

uint8_t response_2[] = { 0x7E, 0xA0, 0x3A, 0x41, 0x00, 0x02, 0x44, 0xC9, 0x30, 0xD6, 0xB7, 0xE6, 0xE7, 0x00, 0x61, 0x29,
	0xA1, 0x09, 0x06, 0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x01, 0xA2, 0x03, 0x02, 0x01, 0x00,
	0xA3, 0x05, 0xA1, 0x03, 0x02, 0x01, 0x00, 0xBE, 0x10, 0x04, 0x0E, 0x08, 0x00, 0x06, 0x5F, 0x1F,
	0x04, 0x00, 0x00, 0x10, 0x15, 0x04, 0x00, 0x00, 0x07, 0x62, 0xC5, 0x7E };

uint8_t reqest_3[] = { 0x7E, 0xA0, 0x1C, 0x00, 0x02, 0x44, 0xC9, 0x41, 0x32, 0x4A, 0x53, 0xE6, 0xE6, 0x00, 0xC0, 0x01,
	0x40, 0x00, 0x03, 0x01, 0x00, 0x48, 0x07, 0x00, 0xFF, 0x02, 0x00, 0xE6, 0xE2, 0x7E };

uint8_t response_3[] = { 0x7E, 0xA0, 0x18, 0x41, 0x00, 0x02, 0x44, 0xC9, 0x52, 0xFA, 0xA3, 0xE6, 0xE7, 0x00, 0xC4, 0x01,
		0x40, 0x00, 0x17, 0x43, 0x67, 0x61, 0x40, 0x0A, 0x3A, 0x7E };

uint8_t reqest_4[] = { 0x7E, 0xA0, 0x1C, 0x00, 0x02, 0x44, 0xC9, 0x41, 0x54, 0x7A, 0x55, 0xE6, 0xE6, 0x00, 0xC0, 0x01,
	0x40, 0x00, 0x03, 0x01, 0x00, 0x48, 0x07, 0x00, 0xFF, 0x03, 0x00, 0x3E, 0xFB, 0x7E};

uint8_t response_4[] = { 0x7E, 0xA0, 0x19, 0x41, 0x00, 0x02, 0x44, 0xC9, 0x74, 0x1B, 0x78, 0xE6, 0xE7, 0x00, 0xC4, 0x01,
	0x40, 0x00, 0x02, 0x02, 0x0F, 0x00, 0x16, 0x23, 0x5A, 0x74, 0x7E};

uint8_t reqest_5[] = { 0x7E, 0xA0, 0x0A, 0x00, 0x02, 0x44, 0xC9, 0x41, 0x53, 0xC1, 0xCC, 0x7E};

uint8_t response_5[] = {0x7E, 0xA0, 0x21, 0x41, 0x00, 0x02, 0x44, 0xC9, 0x73, 0x02, 0x04, 0x81, 0x80, 0x12, 0x05, 0x01,
	0x80, 0x06, 0x01, 0x80, 0x07, 0x04, 0x00, 0x00, 0x00, 0x01, 0x08, 0x04, 0x00, 0x00, 0x00, 0x01, 0x53 , 0x3B, 0x7E};

//t_HDLC_pocket* pack = (t_HDLC_pocket*) buf;
//struct HDLC_get_pocket get_pack = {0};
uint8_t ERROR_repack=10;

uint8_t y;
uint16_t x;

uint8_t tesss(void* a) {
	return sizeof(a);
}

int main() {
	
	setlocale(LC_ALL, "ru_RU.utf8");

//СВЯЗЬ
	t_connect_data connect = {0};
	*connect.max_cadr_reception_data = 0x0400;
	connect.max_cadr_reception_len = 2;
	*connect.max_cadr_transmission_data = 0x0400;
	connect.max_cadr_transmission_len = 2;
	*connect.max_window_reception_data = 0x00000001;
	connect.max_window_reception_len = 4;
	*connect.max_window_transmission_data = 0x00000001;
	connect.max_window_transmission_len = 4;
	f_connect_pack(buf, sizeof(buf), connect);
	
	/*
//	cout << "ЗАПРОС 1" << endl << "размер сообщения = " << (int)f_HDLC_CalcPackSize(buf_test) << endl;
	cout << "ERROR= " << (int)f_HDLC_unpack(buf_test, sizeof(buf_test)) << endl; // TODO длину указывай как sizeof(buf_test)
	ERROR_repack=f_HDLC_unpack(buf_test, sizeof(buf_test));
	cout << endl << endl;

//	cout << "ОТВЕТ 1" << endl << "размер сообщения = " << (int)f_HDLC_CalcPackSize(buf_test_1) << endl;
	cout << "ERROR= " << (int)f_HDLC_unpack(buf_test_1, sizeof(buf_test)) << endl;
	ERROR_repack = f_HDLC_unpack(buf_test_1, sizeof(buf_test));
	cout << endl << endl;
	
//	cout << "ЗАПРОС 2" << endl << "размер сообщения = " << (int)f_HDLC_CalcPackSize(buf_test_2) << endl;
	cout << "ERROR= " << (int)f_HDLC_unpack(buf_test_2, sizeof(buf_test_2)) << endl;
	ERROR_repack = f_HDLC_unpack(buf_test_2, sizeof(buf_test_2));
	cout << endl << endl;

//	cout << "ОТВЕТ 2" << endl << "размер сообщения = " << (int)f_HDLC_CalcPackSize(buf_test_3) << endl;
	cout << "ERROR= " << (int)f_HDLC_unpack(buf_test_3, sizeof(buf_test_2)) << endl;
	ERROR_repack = f_HDLC_unpack(buf_test_3, sizeof(buf_test_2));
	cout << endl << endl;
	//f_HDLC_Print(&get_pack);
*/	
	//authorization(buf_regist, sizeof(buf_regist));
	
	return 0;
}
