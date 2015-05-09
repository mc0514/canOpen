#include "SDO.h"
#include "CO_DEFS.DEF"
#include "CO_TYPES.H"
#include "CO_CANDRV.H"
#include "CO_ABERR.H"
#include "CO_TOOLS.h"
#include "CO_COMM.h"
#include "IOutils.h"


unsigned char _uSDO_NodeID;
unsigned char _uSDO_Command;
unsigned char _uSDO_Index2;
unsigned char _uSDO_Index1;
unsigned char _uSDO_Subindex;
unsigned char _uSDO_Data1;
unsigned char _uSDO_Data2;
unsigned char _uSDO_Data3;
unsigned char _uSDO_Data4;


signed int _uSDOTimer = SDO_TIMEOUT;
unsigned char SDOHandles[SDO_MAX_HANDLES] = {SDO_FREE};
unsigned char currentHandle = 0;


signed long SDO_Receive_COBID = 0;
unsigned char SDO_Receive_Status;
unsigned char SDO_Receive_Index2;
unsigned char SDO_Receive_Index1;
unsigned char SDO_Receive_SubIndex;
unsigned char SDO_Receive_Buffer[4] = {0};

unsigned char SDO_Received = 0;


void _CO_COMM_SDO_RXEvent(signed long acceptedcobid)
{
        SDOHandles[currentHandle] = SDO_RECEIVED;
        SDO_Receive_COBID = acceptedcobid;
        SDO_Receive_Status = mCANGetDataByte0();
        SDO_Receive_Index2 = mCANGetDataByte1();
        SDO_Receive_Index1 = mCANGetDataByte2();
        SDO_Receive_SubIndex = mCANGetDataByte3();
        SDO_Receive_Buffer[0] = mCANGetDataByte4();
        SDO_Receive_Buffer[1] = mCANGetDataByte5();
        SDO_Receive_Buffer[2] = mCANGetDataByte6();
        SDO_Receive_Buffer[3] = mCANGetDataByte7();
        SDO_Received = 1;
}

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
        unsigned char databyte4)
{
    if(!SDOHandles[nhandle] && !COMM_SDO_MASTER_TF)
    {
        SDOHandles[nhandle] = SDO_DATA_PUT;
        _uSDO_NodeID = nodeid;
        _uSDO_Command = command;
        _uSDO_Index2 = index_part2;
        _uSDO_Index1 = index_part1;
        _uSDO_Subindex = subindex;
        _uSDO_Data1 = databyte1;
        _uSDO_Data2 = databyte2;
        _uSDO_Data3 = databyte3;
        _uSDO_Data4 = databyte4;
        currentHandle = nhandle;
        COMM_SDO_MASTER_TF = 1;
    }
}

void _CO_COMM_SDO_TXEvent(void)
{
    if(SDOHandles[currentHandle] == SDO_DATA_PUT)
    {
        mTOOLS_CO2MCHP(_uSDO_NodeID + 0xC0000600L);
        *(unsigned long *)(mCANGetPtrTxCOB()) = mTOOLS_GetCOBID();
        mCANPutDataLen(8);
        mCANPutDataByte0(_uSDO_Command);
        mCANPutDataByte1(_uSDO_Index2);
        mCANPutDataByte2(_uSDO_Index1);
        mCANPutDataByte3(_uSDO_Subindex);
        mCANPutDataByte4(_uSDO_Data1);
        mCANPutDataByte5(_uSDO_Data2);
        mCANPutDataByte6(_uSDO_Data3);
        mCANPutDataByte7(_uSDO_Data4);
        SDOHandles[currentHandle] = SDO_READY_TO_SEND;
        mCANSendMessage();
    }
}

void _CO_COMM_SDO_LSTimerEvent(void)
{
	if (SDOHandles[currentHandle] >= 1 && SDOHandles[currentHandle] < 3)
	{
		_uSDOTimer -= CO_TICK_PERIOD;

		if (_uSDOTimer <= 0)
		{
                    SDOHandles[currentHandle] = SDO_FREE;
                    COMM_SDO_MASTER_TF = 0;
                    _uSDOTimer = SDO_TIMEOUT;
		}
	}
}

