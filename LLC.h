#ifndef _LLC_
#define _LLC_

#include <stdint.h>
#include "LLC_unpack.h"
#include "LLC_pack.h"

#define RECEIVER		0xE6
#define COMMAND			0xE6
#define RESULT			0xE7
#define CONTROL			0
#define CLASS			0x3
#define ATRIBUT			0x2

#define GET_request 	0xC0
#define GET_response 	0xC4

#define LEN_FLOAT32		sizeof(float32) // TODO sizeof(float32)
#define RES_0			0x01
#define RES_1			0x40
#define RES_2			0x00

#define LEN_FLOAT32		4

#define LEN_OBIS		6

//параметры калибровки параметров связи
#define GROUP_ID					0x8180	//идентификатор группы
#define MAX_CADR_TRANSMISSION_ID	0x05	//идентификатор максимальной длинны кадра при передаче
#define MAX_CADR_RECEPTION_ID		0x06	//идентификатор максимальной длинны кадра при приеме
#define MAX_WINDOW_TRANSMISSION_ID	0x07	//идентификатор максимальной ширины окна при передаче
#define MAX_WINDOW_RECEPTION_ID		0x08	//идентификатор максимальной ширины окна при приеме

#define ID_SIZE						8		//суммарный размер идентификаторов параметров и их "размеров" в байтах

//передача пароля
static uint8_t PASWORD_RESERV_1[] = { 0x60, 0x36, 0xA1, 0x09, 0x06, 0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x01, 0x8A, 0x02, 0x07, 0x80, 0x8B,
0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x02, 0x01, 0xAC, 0x0A, 0x80, 0x08 };
static uint8_t PASWORD_RESERV_2[] = { 0xBE, 0x10, 0x04, 0x0E, 0x01, 0x00, 0x00, 0x00, 0x06, 0x5F, 0x1F, 0x04, 0x00, 0xFF, 0xFF, 0xFF, 0x08, 0x00 };
#define PASSWORD					"12345678"
static uint8_t PASWORD_RESPONSE[] = { 0xE6, 0xE7, 0x00, 0x61, 0x29,
	0xA1, 0x09, 0x06, 0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x01, 0xA2, 0x03, 0x02, 0x01, 0x00,
	0xA3, 0x05, 0xA1, 0x03, 0x02, 0x01, 0x00, 0xBE, 0x10, 0x04, 0x0E, 0x08, 0x00, 0x06, 0x5F, 0x1F,
	0x04, 0x00, 0x00, 0x10, 0x15, 0x04, 0x00, 0x00, 0x07 };

//OBIS-коды
static uint8_t OBIS_VOLTAGE_A[] = { 1,0,32,7,0,255 };//LAST_REQUEST =  1
static uint8_t OBIS_VOLTAGE_B[] = { 1,0,52,7,0,255 };//LAST_REQUEST =  2
static uint8_t OBIS_VOLTAGE_C[] = { 1,0,72,7,0,255 };//LAST_REQUEST =  3

static uint8_t OBIS_CURRENT_A[] = { 1,0,31,7,0,255 };//LAST_REQUEST =  4
static uint8_t OBIS_CURRENT_B[] = { 1,0,51,7,0,255 };//LAST_REQUEST =  5
static uint8_t OBIS_CURRENT_C[] = { 1,0,71,7,0,255 };//LAST_REQUEST =  6
//полная мощьность по фазам
static uint8_t OBIS_POWER_A[] = { 1,0,29,7,0,255 };//LAST_REQUEST =  7
static uint8_t OBIS_POWER_B[] = { 1,0,49,7,0,255 };//LAST_REQUEST =  8
static uint8_t OBIS_POWER_C[] = { 1,0,69,7,0,255 };//LAST_REQUEST =  9

static uint8_t OBIS_ENERGY_ACTIVE_IMPORT[] = { 1,0,1,8,0,255 };//LAST_REQUEST =  10
static uint8_t OBIS_ENERGY_ACTIVE_EXPORT[] = { 1,0,2,8,0,255 };//LAST_REQUEST =  11
static uint8_t OBIS_ENERGY_REACTIVE_IMPORT[] = { 1,0,3,8,0,255 };//LAST_REQUEST =  12
static uint8_t OBIS_ENERGY_REACTIVE_EXPORT[] = { 1,0,4,8,0,255 };//LAST_REQUEST =  13

static uint8_t* OBIS[] = { OBIS_VOLTAGE_A, OBIS_VOLTAGE_B, OBIS_VOLTAGE_C, OBIS_CURRENT_A, OBIS_CURRENT_B, OBIS_CURRENT_C,
							OBIS_POWER_A, OBIS_POWER_B, OBIS_POWER_C, OBIS_ENERGY_ACTIVE_IMPORT, OBIS_ENERGY_ACTIVE_EXPORT,
							OBIS_ENERGY_REACTIVE_IMPORT, OBIS_ENERGY_REACTIVE_EXPORT };

typedef struct {
	uint8_t type;
	uint8_t len;
	uint8_t data[10];
}t_param_inf;

//хранение данных
extern t_param_inf voltage_A;
extern t_param_inf voltage_B;
extern t_param_inf voltage_C;

extern t_param_inf current_A;
extern t_param_inf current_B;
extern t_param_inf current_C;
//полная мощьность по фазам
extern t_param_inf power_A;
extern t_param_inf power_B;
extern t_param_inf power_C;

extern t_param_inf energy_active_import;
extern t_param_inf energy_active_export;
extern t_param_inf energy_reactive_import;
extern t_param_inf energy_reactive_export;

extern uint8_t LAST_REQUEST;
// TODO похоже, что в слове control первые два символа "co" написаны русскими буквами (переписал)
typedef struct{
	uint8_t receiver;
	uint8_t source;
	uint8_t control;
	uint8_t tag;
}t_LLC;

typedef struct {
	uint8_t tag;
	uint8_t reserv[3];
	uint8_t inf;
}t_LLC_inf;

typedef struct {
	uint8_t clas;
	uint8_t param[6];
	uint8_t atr;
}t_LLC_inf_request;

typedef struct {
	uint8_t type;
	uint8_t data;
}t_LLC_inf_response;

#endif // !_LLC_



