/*****************************************************************************
 *
 * Microchip CANopen Stack (Process Data Objects)
 *
 *****************************************************************************
 * FileName:        CO_PDO.C
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


#ifndef	__CO_PDO_H
#define	__CO_PDO_H


typedef struct __PDO_BUFFERS
{
	struct __RPDO_BUF
	{
		unsigned char len;
		unsigned char *buf;
	}RPDO;
	
	struct __TPDO_BUF
	{
		unsigned char len;
		unsigned char *buf;
	}TPDO;
}_PDOBUF;


extern UNSIGNED32		uRPDOComm1;		// RPDO communication setting
extern UNSIGNED32		uTPDOComm1;		// TPDO communication setting
extern _PDOBUF 			_uPDO1;
extern unsigned char 	_uPDOHandles1;

#if CO_NUM_OF_PDO > 1
extern UNSIGNED32		uRPDOComm2;		// RPDO communication setting
extern UNSIGNED32		uTPDOComm2;		// TPDO communication setting
extern _PDOBUF 			_uPDO2;
extern unsigned char 	_uPDOHandles2;
#endif

#if CO_NUM_OF_PDO > 2
extern UNSIGNED32		uRPDOComm3;		// RPDO communication setting
extern UNSIGNED32		uTPDOComm3;		// TPDO communication setting
extern _PDOBUF 			_uPDO3;
extern unsigned char 	_uPDOHandles3;
#endif

#if CO_NUM_OF_PDO > 3
extern UNSIGNED32		uRPDOComm4;		// RPDO communication setting
extern UNSIGNED32		uTPDOComm4;		// TPDO communication setting
extern _PDOBUF 			_uPDO4;
extern unsigned char 	_uPDOHandles4;
#endif


/*********************************************************************
 * Function:        void _CO_COMM_PDO1_Open(void)
 *
 * PreCondition:    none
 *
 * Input:       	none		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Open the PDO.
 *
 * Note:            
 ********************************************************************/
void _CO_COMM_PDO1_Open(void);

/*********************************************************************
 * Function:        void _CO_COMM_PDO1_Close(void)
 *
 * PreCondition:    none
 *
 * Input:       	none		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Close the PDO.
 *
 * Note:            
 ********************************************************************/
void _CO_COMM_PDO1_Close(void);

/*********************************************************************
 * Function:        void _CO_COMM_PDO1_RXEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Receive event handling function.
 *
 * Note:            
 ********************************************************************/
void _CO_COMM_PDO1_RXEvent(void);

/*********************************************************************
 * Function:        void _CO_COMM_PDO1_TXEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Transmit event handling function.
 *
 * Note:            
 ********************************************************************/
void _CO_COMM_PDO1_TXEvent(void);

#if CO_NUM_OF_PDO > 1
void _CO_COMM_PDO2_Open(void);
void _CO_COMM_PDO2_Close(void);
void _CO_COMM_PDO2_RXEvent(void);
void _CO_COMM_PDO2_TXEvent(void);
#endif

#if CO_NUM_OF_PDO > 2
void _CO_COMM_PDO3_Open(void);
void _CO_COMM_PDO3_Close(void);
void _CO_COMM_PDO3_RXEvent(void);
void _CO_COMM_PDO3_TXEvent(void);
#endif

#if CO_NUM_OF_PDO > 3
void _CO_COMM_PDO4_Open(void);
void _CO_COMM_PDO4_Close(void);
void _CO_COMM_PDO4_RXEvent(void);
void _CO_COMM_PDO4_TXEvent(void);
#endif



/*********************************************************************
 * Function:        void mRPDOOpen(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Open the RPDO.
 *
 * Note:            
 ********************************************************************/
#define	mRPDOOpen(PDOn)				_CO_COMM_PDO##PDOn##_Open()


/*********************************************************************
 * Function:        BOOL mRPDOIsOpen(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	BOOL, true if open	
 *
 * Side Effects:    none
 *
 * Overview:        Query if the RPDO is open.
 *
 * Note:            
 ********************************************************************/
#define mRPDOIsOpen(PDOn)			COMM_RPDO_##PDOn##_EN


/*********************************************************************
 * Function:        void mRPDOClose(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Close the RPDO.
 *
 * Note:            
 ********************************************************************/
#define mRPDOClose(PDOn)			_CO_COMM_PDO##PDOn##_Close()


/*********************************************************************
 * Function:        BOOL mRPDOIsGetRdy(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	BOOL, true if message is received.	
 *
 * Side Effects:    none
 *
 * Overview:        Query if the RPDO has data ready for processing.
 *
 * Note:            
 ********************************************************************/
#define	mRPDOIsGetRdy(PDOn)			(COMM_PDO_##PDOn##_RF)


/*********************************************************************
 * Function:        void mRPDORead(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Indicate to the stack that the RPDO has been 
 *					processed.
 *
 * Note:            
 ********************************************************************/
#define	mRPDORead(PDOn)				COMM_PDO_##PDOn##_RF = 0


/*********************************************************************
 * Function:        void mRPDOSetCOB(PDOn, rpdoCOB)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4
 * 					rpdoCOB, the CAN ID of the RPDO
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Set the CAN identifier for the RPDO.
 *
 * Note:            
 ********************************************************************/
#define mRPDOSetCOB(PDOn, rpdoCOB)	uRPDOComm##PDOn##.word = rpdoCOB


/*********************************************************************
 * Function:        UNSIGNED32 mRPDOGetCOB(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	UNSIGNED32, CAN id in MCHP format	
 *
 * Side Effects:    none
 *
 * Overview:        Get the can identifier used by the RPDO.
 *
 * Note:            
 ********************************************************************/
