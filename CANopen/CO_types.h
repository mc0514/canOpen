/*****************************************************************************
 *
 * Microchip CANopen Stack (Data types)
 *
 *****************************************************************************
 * FileName:        CO_TYPES.H
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


typedef struct _SID
{
	union _SIDH
	{
		unsigned char 	byte;
		struct _SIDH_BITS
		{
			unsigned	SIDH:8;	
		}bits;
	}h;
	union _SIDL
	{
		unsigned char byte;
		struct _SIDL_BITS
		{
			unsigned 	:2;
			unsigned	fen:1;
			unsigned	EXIDEN:1;
			unsigned	:1;
			unsigned	SIDL:3;
		}bits;
	}l;
}CAN_SID;


typedef struct _EID
{
	union _EIDUH
	{
		unsigned char byte;
		struct _EIDUH_BITS
		{
			unsigned	EIDUH:8;
		}bits;
	}uh;
	union _EIDUL
	{
		unsigned char byte;
		struct _EIDUL_BITS
		{
			unsigned 	EIDUL1:2;
			unsigned	fen:1;
			unsigned	EXIDEN:1;
			unsigned	:1;
			unsigned	EIDUL2:3;
		}bits;
	}ul;
	union _EIDH
	{
		unsigned char byte;
		struct _EIDH_BITS
		{
			unsigned	EIDH:8;
		}bits;
	}h;
	union _EIDL
	{
		unsigned char byte;
		struct _EIDL_BITS
		{
			unsigned 	EIDL:8;
		}bits;
	}l;
}CAN_EID;



typedef union _CID
{
	CAN_EID ext;
	CAN_SID	std;
}CAN_CID;



typedef union _DLC
{
	unsigned char byte;
	struct _DLC_BITS
	{
		unsigned 	count:4;
		unsigned 	:2;
		unsigned	rtr:1;
		unsigned 	:1;
	}bits;	
}CAN_DLC;



typedef struct _CAN_MSG
{
	CAN_CID cid;
	CAN_DLC dlc;
	unsigned char D0;
	unsigned char D1;
	unsigned char D2;
	unsigned char D3;
	unsigned char D4;
	unsigned char D5;
	unsigned char D6;
	unsigned char D7;
}CAN_MSG;
	



/* Message handle */
typedef union _CAN_MSGHANDLE
{
	unsigned char byte;
	struct _CAN_MSGHANDLE_BITS
	{
		unsigned	h1:1;
		unsigned	h2:1;
		unsigned	h3:1;
		unsigned	h4:1;
		unsigned	h5:1;
		unsigned	h6:1;
		unsigned	h7:1;
		unsigned	h8:1;
	}bits;
	struct _CAN_MSGHANDLE_NIB
	{
		unsigned num:3;		// 8 possible messages
		unsigned grp:2;		// in 4 possible groups
		unsigned hwbuf:3;	// 8 possible buffers
	}msg;
}CAN_HMSG;





typedef struct _CAN_DATA
{
	unsigned char B0;
	unsigned char B1;
	unsigned char B2;
	unsigned char B3;
	unsigned char B4;
	unsigned char B5;
	unsigned char B6;
	unsigned char B7;
}CAN_DATA;


struct _BITS
{
	unsigned b0:1;
	unsigned b1:1;
	unsigned b2:1;
	unsigned b3:1;
	unsigned b4:1;
	unsigned b5:1;
	unsigned b6:1;
	unsigned b7:1;
};

union _UINT8								// Array of 8 bits
{
	unsigned char byte;	
	struct _BITS bits;
};

union _SINT8								// Array of 8 bits
{
	char byte;	
	struct _BITS bits;
};

struct _INT16
{
	union _UINT8 B0;
	union _UINT8 B1;
};

struct _INT24
{
	union _UINT8 B0;
	union _UINT8 B1;
	union _UINT8 B3;
};

