#include "pduUtil.h"

int createPDU(uint8_t *pduBuffer, uint32_t sequenceNumber, uint8_t flag, uint8_t *payload, int payloadLen)
{
    int pduLength = -1;

    uint32_t netSequenceNumber = htonl(sequenceNumber);
    uint32_t index = 0;

    // Copy network sequence number
    memcpy(pduBuffer + index, &netSequenceNumber, 4);
    index += 4;

    // Skip checksum for now, will compute after
    int checksumIndex = index;
    index += 2;

    // Copy flag
    memcpy(pduBuffer + index, &flag, 1);
    index += 1;

    // Copy payload
    memcpy(pduBuffer + index, payload, payloadLen);
    index += payloadLen;

    // Compute checksum and copy into buffer
    unsigned short checksum = in_cksum((unsigned short *)pduBuffer, index);
    unsigned short netChecksum = htons(checksum);
    memcpy(pduBuffer + checksumIndex, &netChecksum, 2);

    pduLength = index;

    return pduLength;
}

void printPDU(uint8_t *aPDU, int pduLength)
{
}
