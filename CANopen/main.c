/*****************************************************************************
 *
 * Microchip CANopen Stack (Main Entry)
 *
 *****************************************************************************
 * FileName:        main.C
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
 * This is the main entry into the demonstration. In this file some startup
 * and running conditions are demonstrated.
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ross Fosler			11/13/03	...	
 * 
 *****************************************************************************/



#include	"CO_MAIN.H"
#include	"Timer.H"
#include	"DemoObj.h"


unsigned char test3[0x20];
unsigned long msgID;
unsigned char hMsg;



/*********************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Main entry into the application.
 *
 * Note:          	The following is simply a demonstration of 
 *					initialization and running the CANopen stack. 
 ********************************************************************/
void main(void)
{	
	// Perform any application specific initialization

	TimerInit();				// Init my timer

	mSYNC_SetCOBID(0x1000);		// Set the SYNC COB ID (MCHP format)
	mCO_SetNodeID(0x02);		// Set the Node ID
	mCO_SetBaud(0x00);			// Set the baudrate
	
	mNMTE_SetHeartBeat(20000);	// Set the initial heartbeat
	mNMTE_SetGuardTime(0000);	// Set the initial guard time
	mNMTE_SetLifeFactor(0x00);	// Set the initial life time

	DemoInit();					// Initialize my demo

	mCO_InitAll();				// Initialize CANopen to run, bootup will be sent
		
	while(1)
	{
		// Process CANopen events
		mCO_ProcessAllEvents();		
		
		// Process application specific functions
		DemoProcessEvents();		
		
		// 1ms timer events
		if (TimerIsOverflowEvent())
		{
			// Process timer related events
			mCO_ProcessAllTimeEvents();	
		}
	}
}




