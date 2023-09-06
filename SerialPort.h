#ifndef COM
#define COM

#include <iostream>
#include <Windows.h>

uint8_t ConfigCOM();
bool ReadCOM(uint8_t* buf);
int WriteCOM(void* data, uint16_t len);

#endif // !COM


