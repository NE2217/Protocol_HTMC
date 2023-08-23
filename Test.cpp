//#include <stdint.h>
//#include <iostream>
//#include "HDLC_PROTOCOL.h"
//
//using namespace std;
//
//typedef struct
//{
//	uint8_t a;
//	uint8_t b;
//} t_str;
//
//typedef struct
//{
//	uint8_t p;
//	uint8_t ar[10];
//} t_ar;
//
//
//void Pack(uint8_t* data, uint16_t len);
//void Repack(uint8_t* data, uint16_t len);
//
//int main()
//{
//	t_ar ar_p[10] = {NULL};
//	uint16_t size_ar = { NULL };
//
//	size_ar=sizeof(ar_p->ar) / sizeof(ar_p->ar[0]);
//	cout << "size_ar = " << size_ar << endl;
//
//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
//
//	uint8_t buf[100] = { 0 };
//	t_str* p_data = (t_str*)buf;
//
//	cout << "a = " << p_data->a << "; b = " << p_data->b << endl;
//	Pack(buf, 100);
//	cout << "a = " << p_data->a << "; b = " << p_data->b << endl;
//
//	Repack(buf, sizeof(t_str));
//
//	return 0;
//}
//
//
//
//void Pack(uint8_t* data, uint16_t len)
//{
//	t_str* p_data = (t_str*)data;
//
//	if (len < sizeof(t_str))
//		return;
//
//	p_data->a = 'A';
//	p_data->b = 'B';
//}
//
//
//void Repack(uint8_t* data, uint16_t len)
//{
//	t_str* p_data = (t_str*)data;
//
//	if (len < sizeof(t_str))
//		return;
//
//	if (p_data->a == 'A')
//		cout << "A. OK" << endl;
//	else
//		cout << "A. NOT OK" << endl;
//	if (p_data->b == 'B')
//		cout << "B. OK" << endl;
//	else
//		cout << "B. NOT OK" << endl;
//}
