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
    uint16_t checksum = in_cksum((unsigned short *)pduBuffer, index);
    memcpy(pduBuffer + checksumIndex, &checksum, 2);

    pduLength = index;

    return pduLength;
}

void printPDU(uint8_t *aPDU, int pduLength)
{
    uint32_t sequenceNum;
    uint32_t hostSequenceNum;
    uint16_t checksum;
    uint8_t flag;
    uint32_t index = 0;

    memcpy(&sequenceNum, aPDU + index, 4);
    hostSequenceNum = ntohl(sequenceNum);
    index += 4;
    memcpy(&checksum, aPDU + index, 2);
    index += 2;
    memcpy(&flag, aPDU + index, 1);
    index += 1;

    // Print static
    printf("Sequence number: %d\n", hostSequenceNum);
    printf("Flag: %d\n", flag);

    // Print payload
    int payloadLength = pduLength - index;
    uint8_t payloadBuffer[payloadLength + 1];
    memset(payloadBuffer, 0, payloadLength + 1);
    memcpy(payloadBuffer, aPDU + index, payloadLength);

    printf("Payload: %s\n", payloadBuffer);
    printf("Payload length: %d\n", payloadLength);

    uint8_t checksumRes = in_cksum((unsigned short *)aPDU, pduLength);
    if (checksumRes != 0)
    {
        fprintf(stderr, "Checksum failed: %d\n", checksum);
    }
}
