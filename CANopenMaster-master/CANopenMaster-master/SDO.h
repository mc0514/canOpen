#ifndef SDO_H
#define	SDO_H

/**
 * Needs to be set by the application programmer.
 */
#define SDO_MAX_HANDLES     16

/**
 * The maximum time allowed from an SDO is sent until an answer is received.
 */
#define SDO_TIMEOUT         5000

#define SDO_FREE            0
#define SDO_DATA_PUT        1
#define SDO_READY_TO_SEND   2
#define SDO_RECEIVED        3


extern unsigned char _uSDO_NodeID;
extern unsigned char _uSDO_Command;
extern unsigned char _uSDO_Index2;
extern unsigned char _uSDO_Index1;
extern unsigned char _uSDO_Subindex;
extern unsigned char _uSDO_Data1;
extern unsigned char _uSDO_Data2;
extern unsigned char _uSDO_Data3;
extern unsigned char _uSDO_Data4;


extern unsigned char SDOHandles[SDO_MAX_HANDLES];
extern unsigned char currentHandle;


extern signed long SDO_Receive_COBID;
extern unsigned char SDO_Receive_Status;
extern unsigned char SDO_Receive_Index2;
extern unsigned char SDO_Receive_Index1;
extern unsigned char SDO_Receive_SubIndex;
extern unsigned char SDO_Receive_Buffer[4];

extern unsigned char SDO_Received;


#define SDO_FREE_HANDLE(nHandle)    SDOHandles[nHandle] = SDO_FREE;
#define SDO_READY()                 (SDOHandles[currentHandle] == SDO_READY_TO_SEND)

//#define mSDOIsFreeToAccept()    //(RPDO_Received == 0)
#define mSDOIsGetRdy()          (SDO_Received == 1)
#define mSDORead()              SDO_Received = 0; COMM_SDO_MASTER_TF = 0;
#define mSDOGetReceiveCOBID()   SDO_Receive_COBID
#define mSDOGetReceiveStatus()  SDO_Receive_Status

/**
 * Is called by _CO_COMMRXEventManager when an answer to an SDO request is
 * received.
 * The application programmer should never call this function.
 * @param acceptedcobid The COBID of the received message.
 */
void _CO_COMM_SDO_RXEvent(signed long acceptedcobid);

/**
 * Load data for transmit.
 * @param nhandle The number of the SDO handle to use.
 * @param nodeid
 * @param command Set if the SDO should download or upload data to the
 * server node.
 * @param index_part2 The least significant byte of the index.
 * @param index_part1 The most significant byte of the index.
 * @param subindex
 * @param databyte1
 * @param databyte2
 * @param databyte3
 * @param databyte4
 */
void _CO_COMM_SDO_Transmit(
        unsigned char nhandle,
        unsigned char nodeid,
        unsigned char command,
        unsigned char index_part2,
        unsigned char index_part1,
        unsigned char subindex,
        unsigned char databyte1,
        unsigned char databyte2,
        unsigned char databyte3,
        unsigned char databyte4);

/**
 * Is called by the _CO_COMMTXRdyEventManager.
 * The application programmer should never call this function.
 */
void _CO_COMM_SDO_TXEvent(void);

/**
 * Tracks the time from the SDO was sent and will free the SDO handle
 * if an answer is not received within SDO_TIMEOUT.
 */
void _CO_COMM_SDO_LSTimerEvent(void);

#endif	/* SDO_H */

