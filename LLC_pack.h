
#ifndef _LLC_PACK_
#define _LLC_PACK_

#include <iostream>;

typedef struct {
	uint8_t* max_cadr_transmission_data;
	uint8_t max_cadr_transmission_len;
	uint8_t* max_cadr_reception_data;
	uint8_t max_cadr_reception_len;
	uint8_t* max_window_transmission_data;
	uint8_t max_window_transmission_len;
	uint8_t* max_window_reception_data;
	uint8_t max_window_reception_len;
}t_connect_data;

typedef struct {
	uint8_t ID;
	uint8_t len;
	uint8_t* data;
}t_connect_param;

typedef struct {
	uint8_t group_id;
	uint8_t len_group_id;
	t_connect_param max_cadr_transmission;
	t_connect_param max_cadr_reception;
	t_connect_param max_window_transmission;
	t_connect_param max_window_reception;
}t_connect;

typedef struct {
	uint8_t receiver;
	uint8_t source;
	uint8_t control;
	uint8_t tag;
	uint8_t reserv[3];
	uint8_t clas;
	uint8_t param[6];
	uint8_t atr;
}t_LLC_inf_request_pack;

typedef struct {
	uint8_t receiver;
	uint8_t source;
	uint8_t ñîntrol;
	uint8_t reserv_1[30];
	uint8_t pasword[8];
	uint8_t reserv_2[18];
}t_LLC_pasword_pack;

uint8_t f_connect_pack(uint8_t* buf, uint16_t len, t_connect_data data);

#endif // !_LLC_PACK_

