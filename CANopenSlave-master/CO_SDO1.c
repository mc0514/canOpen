/*****************************************************************************
 *
 * Microchip CANopen Stack (The Default SDO)
 *
 *****************************************************************************
 * FileName:        CO_SDO1.C
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
#include	"CO_ABERR.H"			// Abort types
#include	"CO_CANDRV.H"			// Driver services
#include	"CO_COMM.H"				// Object
#include	"CO_DICT.H"				// Dictionary Object Services
#include	"CO_TOOLS.H"			// COB ID tools









union _SDO_CTL
{
	unsigned char byte;
	struct _SDO_INITIATE_CTL
	{
		unsigned s:1;
		unsigned e:1;
		unsigned n:2;
		unsigned x:1;
		unsigned cmd:3;	
	}ictl;
	struct _SDO_REGULAR_CTL
	{
		unsigned c:1;
		unsigned n:3;
		unsigned t:1;
		unsigned cmd:3;
	}rctl;
	struct _SDO_RESPONSE
	{
		unsigned x:4;
		unsigned t:1;
		unsigned cmd:3;
	}rsp;
};

union _SDO_STATE
{
	unsigned char byte;
	struct _SDO_STATE_BITS
	{
		unsigned :3;
		unsigned ntime:1;
		unsigned tog:1;
		unsigned start:1;
		unsigned dnld:1;	
		unsigned abrt:1;
	}bits;
};


rom unsigned char 	_uSDO1COMMIndx = 3;	// The length of the object


UNSIGNED32 			_uSDO1_CS_COBID;	// COB IDs used by the default SDO
UNSIGNED32 			_uSDO1_SC_COBID;

unsigned char 		_hSDO1;				// Handle to the connection

union _SDO_STATE	_uSDO1State;		// State bitmap for this SDO
REQ_STAT			_uSDO1ACode;		// Abort code
union _SDO_CTL 		_uSDO1Ctl;			// Received control byte buffer
DICT_OBJ			_uSDO1Dict;			// Local dictionary object, loaded during inits
unsigned int	 	_uSDO1Timer;		// Watchdog, defined by the application
UNSIGNED16	 		_uSDO1BytesLeft;	// Bytes to send

/* Buffers used in this design */
unsigned char		_uSDO1RxBuf[CO_SDO1_MAX_RX_BUF];	// Receive space for downloads
unsigned char 		_uSDO1TxBuf[8];		// Transmit space for uploads



/*********************************************************************
 * Function:        void _CO_COMM_SDO1_CS_COBIDAccessEvent(void)
 *
 * PreCondition:    
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Process any access events to the SDO client to
 *					server COB ID.
 *
 * Note:          	
 ********************************************************************/
// Process access events to the COB ID
void _CO_COMM_SDO1_CS_COBIDAccessEvent(void)
{
	switch (mCO_DictGetCmd())
	{
		case DICT_OBJ_READ: 	// Read the object
			// Translate MCHP COB to CANopen COB
			mTOOLS_MCHP2CO(_uSDO1_CS_COBID.word);

			// Return the COBID
			*(unsigned long *)(uDict.obj->pReqBuf) = mTOOLS_GetCOBID();				
			break;
	}	
}


/*********************************************************************
 * Function:        void _CO_COMM_SDO1_SC_COBIDAccessEvent(void)
 *
 * PreCondition:    
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Process any access events to the SDO server to
 *					client COB ID.
 *
 * Note:          	
 ********************************************************************/
// Process access events to the COB ID
void _CO_COMM_SDO1_SC_COBIDAccessEvent(void)
{
	switch (mCO_DictGetCmd())
	{
		case DICT_OBJ_READ: 	// Read the object
			// Translate MCHP COB to CANopen COB
			mTOOLS_MCHP2CO(_uSDO1_SC_COBID.word);

			// Return the COBID
			*(unsigned long *)(uDict.obj->pReqBuf) = mTOOLS_GetCOBID();				
			break;
	}
}






