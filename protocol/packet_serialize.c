#include <string.h>
#include <stdint.h>
#include "packet_serialize.h"
#include "packet.h"

void packet_serialize(packet_t *packet, uint8_t *tx_buffer,uint8_t * len)
{
    uint8_t idx = 0;
    tx_buffer[idx++] = packet->header;
    tx_buffer[idx++] = packet->cmd;
    tx_buffer[idx++] = packet->length;
    memcpy(&tx_buffer[idx] , packet->data , packet->length);
    idx += packet->length;
    tx_buffer[idx++] = packet->crc;
    *len = idx;
}