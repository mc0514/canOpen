
/*****************************************************************************
 *
 * Timer 
 *
 *****************************************************************************
 * FileName:        Timer.h
 * Dependencies:    
 * Processor:       PIC18F with CAN
 * Compiler:       	C18 02.10.02 or higher
 * Linker:          MPLINK 03.20.01 or higher
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
 * This is a simple timer function used within the DeviceNet Stack for
 * demonstration.
 * 
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ross Fosler			04/28/03	...	
 * 
 *****************************************************************************/



/*********************************************************************
 * Function:        void TimerInit(void)
 *
 * PreCondition:    none
 *
 * Input:       	none	
 *                  
 * Output:      	none
 *
 * Side Effects:    None
 *
 * Overview:        Initializes Timer0 for use.
 *
 * Note:            None
 ********************************************************************/
void TimerInit(void);


/*********************************************************************
 * Function:        unsigned char TimerIsOverflowEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none	
 *                  
 * Output:      	unsigned char status
 *
 * Side Effects:    None
 *
 * Overview:        Checks for an overflow event, returns TRUE if 
 *					an overflow occured.
 *
 * Note:            This function should be checked at least twice
 *					per overflow period.
 ********************************************************************/
unsigned char TimerIsOverflowEvent(void);


