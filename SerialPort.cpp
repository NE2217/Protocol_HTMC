
#include <iostream>
#include <Windows.h>

using namespace std;

HANDLE hSerial;

uint8_t ConfigCOM() {
    LPCTSTR sPortName = L"COM4";
    hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            cout << "serial port does not exist.\n";
        }
        cout << "some other error occurred.\n";
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        cout << "getting state error\n";
    }
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        cout << "error setting serial port state\n";
    }
    return 0;
}

bool ReadCOM(uint8_t* buf)
{
    uint8_t* get = buf;
    DWORD iSize;
    uint8_t sReceivedChar;
   /* while (true)
    {*/
        ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // получаем 1 байт
        if (iSize > 0) {   // если что-то принято, выводим
            *get = sReceivedChar;
            return true;
        }
    //}
    return false;
}

int WriteCOM(void* data, uint16_t len)
{
     //    uint8_t data[] = { 0x7E, 0xA0, 0x23, 0x00, 0x02, 0x44, 0xC9,
    //0x61, 0x93, 0x44, 0x0B, 0x81, 0x80, 0x14, 0x05, 0x02,
    //0x04, 0x00, 0x06, 0x02, 0x04, 0x00, 0x07, 0x04, 0x00, 0x00, 0x00, 0x01, 0x08,
    //0x04, 0x00, 0x00, 0x00, 0x01, 0x72, 0xE3, 0x7E };  // строка для передачи
    DWORD dwSize = len;   // размер этой строки
    DWORD dwBytesWritten;    // тут будет количество собственно переданных байт

    BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);

    cout << dwSize << " Bytes in string. " << dwBytesWritten << " Bytes sended. " << endl;
    return 0;
}