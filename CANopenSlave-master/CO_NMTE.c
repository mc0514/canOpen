
/*****************************************************************************
 *
 * Microchip CANopen Stack (Network Management Error Communications Handler)
 *
 *****************************************************************************
 * FileName:        CO_NMTE.C
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


// Heartbeat or node-guard

#include	"CO_DEFS.DEF"			// Global definitions
#include	"CO_TYPES.H"			// Data types
#include	"CO_CANDRV.H"			// Driver services
#include	"CO_COMM.H"				// Object
#include	"CO_DICT.H"				// Dictionary Object Services
#include	"CO_NMTE.H"				// Network Management Error services
#include	"CO_TOOLS.H"			// COB ID tools



UNSIGNED32 		_uNMTE_COBID;

short long 		_uNMTETimer;
UNSIGNED8		_uNMTEState;
UNSIGNED8		_uNMTELocalState;

UNSIGNED16		_uNMTEHeartBeat;
UNSIGNED16		_uNMTEGuardTime;
UNSIGNED8		_uNMTELifeFactor;


unsigned char 	_hNMTE;


void CO_NMTENodeGuardErrEvent(void);


/*********************************************************************
 * Function:        void _CO_COMM_NMTE_HeartBeatAccessEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Process access events to the heartbeat.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMTE_HeartBeatAccessEvent(void)
{
	switch (uDict.cmd)
	{
		//case DICT_OBJ_INFO:		// Get information about the object
		//	break;

		case DICT_OBJ_READ: 	// Read the object
			*(UNSIGNED16 *)(uDict.obj->pReqBuf) = _uNMTEHeartBeat;
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			_uNMTEHeartBeat = *(UNSIGNED16 *)(uDict.obj->pReqBuf);

			// Reset the state
			_uNMTEState.byte = 0;

			// If the heartbeat is greater than 0 then enable heartbeat
			if (_uNMTEHeartBeat.word) 
			{
				NMTE_TMR_LOCAL_EN = 1;
				_uNMTETimer = _uNMTEHeartBeat.word;
			}
			else 

			// else if the node guard and life is greater than 0 then enable node guard
			if (_uNMTEGuardTime.word && _uNMTELifeFactor.byte) 
			{
				_uNMTELocalState.byte = 0x80;
				NMTE_NODE_GUARD_EN = 1;
				NMTE_TMR_LOCAL_EN = 1;
				_uNMTETimer = _uNMTEGuardTime.word * _uNMTELifeFactor.byte;
			}
			break;
	}	
}




/*********************************************************************
 * Function:        void _CO_COMM_NMTE_GuardTimeAccessEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Process access events to the guard time.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMTE_GuardTimeAccessEvent(void)
{
	switch (uDict.cmd)
	{
		//case DICT_OBJ_INFO:		// Get information about the object
		//	break;

		case DICT_OBJ_READ: 	// Read the object
			*(UNSIGNED16 *)(uDict.obj->pReqBuf) = _uNMTEGuardTime;
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			_uNMTEGuardTime = *(UNSIGNED16 *)(uDict.obj->pReqBuf);

			// Reset the state
			_uNMTEState.byte = 0;

			// If the heartbeat is greater than 0 then enable heartbeat
			if (_uNMTEHeartBeat.word) 
			{
				NMTE_TMR_LOCAL_EN = 1;
				_uNMTETimer = _uNMTEHeartBeat.word;
			}
			else 

			// else if the node guard and life is greater than 0 then enable node guard
			if (_uNMTEGuardTime.word && _uNMTELifeFactor.byte) 
			{
				_uNMTELocalState.byte = 0x80;
				NMTE_NODE_GUARD_EN = 1;
				NMTE_TMR_LOCAL_EN = 1;
				_uNMTETimer = _uNMTEGuardTime.word * _uNMTELifeFactor.byte;
			}		
			break;
	}	
}



/*********************************************************************
 * Function:        void _CO_COMM_NMTE_GuardTimeAccessEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Process access events to the life time factor.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMTE_LifeFactorAccessEvent(void)
{
	switch (uDict.cmd)
	{
		//case DICT_OBJ_INFO:		// Get information about the object
		//	break;

		case DICT_OBJ_READ: 	// Read the object
			*(UNSIGNED8 *)(uDict.obj->pReqBuf) = _uNMTELifeFactor;
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			_uNMTELifeFactor = *(UNSIGNED8 *)(uDict.obj->pReqBuf);

			// Reset the state
			_uNMTEState.byte = 0;

			// If the heartbeat is greater than 0 then enable heartbeat
			if (_uNMTEHeartBeat.word) 
			{
				NMTE_TMR_LOCAL_EN = 1;
				_uNMTETimer = _uNMTEHeartBeat.word;
			}
			else 

			// else if the node guard and life is greater than 0 then enable node guard
			if (_uNMTEGuardTime.word && _uNMTELifeFactor.byte) 
			{
				_uNMTELocalState.byte = 0x80;
				NMTE_NODE_GUARD_EN = 1;
				NMTE_TMR_LOCAL_EN = 1;
				_uNMTETimer = _uNMTEGuardTime.word * _uNMTELifeFactor.byte;
			}		
			break;
	}	
}


/*********************************************************************
 * Function:        void _CO_COMM_NMTE_Open(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Open the NMTE endpoint.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMTE_Open(void)
{
	// Set the COB ID and convert it to MCHP
	_uNMTE_COBID.word = 0x700L + _uCO_nodeID.byte;
	mTOOLS_CO2MCHP(_uNMTE_COBID.word);
	_uNMTE_COBID.word = mTOOLS_GetCOBID();
		
	_uNMTEState.byte = 0;

	// If the heartbeat is greater than 0 then enable heartbeat
	if (_uNMTEHeartBeat.word) 
	{
		NMTE_TMR_LOCAL_EN = 1;
		COMM_NETCTL_NMTE_EN = 1;
		_uNMTETimer = _uNMTEHeartBeat.word;
	}
	else 

	// else if the node guard and life is greater than 0 then enable node guard
	if (_uNMTEGuardTime.word && _uNMTELifeFactor.byte) 
	{
		// Call the driver and request to open a receive endpoint
		mCANOpenMessage((COMM_MSGGRP_NETCTL) | COMM_NETCTL_NMTE, _uNMTE_COBID.word, _hNMTE);
		if (_hNMTE)
		{ 
			COMM_NETCTL_NMTE_EN = 1;
		
			// Reset the toggle memory
			_uNMTELocalState.byte = 0x80;

			NMTE_NODE_GUARD_EN = 1;
			NMTE_TMR_LOCAL_EN = 1;
			_uNMTETimer = _uNMTEGuardTime.word * _uNMTELifeFactor.byte;
		}
	}
}



/*********************************************************************
 * Function:        void _CO_COMM_NMTE_Close(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Close the NMTE endpoint.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMTE_Close(void)
{
	// Call the driver, request to close the receive endpoint
	mCANCloseMessage(_hNMTE);
	COMM_NETCTL_NMTE_EN = 0;
}




/*********************************************************************
 * Function:        void _CO_COMM_NMTE_RXEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is the receive event handler for the NMTE
 *					endpoint. 
 *
 * Note:          	This is only used for nodeguard.
 ********************************************************************/
