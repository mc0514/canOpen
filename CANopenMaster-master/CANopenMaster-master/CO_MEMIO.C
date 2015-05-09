/*****************************************************************************
 *
 * Microchip CANopen Stack (Memory APIs)
 *
 *****************************************************************************
 * FileName:        CO_MEMIO.C
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
 * This file contains some basic memory copy APIs. They are designed to 
 * accelerate data movement above typical looped index coppies.
 * 
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ross Fosler			11/13/03	...	
 * 
 *****************************************************************************/



#include	"CO_DEFS.DEF"			// Global definitions
#include	"CO_MEMIO.H"


// Private structures used to set block copy sizes
typedef struct _DATA_BLOCK_16
{
	unsigned char bytes[16];
}_DATA16;

typedef struct _DATA_BLOCK_8
{
	unsigned char bytes[8];
}_DATA8;

typedef struct _DATA_BLOCK_4
{
	unsigned char bytes[4];
}_DATA4;





/*********************************************************************
 * Function:        void CO_MEMIO_CopySram(unsigned char *pIn, 
 *											unsigned char *pOut, 
 *											unsigned int len)
 *
 * PreCondition:    none
 *
 * Input:       	unsigned char *pIn - pointer to in buffer
 *					unsigned char *pOut - pointer to out buffer
 *					unsigned int len - number of bytes to copy
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Copy memory SRAM to SRAM.
 *
 * Note:          	
 ********************************************************************/
void CO_MEMIO_CopySram(unsigned char *pIn, unsigned char *pOut, unsigned int len)
{	
	while (len)
	{
		if (len < 4)
		{
			*pOut = *pIn;
			
			pOut++; 
			pIn++; 
			len--;	
		}
		else 
		if (len < 8)
		{
			*((_DATA4 *)pOut) = *((_DATA4 *)(pIn));
			
			pOut += 4;
			pIn += 4;
			len -= 4;
		}
		else 
		if (len < 16)
		{
			*((_DATA8 *)pOut) = *((_DATA8 *)(pIn));
			
			pOut += 8;
			pIn += 8;
			len -= 8;
		}
		else 
		{
			*((_DATA16 *)pOut) = *((_DATA16 *)(pIn));
			
			pOut += 16;
			pIn += 16;
			len -= 16;
		}
	}
}



/*********************************************************************
 * Function:        void CO_MEMIO_CopyRomToRam(rom unsigned char *pIn,
 * 												unsigned char *pOut, 
 * 												unsigned int len) 
 *
 * PreCondition:    none
 *
 * Input:       	unsigned char *pIn - pointer to rom in buffer
 *					unsigned char *pOut - pointer to sram out buffer
 *					unsigned int len - number of bytes to copy
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Copy memory ROM to SRAM.
 *
 * Note:          	
 ********************************************************************/
void CO_MEMIO_CopyRomToRam(rom unsigned char *pIn, unsigned char *pOut, unsigned int len)
{
#if (CO_SPEED_UP_CODE)	

	*pOut;
	*pIn;
	
	while (len)
	{
		if (len < 4)
		{
			_asm
	        TBLRDPOSTINC
	        movff TABLAT,POSTINC0       //1
	        _endasm
	        
	        len--;
		}
		else 
		if (len < 8)
		{
			_asm
	        TBLRDPOSTINC
	        movff TABLAT,POSTINC0       //1
	        TBLRDPOSTINC
	        movff TABLAT,POSTINC0       //2
	        TBLRDPOSTINC
	        movff TABLAT,POSTINC0       //3
	        TBLRDPOSTINC
	        movff TABLAT,POSTINC0       //4
	        _endasm
	        
	        len-=4;
		}
		else
		{
			_asm
	        TBLRDPOSTINC
	        movff TABLAT,POSTINC0       //1
	        TBLRDPOSTINC
	        movff TABLAT,POSTINC0       //2
	        TBLRDPOSTINC
	        movff TABLAT,POSTINC0       //3
	        TBLRDPOSTINC
	        movff TABLAT,POSTINC0       //4
	        TBLRDPOSTINC
	        movff TABLAT,POSTINC0       //5
	        TBLRDPOSTINC
	        movff TABLAT,POSTINC0       //6
	        TBLRDPOSTINC
	        movff TABLAT,POSTINC0       //7
	        TBLRDPOSTINC
	        movff TABLAT,POSTINC0       //8
	        _endasm
	        
	        len-=8;
		}
	}
		
		
#else
	while (len)
	{	
		if (len < 4)
		{
			*pOut = *pIn;			
			
			pOut++; 
			pIn++; 
			len--;	
		}
		else 
		if (len < 8)
		{
			*((_DATA4 *)(pOut)) = *((rom _DATA4 *)pIn);
			
			pOut += 4;
			pIn += 4;
			len -= 4;
		}
		else 
		{
			*((_DATA8 *)(pOut)) = *((rom _DATA8 *)pIn);
			
			pOut += 8;
			pIn += 8;
			len -= 8;
		}
	}
#endif
}
