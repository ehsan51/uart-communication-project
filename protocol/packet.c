#include <string.h>
#include "packet.h"
#include "../protocol/crc.h"
#include "../protocol/commands.h"

void packet_build(packet_t *packet, uint8_t cmd, uint8_t length, uint8_t *data)
{
    packet->header = 0xFF;
    packet->cmd = cmd;
    packet->length = length;

    // Checksum data 
    uint8_t crc_buffer[258];
    crc_buffer[0] = cmd;
    crc_buffer[1] = length;
    memcpy(&crc_buffer[2], data, length);
    uint8_t crc_value = crc(crc_buffer, length + 2);


    for(uint8_t i=0; i<length; i++)
    {
        packet->data[i] = data[i];
    }
    packet->crc = crc_value;

}
