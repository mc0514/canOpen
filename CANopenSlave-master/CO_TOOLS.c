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




#include	"CO_TYPES.H"			// Data types




typedef struct _MCHP_SID
{
	union _SIDH
	{
		unsigned char 	byte;
	}h;
	union _SIDL
	{
		unsigned char byte;
		struct _SIDL_BITS
		{
			unsigned 	:2;
			unsigned	b0:1;
			unsigned	id:1;
			unsigned	b1:1;
			unsigned	SIDL:3;
		}bits;
	}l;
}MCHP_SID;


typedef struct _MCHP_EID
{
	union _EIDUH
	{
		unsigned char byte;
	}uh;
	union _EIDUL
	{
		unsigned char byte;
		struct _EIDUL_BITS
		{
			unsigned 	EIDUL1:2;
			unsigned	b0:1;
			unsigned	id:1;
			unsigned	b1:1;
			unsigned	EIDUL2:3;
		}bits;
	}ul;
	union _EIDH
	{
		unsigned char byte;
	}h;
	union _EIDL
	{
		unsigned char byte;
	}l;
}MCHP_EID;



typedef union _CID
{
	unsigned long lword;
	MCHP_EID ext;
	MCHP_SID std;
}MCHP_CID;



typedef struct _CO_CID
{
	union _CO_L
	{
		unsigned char byte;
	}l;
	union _CO_H
	{
		unsigned char byte;
	}h;
	union _CO_UL
	{
		unsigned char byte;
	}ul;
	union _CO_UH
	{
		unsigned char byte;
		struct _CO_UH_BITS
		{
			unsigned 	:5;
			unsigned 	id:1;
			unsigned	b0:1;
			unsigned 	b1:1;
		}bits;
	}uh;
}CO_CID;



//unsigned long uMCHP_COB;
//unsigned long uCO_COB;

UNSIGNED32		_uCOB_ID_in;
UNSIGNED32		_uCOB_ID_out;



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
void _CO_COB_CANopen2MCHP(void)
{
	// If this is an extended ID
	if (_uCOB_ID_in.bytes.B3.byte & 0x20)
	{
		// Shift bits 28 - 16
		*(unsigned int *)(&_uCOB_ID_out.bytes.B0.byte) = (*(unsigned int *)(&_uCOB_ID_in.bytes.B2.byte)) << 3;
		
		// Temporarily store SIDH
		_uCOB_ID_out.bytes.B3.byte = _uCOB_ID_out.bytes.B1.byte;
		
		// Generate SIDL
		_uCOB_ID_out.bytes.B1.byte = ((_uCOB_ID_out.bytes.B0.byte & 0xE0) | (_uCOB_ID_in.bytes.B2.byte & 0x03)) | 0x08;
		
		// Copy SIDH
		_uCOB_ID_out.bytes.B0.byte = _uCOB_ID_out.bytes.B3.byte;
		
		// Copy EIDL and EIDH
		_uCOB_ID_out.bytes.B3.byte = _uCOB_ID_in.bytes.B0.byte;
		_uCOB_ID_out.bytes.B2.byte = _uCOB_ID_in.bytes.B1.byte;
	}
	// Else 11-bit ID
	else
	{
		// Convert the ID
		_uCOB_ID_out.word = ((unsigned int)(_uCOB_ID_in.word) << 5);
		_uCOB_ID_out.bytes.B2.byte = _uCOB_ID_out.bytes.B0.byte;
		_uCOB_ID_out.bytes.B0.byte = _uCOB_ID_out.bytes.B1.byte;
		_uCOB_ID_out.bytes.B1.byte = _uCOB_ID_out.bytes.B2.byte & 0xE0;
		_uCOB_ID_out.bytes.B2.byte = 0;
	} 

	// Set the option bits
	if (_uCOB_ID_in.bytes.B3.bits.b7) _uCOB_ID_out.bytes.B1.bits.b4 = 1;
	if (_uCOB_ID_in.bytes.B3.bits.b6) _uCOB_ID_out.bytes.B1.bits.b2 = 1;
}






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
 * Note:			B3       B2       B1       B0					
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
void _CO_COB_MCHP2CANopen(void)
{
	// If this is an extended ID
	if (_uCOB_ID_in.bytes.B1.byte & 0x08)
	{
		// Generate part of upper high and part of upper low
		_uCOB_ID_out.bytes.B3.byte = _uCOB_ID_in.bytes.B0.byte;
		_uCOB_ID_out.bytes.B2.byte = _uCOB_ID_in.bytes.B1.byte;
				
		*(unsigned int *)(&_uCOB_ID_out.bytes.B2.byte) = ((*(unsigned int *)(&_uCOB_ID_out.bytes.B2.byte)) >> 3);
		
		_uCOB_ID_out.bytes.B3.byte = _uCOB_ID_out.bytes.B3.byte | 0x20;

		// Get the last two bits to complete upper low
		_uCOB_ID_out.bytes.B2.byte = (_uCOB_ID_out.bytes.B2.byte & 0xFC) | (_uCOB_ID_in.bytes.B1.byte & 0x03);
		
		// Get high
		_uCOB_ID_out.bytes.B0.byte = _uCOB_ID_in.bytes.B3.byte;
		
		// Get low
		_uCOB_ID_out.bytes.B1.byte = _uCOB_ID_in.bytes.B2.byte;
	}
	// Else 11-bit ID
	else
	{
		// Swap the bytes
		_uCOB_ID_out.bytes.B1.byte = _uCOB_ID_in.bytes.B0.byte;
		_uCOB_ID_out.bytes.B0.byte = _uCOB_ID_in.bytes.B1.byte;
		
		// Generate the low byte and part of the high byte
		(*(unsigned int *)(&_uCOB_ID_out.bytes.B0.byte)) = ((*(unsigned int *)(&_uCOB_ID_out.bytes.B0.byte)) >> 5);
	}

	// Set the option bits
	if (_uCOB_ID_in.bytes.B1.bits.b2) _uCOB_ID_out.bytes.B3.bits.b6 = 1;
	if (_uCOB_ID_in.bytes.B1.bits.b4) _uCOB_ID_out.bytes.B3.bits.b7 = 1;
}
