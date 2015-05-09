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



#ifndef	__CO_SDO1_H
#define	__CO_SDO1_H


extern rom unsigned char _uSDO1COMMIndx;



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
void _CO_COMM_SDO1_CS_COBIDAccessEvent(void);


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
void _CO_COMM_SDO1_SC_COBIDAccessEvent(void);



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
void _CO_COMM_SDO1_Open(void);


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
void _CO_COMM_SDO1_Close(void);


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
void _CO_COMM_SDO1_LSTimerEvent(void);


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
void _CO_COMM_SDO1_TXEvent(void);


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
void _CO_COMM_SDO1_RXEvent(void);



#endif	//__CO_SDO1_H



