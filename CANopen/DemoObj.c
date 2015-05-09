/*****************************************************************************
 *
 * Microchip CANopen Stack (Demonstration Object)
 *
 *****************************************************************************
 * FileName:        DemoObj.C
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


#include	"CO_MAIN.H"


#define	RTR_DIS	bytes.B1.bits.b2
#define STD_DIS	bytes.B1.bits.b3
#define PDO_DIS	bytes.B1.bits.b4

// These are mapping constants for TPDO1 
// starting at 0x1A00 in the dictionary
rom unsigned long uTPDO1Map = 0x60000108;
rom unsigned long uRPDO1Map = 0x62000108;
rom unsigned long uPDO1Dummy = 0x00000008;

unsigned char uIOinFilter;					// 0x6003 filter
unsigned char uIOinPolarity;				// 0x6002 polarity
unsigned char uIOinIntChange;				// 0x6006 interrupt on change
unsigned char uIOinIntRise;					// 0x6007 interrupt on positive edge
unsigned char uIOinIntFall;					// 0x6008 interrupt on negative edge
unsigned char uIOinIntEnable;				// 0x6005 enable interrupts

unsigned char uIOinDigiInOld;				// 

// Static data refered to by the dictionary
rom unsigned char rMaxIndex1 = 1;
rom unsigned char rMaxIndex2 = 8;
rom unsigned char uDemoTPDO1Len = 2;


unsigned char uLocalXmtBuffer[8];			// Local buffer for TPDO1
unsigned char uLocalRcvBuffer[8];			// local buffer fot RPDO1

UNSIGNED8 uDemoState; 					// Bits used to control various states
unsigned char uDemoSyncCount;			// Counter for synchronous types
unsigned char uDemoSyncSet;				// Internal TPDO type control



/*********************************************************************
 * Function:        void DemoInit(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is the initialization to the demonstration
 *					object.
 *
 * Note:          	
 ********************************************************************/
void DemoInit(void)
{
	// Start the A/D	
	ADCON0 = 0xC1;
	ADCON1 = 0;

	// Port D is all output
	LATD = 0;
	TRISD = 0;
	
	uDemoSyncSet = 255;

	uIOinFilter = 0;
	uIOinPolarity = 0;
	uIOinIntChange = 1;
	uIOinIntRise = 0;
	uIOinIntFall = 0;
	uIOinIntEnable = 1;

	uIOinDigiInOld = uLocalXmtBuffer[0] = 0;
	uLocalRcvBuffer[1] = uLocalXmtBuffer[1] = 0;
	uLocalRcvBuffer[2] = uLocalXmtBuffer[2] = 0;
	uLocalRcvBuffer[3] = uLocalXmtBuffer[3] = 0;
	uLocalRcvBuffer[4] = uLocalXmtBuffer[4] = 0;
	uLocalRcvBuffer[5] = uLocalXmtBuffer[5] = 0;
	uLocalRcvBuffer[6] = uLocalXmtBuffer[6] = 0;
	uLocalRcvBuffer[7] = uLocalXmtBuffer[7] = 0;


	// Convert to MCHP
	mTOOLS_CO2MCHP(mCOMM_GetNodeID().byte + 0xC0000180L);
	
	// Store the COB
	mTPDOSetCOB(1, mTOOLS_GetCOBID());

	// Convert to MCHP
	mTOOLS_CO2MCHP(mCOMM_GetNodeID().byte + 0xC0000200L);
	
	// Store the COB
	mRPDOSetCOB(1, mTOOLS_GetCOBID());
	
	// Set the pointer to the buffers
	mTPDOSetTxPtr(1, (unsigned char *)(&uLocalXmtBuffer[0]));
	
	// Set the pointer to the buffers
	mRPDOSetRxPtr(1, (unsigned char *)(&uLocalRcvBuffer[0]));

	// Set the length
	mTPDOSetLen(1, 8);
}




/*********************************************************************
 * Function:        void CO_COMMSyncEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is a simple demonstration of a SYNC event 
 *					handling function.
 *
 * Note:          	
 ********************************************************************/
