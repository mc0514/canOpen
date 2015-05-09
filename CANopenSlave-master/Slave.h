#ifndef SLAVE_H
#define	SLAVE_H

// These are mapping constants for TPDO1
// starting at 0x1A00 in the dictionary
extern rom unsigned long uTPDO1Map;
extern rom unsigned long uRPDO1Map;
extern rom unsigned long uPDO1Dummy;


extern unsigned char uIOinFilter;				// 0x6003 filter
extern unsigned char uIOinPolarity;				// 0x6002 polarity
extern unsigned char uIOinIntChange;			// 0x6006 interrupt on change
extern unsigned char uIOinIntRise;				// 0x6007 interrupt on positive edge
extern unsigned char uIOinIntFall;				// 0x6008 interrupt on negative edge
extern unsigned char uIOinIntEnable;			// 0x6005 enable interrupts
extern unsigned char uIOinDigiInputs;			// 0x6000 digital inputs

extern unsigned char uIOinDigiInOld;			

extern unsigned char uLocalXmtBuffer[8];			// Local buffer for TPDO1
extern unsigned char uLocalRcvBuffer[8];			// local buffer fot RPDO1

extern rom unsigned char uDemoTPDO1Len;
extern rom unsigned char rMaxIndex1;
extern rom unsigned char rMaxIndex2;

void Slave_Init(void);
void Slave_ProcessEvents(void);

void CO_COMM_TPDO1_COBIDAccessEvent(void);
void CO_COMM_RPDO1_COBIDAccessEvent(void);
void CO_COMM_TPDO1_TypeAccessEvent(void);

#endif

