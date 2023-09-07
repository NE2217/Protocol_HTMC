#ifndef HDLC_PROTOCOL_H
#define HDLC_PROTOCOL_H

#include <stdint.h>
#include "pack.h"
#include "unpack.h"
#include "CRC.h"
#include "LLC.h"

#define FLAG		0x7e
#define HEADER_LEN	8 //байт, длинна заголовка
//команды в окне формат	
	
//Разряды байта управляющего поля	Команда / ответ					Формат
//1	 2	3	4	5	6	7	8		Тип кадра
//0	   N(S)	   P/F	   N(R)			-								I   информационный
//1	 0	0	0  P/F	   N(R)		RR - готов к приему					S	супервизорный
//1	 0	1	0  P/F	   N(R)		RNR - не готов к приему
//1	 0	0	1  P/F	   N(R)		REJ - отказ в приеме				
//1	 0	1	1  P/F	   N(R)		SREJ - выборочный отказ в приеме
//1	 1	0	0  P/F	0	0	0	UI - короткая информация			U	ненумерованный, управляющий
//1	 1	0	0	Р	0	0	1	SNRM - режим нормального ответа
//1	 1	0	0	Р	0	1	0	DISC - разъединить
//1	 1	0	0	Р	1	0	0	UP - ненумерованный опрос
//1	 1	0	0	F	1	1	0	UA - подтверждение
//1	 1	0	0  P/F	1	1	1	TEST - проверка
//1	 1	1	0  P/F	0	0	0	SIM - режим инициативного выхода
//1	 1	1	0	F	0	0	1	FRMR - неприем кадра
//1	 1	1	1	F	0	0	0	DM - "Разъединено"
//1	 1 	1	1	Р	0	0	1	RSET - сброс счетчика принятых кадров
//1	 1	1	1	Р	0	1	0	SARME - режим длинного асинхронного ответа
//1	 1	1	1	Р	0	1	1	SNRME - режим длинного нормального ответа
//1	 1	1	1	Р	1	0	0	SABM - асинхронный сбалансированный режим
//1	 1	1	1  P/F	1	0	1	XID - идентификация станции
//1	 1	1	1	Р	1	1	0	SABME - режим длинного сбалансированного асинхронного ответа


//											
//Маски команд (неопределенные биты нулевые)       Команда / ответ							 Формат                        
#define Inf		0x0	//										I   информационный

#define RR		0x1		//готов к приему					S	супервизорный
#define RNR		0x5		//не готов к приему
#define REJ		0x9		//отказ в приеме				
#define SREJ	0xD		//выборочный отказ в приеме

#define UI		0x3		//короткая информация				U	ненумерованный, управляющий
#define SNRM	0x83	//режим нормального ответа
#define DISC	0x43	//разъединить
#define UP		0x23	//ненумерованный опрос
#define UA		0x63	//подтверждение
#define TEST	0xC7	//проверка
#define SIM 	0x7		//режим инициативного выхода
#define FRMR	0x87	//неприем кадра
#define DM		0xF		//"Разъединено"
#define RSET	0x8F	//сброс счетчика принятых кадров
#define CF		0x4F	//режим длинного асинхронного ответа
#define SNRME	0xCF	//режим длинного нормального ответа
#define SABM	0x2F	//асинхронный сбалансированный режим
#define XID		0xAF	//идентификация станции
#define SABME	0x6F	//режим длинного сбалансированного асинхронного ответа

#pragma pack(push,1)
// TODO это две структуры объявлены правильно, кроме битовых полей. Остальные нужно сделать также
typedef struct {
	uint8_t comand;
	unsigned S : 3;
	unsigned R : 3;
	unsigned P : 1;
} t_control; // TODO добавляй t_  t_control

typedef struct {
	uint8_t* point;
	uint8_t len;
} t_HDLC_data;

/*
union HDLC_control {
	uint8_t point;
	struct {
		uint8_t reserve: 6;
		uint8_t type_2 : 1;
		uint8_t type_1 : 1;
	}win;
};
*/

union {
	unsigned char point;
	struct {
		unsigned char received_shot : 3;
		unsigned char tell_bit : 1;
		unsigned char sent_shot : 3;
		unsigned char format : 1;
	}win;
}t_HDLC_control_I;

union  {
	uint8_t point;
	struct {
		unsigned received_shot : 3;
		unsigned tell_bit : 1;
		unsigned s_code : 2;
		unsigned format : 2;
	}win;
}t_HDLC_control_S;

union  {
	uint8_t point;
	struct {
		unsigned u_code_second : 3;
		unsigned tell_bit : 1;
		unsigned u_code_first : 2;
		unsigned format : 2;
	}win;
}t_HDLC_control_U;

typedef union {
	uint16_t point;
	struct {
		unsigned size : 11; // TODO переделать все uint16_t в unsigned. Перепроверь все свои битовые поля
		unsigned S : 1;
		unsigned typ : 4;
	}form;
}t_format;

// TODO pocket - карман, packet - пакет. Нужно все pocket переименовать
typedef struct {
	uint8_t flag_open;
	t_format format;
	uint8_t DA_SA[5];//адрес назначения_источника
	uint8_t control;
	uint16_t HCS;//контрольная сумма загаловка
	uint8_t data;
}t_HDLC_packet_begin;


typedef struct  {
	uint16_t FCS;
	uint8_t flag_close;
}t_HDLC_packet_end;

typedef struct HDLC_get_pocket { // TODO не вижу смысла в этой структуре данных. Указатели можно использовать отдельно
	t_HDLC_packet_begin *begin;
	t_HDLC_packet_end *end;
};

typedef struct t_HDLC_pocket {
	uint8_t flag_open;
	uint8_t addr;
	uint8_t control;
	uint8_t data[10];
	uint16_t CRC;
	uint8_t flag_close;
};

typedef struct t_HDLC_data_U {
	uint8_t  param; //U,I,P
	uint16_t  value;
};

typedef struct t_HDLC_data_I {
	uint8_t param; //U,I,P
	uint8_t value;
};

typedef struct t_HDLC_data_P {
	uint8_t param; //U,I,P
	uint8_t value;
	uint8_t tupe; //P,Q,S
};

#pragma pack(pop)

#endif /*HDLC_PROTOCOL.h*/
