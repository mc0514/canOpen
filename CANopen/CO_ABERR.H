/*****************************************************************************
 *
 * Microchip CANopen Stack (Common Errors)
 *
 *****************************************************************************
 * FileName:        CO_ABERR.H
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



typedef enum _SDO_REQ_STATUS
{
	E_SUCCESS = 0,
	E_TOGGLE,
	E_SDO_TIME,
	E_CS_CMD,
	E_MEMORY_OUT,
	E_UNSUPP_ACCESS,
	E_CANNOT_READ,
	E_CANNOT_WRITE,
	E_OBJ_NOT_FOUND,
	E_OBJ_CANNOT_MAP,
	E_OBJ_MAP_LEN,
	E_GEN_PARAM_COMP,
	E_GEN_INTERNAL_COMP,
	E_HARDWARE,
	E_LEN_SERVICE,
	E_LEN_SERVICE_HIGH,
	E_LEN_SERVICE_LOW,
	E_SUBINDEX_NOT_FOUND,
	E_PARAM_RANGE,
	E_PARAM_HIGH,
	E_PARAM_LOW,
	E_MAX_LT_MIN,
	E_GENERAL,
	E_TRANSFER,
	E_LOCAL_CONTROL,
	E_DEV_STATE
}REQ_STAT;
