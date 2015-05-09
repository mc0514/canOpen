/*****************************************************************************
 *
 * Microchip CANopen Stack (ECAN Driver For CANopen)
 *
 *****************************************************************************
 * FileName:        CO_CANDRV.H
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

#ifndef __CO_CANDRV_H
#define __CO_CANDRV_H

#include <p18F4680.h>


void _CANEventManager(void);
void _CANReset(void);
	
void _CANSetBitRate(void);

void _CANIsPutReady(void);
void _CANIsPutFin(void);

void _CANOpenMessage(void);
void _CANCloseMessage(void);
void _CANIsGetReady(void);


// Static passed data
extern unsigned char _uCAN_Handle;
extern unsigned char _uCAN_Param1;
extern unsigned char _uCAN_Param2;
extern unsigned char _uCAN_Param3;
extern unsigned char _uCAN_Param4;
extern unsigned char _uCAN_ret;

extern unsigned char _uCAN_Bitrate;
extern unsigned char _uCANReq;

extern unsigned char _uCANOldMode;


/*********************************************************************
 * Function:        void _CANEventManager(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function processes any queued requests.
 *
 * Note:          	
 ********************************************************************/
#define mCANEventManager()			_CANEventManager();


/*********************************************************************
 * Function:        void _CANReset(void)
 *
 * PreCondition:    
 *
 * Input:       	unsigned char _uCAN_Bitrate
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        All aspects of the CAN driver are reset. Plus the
 *					bitrate is set.
 *
 * Note:          	This function does not automatically enable the 
 *					device on the network.
 ********************************************************************/
#define mCANReset(CANBitRate) 		_uCAN_Bitrate = CANBitRate; _CANReset();


/*********************************************************************
 * Function:        void mCANOpenComm(void)
 *
 * PreCondition:   	mCANReset(CANBitRate) must be executed at least 
 *					once prior to calling this function. 
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Open CAN communications.
 *
 * Note:          	
 ********************************************************************/
#define mCANOpenComm()				CANCON = 0

/*********************************************************************
 * Function:        void mCANCloseComm(void)
 *
 * PreCondition:   	none 
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Stop CAN communications.
 *
 * Note:          	
 ********************************************************************/
#define mCANCloseComm()				CANCON = 0x80

/*********************************************************************
 * Function:        void mCANIsCommOpen(void)
 *
 * PreCondition:   	none 
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Query the communications state.
 *
 * Note:          	
 ********************************************************************/
#define mCANIsCommOpen()			(!(CANSTAT & 0xE0))


/*********************************************************************
 * Function:        void mCANErrIsBusOff(void)
 *
 * PreCondition:   	none 
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Query the bus state.
 *
 * Note:          	
 ********************************************************************/
#define mCANErrIsBusOff()			COMSTATbits.TXBO


/*********************************************************************
 * Function:        void mCANErrIsOverFlow(void)
 *
 * PreCondition:   	none 
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Query the buffer state.
 *
 * Note:          	
 ********************************************************************/
#define	mCANErrIsOverFlow()			COMSTATbits.RXB1OVFL

#define	mCANErrClearOverFlow()		COMSTATbits.RXB1OVFL = 0;


/*********************************************************************
 * Function:        void mCANSetBitRate(void)
 *
 * PreCondition:    The node must be on the bus.
 *
 * Input:       	unsigned char _uCAN_Bitrate
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        The predefined BRG values are set.
 *
 * Note:          	An invalid bitrate will default to _BITRATE0
 ********************************************************************/
#define mCANSetBitRate(CANBitRate)	_uCAN_Bitrate = CANBitRate; _uCANReq = 2;


/*********************************************************************
 * Function:        void mCANGetBitRate(void)
 *
 * PreCondition:    
 *
 * Input:       	none
 *                  
 * Output:         	(unsigned char)_uCAN_Bitrate   
 *
 * Side Effects:    none
 *
 * Overview:        The current bitrate setting is returned
 *
 * Note:          	An invalid bitrate will default to _BITRATE0
 ********************************************************************/
#define mCANGetBitRate()			_uCAN_Bitrate


/*********************************************************************
 * Function:        void mCANOpenMessage(MsgTyp, COBID, hRet)
 *
 * PreCondition:    none
 *
 * Input:       	(unsigned long) COBID
 *					(unsigned char) MsgTyp
 *					(unsigned char) hRet
 *                  
 * Output:         	(unsigned char) hRet   
 *
 * Side Effects:    none
 *
 * Overview:        This function scans the available mailbox space
 * 					for an open slot. If found the COBID is added to 
 *					the list of received messages. The message type 
 *					must be passed in, and it must not be zero. A 
 *					handle is returned to the calling function if
 *					successful. The calling funcion must maintain
 *					the handle if the endpoint is to be released 
 *					at a later time without a reset.
 *
 * Note:            The COBID is added but not activated until the 
 *					bus is ready. In future CAN modules this queuing 
 *					functionality may be removed depending on 
 *					hardware support.
 ********************************************************************/
#define mCANOpenMessage(MsgTyp, COBID, hRet)	_uCANOldMode = CANCON; _uCAN_Handle = MsgTyp; *((unsigned long *)(&_uCAN_Param1)) = COBID; _CANOpenMessage(); hRet = _uCAN_ret;
					
