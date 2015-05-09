
/*****************************************************************************
 *
 * Microchip CANopen Stack (Dictionary Services)
 *
 *****************************************************************************
 * FileName:        CO_DICT.C
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
 * Dictionary services.
 * 
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ross Fosler			11/13/03	...	
 * 
 *****************************************************************************/

#include	"CO_DEFS.DEF"			// Global definitions
#include	"CO_TYPES.H"			// Standard types
#include	"CO_ABERR.H"			// Abort types
#include	"CO_DICT.H"			// Dictionary header
#include	"CO_MEMIO.H"			// Memory IO
#include	"CO_DICT.DEF"			// Standard type and device specific objects
#include	"CO_MFTR.DEF"			// Manufacturer specific objects
#include	"CO_PDO.DEF"			// PDO objects
#include	"CO_STD.DEF"
#include        <p18f4680.h>
#include        "IOutils.h"



// Params used by the dictionary
DICT_PARAM	uDict;


rom unsigned char * _pTmpDBase;
unsigned char 		_tDBaseLen;

unsigned char		_uDictTemp[4];
MULTIPLEXOR			_tMplex;

rom unsigned char	__dummy[4] = {0,0,0,0};



									
/* Dictionary database built into ROM */								
rom DICT_OBJECT_TEMPLATE _db_objects[] = 		{DICTIONARY_DATA_TYPES};
rom DICT_OBJECT_TEMPLATE _db_device[] = 		{DICTIONARY_DEVICE_INFO};
rom DICT_OBJECT_TEMPLATE _db_sdo[] = 			{DICTIONARY_SDO};

rom DICT_OBJECT_TEMPLATE _db_pdo1_tx_comm[] = 		{DICTIONARY_PDO1_TX_COMM};
rom DICT_OBJECT_TEMPLATE _db_pdo2_tx_comm[] = 		{DICTIONARY_PDO2_TX_COMM};

rom DICT_OBJECT_TEMPLATE _db_pdo1_tx_map[] = 		{DICTIONARY_PDO1_TX_MAP};
rom DICT_OBJECT_TEMPLATE _db_pdo2_tx_map[] = 		{DICTIONARY_PDO2_TX_MAP};

rom DICT_OBJECT_TEMPLATE _db_manufacturer_g1[] = 	{DICTIONARY_MANUFACTURER_SPECIFIC_1};
rom DICT_OBJECT_TEMPLATE _db_standard_g1[] = 		{DICTIONARY_STANDARD_1};			

								



/*********************************************************************
 * Function:        void _CO_DictObjectRead(void)
 *
 * PreCondition:    _CO_DictObjectDecode() must have been called to 
 *					fill in the object structure.
 *
 * Input:       	none		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Read the object referenced by uDict.obj.
 *
 * Note:            
 ********************************************************************/
void _CO_DictObjectRead(void)
{
	// If the object is valid, control code must be something other than 0
	if (uDict.obj->ctl) 
	{	
		// Process any functionally defined objects
		if (uDict.obj->ctl & FDEF_BIT)
		{
			uDict.ret = E_SUCCESS;
			uDict.cmd = DICT_OBJ_READ;
			uDict.obj->p.pFunc();	
			return;
		}
		else	

		// Decode the type of object
		switch (uDict.obj->ctl & ACCESS_BITS)
		{
			case CONST:
				//Copy ROM to RAM, uDict.obj->reqLen specifies the amount
				CO_MEMIO_CopyRomToRam(uDict.obj->p.pROM + uDict.obj->reqOffst, uDict.obj->pReqBuf, uDict.obj->reqLen);
				break;

			case RO:
			case RW:
				//Copy RAM to RAM, uDict.obj->reqLen specifies the amount
				CO_MEMIO_CopySram(uDict.obj->p.pRAM + uDict.obj->reqOffst, uDict.obj->pReqBuf, uDict.obj->reqLen);
				break;
				
//			case RW_EE:
//			case RO_EE:
//				break;
						
			default:
				// Error, cannot read object
				uDict.ret = E_CANNOT_READ;
				return;
		}
	}
	
	uDict.ret = E_SUCCESS;
	return;
}



/*********************************************************************
 * Function:        void _CO_DictObjectWrite(void)
 *
 * PreCondition:    _CO_DictObjectDecode() must have been called to 
 *					fill in the object structure.
 *
 * Input:       	none		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Write the object referenced by uDict.obj.
 *
 * Note:            
 ********************************************************************/
void _CO_DictObjectWrite(void)
{
	// If the object is found
	if (uDict.obj->ctl) 
	{
		if (uDict.obj->ctl & FDEF_BIT)
		{
			uDict.ret = E_SUCCESS;
			uDict.cmd = DICT_OBJ_WRITE;
			uDict.obj->p.pFunc();	
			return;
		}
		else	

		// Decode the type of object
		switch (uDict.obj->ctl & ACCESS_BITS)
		{							
			case RW:
			case WO:
				//Copy RAM to RAM, uDict.obj->reqLen specifies the amount
				CO_MEMIO_CopySram(uDict.obj->pReqBuf, uDict.obj->p.pRAM, uDict.obj->reqLen);
				break;
			
//			case RW_EE:
//			case WO_EE:
//				break;
						
			default:
				// Error, write not allowed
				uDict.ret = E_CANNOT_WRITE;
				return;
		}
	}
	
	uDict.ret = E_SUCCESS;
	return;
}


