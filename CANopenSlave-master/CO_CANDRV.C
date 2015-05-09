/*****************************************************************************
 *
 * Microchip CANopen Stack (ECAN Driver For CANopen)
 *
 *****************************************************************************
 * FileName:        CO_CANDRV.C
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
#include	"CO_TYPES.H"
#include	"CO_CANDRV.H"			// Driver services
#include        "Globals.h"
#include        "NMTextension.h"



int k = 1;


// Definition of a Microchip CAN filter
typedef union __FILTER
{
	unsigned long dword;
	struct __BYTES
	{
		unsigned char	SIDH;
		unsigned char	SIDL;
		unsigned char 	EIDH;
		unsigned char 	EIDL;
	}bytes;
}_FILTER;


// Parameter area
unsigned char _uCAN_Handle;				// Statically passed parameters
unsigned char _uCAN_Param1;
unsigned char _uCAN_Param2;
unsigned char _uCAN_Param3;
unsigned char _uCAN_Param4;
unsigned char _uCAN_ret;

// Driver related static data
unsigned char 	_uCAN_Bitrate;						// Stored bitrate
unsigned char 	_uCANRxHndls[CAN_MAX_RCV_ENDP];		// Filter handles
_FILTER			_uCANRxIDRes[CAN_MAX_RCV_ENDP];		// Filters
unsigned char 	_uCANTxHndls[3];					// Transmit handles

unsigned char _uCANReq;					// Queued driver request

unsigned char _uCANOldMode;




/* ******** CAN Control Services ******* */


/*********************************************************************
 * Function:        void _CANEventManager(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function processes any queued requests in
 *					the CAN driver.
 *
 * Note:          	
 ********************************************************************/
