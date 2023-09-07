
#ifndef _LLC_PACK_
#define _LLC_PACK_

#include <iostream>;

typedef struct {
	uint8_t receiver;
	uint8_t source;
	uint8_t ñîntrol;
	uint8_t tag;
	uint8_t reserv[3];
	uint8_t clas;
	uint8_t param[6];
	uint8_t atr;
}t_LLC_inf_request_pack;

#endif // !_LLC_PACK_

