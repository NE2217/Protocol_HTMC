#include"Help_functions.h"

#include <stdlib.h>
#include <stdint.h>
#include <iostream>

#include <assert.h>
#include <string.h>

//#define SWAP_UINT16(val) (uint16_t)( ((val & 0xFF)<<8)|((val & 0xFF00)>>8) )

uint16_t swap(uint8_t* buf, uint16_t len)
{
    uint16_t rev = 0;
    for (int i = 0; i < 2; i++) {
        rev = (rev << 8) + buf[i];
    };
    return rev;
}

//bool ComparringArrays(void* a, void* b)
//{
//
//    if ( (sizeof(a) == sizeof(b)) && !(memcmp(a, b, sizeof(a))) )
//    	return true; // TODO для memcmp #include "string.h"
//
//    else return false;
//}
