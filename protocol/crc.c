#include <stdio.h>
#include <stdint.h>
#include "crc.h"

uint8_t crc(uint8_t *data , uint8_t length)
{
    printf("crc - data : %d" , data[0]);
    printf("crc - data : %d" , data[1]);
    printf("crc - data : %d" , data[2]);
    printf("crc - data : %d" , data[3]);
    uint8_t crc = 0;

    for(int i=0; i<length; i++)
    {
        crc ^= data[i];
    }
    return crc;
}