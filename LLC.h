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

#define LEN_FLOAT32		sizeof(float)
#define RES_0			0x01
#define RES_1			0x40
#define RES_2			0x00

#define LEN_OBIS		6

//параметры калибровки параметров связи
#define GROUP_ID					0x8180	//идентификатор группы
#define MAX_CADR_TRANSMISSION_ID	0x05	//идентификатор максимальной длинны кадра при передаче
#define MAX_CADR_RECEPTION_ID		0x06	//идентификатор максимальной длинны кадра при приеме
#define MAX_WINDOW_TRANSMISSION_ID	0x07	//идентификатор максимальной ширины окна при передаче
#define MAX_WINDOW_RECEPTION_ID		0x08	//идентификатор максимальной ширины окна при приеме

#define ID_SIZE						8		//суммарный размер идентификаторов параметров и их "размеров" в байтах

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

typedef struct
{
	uint8_t receiver;
	uint8_t source;
	uint8_t control;
	uint8_t tag;
}t_LLC;

typedef struct
{
	uint8_t tag;
	uint8_t reserv[3];
	uint8_t inf;
}t_LLC_inf;

typedef struct
{
	uint8_t clas;
	uint8_t param[6];
	uint8_t atr;
}t_LLC_inf_request;

typedef struct
{
	uint8_t type;
	uint8_t data;
}t_LLC_inf_response;

#endif // !_LLC_



