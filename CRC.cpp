#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include "CRC.h"

#include <assert.h>

using namespace std;
uint16_t f_crc16(uint8_t* data, uint16_t len) {
	
	uint16_t fcs = INIT_CRC;
	bool rot = 0;
	while (len--)
		fcs = (fcs >> 8) ^ fcstab[(fcs ^ *data++) & 0xff];

	fcs ^= 0xffff;
	if(rot)
		fcs = (fcs << 8) |
			(fcs >> ((sizeof(fcs) * CHAR_BIT - 8) %
				(sizeof(fcs) * CHAR_BIT)));
	return fcs;
}
