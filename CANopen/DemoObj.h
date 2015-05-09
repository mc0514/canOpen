/*****************************************************************************
 *
 * Microchip CANopen Stack (Demonstration Object)
 *
 *****************************************************************************
 * FileName:        DEMOOBJ.H
 * Dependencies:    
 * Processor:       PIC18F with CAN
 * Compiler:       	C18 02.30.00 or higher
 * Linker:          MPLINK 03.70.00 or higher
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the "Company") is intended and supplied to you, the Company's
 * customer, for use solely and exclusively with products manufactured
 * by the Company. 
 *
 * The software is owned by the Company and/or its supplier, and is 
 * protected under applicable copyright laws. All rights are reserved. 
 * Any use in violation of the foregoing restrictions may subject the 
 * user to criminal sanctions under applicable laws, as well as to 
 * civil liability for the breach of the terms and conditions of this 
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES, 
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT, 
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR 
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * 
 * 
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ross Fosler			11/13/03	...	
 * 
 *****************************************************************************/


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

extern unsigned char uIOinDigiInOld;				// 

extern unsigned char uLocalXmtBuffer[8];			// Local buffer for TPDO1
extern unsigned char uLocalRcvBuffer[8];			// local buffer fot RPDO1

extern rom unsigned char uDemoTPDO1Len;
extern rom unsigned char rMaxIndex1;
extern rom unsigned char rMaxIndex2;


void DemoProcessEvents(void);
void DemoInit(void);
void CO_COMM_TPDO1_COBIDAccessEvent(void);
void CO_COMM_RPDO1_COBIDAccessEvent(void);
void CO_COMM_TPDO1_TypeAccessEvent(void);





