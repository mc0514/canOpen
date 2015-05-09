#ifndef	__CO_PDO1_H
#define	__CO_PDO1_H

#include <p18F4680.h>

extern rom unsigned long uRPDOMap1;
extern rom unsigned long uRPDOMap2;
extern rom unsigned long uRPDOMap3;
extern rom unsigned long uRPDOMap4;


void _CO_COMM_RPDO1_COBIDAccessEvent(void);
void _CO_COMM_RPDO1_TypeAccessEvent(void);

void _CO_COMM_TPDO1_COBIDAccessEvent(void);
void _CO_COMM_TPDO1_TypeAccessEvent(void);
void _CO_COMM_TPDO1_ITimeAccessEvent(void);
void _CO_COMM_TPDO1_ETimeAccessEvent(void);

#endif