void CO_COMMSyncEvent(void)
{
	// Process only if in a synchronous mode
	if ((uDemoSyncSet == 0) && (uDemoState.bits.b2))
	{
		// Reset the synchronous transmit and transfer to async
		uDemoState.bits.b2 = 0;
		uDemoState.bits.b0 = 1;
	}
	else
	if ((uDemoSyncSet >= 1) && (uDemoSyncSet <= 240))
	{
		// Adjust the sync counter
		uDemoSyncCount--;
		
		// If time to generate sync
		if (uDemoSyncCount == 0)
		{
			// Reset the sync counter
			uDemoSyncCount = uDemoSyncSet;
			
			// Start the PDO transmission
			uDemoState.bits.b0 = 1;
		}
	}
}



/*********************************************************************
 * Function:        void DemoProcessEvents(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is a simple demonstration of a demo state
 *					machine for cooperative multitasking.
 *
 * Note:          	
 ********************************************************************/
void DemoProcessEvents(void)
{
	unsigned char change;
	unsigned char rise;
	unsigned char fall;

	// Read the input port
	(*(UNSIGNED8 *)uLocalXmtBuffer).bits.b0 = PORTBbits.RB5;					
	(*(UNSIGNED8 *)uLocalXmtBuffer).bits.b1 = PORTBbits.RB4;					
	

	// Determine the change if any
	change = uIOinDigiInOld ^ uLocalXmtBuffer[0];
	
	// Determine if there were any rise events
	rise = (uIOinIntRise & change) & uLocalXmtBuffer[0];
		
	// Determine if there were any fall events
	fall = (uIOinIntFall & change) & ~uLocalXmtBuffer[0];

	// Determine if there were any change events
	change = (uIOinIntChange & change);

	// Cycle the current value to the old
	uIOinDigiInOld = uLocalXmtBuffer[0];

	// If any of these are true then indicate an interrupt condition
	if (uIOinIntEnable & (change | rise | fall)) uDemoState.bits.b1 = 1;

	if (uDemoState.bits.b1)
	{
		switch (uDemoSyncSet)
		{
			case 0:				// Asyclic synchronous transmit
				// Set a synchronous transmit flag
				uDemoState.bits.b2 = 1;
				break;

			case 254:			// Asynchronous transmit
			case 255:						
				// Reset the asynchronous transmit flag
				uDemoState.bits.b0 = 1;
				break;
		}
	}


	// If ready to send 
	if (mTPDOIsPutRdy(1) && uDemoState.bits.b0)
	{
		// Tell the stack data is loaded for transmit
		mTPDOWritten(1);
		
		// Reset any synchronous or asynchronous flags
		uDemoState.bits.b0 = 0;
		uDemoState.bits.b1 = 0;
	}

	// If any data has been received
	if (mRPDOIsGetRdy(1))
	{
		// Write out the first byte of the buffer
		LATD = uLocalRcvBuffer[0];
		
		// PDO read, free the driver to accept more data
		mRPDORead(1);
	}
}




/*********************************************************************
 * Function:        void CO_COMM_RPDO1_COBIDAccessEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is a simple demonstration of a RPDO COB access
 *					handling function.
 *
 * Note:          	This function is called from the dictionary.
 ********************************************************************/
void CO_COMM_RPDO1_COBIDAccessEvent(void)
{
	switch (mCO_DictGetCmd())
	{
		case DICT_OBJ_READ: 	// Read the object
			// Translate MCHP COB to CANopen COB
			mTOOLS_MCHP2CO(mRPDOGetCOB(1));
			
			// Return the COBID
			*(unsigned long *)(uDict.obj->pReqBuf) = mTOOLS_GetCOBID();
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			// Translate the COB to MCHP format
			mTOOLS_CO2MCHP(*(unsigned long *)(uDict.obj->pReqBuf));
			
			// If the request is to stop the PDO
			if ((*(UNSIGNED32 *)(&mTOOLS_GetCOBID())).PDO_DIS)
			{
				// And if the COB received matches the stored COB and type then close
				if (!((mTOOLS_GetCOBID() ^ mRPDOGetCOB(1)) & 0xFFFFEFFFL))
				{
					// but only close if the PDO endpoint was open
					if (mRPDOIsOpen(1)) {mRPDOClose(1);}
		
					// Indicate to the local object that this PDO is disabled
					(*(UNSIGNED32 *)(&mRPDOGetCOB(1))).PDO_DIS = 1;
				}
				else {mCO_DictSetRet(E_PARAM_RANGE);} //error
			}

			// Else if the TPDO is not open then start the TPDO
			else
			{
				// And if the COB received matches the stored COB and type then open
				if (!((mTOOLS_GetCOBID() ^ mRPDOGetCOB(1)) & 0xFFFFEFFFL))
				{
					// but only open if the PDO endpoint was closed
					if (!mRPDOIsOpen(1)) {mRPDOOpen(1);}
						
					// Indicate to the local object that this PDO is enabled
					(*(UNSIGNED32 *)(&mRPDOGetCOB(1))).PDO_DIS = 0;
				}
				else {mCO_DictSetRet(E_PARAM_RANGE);} //error
			}
			break;
	}	
}



