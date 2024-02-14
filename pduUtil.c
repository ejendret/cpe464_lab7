#include "pduUtil.h";

int createPDU(uint8_t *pduBuffer, uint32_t sequenceNumber, uint8_t flag, uint8_t *payload, int payloadLen)
{
    int pduLength = -1;

    uint32_t netSequenceNumber = htonl(sequenceNumber);
    uint32_t index = 0;
    memcpy(pduBuffer + index, &netSequenceNumber, 4);
    index += 4;
    return pduLength;
}
