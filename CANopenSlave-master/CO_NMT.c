/*****************************************************************************
 *
 * Microchip CANopen Stack (Network Management and Communications)
 *
 *****************************************************************************
 * FileName:        CO_NMT.C
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
 * This is the network management object.
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

#include        "NMTextension.h"
#include        "Globals.h"

/*
// Event functions for reset requests
void CO_NMTStateChangeEvent(void);
void CO_NMTResetEvent(void);
void CO_NMTAppResetRequest(void);
*/

// Handle for NMT
unsigned char _hNMT;



/*********************************************************************
 * Function:        void _CO_COMM_NMT_Open(void)
 *
 * PreCondition:    The ECAN driver must be initialized.
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function opens an in endpoint for network
 *					management.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMT_Open(void)
{	
	// Open a receive message endpoint in the driver
	mCANOpenMessage((COMM_MSGGRP_NETCTL) | COMM_NETCTL_NMT, 0x00L, _hNMT);
	
	// Enable NMT
	if (_hNMT) COMM_NETCTL_NMT_EN = 1;
}



/*********************************************************************
 * Function:        void _CO_COMM_NMT_Close(void)
 *
 * PreCondition:    The ECAN driver must be initialized.
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function closes the in endpoint.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMT_Close(void)
{
	// Call the driver, request to close the receive endpoint
	mCANCloseMessage(_hNMT);
	COMM_NETCTL_NMT_EN = 0;
}





/*********************************************************************
 * Function:        void _CO_COMM_NMT_RXEvent(void)
 *
 * PreCondition:    The ECAN driver must be initialized.
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function processes receive events for this 
 *					endpoint, in particular network management.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMT_RXEvent(void)
{	
	// If the length of the data is 2 then continue
	if (mCANGetDataLen() == 2)
	{
		// Check the received Node ID or broadcast
		if ((mCANGetDataByte1() == _uCO_nodeID.byte) || (!mCANGetDataByte1()))
		{
			// OPP, STOP, PRE
			//  x    x    0		Not started, will never enter this function
			//  0    0    1		Pre-operational
			//  0    1    1		Stopped from pre-operational
			//  1    0    1		Operational
			//  1    1    1		Stopped from operational
			
			// Decode the network request and execute
			switch(mCANGetDataByte0())
			{
				case 1:		// Start Node
					COMM_STATE_OPER = 1;
					COMM_STATE_STOP = 0;
					CO_NMTStateChangeEvent();  // Notify the app 
					break;
				case 2:		// Stop Node
					COMM_STATE_STOP = 1;
					CO_NMTStateChangeEvent();  // Notify the app 
					break;
				case 128:	// Pre-operational
					COMM_STATE_OPER = 0;
					COMM_STATE_STOP = 0;					
					CO_NMTStateChangeEvent();  // Notify the app 
					break;
					
				case 129:	// Reset node
					CO_NMTAppResetRequest(); 	// Notify the app
							
				case 130:	// Reset communications	
					CO_NMTResetEvent();		// Notify the app
					
					// Reset Communications
					_CO_COMMResetEventManager();
					break;
						
			}// Unknown requests, ignore
		}
	} 
}


