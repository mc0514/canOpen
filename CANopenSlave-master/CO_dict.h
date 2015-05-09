/*****************************************************************************
 *
 * Microchip CANopen Stack (Dictionary Services)
 *
 *****************************************************************************
 * FileName:        CO_DICT.C
 * Dependencies:    
 * Processor:       PIC18F with CAN
 * Compiler:       	C18 02.20.00 or higher
 * Linker:          MPLINK 03.40.00 or higher
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
#ifndef _CO_DICT_H
#define _CO_DICT_H

// This is the scalar equivelant of a portion of the DICT_OBJ
typedef struct _DICTIONARY_OBJECT_TEMPLATE
{
	unsigned int index;
	unsigned char subindex;
	unsigned char ctl;
	unsigned int len;
	rom unsigned char * pROM;
}DICT_OBJECT_TEMPLATE;






typedef struct _DICTIONARY_EXTENDED_OBJECT
{
	//enum _DICT_OBJECT_REQUEST		/* Command required for function */
	//{
	//	DICT_OBJ_INFO = 0,
	//	DICT_OBJ_READ,
	//	DICT_OBJ_WRITE
	//}cmd;

	unsigned char * pReqBuf;		/* Pointer to the requestors buffer */

	unsigned int reqLen;			/* Number of bytes requested */
	unsigned int reqOffst;			/* Starting point for the request */

	unsigned int index;				/* CANOpen Index */
	unsigned char subindex;			/* CANOpen Sub-index */

	enum DICT_CTL					/* Memory access type */
	{
		ACCESS_BITS	= 0b00000111,
				
		NA			= 0b00000000,	/* Default, non-existant */
		CONST		= 0b00000101,	/* Default, read only from ROM */
		RW			= 0b00000011,	/* Default, read/write from RAM */
		RO			= 0b00000001,	/* Default, read only from RAM */
		WO			= 0b00000010,	/* Default, write only to RAM */
		RW_EE		= 0b00001011,	/* Default, read/write from EEDATA */
		RO_EE		= 0b00001001,	/* Default, read only from EEDATA */
		WO_EE		= 0b00001010,	/* Default, write only to EEDATA */
		FUNC		= 0b00010000,	/* Default, function specific */
		
		RD_BIT		= 0b00000001,	/* Read Access */
		RD			= 0b01111111,	
		N_RD		= 0b01111110,	
		
		WR_BIT		= 0b00000010,	/* Write Access */
		WR			= 0b01111111,	
		N_WR		= 0b01111101,
		
		ROM_BIT		= 0b00000100,	/* ROM based object */
		ROM			= 0b01111111,	
		N_ROM		= 0b01111011,
		
		EE_BIT		= 0b00001000,	/* EEDATA based object */
		EE			= 0b01111111,
		N_EE		= 0b01110111,
		
		FDEF_BIT	= 0b00010000,	/* Functionally defined access */
		FDEF		= 0b01111111,	
		N_FDEF		= 0b01101111,
		
		MAP_BIT		= 0b00100000,	/* PDO Mappability*/
		MAP			= 0b01111111,
		N_MAP		= 0b01011111,	
		
		FSUB_BIT	= 0b01000000,	/* Functionally defined sub-index */
		FSUB		= 0b01111111,
		N_FSUB		= 0b00111111	
	}ctl;
	
	unsigned int len;				/* Size of the object in bytes */
	
	union DICT_PTRS					/* Pointers to objects */
	{
		void (* pFunc)(void);
		unsigned char * pRAM;
		rom unsigned char * pROM;
		unsigned int pEEDATA;
	}p;
	
}DICT_OBJ;




typedef struct _MULTIPLEXOR
{
	UNSIGNED16 index;
	UNSIGNED8 sindex;
}MULTIPLEXOR;


typedef struct _DICTIONARY_DATA
{
	DICT_OBJ * obj;					/* Pointer to the local object */
	enum _DICT_OBJECT_REQUEST		/* Command required for function */
	{
		DICT_OBJ_INFO = 0,
		DICT_OBJ_READ,
		DICT_OBJ_WRITE
	}cmd;
	unsigned char ret;				/* Return status */
}DICT_PARAM;


extern DICT_PARAM uDict;



void _CO_DictObjectRead(void);
void _CO_DictObjectWrite(void);
void _CO_DictObjectDecode(void);
void _CO_DictTest(void);
void _CO_TestObjectAccessEvent(void);


#define	mCO_DictObjectRead(myObj)	{uDict.obj = &myObj; _CO_DictObjectRead();}
#define	mCO_DictObjectWrite(myObj) 	{uDict.obj = &myObj; _CO_DictObjectWrite();}
#define mCO_DictObjectDecode(myObj)	{uDict.obj = &myObj; _CO_DictObjectDecode();}
#define mCO_DictGetCmd()			uDict.cmd
#define mCO_DictGetRet()			uDict.ret
#define mCO_DictSetRet(retVal)		uDict.ret = retVal

#endif
