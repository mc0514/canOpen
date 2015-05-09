/*****************************************************************************
 *
 * Microchip CANopen Stack (Process Data Objects)
 *
 *****************************************************************************
 * FileName:        CO_PDO.C
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

#include	"CO_DEFS.DEF"			// Global definitions
#include	"CO_TYPES.H"			// Data types
#include	"CO_CANDRV.H"			// Driver services
#include	"CO_COMM.H"				// Object
#include	"CO_PDO.H"



#if CO_NUM_OF_PDO < 1
	#error "Number of PDOs too low, must have at least 1..."
#endif

#if CO_NUM_OF_PDO > 4
	#error "Number of PDOs too high, this version only supports up to 4 PDOs..."
#endif


UNSIGNED32		uRPDOComm1;		// RPDO communication setting
UNSIGNED32		uTPDOComm1;		// TPDO communication setting
_PDOBUF 		_uPDO1;
unsigned char           _uPDOHandles1;

#if CO_NUM_OF_PDO > 1
UNSIGNED32		uRPDOComm2;		// RPDO communication setting
UNSIGNED32		uTPDOComm2;		// TPDO communication setting
_PDOBUF 		_uPDO2;
unsigned char 	_uPDOHandles2;
#endif

#if CO_NUM_OF_PDO > 2
UNSIGNED32		uRPDOComm3;		// RPDO communication setting
UNSIGNED32		uTPDOComm3;		// TPDO communication setting
_PDOBUF 		_uPDO3;
unsigned char 	_uPDOHandles3;
#endif

#if CO_NUM_OF_PDO > 3
UNSIGNED32		uRPDOComm4;		// RPDO communication setting
UNSIGNED32		uTPDOComm4;		// TPDO communication setting
_PDOBUF 		_uPDO4;
unsigned char 	_uPDOHandles4;
#endif


void _CO_COMM_PDO1_Open(void)
{
	// Call the driver and request to open a receive endpoint
	mCANOpenMessage((COMM_MSGGRP_PDO) | COMM_PDO_1, uRPDOComm1.word, _uPDOHandles1);
	if (_uPDOHandles1) COMM_RPDO_1_EN = 1;	
}

void _CO_COMM_PDO1_Close(void)
{
	// Call the driver, request to close the receive endpoint
	mCANCloseMessage(_uPDOHandles1);
	COMM_RPDO_1_EN = 0;	
}

void _CO_COMM_PDO1_RXEvent(void)
{
	*((_DATA8 *)(_uPDO1.RPDO.buf)) = *((_DATA8 *)(mCANGetPtrRxData()));
	_uPDO1.RPDO.len = mCANGetDataLen();
}

void _CO_COMM_PDO1_TXEvent(void)
{
	// Set the COB
	*(unsigned long *)(mCANGetPtrTxCOB()) = uTPDOComm1.word; //orig
        //*(unsigned long *)(mCANGetPtrTxCOB()) = 0; //test
	
	// Call the driver, load data to transmit
	*((_DATA8 *)(mCANGetPtrTxData())) = *((_DATA8 *)(_uPDO1.TPDO.buf));
	mCANPutDataLen(_uPDO1.TPDO.len);
}






#if CO_NUM_OF_PDO > 1
void _CO_COMM_PDO2_Open(void)
{
	// Call the driver and request to open a receive endpoint
	mCANOpenMessage((COMM_MSGGRP_PDO) | COMM_PDO_2, uRPDOComm2.word, _uPDOHandles2);
	if (_uPDOHandles2) COMM_RPDO_2_EN = 1;	
}

void _CO_COMM_PDO2_Close(void)
{
	// Call the driver, request to close the receive endpoint
	mCANCloseMessage(_uPDOHandles2);
	COMM_RPDO_2_EN = 0;	
}

void _CO_COMM_PDO2_RXEvent(void)
{
	*((_DATA8 *)(_uPDO2.RPDO.buf)) = *((_DATA8 *)(mCANGetPtrRxData()));
	_uPDO2.RPDO.len = mCANGetDataLen();
}

void _CO_COMM_PDO2_TXEvent(void)
{
	// Set the COB
	*(unsigned long *)(mCANGetPtrTxCOB()) = uTPDOComm2.word;

	// Call the driver, load data to transmit
	*((_DATA8 *)(mCANGetPtrTxData())) = *((_DATA8 *)(_uPDO2.TPDO.buf));
	mCANPutDataLen(_uPDO2.TPDO.len);
}
#endif



#if CO_NUM_OF_PDO > 2
void _CO_COMM_PDO3_Open(void)
{
	// Call the driver and request to open a receive endpoint
	mCANOpenMessage((COMM_MSGGRP_PDO) | COMM_PDO_3, uRPDOComm3.word, _uPDOHandles3);
	if (_uPDOHandles3) COMM_RPDO_3_EN = 1;	
}

void _CO_COMM_PDO3_Close(void)
{
	// Call the driver, request to close the receive endpoint
	mCANCloseMessage(_uPDOHandles3);
	COMM_RPDO_3_EN = 0;	
}

void _CO_COMM_PDO3_RXEvent(void)
{
	*((_DATA8 *)(_uPDO3.RPDO.buf)) = *((_DATA8 *)(mCANGetPtrRxData()));
	_uPDO3.RPDO.len = mCANGetDataLen();
}

void _CO_COMM_PDO3_TXEvent(void)
{
	// Set the COB
	*(unsigned long *)(mCANGetPtrTxCOB()) = uTPDOComm3.word;

	// Call the driver, load data to transmit
	*((_DATA8 *)(mCANGetPtrTxData())) = *((_DATA8 *)(_uPDO3.TPDO.buf));
	mCANPutDataLen(_uPDO3.TPDO.len);
}
#endif



#if CO_NUM_OF_PDO > 3
void _CO_COMM_PDO4_Open(void)
{
	// Call the driver and request to open a receive endpoint
	mCANOpenMessage((COMM_MSGGRP_PDO) | COMM_PDO_4, uRPDOComm4.word, _uPDOHandles4);
	if (_uPDOHandles4) COMM_RPDO_4_EN = 1;	
}

void _CO_COMM_PDO4_Close(void)
{
	// Call the driver, request to close the receive endpoint
	mCANCloseMessage(_uPDOHandles4);
	COMM_RPDO_4_EN = 0;	
}

void _CO_COMM_PDO4_RXEvent(void)
{
	*((_DATA8 *)(_uPDO4.RPDO.buf)) = *((_DATA8 *)(mCANGetPtrRxData()));
	_uPDO4.RPDO.len = mCANGetDataLen();
}

void _CO_COMM_PDO4_TXEvent(void)
{
	// Set the COB
	*(unsigned long *)(mCANGetPtrTxCOB()) = uTPDOComm4.word;

	// Call the driver, load data to transmit
	*((_DATA8 *)(mCANGetPtrTxData())) = *((_DATA8 *)(_uPDO4.TPDO.buf));
	mCANPutDataLen(_uPDO4.TPDO.len);
}
#endif










