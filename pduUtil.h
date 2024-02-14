#ifndef __PDU_UTIL_H__
#define __PDU_UTIL_H__

#include "networks.h"
#include "checksum.h"

// Defines
#define HEADER_LEN 7

// Functions
int createPDU(uint8_t *pduBuffer, uint32_t sequenceNumber, uint8_t flag, uint8_t *payload, int payloadLen);
void printPDU(uint8_t *aPDU, int pduLength);

#endif