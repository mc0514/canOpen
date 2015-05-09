#include        "PRAGMAS.h"
#include	"CO_MAIN.H"
#include	"Timer.H"
#include        "CO_COMM.h"
#include        "NMTextension.h"
#include        "IOutils.h"
#include	"Slave.h"


void main(void)
{	

	TimerInit();			// Init my timer

	//mSYNC_SetCOBID(0x1000);		// Set the SYNC COB ID (MCHP format)

	mCO_SetNodeID(0x02);		// Set the Node ID

        // 0x05 => 125kbps
        // 0x00 => 1Mbps
	mCO_SetBaud(0x05);		// Set the baudrate

	mNMTE_SetHeartBeat(100);	// Set the initial heartbeat
	mNMTE_SetGuardTime(0000);	// Set the initial guard time
	mNMTE_SetLifeFactor(0x00);	// Set the initial life time

        IO_Init();
        Slave_Init();
        
	mCO_InitAll();	// Initialize CANopen to run, bootup will be sent

        CO_NMTStateChangeEvent();

        if( !COMM_STATE_PREOP )
            while( 1 );             // Stop if wrong mode.
        

        _CO_COMM_SDO1_Open();

        // Enable TPDO:s and RPDO:s
        //mTPDOOpen(1);
        //mRPDOOpen(1);
     
	while(1)
	{
                
		// Process CANopen events
		mCO_ProcessAllEvents();

                // Process application specific functions

                Slave_ProcessEvents();
		
		// 1ms timer events
		if (TimerIsOverflowEvent())
		{
			// Process timer related events
			mCO_ProcessAllTimeEvents();	
		}

	}
}




