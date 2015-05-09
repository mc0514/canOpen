/*****************************************************************************
 *
 * Microchip CANopen Stack (Main Managing Routines)
 *
 *****************************************************************************
 * FileName:        CO_MAIN.C
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


#include	"CO_TYPES.H"			// Data types
#include	"CO_CANDRV.H"			// Driver services
#include	"CO_COMM.H"				// Object
#include	"CO_NMTE.H"				// Error protocols: heartbeat, node-guard



/*********************************************************************
 * Function:        void CO_ProcessAllEvents(void)
 *
 * PreCondition:    All driver and CANopen initialization must be 
 *					complete before calling this function.
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function is the main entry into CANopen
 *					background processing. In addition the driver 
 *					background functions are controlled from here.
 *
 * Note:          	This function should be called as often as 
 *					necessary to capture CAN events.
 ********************************************************************/
void CO_ProcessAllEvents(void)
{
	// Process driver events
	_CANEventManager();

	// Process receive events
	_CO_COMMRXEventManager();

	// Process transmit events
	_CO_COMMTXRdyEventManager();

	// Process transmit events
	_CO_COMMTXFinEventManager();
}




