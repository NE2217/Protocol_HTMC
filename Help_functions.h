#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <iostream>

#include <assert.h>

uint16_t svipe(uint8_t* buf, uint16_t len) { // TODO swap - менять, swipe - махать
    uint16_t rev = NULL;
    for (int i = 0; i < 2; i++) {
        rev = (rev << 8) + buf[i];
    };
    return rev;
}