void _CANEventManager(void)
{
	if (_uCANReq)
	{
		switch (_uCANReq)
		{	
			// Filter has been modified, re-sync		
			case 1:
				// Check for config mode
				if (CANSTATbits.OPMODE2)
				{
					if (_uCANRxHndls[0]) {*(_FILTER *)(&RXF0SIDH) = _uCANRxIDRes[0]; RXFCON0bits.RXF0EN = 1;}
					else RXFCON0bits.RXF0EN = 0;
					#if CAN_MAX_RCV_ENDP > 1
					if (_uCANRxHndls[1]) {*(_FILTER *)(&RXF1SIDH) = _uCANRxIDRes[1]; RXFCON0bits.RXF1EN = 1;}
					else RXFCON0bits.RXF1EN = 0;
					#endif
					#if CAN_MAX_RCV_ENDP > 2
					if (_uCANRxHndls[2]) {*(_FILTER *)(&RXF2SIDH) = _uCANRxIDRes[2]; RXFCON0bits.RXF2EN = 1;}
					else RXFCON0bits.RXF2EN = 0;
					#endif
					#if CAN_MAX_RCV_ENDP > 3
					if (_uCANRxHndls[3]) {*(_FILTER *)(&RXF3SIDH) = _uCANRxIDRes[3]; RXFCON0bits.RXF3EN = 1;}
					else RXFCON0bits.RXF3EN = 0;
					#endif
					#if CAN_MAX_RCV_ENDP > 4
					if (_uCANRxHndls[4]) {*(_FILTER *)(&RXF4SIDH) = _uCANRxIDRes[4]; RXFCON0bits.RXF4EN = 1;}
					else RXFCON0bits.RXF4EN = 0;
					#endif
					#if CAN_MAX_RCV_ENDP > 5
					if (_uCANRxHndls[5]) {*(_FILTER *)(&RXF5SIDH) = _uCANRxIDRes[5]; RXFCON0bits.RXF5EN = 1;}
					else RXFCON0bits.RXF5EN = 0;
					#endif
					#if CAN_MAX_RCV_ENDP > 6
					if (_uCANRxHndls[6]) {*(_FILTER *)(&RXF6SIDH) = _uCANRxIDRes[6]; RXFCON0bits.RXF6EN = 1;}
					else RXFCON0bits.RXF6EN = 0;
					#endif
					#if CAN_MAX_RCV_ENDP > 7
					if (_uCANRxHndls[7]) {*(_FILTER *)(&RXF7SIDH) = _uCANRxIDRes[7]; RXFCON0bits.RXF7EN = 1;}
					else RXFCON0bits.RXF7EN = 0;
					#endif
					#if CAN_MAX_RCV_ENDP > 8
					if (_uCANRxHndls[8]) {*(_FILTER *)(&RXF8SIDH) = _uCANRxIDRes[8]; RXFCON1bits.RXF8EN = 1;}
					else RXFCON1bits.RXF8EN = 0;
					#endif
					#if CAN_MAX_RCV_ENDP > 9
					if (_uCANRxHndls[9]) {*(_FILTER *)(&RXF9SIDH) = _uCANRxIDRes[9]; RXFCON1bits.RXF9EN = 1;}
					else RXFCON1bits.RXF9EN = 0;
					#endif
					#if CAN_MAX_RCV_ENDP > 10
					if (_uCANRxHndls[10]) {*(_FILTER *)(&RXF10SIDH) = _uCANRxIDRes[10]; RXFCON1bits.RXF10EN = 1;}
					else RXFCON1bits.RXF10EN = 0;
					#endif
					#if CAN_MAX_RCV_ENDP > 11
					if (_uCANRxHndls[11]) {*(_FILTER *)(&RXF11SIDH) = _uCANRxIDRes[11]; RXFCON1bits.RXF11EN = 1;}
					else RXFCON1bits.RXF11EN = 0;
					#endif
					#if CAN_MAX_RCV_ENDP > 12
					if (_uCANRxHndls[12]) {*(_FILTER *)(&RXF12SIDH) = _uCANRxIDRes[12]; RXFCON1bits.RXF12EN = 1;}	
					else RXFCON1bits.RXF12EN = 0;	
					#endif
					#if CAN_MAX_RCV_ENDP > 13
					if (_uCANRxHndls[13]) {*(_FILTER *)(&RXF13SIDH) = _uCANRxIDRes[13]; RXFCON1bits.RXF13EN = 1;}
					else RXFCON1bits.RXF13EN = 0;
					#endif
					#if CAN_MAX_RCV_ENDP > 14
					if (_uCANRxHndls[14]) {*(_FILTER *)(&RXF14SIDH) = _uCANRxIDRes[14]; RXFCON1bits.RXF14EN = 1;}
					else RXFCON1bits.RXF14EN = 0;
					#endif
					#if CAN_MAX_RCV_ENDP > 15
					if (_uCANRxHndls[15]) {*(_FILTER *)(&RXF15SIDH) = _uCANRxIDRes[15]; RXFCON1bits.RXF15EN = 1;}
					else RXFCON1bits.RXF15EN = 0;
					#endif
					
					// Cancel the request
					_uCANReq = 0;
					
					// Request normal operation
					CANCON = _uCANOldMode;;
				}
				
				// Request config mode
				else CANCON = 0x80;
				break;
				
			case 2:
				// Check for config mode
				if (CANCONbits.REQOP2)
				{
					// Set the bitrate
					_CANSetBitRate();
					
					// Cancel the request
					_uCANReq = 0;
					
					// Request normal operation
					CANCON = _uCANOldMode;;
				}
				// Request config mode
				else CANCON = 0x80;
				break;
		}			
	}
}



/*********************************************************************
 * Function:        void _CANReset(void)
 *
 * PreCondition:    none
 *
 * Input:       	unsigned char _uCAN_Bitrate
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        All aspects of the CAN driver are reset.
 *
 * Note:          	This function does not automatically enable the 
 *					device on the network.
 ********************************************************************/
