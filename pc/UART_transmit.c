#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

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

    uint8_t packet[] = {0xFF , 0x03 , 0x03 , 0x04 , 0x05 , 0x02};
    DWORD bytesWritten = 0;

    BOOL ok = WriteFile(hSerial, packet, sizeof(packet), &bytesWritten, NULL);

    // const char *msg = "Hello UART\r\n";
    // DWORD bytesWritten = 0;

    // BOOL ok = WriteFile(hSerial, msg, strlen(msg), &bytesWritten, NULL);

    if (!ok) {
        printf("WriteFile failed\n");
    } else {
        printf("Sent %lu bytes\n", bytesWritten);
    }

    CloseHandle(hSerial);
    return 0;
}