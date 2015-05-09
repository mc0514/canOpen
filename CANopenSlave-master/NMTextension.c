#include <p18F4680.h>

#include "CO_NMT.h"
#include "IOutils.h"

void CO_NMTStateChangeEvent(void)
{
    if( mNMT_StateIsStopped() )
    {
        STOPLED     = 1;
        PREOPLED    = 0;
        OPLED       = 0;
    }
    else if( mNMT_StateIsPreOperational() )
    {
        STOPLED     = 0;
        PREOPLED    = 1;
        OPLED       = 0;
    }
    else if( mNMT_StateIsOperational() )
    {
        STOPLED     = 0;
        PREOPLED    = 0;
        OPLED       = 1;
    }
}

void CO_NMTResetEvent(void)
{
	_asm reset _endasm
}

void CO_NMTAppResetRequest(void)
{
}

void CO_NMTENodeGuardErrEvent(void)
{
	LATDbits.LATD0 = ~LATDbits.LATD0;
}
