#ifndef PDO_H
#define	PDO_H

extern signed long RPDO_COBID;
extern unsigned char RPDO_Receive_Buffer[8];
extern unsigned char RPDO_Received;

extern signed long _uPDO_COBID;
extern unsigned char _uPDO_DataLen;
extern unsigned char _uPDO_Byte0;
extern unsigned char _uPDO_Byte1;
extern unsigned char _uPDO_Byte2;
extern unsigned char _uPDO_Byte3;
extern unsigned char _uPDO_Byte4;
extern unsigned char _uPDO_Byte5;
extern unsigned char _uPDO_Byte6;
extern unsigned char _uPDO_Byte7;


#define mRPDOIsFreeToAccept()   (RPDO_Received == 0)
#define mRPDOIsGetRdy()         (RPDO_Received == 1)
#define mRPDORead()             RPDO_Received = 0

/**
 * Called by _CO_COMMRXEventManager when a PDO is received.
 * Loads the message into the RPDO_Receive_Buffer[8] and RPDO_COBID from
 * which the application programmer would retrieve the data.
 * The application programmer should never call this function.
 * @param acceptedcobid The COBID of the message that was loaded into one of
 * the buffers.
 */
void _CO_COMM_PDO_RXEvent(signed long acceptedcobid);

/**
 * Put data for transmit. The function does not actually send the data.
 * The data will be loaded and sent automatically by the 
 * _CO_COMMTXRdyEventManager.
 * @param cobid The COBID of the PDO.
 * @param datalen The number of bytes you want to send.
 * @param databyte0
 * @param databyte1
 * @param databyte2
 * @param databyte3
 * @param databyte4
 * @param databyte5
 * @param databyte6
 * @param databyte7
 */
void _CO_COMM_PDO_PutTxData(
        signed long cobid,
        unsigned char datalen,
        unsigned char databyte0,
        unsigned char databyte1,
        unsigned char databyte2,
        unsigned char databyte3,
        unsigned char databyte4,
        unsigned char databyte5,
        unsigned char databyte6,
        unsigned char databyte7
        );

/**
 * Called by the _CO_COMMTXRdyEventManager. This function
 * should never be called by the application programmer.
 */
void _CO_COMM_PDO_TXEvent(void);

/**
 * Tell the stack data has been loaded for transmit.
 * If this is not done the data put by _CO_COMM_PDO_PutTxData will never be
 * sent.
 */
#define mPDOWritten() COMM_PDO_TF = 1

#endif	/* PDO_H */

