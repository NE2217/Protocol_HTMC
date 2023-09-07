
#ifndef _LLC_PACK_
#define _LLC_PACK_

#include <iostream>;

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

#endif // !_LLC_PACK_

