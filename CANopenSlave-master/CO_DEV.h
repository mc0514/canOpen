
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

#ifndef __CO_DEV_H
#define __CO_DEV_H

extern rom unsigned long rCO_DevType; 
extern rom unsigned char rCO_DevName[]; 
extern rom unsigned char rCO_DevHardwareVer[];
extern rom unsigned char rCO_DevSoftwareVer[]; 

extern rom unsigned char rCO_DevIdentityIndx;
extern rom unsigned long rCO_DevVendorID; 
extern rom unsigned long rCO_DevProductCode;
extern rom unsigned long rCO_DevRevNo;
extern rom unsigned long rCO_DevSerialNo;

extern unsigned char uCO_DevErrReg;
extern unsigned long uCO_DevManufacturerStatReg;
extern unsigned long uCO_DevPredefinedErrField;


#endif