void _CANReset(void)
{
	// Empty an queued requests
	_uCANReq = 0;
	
	// Force the CAN peripherial into Config mode
	CANCON = 0x40;
	CANCON = 0x80;
	
	// Set the bitrate
	_CANSetBitRate();
	
	// Make all programmable buffers receive buffers
	BSEL0 = 0x00;
	
	// Setup the receive buffers
	RXB0CON = 0;
	RXB1CON = 0;
	B0CON = 0;
	B1CON = 0;
	B2CON = 0;
	B3CON = 0;
	B4CON = 0;
	B5CON = 0;
	
	
	// Place the module in enhanced legacy mode
	ECANCON = 0x50;
	
	// Disable all filters
	RXFCON0 = 0;
	RXFCON1 = 0;
	
	// No data byte filtering
	SDFLC = 0;
	
	// Setup filter/buffer association, two filters per buffer
	RXFBCON0 = 0x00;
	RXFBCON1 = 0x11;
	RXFBCON2 = 0x22;
	RXFBCON3 = 0x33;
	RXFBCON4 = 0x44;
	RXFBCON5 = 0x55;
	RXFBCON6 = 0x66;
	RXFBCON7 = 0x77;
	
	// Setup filter/mask association to Mask 0
	MSEL0 = MSEL1 = MSEL2 = MSEL3 = 0;
	
	// Set Mask 0 to not mask any filter bit
        
	RXM0SIDH = 0xFF;
	RXM0SIDL = 0xE3;
	RXM0EIDH = 0xFF;
	RXM0EIDL = 0xFF;
        

        /*
        RXM0SIDH = 0x00;
        RXM0SIDL = 0x00;
        RXM0EIDH = 0x00;
        RXM0EIDL = 0x00;
        */

	
	// Set I/O control
	CIOCON = 0x20;
	
	// Set interrupts
	TXBIE = 0x1C;
	BIE0 = 0xFF;
	
	// Reset all handles
	_uCANRxHndls[0] = 0;
	#if CAN_MAX_RCV_ENDP > 1
	_uCANRxHndls[1] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 2
	_uCANRxHndls[2] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 3
	_uCANRxHndls[3] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 4
	_uCANRxHndls[4] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 5
	_uCANRxHndls[5] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 6
	_uCANRxHndls[6] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 7
	_uCANRxHndls[7] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 8
	_uCANRxHndls[8] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 9
	_uCANRxHndls[9] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 10
	_uCANRxHndls[10] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 11
	_uCANRxHndls[11] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 12
	_uCANRxHndls[12] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 13
	_uCANRxHndls[13] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 14
	_uCANRxHndls[14] = 0;
	#endif
	#if CAN_MAX_RCV_ENDP > 15
	_uCANRxHndls[15] = 0;
	#endif
}







/*********************************************************************
 * Function:        void _CANSetBitRate(void)
 *
 * PreCondition:    This function should only be called when the 
 *					device is not active on the CAN bus.
 *
 * Input:       	unsigned char _uCAN_Bitrate
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        The predefined BRG values are set.
 *
 * Note:          	This message is intended to be called from within
 *					the event manager. It is also called on reset.
 *
 *					An invalid bitrate will default to _BITRATE0
 ********************************************************************/
void _CANSetBitRate(void)
{
	switch(_uCAN_Bitrate)
	{
		case 0:							/* 1Mbit */
			BRGCON1 = CAN_BITRATE0_BRGCON1;
			BRGCON2 = CAN_BITRATE0_BRGCON2;
			BRGCON3 = CAN_BITRATE0_BRGCON3;
			break;
		#if CAN_BITRATE1
		case 1:							/* 800kbits */
			BRGCON1 = CAN_BITRATE1_BRGCON1;
			BRGCON2 = CAN_BITRATE1_BRGCON2;
			BRGCON3 = CAN_BITRATE1_BRGCON3;
			break;
		#endif
		#if CAN_BITRATE2
		case 2:							/* 500kbits */
			BRGCON1 = CAN_BITRATE2_BRGCON1;
			BRGCON2 = CAN_BITRATE2_BRGCON2;
			BRGCON3 = CAN_BITRATE2_BRGCON3;
			break;
		#endif
		#if CAN_BITRATE3
		case 3:							/* 500kbits */
			BRGCON1 = CAN_BITRATE3_BRGCON1;
			BRGCON2 = CAN_BITRATE3_BRGCON2;
			BRGCON3 = CAN_BITRATE3_BRGCON3;
			break;
		#endif
		#if CAN_BITRATE4
		case 4:							/* 250kbits */
			BRGCON1 = CAN_BITRATE4_BRGCON1;
			BRGCON2 = CAN_BITRATE4_BRGCON2;
			BRGCON3 = CAN_BITRATE4_BRGCON3;
			break;
		#endif
		#if CAN_BITRATE5
		case 5:							/* 125kbits */
			BRGCON1 = CAN_BITRATE5_BRGCON1;
			BRGCON2 = CAN_BITRATE5_BRGCON2;
			BRGCON3 = CAN_BITRATE5_BRGCON3;
			break;
		#endif
		#if CAN_BITRATE6
		case 6:							/* 50kbits */
			BRGCON1 = CAN_BITRATE6_BRGCON1;
			BRGCON2 = CAN_BITRATE6_BRGCON2;
			BRGCON3 = CAN_BITRATE6_BRGCON3;
			break;
		#endif
		#if CAN_BITRATE7
		case 7:							/* 20kbits */
			BRGCON1 = CAN_BITRATE7_BRGCON1;
			BRGCON2 = CAN_BITRATE7_BRGCON2;
			BRGCON3 = CAN_BITRATE7_BRGCON3;
			break;
		#endif
		#if CAN_BITRATE8
		case 8:							/* 10kbits */
			BRGCON1 = CAN_BITRATE8_BRGCON1;
			BRGCON2 = CAN_BITRATE8_BRGCON2;
			BRGCON3 = CAN_BITRATE8_BRGCON3;
			break;
		#endif
		default:
			BRGCON1 = CAN_BITRATE0_BRGCON1;
			BRGCON2 = CAN_BITRATE0_BRGCON2;
			BRGCON3 = CAN_BITRATE0_BRGCON3;
			break;
	}
}