struct _INT32
{
	union _UINT8 B0;
	union _UINT8 B1;
	union _UINT8 B2;
	union _UINT8 B3;
};


struct _INT40
{
	union _UINT8 B0;
	union _UINT8 B1;
	union _UINT8 B2;
	union _UINT8 B3;
	union _UINT8 B4;
};


struct _INT48
{
	union _UINT8 B0;
	union _UINT8 B1;
	union _UINT8 B2;
	union _UINT8 B3;
	union _UINT8 B4;
	union _UINT8 B5;
};


struct _INT56
{
	union _UINT8 B0;
	union _UINT8 B1;
	union _UINT8 B2;
	union _UINT8 B3;
	union _UINT8 B4;
	union _UINT8 B5;
	union _UINT8 B6;
};


struct _INT64
{
	union _UINT8 B0;
	union _UINT8 B1;
	union _UINT8 B2;
	union _UINT8 B3;
	union _UINT8 B4;
	union _UINT8 B5;
	union _UINT8 B6;
	union _UINT8 B7;
};


union _UINT16
{
	unsigned int word;
	struct _INT16 bytes;
};

union _SINT16
{
	signed int word;
	struct _INT16 bytes;	
};

union _UINT24
{
	unsigned short long word;
	struct _INT24 bytes;	
};

union _SINT24
{
	signed short long word;
	struct _INT24 bytes;	
};


union _UINT32
{
	unsigned long word;
	struct _INT32 bytes;	
};

union _SINT32
{
	signed long word;
	struct _INT32 bytes;	
};


union _UINT40
{
	unsigned long word;
	struct _INT40 bytes;	
};

union _SINT40
{
	signed long word;
	struct _INT40 bytes;	
};


union _UINT48
{
	unsigned long word;
	struct _INT48 bytes;	
};

union _SINT48
{
	signed long word;
	struct _INT48 bytes;	
};


union _UINT56
{
	unsigned long word;
	struct _INT56 bytes;	
};

union _SINT56
{
	signed long word;
	struct _INT56 bytes;	
};


union _UINT64
{
	unsigned long word;
	struct _INT64 bytes;	
};

union _SINT64
{
	signed long word;
	struct _INT64 bytes;	
};


union _FLOAT
{
	double word;	
};




typedef enum _BOOL { FALSE = 0, TRUE } BOOLEAN;		// Boolean
typedef union _SINT8 INTEGER8;						// Signed 8-bit number
typedef union _UINT8 UNSIGNED8;						// Unsigned 8-bit number
typedef union _SINT16 INTEGER16;					// Signed 16-bit number
typedef union _UINT16 UNSIGNED16;					// Unsigned 16-bit number
typedef union _SINT24 INTEGER24;					// Signed 24-bit number
typedef union _UINT24 UNSIGNED24;					// Unsigned 24-bit number
typedef union _SINT32 INTEGER32;					// Signed 32-bit number
typedef union _UINT32 UNSIGNED32;					// Unsigned 32-bit number
typedef union _SINT40 INTEGER40;					// Signed 40-bit number
typedef union _UINT40 UNSIGNED40;					// Unsigned 40-bit number
typedef union _SINT48 INTEGER48;					// Signed 48-bit number
typedef union _UINT48 UNSIGNED48;					// Unsigned 48-bit number
typedef union _SINT56 INTEGER56;					// Signed 56-bit number
typedef union _UINT56 UNSIGNED56;					// Unsigned 56-bit number
typedef union _SINT64 INTEGER64;					// Signed 64-bit number
typedef union _UINT64 UNSIGNED64;					// Unsigned 64-bit number
typedef union _FLOAT FLOAT;
typedef unsigned char * STRING;						// String data type



/* Data types used for block copy */
typedef struct _DATA_BLOCK_4
{
	unsigned char bytes[4];
}_DATA4;

typedef struct __DATA7
{
	unsigned char myDat[7];
}_DATA7;

typedef struct __DATA8
{
	unsigned char myDat[8];
}_DATA8;
