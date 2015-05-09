#include "CO_CANDRV.H"
#include "Emergency.h"
#include "EmergencyEvent.h"

void _CO_COMM_EMERGENCY_RXEvent(signed long ACCEPTED_COBID)
{
    onEmergencyReceive((unsigned char) (ACCEPTED_COBID - 0x0080L), mCANGetDataByte0(), mCANGetDataByte1(),
            mCANGetDataByte2(), mCANGetDataByte3(), mCANGetDataByte4(),
            mCANGetDataByte5(), mCANGetDataByte6(), mCANGetDataByte7()
            );
}

