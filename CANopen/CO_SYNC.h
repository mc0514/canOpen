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



#ifndef	__CO_SYNC_H
#define	__CO_SYNC_H


// Object 1005h, this is also defined functionally
// This is also initialized by the app at startup since it could be 
// initialized from non-volitile memory.
extern UNSIGNED32 _uSYNC_COBID;




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
void _CO_COMM_SYNC_Open(void);


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
void _CO_COMM_SYNC_Close(void);



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
void _CO_COMM_SYNC_RXEvent(void);


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
void _CO_COMM_SYNC_COBIDAccessEvent(void);


/*********************************************************************
 * Function:        void mSYNC_SetCOBID(UNSIGNED32 SYNC_COB)
 *
 * PreCondition:    none
 *
 * Input:       	SYNC_COB, the CAN ID in MCHP format
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Set the CAN ID for the SYNC object.
 *
 * Note:          	
 ********************************************************************/
#define	mSYNC_SetCOBID(SYNC_COB)	_uSYNC_COBID.word = SYNC_COB;


/*********************************************************************
 * Function:        UNSIGNED32 mSYNC_GetCOBID(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	UNSIGNED32, the CAN ID in MCHP format  
 *
 * Side Effects:    none
 *
 * Overview:        Get the CAN ID used by the SYNC object.
 *
 * Note:          	
 ********************************************************************/
#define mSYNC_GetCOBID()			SYNC_COB


#endif	//__CO_SYNC_H


