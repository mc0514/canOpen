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






#ifndef	__CO_MEMIO_H
#define	__CO_MEMIO_H



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
void CO_MEMIO_CopySram(unsigned char *pIn, unsigned char *pOut, unsigned int len);



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
void CO_MEMIO_CopyRomToRam(rom unsigned char *pIn, unsigned char *pOut, unsigned int len);

#endif	//__CO_MEMIO_H



