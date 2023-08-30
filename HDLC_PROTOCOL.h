#pragma once
#ifndef HDLC_PROTOCOL_H
#define HDLC_PROTOCOL_H

#include <stdint.h>
#include "pack.h"
#include "repack.h"
#include "CRC.h"

#define FLAG		0x7e
//������� � ���� ������	
	
//������� ����� ������������ ����	������� / �����					������
//1	 2	3	4	5	6	7	8		��� �����
//0	   N(S)	   P/F	   N(R)			-								I   ��������������
//1	 0	0	0  P/F	   N(R)		RR - ����� � ������					S	�������������
//1	 0	1	0  P/F	   N(R)		RNR - �� ����� � ������
//1	 0	0	1  P/F	   N(R)		REJ - ����� � ������				
//1	 0	1	1  P/F	   N(R)		SREJ - ���������� ����� � ������
//1	 1	0	0  P/F	0	0	0	UI - �������� ����������			U	��������������, �����������
//1	 1	0	0	�	0	0	1	SNRM - ����� ����������� ������
//1	 1	0	0	�	0	1	0	DISC - �����������
//1	 1	0	0	�	1	0	0	UP - �������������� �����
//1	 1	0	0	F	1	1	0	UA - �������������
//1	 1	0	0  P/F	1	1	1	TEST - ��������
//1	 1	1	0  P/F	0	0	0	SIM - ����� ������������� ������
//1	 1	1	0	F	0	0	1	FRMR - ������� �����
//1	 1	1	1	F	0	0	0	DM - "�����������"
//1	 1 	1	1	�	0	0	1	RSET - ����� �������� �������� ������
//1	 1	1	1	�	0	1	0	SARME - ����� �������� ������������ ������
//1	 1	1	1	�	0	1	1	SNRME - ����� �������� ����������� ������
//1	 1	1	1	�	1	0	0	SABM - ����������� ���������������� �����
//1	 1	1	1  P/F	1	0	1	XID - ������������� �������
//1	 1	1	1	�	1	1	0	SABME - ����� �������� ����������������� ������������ ������


//											
//����� ������ (�������������� ���� �������)       ������� / �����							 ������                        
#define Inf		0x0	//										I   ��������������

#define RR		0x1	//����� � ������						S	�������������
#define RNR		0x5	//�� ����� � ������
#define REJ		0x9	//����� � ������				
#define SREJ	0xD	//���������� ����� � ������

#define UI		0x3	//�������� ����������					U	��������������, �����������
#define SNRM	0x83	//����� ����������� ������
#define DISC	0x43	//�����������
#define UP		0x23	//�������������� �����
#define UA		0x63	//�������������
#define TEST	0xC7	//��������
#define SIM 	0x7	//����� ������������� ������
#define FRMR	0x87	//������� �����
#define DM		0xF	//"�����������"
#define RSET	0x8F	//����� �������� �������� ������
#define CF		0x4F	//����� �������� ������������ ������
#define SNRME	0xCF	//����� �������� ����������� ������
#define SABM	0x2F	//����������� ���������������� �����
#define XID		0xAF	//������������� �������
#define SABME	0x6F	//����� �������� ����������������� ������������ ������

#pragma pack(push,1)

typedef struct {
	uint8_t comand;
	uint8_t S : 3;
	uint8_t R : 3;
	uint8_t P : 1;
} control;

typedef struct {
	uint8_t* point;
	uint8_t len;
} HDLC_data;

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
	uint8_t point;
	struct {
		unsigned received_shot : 3;
		unsigned tell_bit : 1;
		unsigned s_code : 2;
		unsigned format : 2;
	}win;
};

union HDLC_control_U {
	uint8_t point;
	struct {
		unsigned u_code_second : 3;
		unsigned tell_bit : 1;
		unsigned u_code_first : 2;
		unsigned format : 2;
	}win;
};

typedef union format{
	uint16_t point;
	struct {
		uint16_t size : 11;
		uint16_t S : 1;
		uint16_t typ : 4;
	}form;
};


typedef struct HDLC_pocket_begin{
	uint8_t flag_open;
	format format;
	uint8_t DA_SA[5];//����� ����������_���������
	uint8_t control;
	uint16_t HCS;//����������� ����� ���������
	uint8_t data;
};


typedef struct HDLC_pocket_end {
	uint16_t FCS;
	uint8_t flag_close;
};

typedef struct HDLC_get_pocket {
	struct HDLC_pocket_begin *begin;
	struct HDLC_pocket_end *end;
};

typedef struct HDLC_pocket {
	uint8_t flag_open;
	uint8_t addr;
	uint8_t control;
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
