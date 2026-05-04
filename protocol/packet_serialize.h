#ifndef PACKET_SERIALIZE
#define PACKET_SERIALIZE
#include <stdint.h>
#include <stdint.h>
#include "packet.h"


void packet_serialize(packet_t *packet, uint8_t *tx_buffer,uint8_t * len);

#endif