#define mRPDOGetCOB(PDOn)			uRPDOComm##PDOn##.word


/*********************************************************************
 * Function:        UNSIGNED8 mRPDOGetLen(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	UNSIGNED8, the length of the RPDO	
 *
 * Side Effects:    none
 *
 * Overview:        Get the length of the RPDO.
 *
 * Note:            
 ********************************************************************/
#define	mRPDOGetLen(PDOn)			(_uPDO##PDOn##.RPDO.len)


/*********************************************************************
 * Function:        BOOL mRPDOGetRTR(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	BOOL, the RTR bit	
 *
 * Side Effects:    none
 *
 * Overview:        Get the status of the RTR for the RPDO.
 *
 * Note:            
 ********************************************************************/
#define	mRPDOGetRTR(PDOn)			(_uPDO##PDOn##.RPDO.len & 0x40)


/*********************************************************************
 * Function:        UNSIGNED8* mRPDOGetRxPtr(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	UNSIGNED8*, pointer to the buffer	
 *
 * Side Effects:    none
 *
 * Overview:        Get the pointer to the RPDO buffer.
 *
 * Note:            
 ********************************************************************/
#define	mRPDOGetRxPtr(PDOn)			(_uPDO##PDOn##.RPDO.buf)


/*********************************************************************
 * Function:        void mRPDOSetRxPtr(PDOn, pRXBUF)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  pRXBUF, pointer to the buffer
 *
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Set the pointer to the RDPO buffer.
 *
 * Note:            
 ********************************************************************/
#define	mRPDOSetRxPtr(PDOn, pRXBUF)	_uPDO##PDOn##.RPDO.buf = pRXBUF



/*********************************************************************
 * Function:        void mTPDOOpen(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Open the TPDO.
 *
 * Note:            
 ********************************************************************/
#define mTPDOOpen(PDOn)				COMM_TPDO_##PDOn##_EN = 1


/*********************************************************************
 * Function:        BOOL mTPDOIsOpen(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	BOOL, true if the TPDO is open	
 *
 * Side Effects:    none
 *
 * Overview:        Query if the TPDO is open.
 *
 * Note:            
 ********************************************************************/
#define mTPDOIsOpen(PDOn)			COMM_TPDO_##PDOn##_EN


/*********************************************************************
 * Function:        void mTPDOClose(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Close the PDO.
 *
 * Note:            
 ********************************************************************/
#define mTPDOClose(PDOn)			COMM_TPDO_##PDOn##_EN = 0


/*********************************************************************
 * Function:        BOOL mTPDOIsPutRdy(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	BOOL, true if the TPDO buffer is available.	
 *
 * Side Effects:    none
 *
 * Overview:        Query if the TPDO is ready to load.
 *
 * Note:            
 ********************************************************************/
#define	mTPDOIsPutRdy(PDOn)			(!COMM_PDO_##PDOn##_TF)


/*********************************************************************
 * Function:        void mTPDOWritten(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Indicate to the stack that the TPDO has been 
 *					loaded and is ready to send.
 *
 * Note:            
 ********************************************************************/
#define	mTPDOWritten(PDOn)			COMM_PDO_##PDOn##_TF = 1


/*********************************************************************
 * Function:        void mTPDOSetCOB(PDOn, tpdoCOB)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4	
 *					tpdoCOB, TPDO CAN ID in MCHP format	
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Set the CAN identifier for the TPDO.
 *
 * Note:            
 ********************************************************************/
#define mTPDOSetCOB(PDOn, tpdoCOB)	uTPDOComm##PDOn##.word = tpdoCOB


/*********************************************************************
 * Function:        UNSIGNEED32 mTPDOGetCOB(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4		
 *                  
 * Output:      	UNSIGNEED32, the CAN ID in MCHP format	
 *
 * Side Effects:    none
 *
 * Overview:        Get the CAN identifier for the TPDO.
 *
 * Note:            
 ********************************************************************/
#define mTPDOGetCOB(PDOn)			uTPDOComm##PDOn##.word


/*********************************************************************
 * Function:        void mTPDOSetLen(PDOn, length)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4
 *					length, the length of the PDO		
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Set length of the TPDO.
 *
 * Note:            
 ********************************************************************/
#define	mTPDOSetLen(PDOn, length)	_uPDO##PDOn##.TPDO.len = length


/*********************************************************************
 * Function:        void mTPDOSetRTR(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4	
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Set the RTR for this PDO.
 *
 * Note:            
 ********************************************************************/
#define	mTPDOSetRTR(PDOn)			_uPDO##PDOn##.TPDO.len |= 0x40


/*********************************************************************
 * Function:        UNSIGNED8* mTPDOGetTxPtr(PDOn)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4	
 *                  
 * Output:      	UNSIGNED8*, pointer to the TPDO buffer	
 *
 * Side Effects:    none
 *
 * Overview:        Get the pointer to the TPDO buffer.
 *
 * Note:            
 ********************************************************************/
#define	mTPDOGetTxPtr(PDOn)			(_uPDO##PDOn##.TPDO.buf)


/*********************************************************************
 * Function:        void mTPDOSetTxPtr(PDOn, PTXBUF)
 *
 * PreCondition:    none
 *
 * Input:       	PDOn, this must be a constant from 1 to 4
 *					PTXBUF, pointer to the TPDO buffer	
 *                  
 * Output:      	none	
 *
 * Side Effects:    none
 *
 * Overview:        Set the pointer to the TPDO buffer.
 *
 * Note:            
 ********************************************************************/
#define	mTPDOSetTxPtr(PDOn, PTXBUF)	_uPDO##PDOn##.TPDO.buf = PTXBUF




#endif	//__CO_PDO_H
