/*****************************************************************************
 *
 * Microchip CANopen Stack (SYNC Object)
 *
 *****************************************************************************
 * FileName:        CO_SYNC.C
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


									// Global definitions
#include	"CO_TYPES.H"			// Data types
#include	"CO_CANDRV.H"			// Driver services
#include	"CO_COMM.H"				// Object
#include	"CO_DICT.H"				// Dictionary Object Services
#include	"CO_ABERR.H"			// Abort types
#include	"CO_TOOLS.H"




// External communications event
void CO_COMMSyncEvent(void);

// Object 1005h, this is also defined functionally
// This is also initialized by the app at startup since it could be 
// initialized from non-volitile memory.
UNSIGNED32 _uSYNC_COBID;

// Local handle to the receive endpoint. Links to filtering in the driver.
unsigned char _hSYNC;



/*********************************************************************
 * Function:        void _CO_COMM_SYNC_Open(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Open the SYNC endpoint.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_SYNC_Open(void)
{	
	// Call the driver and request to open a receive endpoint
	mCANOpenMessage(COMM_MSGGRP_NETCTL | COMM_NETCTL_SYNC, _uSYNC_COBID.word, _hSYNC);

	// Enable SYNC
	if (_hSYNC) COMM_NETCTL_SYNC_EN = 1;
}


/*********************************************************************
 * Function:        void _CO_COMM_SYNC_Close(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Close the SYNC endpoint.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_SYNC_Close(void)
{
	// Call the driver, request to close the receive endpoint
	mCANCloseMessage(_hSYNC);
	COMM_NETCTL_SYNC_EN = 0;
}



/*********************************************************************
 * Function:        void _CO_COMM_SYNC_RXEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is the receive event handling function.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_SYNC_RXEvent(void)
{
	// If the length of the data is 0 then continue
	if (!mCANGetDataLen())
	{
		// Notify the app that a SYNC has been received
		CO_COMMSyncEvent();	
	}
}


/*********************************************************************
 * Function:        void _CO_COMM_SYNC_COBIDAccessEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Process access events to the COB ID.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_SYNC_COBIDAccessEvent(void)
{
	switch (mCO_DictGetCmd())
	{
		//case DICT_OBJ_INFO:		// Get information not required for this object
		//	break;

		case DICT_OBJ_READ: 	// Read the object
			// Translate MCHP COB to CANopen COB
			mTOOLS_MCHP2CO(_uSYNC_COBID.word);

			// Return the COBID
			*(unsigned long *)(uDict.obj->pReqBuf) = mTOOLS_GetCOBID();
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			// Translate the COB to MCHP format
			mTOOLS_CO2MCHP(*(unsigned long *)(uDict.obj->pReqBuf));

			// Check for good COBID not necessary
			
			// Insure the COB indicates receive only
			if ((*(UNSIGNED32 *)(&mTOOLS_GetCOBID())).bytes.B1.bits.b2 == 0)
			{
				// Close the SYNC object
				_CO_COMM_SYNC_Close();

				// Copy the output to the local COB ID
				_uSYNC_COBID.word = mTOOLS_GetCOBID();

				// Start the SYNC object
				_CO_COMM_SYNC_Open();
			}
			
			// Else return error code
			else {mCO_DictSetRet(E_PARAM_RANGE);}
				
			break;
	}	
}


