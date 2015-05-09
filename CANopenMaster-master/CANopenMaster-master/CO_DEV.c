#include	"CO_TYPES.H"
#include        "CO_DEV.h"


// CANopen object 0x1000
rom unsigned long rCO_DevType = 		0x8934AL;

// CANopen object 0x1008
rom unsigned char rCO_DevName[] = 		"MASTER";

// CANopen object 0x1009
rom unsigned char rCO_DevHardwareVer[] = 	"V1.0";

// CANopen object 0x100A
rom unsigned char rCO_DevSoftwareVer[] = 	"V1.0";

// CANopen object 0x1018
rom unsigned char rCO_DevIdentityIndx = 	0x5;
rom unsigned long rCO_DevVendorID = 		0x11112222L;
rom unsigned long rCO_DevProductCode = 		0x11113333L;
rom unsigned long rCO_DevRevNo = 		0x11114444L;
rom unsigned long rCO_DevSerialNo = 		0x11115555L;

// CANopen object 0x1001
unsigned char uCO_DevErrReg;

// CANopen object 0x1002
unsigned long uCO_DevManufacturerStatReg;

