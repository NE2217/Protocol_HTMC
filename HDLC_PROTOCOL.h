#pragma once
#ifndef HDLC_PROTOCOL_H
#define HDLC_PROTOCOL_H

#include "pack.h"
#include "repack.h"
#include "CRC.h"

#define FLAG		0x7e

#pragma pack(push,1)

typedef struct {
	uint8_t* point;
	uint8_t len;
} HDLC_data;

union HDLC_control {
	uint8_t point;
	struct {
		uint8_t reserve: 6;
		uint8_t type_2 : 1;
		uint8_t type_1 : 1;
	}win;
};

union HDLC_control_I {
	unsigned char point;
	struct {
		unsigned char received_shot : 3;
		unsigned char tell_bit : 1;
		unsigned char sent_shot : 3;
		unsigned char format : 1;
	}win;
};

union HDLC_control_S {
	unsigned char point;
	struct {
		unsigned char received_shot : 3;
		unsigned char tell_bit : 1;
		unsigned char s_code : 2;
		unsigned char format : 2;
	}win;
};

union HDLC_control_U {
	uint8_t point;
	struct {
		uint8_t u_code_second : 3;
		uint8_t tell_bit : 1;
		uint8_t u_code_first : 2;
		uint8_t format : 2;
	}win;
};

typedef struct HDLC_pocket_begin {
	uint8_t flag_open;
	uint8_t addr;
	union HDLC_control control;
	uint8_t data;
	//struct HDLC_data data;
};

typedef struct HDLC_pocket_end {
	uint16_t CRC;
	uint8_t flag_close;
};

typedef struct HDLC_get_pocket {
	struct HDLC_pocket_begin *begin;
	struct HDLC_pocket_end *end;
};

typedef struct HDLC_pocket {
	uint8_t flag_open;
	uint8_t addr;
	union HDLC_control control;
	uint8_t data[10];
	uint16_t CRC;
	uint8_t flag_close;
};

typedef struct HDLC_data_U {
	uint8_t  param; //U,I,P
	uint16_t  value;
};

typedef struct HDLC_data_I {
	uint8_t param; //U,I,P
	uint8_t value;
};

typedef struct HDLC_data_P {
	uint8_t param; //U,I,P
	uint8_t value;
	uint8_t tupe; //P,Q,S
};

#pragma pack(pop)

#endif /*HDLC_PROTOCOL.h*/
