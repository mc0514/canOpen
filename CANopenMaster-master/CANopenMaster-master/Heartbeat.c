#include "Heartbeat.h"
#include "IOutils.h"
#include "CO_DEFS.DEF"
#include "Globals.h"
#include <limits.h>
#include "CO_CANDRV.H"
#include "HeartbeatEvent.h"


unsigned int _HeartbeatsReceived[HEARTBEAT_MAXID] = {0};
unsigned int _HeartbeatTimeouts[HEARTBEAT_MAXID] = {0};
unsigned int _HeartbeatTickCounter = 0;


void NMTE_OpenHeartbeatReceiveEndpoint(unsigned char nodeid, unsigned int timeout)
{
    _HeartbeatTimeouts[nodeid-1] = timeout;
}

void NMTE_CloseHeartbeatReceiveEndpoint(unsigned char nodeid)
{
    _HeartbeatTimeouts[nodeid-1] = 0;
}

void _CO_COMM_NMTE_HEARTBEAT_RXEvent(signed long acceptedcobid)
{
    if (mCANGetDataLen() == 1)
    {
        _HeartbeatsReceived[(acceptedcobid - 0x0700L)-1] = _HeartbeatTickCounter;
        onHeartbeatReceive(acceptedcobid - 0x0700L, mCANGetDataByte0());
    }
}

void _CO_COMM_NMTE_HEARTBEAT_LSTimerEvent(void)
{
    signed int nodeid;
    
    _HeartbeatTickCounter += CO_TICK_PERIOD; //om int overflow?

    for(nodeid = 1; nodeid <= HEARTBEAT_MAXID; nodeid++)
    {
        // Is the endpoint enabled?
        if (_HeartbeatTimeouts[nodeid-1] > 0)
        {
            // if the HeartbeatTickCounter wrapped around (> UINT_MAX)
            if (_HeartbeatTickCounter < _HeartbeatsReceived[nodeid-1]) // detta måste testas mer
            {
                if( (UINT_MAX - _HeartbeatsReceived[nodeid-1] + _HeartbeatTickCounter) >
                        _HeartbeatTimeouts[nodeid-1])
                    onHeartbeatTimeout((unsigned char) nodeid);
            } else
            {
                if( ( _HeartbeatTickCounter - _HeartbeatsReceived[nodeid-1] ) > _HeartbeatTimeouts[nodeid-1] )
                    onHeartbeatTimeout((unsigned char) nodeid);
            }
        }
    }

}

