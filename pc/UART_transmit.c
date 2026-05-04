#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../protocol/commands.h"
#include "../protocol/packet.h"
#include "../protocol/crc.h"
#include "../protocol/packet_serialize.h"


int main() {
    HANDLE hSerial;

    hSerial = CreateFileA("\\\\.\\COM14",
                          GENERIC_WRITE,
                          0,
                          NULL,
                          OPEN_EXISTING,
                          0,
                          NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error opening serial port\n");
        return 1;
    }

    // IMPORTANT: clear buffers
    PurgeComm(hSerial, PURGE_TXCLEAR | PURGE_RXCLEAR);

    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);

    if (!GetCommState(hSerial, &dcb)) {
        printf("GetCommState failed\n");
        CloseHandle(hSerial);
        return 1;
    }

    dcb.BaudRate = CBR_115200;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity   = NOPARITY;

    if (!SetCommState(hSerial, &dcb)) {
        printf("SetCommState failed\n");
        CloseHandle(hSerial);
        return 1;
    }


    COMMTIMEOUTS timeouts = {0};
    timeouts.WriteTotalTimeoutConstant = 1000;
    timeouts.WriteTotalTimeoutMultiplier = 0;
    SetCommTimeouts(hSerial, &timeouts);

    // Packet initialization
    packet_t packet = {0};
    uint8_t data[2] = {0x04,0x06};
    uint8_t data_length = 2;
    packet_build(&packet, CMD_LED_ON, data_length , data);

    // Debuging part
    printf("\npacket.header : %x", packet.header);
    printf("\nCOMMAND : %d", CMD_LED_OFF);
    printf("\ndata[0] : %x", data[0]);
    printf("\ndata[1] : %x", data[1]);
    printf("\nCRC : %x", packet.crc);
    printf("\n");

    // Packet serialization
    uint8_t tx_buffer[260];
    uint8_t len = 0;
    packet_serialize(&packet , tx_buffer , &len);

    DWORD bytesWritten = 0;
    // BOOL ok = WriteFile(hSerial, tx_buffer, len, &bytesWritten, NULL);
    BOOL ok = 0;
    for (int i = 0; i < len; i++)
    {
        ok = WriteFile(hSerial, &tx_buffer[i], 1, &bytesWritten, NULL);
        Sleep(2);   //  2–10 ms for improve stable receiving by STM32
    }

    if (!ok) {
        printf("WriteFile failed\n");
    } else {
        printf("Sent %lu bytes\n", bytesWritten);
    }

    CloseHandle(hSerial);
    return 0;
}