/*********************************************************************
 * Function:        void CO_COMM_TPDO1_COBIDAccessEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is a simple demonstration of a TPDO COB access
 *					handling function.
 *
 * Note:          	This function is called from the dictionary.
 ********************************************************************/
void CO_COMM_TPDO1_COBIDAccessEvent(void)
{
	switch (mCO_DictGetCmd())
	{
		case DICT_OBJ_READ: 	// Read the object
			// Translate MCHP COB to CANopen COB
			mTOOLS_MCHP2CO(mTPDOGetCOB(1));
			
			// Return the COBID
			*(unsigned long *)(uDict.obj->pReqBuf) = mTOOLS_GetCOBID();
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			// Translate the COB to MCHP format
			mTOOLS_CO2MCHP(*(unsigned long *)(uDict.obj->pReqBuf));
			
			// If the request is to stop the PDO
			if ((*(UNSIGNED32 *)(&mTOOLS_GetCOBID())).PDO_DIS)
			{
				// And if the COB received matches the stored COB and type then close
				if (!((mTOOLS_GetCOBID() ^ mTPDOGetCOB(1)) & 0xFFFFEFFFL))
				{
					// but only close if the PDO endpoint was open
					if (mTPDOIsOpen(1)) {mTPDOClose(1);}
		
					// Indicate to the local object that this PDO is disabled
					(*(UNSIGNED32 *)(&mTPDOGetCOB(1))).PDO_DIS = 1;
				}
				else {mCO_DictSetRet(E_PARAM_RANGE);} //error
			}

			// Else if the TPDO is not open then start the TPDO
			else
			{
				// And if the COB received matches the stored COB and type then open
				if (!((mTOOLS_GetCOBID() ^ mTPDOGetCOB(1)) & 0xFFFFEFFFL))
				{
					// but only open if the PDO endpoint was closed
					if (!mTPDOIsOpen(1)) {mTPDOOpen(1);}
						
					// Indicate to the local object that this PDO is enabled
					(*(UNSIGNED32 *)(&mTPDOGetCOB(1))).PDO_DIS = 0;
				}
				else {mCO_DictSetRet(E_PARAM_RANGE);} //error
			}
			break;
	}	
}



/*********************************************************************
 * Function:        void CO_COMM_TPDO1_TypeAccessEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is a simple demonstration of a TPDO type access
 *					handling function.
 *
 * Note:          	This function is called from the dictionary.
 ********************************************************************/
void CO_COMM_TPDO1_TypeAccessEvent(void)
{
	unsigned char tempType;
	
	switch (mCO_DictGetCmd())
	{
		//case DICT_OBJ_INFO:		// Get information about the object
			// The application should use this to load the 
			// structure with legth, access, and mapping.
		//	break;

		case DICT_OBJ_READ: 	// Read the object
			// Write the Type to the buffer
			*(uDict.obj->pReqBuf) = uDemoSyncSet;
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			tempType = *(uDict.obj->pReqBuf);
			if ((tempType >= 0) && (tempType <= 240))
			{
				// Set the new type and resync
				uDemoSyncCount = uDemoSyncSet = tempType;
			}
			else 
			if ((tempType == 254) || (tempType == 255))
			{
				uDemoSyncSet = tempType;
			}
			else {mCO_DictSetRet(E_PARAM_RANGE);} //error
			
			break;
	}	
}








/*********************************************************************
 * Function:        void CO_PDO1LSTimerEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        none
 *
 * Note:          	none
 ********************************************************************/
void CO_PDO1LSTimerEvent(void)
{
	
}



/*********************************************************************
 * Function:        void CO_PDO1TXFinEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        none
 *
 * Note:          	none
 ********************************************************************/
void CO_PDO1TXFinEvent(void)
{
	
}


