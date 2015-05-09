#ifndef __CO_DEV_H
#define	__CO_DEV_H

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

