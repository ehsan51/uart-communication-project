#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

typedef struct {
    uint8_t header;
    uint8_t cmd;
    uint8_t length;
    uint8_t data[256];
    uint8_t crc;

}packet_t;

void packet_build(packet_t *packet, uint8_t cmd, uint8_t length, uint8_t *data);

#endif