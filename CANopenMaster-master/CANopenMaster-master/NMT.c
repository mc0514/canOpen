#include	"CO_TYPES.H"			
#include	"CO_CANDRV.H"			
#include	"CO_COMM.H"			
#include        "NMT.h"
#include        "NMTextension.h"
#include        "Globals.h"


// Handle for NMT
unsigned char _hNMT;

unsigned char _NMT_TxNodeID;
unsigned char _NMT_TxState;


void _CO_COMM_NMT_Open(void)
{
	// Open a receive message endpoint in the driver
	mCANOpenMessage((COMM_MSGGRP_NETCTL) | COMM_NETCTL_NMT, 0x00L, _hNMT);

	// Enable NMT
	if (_hNMT) COMM_NETCTL_NMT_EN = 1;
}


void _CO_COMM_NMT_Close(void)
{
	// Call the driver, request to close the receive endpoint
	mCANCloseMessage(_hNMT);
	COMM_NETCTL_NMT_EN = 0;
}


void _CO_COMM_NMT_TXEvent(void)
{
    *(unsigned long *)(mCANGetPtrTxCOB()) = 0;
    mCANPutDataLen(2); // NMT-messages are 2 bytes long(state+nodeid).
    mCANPutDataByte0(mNMTGetTxState());
    mCANPutDataByte1(mNMTGetTxNodeID());
}


