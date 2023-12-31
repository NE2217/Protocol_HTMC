#ifndef _LLC_UNPACK_
#define _LLC_UNPACK_

#include <iostream>
#include <stdint.h>
#include <assert.h>
#include"LLC.h"

uint8_t unpack_LLC(uint8_t* data);
uint8_t unpack_LLC_inf(uint8_t* data);
uint8_t unpack_LLC_inf_response(uint8_t* data);
uint8_t f_connect_unpack(uint8_t* request, uint16_t request_len, uint8_t* response, uint16_t response_len);
#endif // !_LLC_UNPACK_


