#include "PDO.h"
#include "CO_DEFS.DEF"
#include "CO_TYPES.H"
#include "CO_CANDRV.H"
#include "CO_ABERR.H"
#include "CO_TOOLS.h"
#include "CO_COMM.h"
#include "IOutils.h"

signed long RPDO_COBID = 0;
unsigned char RPDO_Receive_Buffer[8] = {0};
unsigned char RPDO_Received = 0;

signed long _uPDO_COBID;
unsigned char _uPDO_DataLen;
unsigned char _uPDO_Byte0;
unsigned char _uPDO_Byte1;
unsigned char _uPDO_Byte2;
unsigned char _uPDO_Byte3;
unsigned char _uPDO_Byte4;
unsigned char _uPDO_Byte5;
unsigned char _uPDO_Byte6;
unsigned char _uPDO_Byte7;


void _CO_COMM_PDO_RXEvent(signed long cobid)
{
    RPDO_COBID = cobid;
    RPDO_Receive_Buffer[0] = mCANGetDataByte0();
    RPDO_Receive_Buffer[1] = mCANGetDataByte1();
    RPDO_Receive_Buffer[2] = mCANGetDataByte2();
    RPDO_Receive_Buffer[3] = mCANGetDataByte3();
    RPDO_Receive_Buffer[4] = mCANGetDataByte4();
    RPDO_Receive_Buffer[5] = mCANGetDataByte5();
    RPDO_Receive_Buffer[6] = mCANGetDataByte6();
    RPDO_Receive_Buffer[7] = mCANGetDataByte7();
    RPDO_Received = 1;
}


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
        )
{
        _uPDO_COBID = cobid;
        _uPDO_DataLen = datalen;
        _uPDO_Byte0 = databyte0;
        _uPDO_Byte1 = databyte1;
        _uPDO_Byte2 = databyte2;
        _uPDO_Byte3 = databyte3;
        _uPDO_Byte4 = databyte4;
        _uPDO_Byte5 = databyte5;
        _uPDO_Byte6 = databyte6;
        _uPDO_Byte7 = databyte7;
}

void _CO_COMM_PDO_TXEvent(void)
{
        mTOOLS_CO2MCHP(_uPDO_COBID);
        *(unsigned long *)(mCANGetPtrTxCOB()) = mTOOLS_GetCOBID();
        mCANPutDataLen(_uPDO_DataLen);
        mCANPutDataByte0(_uPDO_Byte0);
        mCANPutDataByte1(_uPDO_Byte1);
        mCANPutDataByte2(_uPDO_Byte2);
        mCANPutDataByte3(_uPDO_Byte3);
        mCANPutDataByte4(_uPDO_Byte4);
        mCANPutDataByte5(_uPDO_Byte5);
        mCANPutDataByte6(_uPDO_Byte6);
        mCANPutDataByte7(_uPDO_Byte7);
}