void _CO_COMM_NMTE_RXEvent(void)
{
	// If node guard is used and an RTR with 1 byte is received
	if (NMTE_NODE_GUARD_EN)
	{
		if (mCANIsGetRTR())
		{
			if (mCANGetDataLen() == 1) 
			{
				// Queue a request to send data
				COMM_NETCTL_NMTE_TF = 1;
 
				// Reset the timer
				_uNMTETimer = _uNMTEGuardTime.word * _uNMTELifeFactor.byte;
			}
		}
	}
}



/*********************************************************************
 * Function:        void _CO_COMM_NMTE_TXEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is the transmit event handler for the NMTE
 *					endpoint. Node guarding and heartbeat
 *					transmissions are handled.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMTE_TXEvent(void)
{
	{
		// Set the COB
		*(unsigned long *)(mCANGetPtrTxCOB()) = _uNMTE_COBID.word;

		// Set the length
		mCANPutDataLen(1);

		
		// Send the state or the boot
		if (!NMTE_BOOT_SERVICE)
		{
			// Toggle and strip old state (also known as bootup state)
			_uNMTELocalState.byte = _uNMTELocalState.byte & 0x80;
			if (NMTE_NODE_GUARD_EN) {_uNMTELocalState.bits.b7 = (~_uNMTELocalState.bits.b7);}
			else {_uNMTELocalState.bits.b7 = 0;}

			// Set the data
			if (COMM_STATE_STOP) _uNMTELocalState.byte = _uNMTELocalState.byte | 4;
			else
			if (COMM_STATE_OPER) _uNMTELocalState.byte = _uNMTELocalState.byte | 5;
			else
			if (COMM_STATE_PREOP) _uNMTELocalState.byte = _uNMTELocalState.byte | 127;

			// Load the data
			mCANPutDataByte0(_uNMTELocalState.byte);
		}
		else
		{
			NMTE_BOOT_SERVICE = 0;
			mCANPutDataByte0(0);
		}
	}
}


/*********************************************************************
 * Function:        void _CO_COMM_NMTE_LSTimerEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is the timer event handler for the NMTE
 *					endpoint. 
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMTE_LSTimerEvent(void)
{
	// Process only if the local timer is enabled
	if (NMTE_TMR_LOCAL_EN)
	{
		// Adjust the time
		_uNMTETimer -= CO_TICK_PERIOD;
			
		// If the timer is zero then
		//if (_uNMTETimer == 0)
		if (_uNMTETimer <= 0)
		{
			// If the heartbeat protocol is enabled
			if (!NMTE_NODE_GUARD_EN)
			{
				// Reset the timer
				_uNMTETimer = _uNMTETimer + _uNMTEHeartBeat.word;
						
				// Queue the endpoint to send a heartbeat	
				COMM_NETCTL_NMTE_TF = 1;
			}

			// Else the node guard protocol is enabled
			else
			{
				// Reset the timer
				_uNMTETimer = _uNMTEGuardTime.word * _uNMTELifeFactor.byte;

				// Notify the application of an error
				CO_NMTENodeGuardErrEvent();
			}
		}
	}
}
