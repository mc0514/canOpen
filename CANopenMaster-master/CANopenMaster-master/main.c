#include        "PRAGMAS.h"
#include	"CO_MAIN.H"
#include	"Timer.H"
#include        "CO_COMM.h"
#include        "NMTextension.h"
#include        "IOutils.h"
#include	"Master.h"
#include        "SDO.h"
#include        "Heartbeat.h"
#include        "NMT.h"
#include        "NMTE.h"
#include        "Globals.h"


int StartDelay = 0;



void main(void)
{	
	TimerInit();
       
	mCO_SetNodeID(0x01);

        mCO_SetBaud(0x05); // 0x00 == 1Mbps, 0x05 == 125kbps

	mNMTE_SetHeartBeat(0); // Disable heartbeats.

        IO_Init();
       
	mCO_InitAll();
        CO_NMTStateChangeEvent();

        // Make a delay so all nodes have time to initialize themselves
        // before the master starts SDO communication.
        while( StartDelay < 3000 )
	{
		mCO_ProcessAllEvents();
                
		// 1ms timer events
		if (TimerIsOverflowEvent())
		{
                        StartDelay += CO_TICK_PERIOD;
			mCO_ProcessAllTimeEvents();
		}
	}
          
        while(!INITIALIZATION_FINISHED())
	{
		mCO_ProcessAllEvents();

                Master_Process_Initialization_Events();

		// 1ms timer events
		if (TimerIsOverflowEvent())
		{
			mCO_ProcessAllTimeEvents();
		}
	}


        while( StartDelay < 10000 )
	{
		mCO_ProcessAllEvents();

		// 1ms timer events
		if (TimerIsOverflowEvent())
		{
                        StartDelay += CO_TICK_PERIOD;
			mCO_ProcessAllTimeEvents();
		}
	}



        mAppGoToPREMANEUVERstate();
        
        NMTE_OpenHeartbeatReceiveEndpoint(USS, 200);
        NMTE_OpenHeartbeatReceiveEndpoint(GPS, 200);
        NMTE_OpenHeartbeatReceiveEndpoint(GYR, 200);
        NMTE_OpenHeartbeatReceiveEndpoint(CON, 200);
        NMTE_OpenHeartbeatReceiveEndpoint(ENG, 200);
        COMM_HEARTBEAT_RECEIVE_MASTER_EN = 1;

        mNMT_GotoOperState();
        mCO_COMM_NMT_PutTxData(0x00, CMD_START);
        mNMTWritten();

	while(1)
	{
		mCO_ProcessAllEvents();

                Master_ProcessEvents();

		// 8ms timer events
		if (TimerIsOverflowEvent())
		{
			mCO_ProcessAllTimeEvents();	
		}
	}
}


