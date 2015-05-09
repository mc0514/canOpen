/*****************************************************************************
 *
 * Microchip CANopen Stack (Device Info)
 *
 *****************************************************************************
 * FileName:        CO_DEV.C
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
 * This file contains many of the standard objects defined by CANopen.
 * 
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ross Fosler			11/13/03	...	
 * 
 *****************************************************************************/

#include	"CO_TYPES.H"

// CANopen object 0x1000
rom unsigned long rCO_DevType = 		0x8934AL;

// CANopen object 0x1008
rom unsigned char rCO_DevName[] = 		"CONTROLLER";

// CANopen object 0x1009
rom unsigned char rCO_DevHardwareVer[] = 	"V1.0";

// CANopen object 0x100A
rom unsigned char rCO_DevSoftwareVer[] = 	"V1.0";

// CANopen object 0x1018
rom unsigned char rCO_DevIdentityIndx = 	0x5;
rom unsigned long rCO_DevVendorID = 		0x55551111L;
rom unsigned long rCO_DevProductCode = 		0x55552222L;
rom unsigned long rCO_DevRevNo = 		0x55553333L;
rom unsigned long rCO_DevSerialNo = 		0x55554444L;

// CANopen object 0x1001
unsigned char uCO_DevErrReg;

// CANopen object 0x1002
unsigned long uCO_DevManufacturerStatReg;