/*********************************************************************
 * Function:        void mCANCloseMessage(hMsg)
 *
 * PreCondition:    Must be a valid handle
 *
 * Input:       	(unsigned long) _uCAN_Param1
 *                  
 * Output:         	none   
 *
 * Side Effects:    none
 *
 * Overview:        This function scans the mailbox space for the 
 * 					handle. If found the COBID is removed from the
 *					receive list. 
 *
 * Note:            The COBID is only queued to be removed from the 
 *					list. In future CAN modules this queuing 
 *					functionality may be removed depending on 
 *					hardware support.
 ********************************************************************/	
#define mCANCloseMessage(hMsg)				_uCANOldMode = CANCON; _uCAN_Handle = hMsg; _CANCloseMessage();
				


/*********************************************************************
 * Function:        boolean mCANIsGetRTR(void)
 *
 * PreCondition:    mCANIsGetReady() must have been called prior to
 *					calling this function.
 *
 * Input:       	none
 *                  
 * Output:         	none   
 *
 * Side Effects:    none
 *
 * Overview:        This function returns the current RTR condition 
 *					for the current received message. 
 *
 * Note:            
 ********************************************************************/		
#define	mCANIsGetRTR()				RXB0DLCbits.RXRTR


/*********************************************************************
 * Function:        void mCANIsGetReady(void)
 *
 * PreCondition:    
 *
 * Input:       	none
 *                  
 * Output:         	unsigned char _uCAN_ret   
 *
 * Side Effects:    none
 *
 * Overview:        This function scans for a receive event. If found
 *					it places a handle associated to the receive
 *					buffer into an internal register which can be 
 *					accessed by mCANFetchRetStat. Otherwise it returns 
 *					NULL.
 *
 * Note:            Buffer access on successive receive related calls
 *					is assumed. I.E. the handle is not required for 
 *					associated read functions.
 ********************************************************************/
#define	mCANIsGetReady()			_CANIsGetReady()
									
#define	mCANReadMessage()			RXB0CONbits.RXFUL = 0; PIR3bits.RXB1IF = 0;

#define mCANGetPtrRxCOB()			(&RXB0SIDH)
#define	mCANGetPtrRxData()			(&RXB0D0)

#define mCANGetDataLen()			(RXB0DLC & 0xF)
#define mCANGetDataByte0() 			RXB0D0
#define	mCANGetDataByte1()			RXB0D1
#define	mCANGetDataByte2()			RXB0D2
#define	mCANGetDataByte3()			RXB0D3
#define	mCANGetDataByte4()			RXB0D4
#define	mCANGetDataByte5()			RXB0D5
#define	mCANGetDataByte6()			RXB0D6
#define	mCANGetDataByte7()			RXB0D7



/*********************************************************************
 * Function:        void mCANIsPutReady(putHndl)
 *
 * PreCondition:    
 *
 * Input:       	(unsigned char) putHndl
 *                  
 * Output:         	none   
 *
 * Side Effects:    none
 *
 * Overview:        This function scans for an available output 
 *					buffer. If successful the handle passed is the 
 *					same as the handle returned. Else a NULL is 
 *					returned on a failure.
 *
 * Note:          	Buffer access on successive transmit related calls
 *					is assumed. I.E. the handle is not required for 
 *					associated write functions.
 ********************************************************************/
#define	mCANIsPutReady(putHndl)		_uCAN_Handle = putHndl;	_CANIsPutReady();


/*********************************************************************
 * Function:        void mCANIsPutFin(void)
 *
 * PreCondition:    A message must have been placed on the bus
 *					for this function to ever report anything.
 *
 * Input:       	none
 *                  
 * Output:         	unsigned char _uCAN_ret   
 *
 * Side Effects:    none
 *
 * Overview:        This function scans the output buffers for any
 *					int flags indicating data has been sent. The 
 *					handle to the message is returned to the user.
 *
 * Note:          	This function should only be called one time for 
 *					a tx indication. Calling a second time after 
 *					receiving an indication may not return the same
 *					handle.
 *
 *					The mCANFetchRetStat() function can be called to 
 *					get the return status.
 ********************************************************************/
#define	mCANIsPutFin()			_CANIsPutFin()
#define	mCANSendMessage()		RXB0CONbits.FILHIT3 = 1
#define	mCANGetPtrTxCOB()		(&RXB0SIDH)
#define	mCANGetPtrTxData()		(&RXB0D0)

#define	mCANPutDataLen(CANlen)		(RXB0DLC = CANlen)
#define mCANPutDataByte0(CANDat)	(RXB0D0 = CANDat)
#define mCANPutDataByte1(CANDat)	(RXB0D1 = CANDat)
#define mCANPutDataByte2(CANDat)	(RXB0D2 = CANDat)
#define mCANPutDataByte3(CANDat)	(RXB0D3 = CANDat)
#define mCANPutDataByte4(CANDat)	(RXB0D4 = CANDat)
#define mCANPutDataByte5(CANDat)	(RXB0D5 = CANDat)
#define mCANPutDataByte6(CANDat)	(RXB0D6 = CANDat)
#define mCANPutDataByte7(CANDat)	(RXB0D7 = CANDat)


#define mCANFetchRetStat()		_uCAN_ret
#define mCANFetchRetHandle()		_uCAN_ret


#endif

