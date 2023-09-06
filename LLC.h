#ifndef _LLC_
#define _LLC_

#include <stdint.h>
#include "LLC_unpack.h"
#include "LLC_pack.h"

#define RECEIVER		0xE6
#define COMMAND			0xE6
#define RESULT			0xE7
#define CONTROL			0

#define GET_request 	0xC0
#define GET_response 	0xC4

#define LEN_FLOAT32		4


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

typedef struct{
	uint8_t receiver;
	uint8_t source;
	uint8_t соntrol;
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