/*********************************************************************
 * Function:        void _CO_DictObjectDecode(void)
 *
 * PreCondition:    The multiplexor referenced by uDict must have been
 *					initialized.
 *
 * Input:       	none		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Find the object in the dictionary and return 
 * 					information related to the object. The user must
 * 					pass a pointer to a structure that contains the 
 *					multiplexor. The decode process will fill the 
 *					rest of the structure with other pertenent
 *					information.
 *
 * Note:            
 ********************************************************************/
/* Decode the object*/
void _CO_DictObjectDecode(void)
{
	// Copy the multiplexor to a local storage area
	_tMplex = *(MULTIPLEXOR *)(&(uDict.obj->index));
	switch (_tMplex.index.bytes.B1.byte & 0xF0)
	{		
		case 0x00:		// Data types
			_pTmpDBase = (rom unsigned char *)_db_objects;
			_tDBaseLen = sizeof(_db_objects)/sizeof(DICT_OBJECT_TEMPLATE);
			break;
		
		case 0x20:		// Manufacturer specific
			_pTmpDBase = (rom unsigned char *)_db_manufacturer_g1;
			_tDBaseLen = sizeof(_db_manufacturer_g1)/sizeof(DICT_OBJECT_TEMPLATE);
			break;
			
		case 0x60:		// Standard
			_pTmpDBase = (rom unsigned char *)_db_standard_g1;
			_tDBaseLen = sizeof(_db_standard_g1)/sizeof(DICT_OBJECT_TEMPLATE);
			break;
					
		case 0x10:
			switch (_tMplex.index.bytes.B1.byte & 0x0F)
			{
				case 0x00:		// Device specific information
					_pTmpDBase = (rom unsigned char *)_db_device;
					_tDBaseLen = sizeof(_db_device)/sizeof(DICT_OBJECT_TEMPLATE);
					break;
					
				case 0x02:		// SDO Server/Client
					_pTmpDBase = (rom unsigned char *)_db_sdo;
					_tDBaseLen = sizeof(_db_sdo)/sizeof(DICT_OBJECT_TEMPLATE);
					break;
					
				case 0x08:		// PDO Transmit Comm				
					if (_tMplex.index.bytes.B0.byte == 0x00)
					{
						_pTmpDBase = (rom unsigned char *)_db_pdo1_tx_comm;
						_tDBaseLen = sizeof(_db_pdo1_tx_comm)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else 
					if (_tMplex.index.bytes.B0.byte == 0x01)
					{
						_pTmpDBase = (rom unsigned char *)_db_pdo2_tx_comm;
						_tDBaseLen = sizeof(_db_pdo2_tx_comm)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else
					{
						// Index not found in database
						uDict.ret = E_OBJ_NOT_FOUND;
						return;
					}
					break;
				
				
				case 0x0A:		// PDO Transmit Map					
					if (_tMplex.index.bytes.B0.byte == 0x00)
					{
						_pTmpDBase = (rom unsigned char *)_db_pdo1_tx_map;
						_tDBaseLen = sizeof(_db_pdo1_tx_map)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else 
					if (_tMplex.index.bytes.B0.byte == 0x01)
					{
						_pTmpDBase = (rom unsigned char *)_db_pdo2_tx_map;
						_tDBaseLen = sizeof(_db_pdo2_tx_map)/sizeof(DICT_OBJECT_TEMPLATE);
					}
					else
					{
						// Index not found in database
						uDict.ret = E_OBJ_NOT_FOUND;
						return;
					}
					break;
	
				default:
					// Index not found in database
					uDict.ret = E_OBJ_NOT_FOUND;
					return;
			}
			break;

		default:
			// Index not found in database
			uDict.ret = E_OBJ_NOT_FOUND;
			return;
	}

	
	// Adjust the status
	uDict.ret = E_OBJ_NOT_FOUND;
	
	// Copy the index and sub-index to local memory
	*(_DATA4 *)(&(_uDictTemp[0])) = *(rom _DATA4 *)_pTmpDBase;

	// Scan the database and load the pointer
	while(_tDBaseLen)
	{					
		// Match the index 
		if ((_uDictTemp[1] == _tMplex.index.bytes.B1.byte) &&
			(_uDictTemp[0] == _tMplex.index.bytes.B0.byte))
		{
			// Adjust the status
			uDict.ret = E_SUBINDEX_NOT_FOUND;
													
			// If the sub index matches then return success code
			if ((_uDictTemp[2] == _tMplex.sindex.byte) ||
			 	(_uDictTemp[3] & FSUB_BIT))
			{
				// Copy control information
		    	*((DICT_OBJECT_TEMPLATE *)(&(uDict.obj->index))) = *((rom DICT_OBJECT_TEMPLATE *)(_pTmpDBase));
		    				    	
		    	// If functionally defined sub-index, copy sub-index from request
		    	if (_uDictTemp[3] & FSUB_BIT) uDict.obj->subindex = _tMplex.sindex.byte;
						
				// If function specific then call the app function for 
				// read/write, mapping, and length info
				if (_uDictTemp[3] & FDEF_BIT) //if (uDict.obj->ctl & FDEF_BIT)
				{
					uDict.ret = E_SUCCESS;
					uDict.cmd = DICT_OBJ_INFO;
					uDict.obj->p.pFunc();	
					return;
				}
				else
				{
					uDict.ret = E_SUCCESS;
					return;
				}
			}
		}

		// Adjust the pointer
		_pTmpDBase += sizeof(DICT_OBJECT_TEMPLATE);
		
		_tDBaseLen--;
		
		// Copy the index and sub-index to local memory
		*(_DATA4 *)(&(_uDictTemp[0])) = *(rom _DATA4 *)_pTmpDBase;
	}
	return;
}