/* ******** Message Write Services ******* */

/*********************************************************************
 * Function:        void _CANIsPutReady(void)
 *
 * PreCondition:    A message must have been placed on the bus
 *					for this function to ever report anything.
 *
 * Input:       	unsigned char _uCAN_Handle
 *                  
 * Output:         	unsigned char _uCAN_ret   
 *
 * Side Effects:    none
 *
 * Overview:        This function scans for an available output 
 *					buffer. If successful the handle passed is the 
 *					same as the handle returned. Else a NULL is 
 *					returned on a failure.
 *
 * Note:          	Buffer access on successive transmit related calls
 *					is assumed. I.E. the handle is not required for 
 *					associated write functions.
 ********************************************************************/
void _CANIsPutReady(void)
{
	// Check to see if buffer 0 is available
	if (!TXB0CONbits.TXREQ) {ECANCON = 0x43; _uCAN_ret = _uCANTxHndls[0] = _uCAN_Handle;}

	// Else check to see if buffer 1 is available
	else if (!TXB1CONbits.TXREQ) {ECANCON = 0x44; _uCAN_ret = _uCANTxHndls[1] = _uCAN_Handle;}

	// Else check to see if buffer 2 is available
	else if (!TXB2CONbits.TXREQ) {ECANCON = 0x45; _uCAN_ret = _uCANTxHndls[2] = _uCAN_Handle;}

	// Else no more buffers available
	else {_uCAN_ret = 0;}
}



/*********************************************************************
 * Function:        void _CANIsPutFin(void)
 *
 * PreCondition:    A message must have been placed on the bus
 *					for this function to ever report anything.
 *
 * Input:       	none
 *                  
 * Output:         	unsigned char _uCAN_ret   
 *
 * Side Effects:    none
 *
 * Overview:        This function scans the output buffers for any
 *					int flags indicating data has been sent. The 
 *					handle to the message is returned to the user.
 *
 * Note:          	This function should only be called one time for 
 *					a tx indication. Calling a second time after 
 *					receiving an indication may not return the same
 *					handle.
 ********************************************************************/
void _CANIsPutFin(void)
{
	// Check to see if buffer 0 has sent a message
	if (TXB0CONbits.TXBIF) {ECANCON = 0x43; TXB0CONbits.TXBIF = 0; _uCAN_ret = _uCANTxHndls[0];}

	// Else check to see if buffer 1 has sent a message
	else if (TXB1CONbits.TXBIF) {ECANCON = 0x44; TXB0CONbits.TXBIF = 0; _uCAN_ret = _uCANTxHndls[1];}

	// Else check to see if buffer 2 has sent a message
	else if (TXB2CONbits.TXBIF) {ECANCON = 0x45; TXB0CONbits.TXBIF = 0; _uCAN_ret = _uCANTxHndls[2];}
	
	// Else no message was sent
	else {_uCAN_ret = 0;}
}













/* ******** Message Read Services ******* */

/*********************************************************************
 * Function:        void _CANOpenMessage(void)
 *
 * PreCondition:    _CANEventManager() must be called frequently for
 *					proper operation.
 *
 * Input:       	(unsigned long) _uCAN_Param1
 *                  
 * Output:         	unsigned char _uCAN_ret   
 *
 * Side Effects:    none
 *
 * Overview:        This function scans the available mailbox space
 * 					for an open slot. If found the COBID is added to 
 *					the list of received messages. 
 *
 * Note:            The COBID is added but not activated until the 
 *					bus is ready. In future CAN modules this queuing 
 *					functionality may be removed depending on 
 *					hardware support.
 ********************************************************************/
