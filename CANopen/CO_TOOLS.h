/*****************************************************************************
 *
 * Microchip CANopen Stack (COB Conversion Tools)
 *
 *****************************************************************************
 * FileName:        CO_TOOLS.C
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


#ifndef	__CO_TOOLS_H
#define	__CO_TOOLS_H

extern UNSIGNED32		_uCOB_ID_in;
extern UNSIGNED32		_uCOB_ID_out;



/*********************************************************************
 * Function:        void _CO_COB_CANopen2MCHP(void)
 *
 * PreCondition:    _uCOB_ID_in must be loaded.
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function converts the CANopen COB format to
 *					the MCHP format.
 *
 * Note:          	B3       B2       B1       B0					
 *					-----------------------------------
 * CANopen format	28 - 24  23 - 16  15 - 8   7 - 0
 *    				nmtxxxxx xxxxxxxx xxxxxxxx xxxxxxxx
 * MCHP format		7 - 0    15 - 8   20 - 16  28 - 21
 *					xxxxxxxx xxxxxxxx xxxntmxx xxxxxxxx
 *
 * CANopen format	                  10 - 8   7 - 0
 *    				nmt----- -------- -----xxx xxxxxxxx
 * MCHP format		                  3 - 0    10 - 3
 *					-------- -------- xxxntm-- xxxxxxxx
 *
 * n = option bit 1
 * m = option bit 2
 * t = ID type (standard = 0, extended = 1)
 ********************************************************************/
void _CO_COB_CANopen2MCHP(void);



/*********************************************************************
 * Function:        void _CO_COB_CANopen2MCHP(void)
 *
 * PreCondition:    _uCOB_ID_in must be loaded.
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function converts the MCHP COB format to
 *					the CANopen format.
 *
 * Notes:			B3       B2       B1       B0					
 *					-----------------------------------
 * CANopen format	28 - 24  23 - 16  15 - 8   7 - 0
 *    				nmtxxxxx xxxxxxxx xxxxxxxx xxxxxxxx
 * MCHP format		7 - 0    15 - 8   20 - 16  28 - 21
 *					xxxxxxxx xxxxxxxx xxxntmxx xxxxxxxx
 *
 * CANopen format	                  10 - 8   7 - 0
 *    				nmt----- -------- -----xxx xxxxxxxx
 * MCHP format		                  3 - 0    10 - 3
 *					-------- -------- xxxntm-- xxxxxxxx
 *
 * n = option bit 1
 * m = option bit 2
 * t = ID type (standard = 0, extended = 1)
 ********************************************************************/
void _CO_COB_MCHP2CANopen(void);



/*********************************************************************
 * Function:        void mTOOLS_MCHP2CO(MCHP_COB)
 *
 * PreCondition:    _uCOB_ID_in must be loaded.
 *
 * Input:       	MCHP_COB, the CAN ID in MCHP format
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function converts the MCHP COB format to
 *					the CANopen format.
 *
 * Notes:		 	Use mTOOLS_GetCOBID to retrieve the result.
 ********************************************************************/
#define mTOOLS_MCHP2CO(MCHP_COB) 	_uCOB_ID_in.word = MCHP_COB; _CO_COB_MCHP2CANopen();



/*********************************************************************
 * Function:        void mTOOLS_CO2MCHP(CO_COB)
 *
 * PreCondition:    _uCOB_ID_in must be loaded.
 *
 * Input:       	CO_COB, the CAN ID in CANopen format
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function converts the MCHP COB format to
 *					the CANopen format.
 *
 * Notes:		 	Use mTOOLS_GetCOBID to retrieve the result.
 ********************************************************************/
#define mTOOLS_CO2MCHP(CO_COB) 		_uCOB_ID_in.word = CO_COB; _CO_COB_CANopen2MCHP();
	


/*********************************************************************
 * Function:        UNSIGNED32 mTOOLS_CO2MCHP(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	UNSIGNED32, the result of the conversion  
 *
 * Side Effects:    none
 *
 * Overview:        This function returns the result of a CAN ID 
 *					conversion.
 *
 * Note:		 	
 ********************************************************************/
#define mTOOLS_GetCOBID()			_uCOB_ID_out.word



#endif	//__CO_TOOLS_H