/*********************************************************************
 * Function:        void _CO_COMM_SDO1_Open(void)
 *
 * PreCondition:    
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function opens the default SDO
 *					communications.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_SDO1_Open(void)
{	
	// Set the client to server COB ID and convert it to MCHP
	_uSDO1_CS_COBID.word = 0x600L + _uCO_nodeID.byte;
	mTOOLS_CO2MCHP(_uSDO1_CS_COBID.word);
	_uSDO1_CS_COBID.word = mTOOLS_GetCOBID();

	// Set the server to client COB ID and convert it to MCHP
	_uSDO1_SC_COBID.word = 0x580L + _uCO_nodeID.byte;
	mTOOLS_CO2MCHP(_uSDO1_SC_COBID.word);
	_uSDO1_SC_COBID.word = mTOOLS_GetCOBID();

	// Open a receive message endpoint in the driver
	mCANOpenMessage(COMM_MSGGRP_SDO | COMM_SDO_1, _uSDO1_CS_COBID.word, _hSDO1);
	if (_hSDO1) COMM_SDO_1_EN = 1;
	
	// Reset internal variables
	_uSDO1State.byte = 0;
}


/*********************************************************************
 * Function:        void _CO_COMM_SDO1_Close(void)
 *
 * PreCondition:    
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function closes the default SDO
 *					communications.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_SDO1_Close(void)
{
	// Call the driver, request to close the receive endpoint
	mCANCloseMessage(_hSDO1);
	COMM_SDO_1_EN = 0;
}











/*********************************************************************
 * Function:        void _CO_COMM_SDO1_LSTimerEvent(void)
 *
 * PreCondition:    
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is the low-speed timer event handler for 
 *					the SDO1 endpoint.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_SDO1_LSTimerEvent(void)
{
	// Process only if the connection is in the middle of active segmented comm
	if (_uSDO1State.bits.start)
	{		
		// Adjust the time						TODO
		_uSDO1Timer -= CO_TICK_PERIOD;
		
		// Reset SDO1 states if a timeout while receiving
		if ((signed int)_uSDO1Timer <= 0)
		{
			// Reset the states
			_uSDO1State.byte = 0;
			
			// Queue an abort, SDO timeout	
			_uSDO1ACode = E_SDO_TIME;
			COMM_SDO_1_TF = 1;
		}
	}
}




/*********************************************************************
 * Function:        void _CO_COMM_SDO1_TXEvent(void)
 *
 * PreCondition:    
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is the SDO1 transmit event handler.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_SDO1_TXEvent(void)
{
	// Set the CID
	*(unsigned long *)(mCANGetPtrTxCOB()) = _uSDO1_SC_COBID.word;
	
	// Set the length
	mCANPutDataLen(8);
	
	if (_uSDO1ACode == E_SUCCESS) 
	{
		// Move the data to the transmit buffer
		*(_DATA8 *)(mCANGetPtrTxData()) = *(_DATA8 *)_uSDO1TxBuf;
	}
	else 
	{
		// Set the abort code
		*(mCANGetPtrTxData()) = 0x80;

		// Set the multiplexor
		*(mCANGetPtrTxData() + 1) = ((UNSIGNED16 *)(&(_uSDO1Dict.index)))->bytes.B0.byte;
		*(mCANGetPtrTxData() + 2) = ((UNSIGNED16 *)(&(_uSDO1Dict.index)))->bytes.B1.byte;
		*(mCANGetPtrTxData() + 3) = _uSDO1Dict.subindex;

		switch (_uSDO1ACode)
		{
		
			case E_TOGGLE:						// Toggle not alternated
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x05030000L;
				break;
	
			case E_SDO_TIME:					// SDO protocol timed out
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x05040000L;
				break;
	
			case E_CS_CMD:						// Client/server command specifier not valid or unknown
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x05040001L;
				break;
	
			case E_MEMORY_OUT:					// Out of memory
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x05040005L;
				break;
	
			case E_UNSUPP_ACCESS:				// Unsupported access to an object
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06010000L;
				break;
	
			case E_CANNOT_READ:					// Attempt to read a write only object
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06010001L;
				break;
	
			case E_CANNOT_WRITE:				// Attempt to write a read only object
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06010002L;
				break;
	
			case E_OBJ_NOT_FOUND:				// Object does not exist in the object dictionary
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06020000L;
				break;
	
			case E_OBJ_CANNOT_MAP:				// Object cannot be mapped to the PDO
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06040041L;
				break;
	
			case E_OBJ_MAP_LEN:					// The number and length of the objects to be mapped would exceed PDO length
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06040042L;
				break;
	
			case E_GEN_PARAM_COMP:				// General parameter incompatibility reason
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06040043L;
				break;
	
			case E_GEN_INTERNAL_COMP:			// General internal incompatibility in the device
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06040047L;
				break;
	
			case E_HARDWARE:					// Access failed due to a hardware error
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06060000L;
				break;
	
			case E_LEN_SERVICE:					// Data type does not match, length of service parameter does not match
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06070010L;
				break;
	
			case E_LEN_SERVICE_HIGH:			// Data type does not match, length of service parameter too high
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06070012L;
				break;
	
			case E_LEN_SERVICE_LOW:				// Data type does not match, length of service parameter too low
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06070013L;
				break;
	
			case E_SUBINDEX_NOT_FOUND:			// Sub-index does not exist
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06090011L;
				break;
	
			case E_PARAM_RANGE:					// Value range of parameter exceeded
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06090030L;
				break;
	
			case E_PARAM_HIGH:					// Value of parameter written too high
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06090031L;
				break;
	
			case E_PARAM_LOW:					// Value of parameter written too low
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06090032L;
				break;
	
			case E_MAX_LT_MIN:					// Maximum value is less than minimum value
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x06090036L;
				break;
	
			case E_GENERAL:						// genral error
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x08000000L;
				break;
	
			case E_TRANSFER:					// Data cannot be transfered or stored to the application
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x08000020L;
				break;
	
			case E_LOCAL_CONTROL:				// Data cannot be transfered or stored to the application because of local control
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x08000021L;
				break;
			
			case E_DEV_STATE:					// Data cannot be transfered or stored to the application because of the device present state
				*(unsigned long *)(mCANGetPtrTxData() + 4) = 0x08000022L;
				break;
	
		}
	}
}




/*********************************************************************
 * Function:        void _CO_COMM_SDO1_RXEvent(void)
 *
 * PreCondition:    
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is the SDO1 receive event handler.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_SDO1_RXEvent(void)
{			
	// Process only if all 8 bytes of data are received
	if (mCANGetDataLen() == 8)
	{
		// Init the abort code to success
		_uSDO1ACode = E_SUCCESS;

		// Get the first byte of the received message
		_uSDO1Ctl.byte = mCANGetDataByte0();
		
		switch(_uSDO1Ctl.byte & 0xE0)
		{
			case 0x00:		// Download
				// Continue only if initiated and in download state
				if (_uSDO1State.bits.start)   	
				if (_uSDO1State.bits.dnld)
				{				
					// Compare the toggle bits. 
					if ((_uSDO1State.byte ^ _uSDO1Ctl.byte) & 0x10)	
					{
						// Reset states
						_uSDO1State.byte = 0;
						
						// abort, toggle not alternated
						_uSDO1ACode = E_TOGGLE;
						COMM_SDO_1_TF = 1;
						return;
					}	
									
					// Copy data from the driver 
					*((_DATA7*)(_uSDO1RxBuf + _uSDO1Dict.reqOffst)) = *((_DATA7*)(mCANGetPtrRxData() + 1));
										
					// Adjust the count or offset to the next segment
					_uSDO1Dict.reqOffst += (~_uSDO1Ctl.rctl.n) & 0x07; 	
					
					// If the count is greater than the object length then abort
					if (_uSDO1Dict.reqOffst > _uSDO1Dict.len)
					{
						// Reset states
						_uSDO1State.byte = 0;
						
						// Abort
						_uSDO1ACode = E_LEN_SERVICE;
						COMM_SDO_1_TF = 1;
						return;	
					}					
					
					// Set the next expected toggle
					_uSDO1State.bits.tog = ~_uSDO1State.bits.tog;
					
					// Set the header to respond, b'001t0000
					_uSDO1TxBuf[0] = (_uSDO1Ctl.byte | 0x20) & 0xF0;
					
					// Check for a complete flag
					if (_uSDO1Ctl.rctl.c)
					{
						// Set the pointer to the buffer
						_uSDO1Dict.pReqBuf = _uSDO1RxBuf;
						
						// Write the object
						mCO_DictObjectWrite(_uSDO1Dict);

						// Reset states
						_uSDO1State.byte = 0;

						// Send code, whatever was returned from the object
						_uSDO1ACode = mCO_DictGetRet();
						COMM_SDO_1_TF = 1;
					}
					else
					{
						// Queue to send acknowledge
						COMM_SDO_1_TF = 1;
					}
				}
				break;
				
				
				
				
			case 0x20:		// Initiate Download				
				// Kill the current start if any
				_uSDO1State.bits.start = 0;
		
				// Store the multiplexor locally
				_uSDO1TxBuf[1] = ((UNSIGNED16 *)(&(_uSDO1Dict.index)))->bytes.B0.byte = mCANGetDataByte1();
				_uSDO1TxBuf[2] = ((UNSIGNED16 *)(&(_uSDO1Dict.index)))->bytes.B1.byte = mCANGetDataByte2();
				_uSDO1TxBuf[3] = _uSDO1Dict.subindex = mCANGetDataByte3();
				
				// Preload potential reserved locations
				_uSDO1TxBuf[4] = 0;
				_uSDO1TxBuf[5] = 0;
				_uSDO1TxBuf[6] = 0;
				_uSDO1TxBuf[7] = 0;
				
				// Decode the object; this gets the data from the dictionary
				// If the object is functionally defined, then the data is retrieved 
				// from the object's defined function.
				mCO_DictObjectDecode(_uSDO1Dict);
				
				// Was the object in the dictionary
				if (mCO_DictGetRet() == E_SUCCESS)
				{					
					// Check the access for this request; must have write capability
					if (_uSDO1Dict.ctl & WR_BIT)  	
					{
						// Expedited download
						if (_uSDO1Ctl.ictl.e)
						{
							// If the count is specified, set the request length from the header
							if (_uSDO1Ctl.ictl.s) _uSDO1Dict.reqLen = (((~_uSDO1Ctl.ictl.n) & 0x03) + 1);
							
							// Otherwise set the length from the object
							else _uSDO1Dict.reqLen = _uSDO1Dict.len;
										
							if (_uSDO1Dict.reqLen == _uSDO1Dict.len)
							{
								// Reset states
								_uSDO1State.byte = 0;
																	
								// Set the pointer to the driver
								_uSDO1Dict.pReqBuf = mCANGetPtrRxData() + 4;
								
								// Call the object dictionary write function 
								mCO_DictObjectWrite(_uSDO1Dict);			
								
								// If the write was successful, queue to send acknowledge
								_uSDO1TxBuf[0] = 0x60;
	
								// Send abort, code returned from object
								_uSDO1ACode = mCO_DictGetRet();
									
								COMM_SDO_1_TF = 1;
							}
							else
							{
								// abort, data length does not match
								_uSDO1ACode = E_LEN_SERVICE;
								COMM_SDO_1_TF = 1;
							}
						}
						
						// Segmented download
						else 
						{							
							// If the count is specified
							if (_uSDO1Ctl.ictl.s) 
							{
								// Test the two upper most bytes, should be zero
								if (mCANGetDataByte6() | mCANGetDataByte7())
								{
									// Send abort, length does not match, 0607 0010
									_uSDO1ACode = E_LEN_SERVICE;
									COMM_SDO_1_TF = 1;	
									return;
								}
								
								// Compare the length against the object's defined length
								if (*((unsigned int *)(mCANGetPtrRxData() + 4)) != _uSDO1Dict.len)
								{
									// abort, data length does not match
									_uSDO1ACode = E_LEN_SERVICE;
									COMM_SDO_1_TF = 1;
									return;
								}
							}
							
							// Set the requested length
							_uSDO1Dict.reqLen = _uSDO1Dict.len;
														
							// Indicate a start download
							_uSDO1State.bits.start = 1;
							_uSDO1State.bits.dnld = 1;
							
							// First toggle should be 0
							_uSDO1State.bits.tog = 0;
							
							// Reset the data count 
							_uSDO1Dict.reqOffst = 0;	
							
							// Start the watchdog
							_uSDO1Timer = CO_SDO1_MAX_SEG_TIME;
							//_uSDO1State.bits.ntime = 0;
							
							// Queue to send acknowledge
							_uSDO1TxBuf[0] = 0x60;
							COMM_SDO_1_TF = 1;
						}
					}
					else
					{
						// abort, access problem	
						_uSDO1ACode = E_CANNOT_WRITE;
						COMM_SDO_1_TF = 1;
					}
				}
				
				// Object not found
				else 
				{
					// Abort, return the appropriate code
					_uSDO1ACode = mCO_DictGetRet();
					COMM_SDO_1_TF = 1;
				}
				break;
			
			
			
			
			case 0x40:		// Initiate Upload
				// Kill the current start
				_uSDO1State.bits.start = 0;
		
				// Store the multiplexor locally
				_uSDO1TxBuf[1] = ((UNSIGNED16 *)(&(_uSDO1Dict.index)))->bytes.B0.byte = mCANGetDataByte1();
				_uSDO1TxBuf[2] = ((UNSIGNED16 *)(&(_uSDO1Dict.index)))->bytes.B1.byte = mCANGetDataByte2();
				_uSDO1TxBuf[3] = _uSDO1Dict.subindex = mCANGetDataByte3();
				
				// Preload potential reserved locations
				_uSDO1TxBuf[4] = 0;
				_uSDO1TxBuf[5] = 0;
				_uSDO1TxBuf[6] = 0;
				_uSDO1TxBuf[7] = 0;
				
				// Decode the object; this gets the data from the dictionary
				mCO_DictObjectDecode(_uSDO1Dict);
			
				// Check the return status from the decode
				if (mCO_DictGetRet() == E_SUCCESS)
				{									
					// Check the access for this request; must have read capability
					if (_uSDO1Dict.ctl & RD_BIT)  	
					{
						// Reset offset
						_uSDO1Dict.reqOffst = 0;
						
						// Reset states
						_uSDO1State.byte = 0;
						
						// If the object len is greater than 4 then segment upload
						if (_uSDO1Dict.len > 4)
						{															
							// Set the watchdog
							_uSDO1Timer = CO_SDO1_MAX_SEG_TIME;
							//_uSDO1State.bits.ntime = 0;
							
							// Indicate a start upload
							_uSDO1State.bits.start = 1;
							
							// Set pointer to internal buffer
							_uSDO1Dict.pReqBuf = &(_uSDO1TxBuf[4]);
														
							// Set the size of the object
							_uSDO1TxBuf[4] = ((UNSIGNED16 *)(&(_uSDO1Dict.len)))->bytes.B0.byte;
							_uSDO1TxBuf[5] = ((UNSIGNED16 *)(&(_uSDO1Dict.len)))->bytes.B1.byte;
							
							// Set the response command, size indicated
							_uSDO1TxBuf[0] = 0x41;
							
							// Queue to send acknowledge
							COMM_SDO_1_TF = 1;
						}
						
						// Expedited upload
						else
						{	
							// Set the length in the header
							switch ((unsigned char)(_uSDO1Dict.len))
							{
								case 1:	_uSDO1TxBuf[0] = 0x4F; break;
								case 2: _uSDO1TxBuf[0] = 0x4B; break;
								case 3: _uSDO1TxBuf[0] = 0x47; break;
								case 4: _uSDO1TxBuf[0] = 0x43; break;				
							}
									
							// Set the read length						
							_uSDO1Dict.reqLen = _uSDO1Dict.len;									
																															
							// Set the pointer to the transmit buffer
							_uSDO1Dict.pReqBuf = &(_uSDO1TxBuf[4]);
							
							// Read the data from the object into the buffer
							mCO_DictObjectRead(_uSDO1Dict);

							// Pass any codes
							_uSDO1ACode = mCO_DictGetRet();
							COMM_SDO_1_TF = 1;
						}
					}
					else
					{
						// abort, access problem		
						_uSDO1ACode = E_CANNOT_READ;
						COMM_SDO_1_TF = 1;
					}
				}
				
				// Object not found
				else 
				{
					// Abort, return the appropriate code
					_uSDO1ACode = mCO_DictGetRet();
					COMM_SDO_1_TF = 1;
				}
				break;
					
			
				
				
			
			case 0x60:		// Upload
				if (_uSDO1State.bits.start)	// Continue only if initiated
				if (!_uSDO1State.bits.dnld)	// and in a upload state
				{
					// Compare the toggle bits. 
					if ((_uSDO1State.byte ^ _uSDO1Ctl.byte) & 0x10)	
					{
						// Reset states
						_uSDO1State.byte = 0;

						// abort, toggle not alternated
						_uSDO1ACode = E_TOGGLE;
						COMM_SDO_1_TF = 1;
						return;
					}				
																															
					// Set the pointer to the transmit buffer
					_uSDO1Dict.pReqBuf = &(_uSDO1TxBuf[1]);
					
					// Set the offset
					_uSDO1BytesLeft.word = _uSDO1Dict.len - _uSDO1Dict.reqOffst;
							
					// If the data to be sent is less than 8 then set n and c
					if (_uSDO1BytesLeft.word > 7)
					{
						_uSDO1TxBuf[0] = 0x00; _uSDO1Dict.reqLen = 7;
					}
					else
					{
						// Reset states
						_uSDO1State.byte = 0;

						switch (_uSDO1BytesLeft.bytes.B0.byte)
						{
							case 1:		_uSDO1TxBuf[0] = 0x0D; _uSDO1Dict.reqLen = 1; break;
							case 2: 	_uSDO1TxBuf[0] = 0x0B; _uSDO1Dict.reqLen = 2; break;
							case 3: 	_uSDO1TxBuf[0] = 0x09; _uSDO1Dict.reqLen = 3; break;
							case 4: 	_uSDO1TxBuf[0] = 0x07; _uSDO1Dict.reqLen = 4; break;	
							case 5: 	_uSDO1TxBuf[0] = 0x05; _uSDO1Dict.reqLen = 5; break;
							case 6: 	_uSDO1TxBuf[0] = 0x03; _uSDO1Dict.reqLen = 6; break;
							case 7: 	_uSDO1TxBuf[0] = 0x01; _uSDO1Dict.reqLen = 7; break;
						}
					}
					
					// Setup the toggle
					if (~_uSDO1Ctl.rctl.t){((union _SDO_CTL *)(_uSDO1TxBuf))->rctl.t = 0;}
					else {((union _SDO_CTL *)(_uSDO1TxBuf))->rctl.t = 1;}
						
					// Read the data from the object into the transmit buffer
					mCO_DictObjectRead(_uSDO1Dict);
					
					// Adjust the offset
					_uSDO1Dict.reqOffst += _uSDO1Dict.reqLen;
					
					// Set the next expected toggle
					_uSDO1State.bits.tog = ~_uSDO1State.bits.tog;
			
					// Queue to send the data
					_uSDO1ACode = mCO_DictGetRet();
					COMM_SDO_1_TF = 1;
				}
				break;
				
				
			
			case 0x80:		// Abort Request
				// Reset SDO states
				_uSDO1State.byte = 0;
				break;
				
				
				
			default:
				// Send abort, not a valid command	
				_uSDO1ACode = E_CS_CMD;	
				COMM_SDO_1_TF = 1;
				break;
		}
	}
}