void _CANOpenMessage(void)
{
	unsigned char i;	
	
	// Scan for an open filter
	for (i = 0; i < CAN_MAX_RCV_ENDP; i++)
	{
		if (_uCANRxHndls[i] == 0)
		{
			// Save the handle to the object
			_uCAN_ret = _uCANRxHndls[i] = _uCAN_Handle;
						
			// Store the ID in a buffer
			_uCANRxIDRes[i].dword = *(unsigned long *)(&_uCAN_Param1);
		
			// Set the filter change request flag
			_uCANReq = 1;
					
			return;
		}
	}
	
	_uCAN_ret = 0;
}


/*********************************************************************
 * Function:        void _CANCloseMessage(void)
 *
 * PreCondition:    Must be a valid handle. 
 *					_CANEventManager() must be called frequently for
 *					proper operation.
 *
 * Input:       	(unsigned long) _uCAN_Param1
 *                  
 * Output:         	none   
 *
 * Side Effects:    none
 *
 * Overview:        This function scans the mailbox space for the 
 * 					handle. If found the COBID is removed from the
 *					receive list. 
 *
 * Note:            The COBID is only queued to be removed from the 
 *					list. In future CAN modules this queuing 
 *					functionality may be removed depending on 
 *					hardware support.
 ********************************************************************/
void _CANCloseMessage(void)
{	
	unsigned char i;
		
	// Scan for an open filter
	for (i = 0; i < CAN_MAX_RCV_ENDP; i++)
	{
		if (_uCANRxHndls[i] == _uCAN_Handle)
		{	
			// Remove the handle
			_uCANRxHndls[i] = 0;
									
			// Set the filter change request flag
			_uCANReq = 1;
			
			// Indicate a successful close of the message receive endpoint
			_uCAN_ret = 1;	
					
			return;
		}
	}
	
	_uCAN_ret = 0;	
}





/*********************************************************************
 * Function:        void _CANIsGetReady(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	unsigned char _uCAN_ret   
 *
 * Side Effects:    none
 *
 * Overview:        This function scans for a receive event. If found
 *					it returns the handle associated to the receive
 *					buffer. Otherwise it returns NULL.
 *
 * Note:            Buffer access on successive receive related calls
 *					is assumed. I.E. the handle is not required for 
 *					associated read functions.
 ********************************************************************/
void _CANIsGetReady(void)
{
	// Check for a receive interrupt
	if (PIR3bits.RXB1IF)
	{				
		// Default receive buffer
		ECANCON = 0x50;

		// Check for an interrupt and set the appropriate buffer
		if (RXB0CONbits.RXFUL) {}
		#if CAN_MAX_RCV_ENDP > 2
		else if (RXB1CONbits.RXFUL) {ECANCON = 0x51;}
		#endif
		#if CAN_MAX_RCV_ENDP > 4
		else if (B0CONbits.RXFUL) {ECANCON = 0x52;}
		#endif
		#if CAN_MAX_RCV_ENDP > 6
		else if (B1CONbits.RXFUL) {ECANCON = 0x53;}
		#endif
		#if CAN_MAX_RCV_ENDP > 8
		else if (B2CONbits.RXFUL) {ECANCON = 0x54;}
		#endif
		#if CAN_MAX_RCV_ENDP > 10
		else if (B3CONbits.RXFUL) {ECANCON = 0x55;}
		#endif
		#if CAN_MAX_RCV_ENDP > 12
		else if (B4CONbits.RXFUL) {ECANCON = 0x56;}
		#endif
		#if CAN_MAX_RCV_ENDP > 14
		else if (B5CONbits.RXFUL) {ECANCON = 0x57;}
		#endif
		else {_uCAN_ret = 0; PIR3bits.RXB1IF = 0; return;}
			
		// Remove the interrupt, it will set again if more are pending
		//PIR3bits.RXB1IF = 0;
				
		// Decode which filter passed the event and return the handle 
		// associated to the filter
		_uCAN_ret = *((RXB0CON & 0x0F) + _uCANRxHndls);
	}
	else _uCAN_ret = 0;
}









