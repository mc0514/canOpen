#include	"CO_MAIN.H"
#include        "NMT.h"
#include        "SDO.h"
#include        "PDO.h"
#include        "Master.h"
#include        "HeartbeatEvent.h"
#include        "EmergencyEvent.h"
#include        "IOutils.h"
#include        "Globals.h"
#include        "Config.h"


int pressedtimes = 0;

#ifdef FEEDBACK_TEST
int nSDOs = 7;
#endif
#ifdef OPENLOOP_TEST
int nSDOs = 6;
#endif
#ifdef RUN_APP
int nSDOs = 14;
#endif


int SDOs_processed = 0;

unsigned char GyroscopeIsWorking = 1;

enum ApplicationState APPLICATION_STATE = INITIALIZATION;

unsigned int MASTER_TICK_COUNTER = 0;

#ifdef FEEDBACK_TEST
void Master_Process_Initialization_Events(void)
{
        // Initialize the gyroscope
        // Controller heartbeat @ 10Hz
        _CO_COMM_SDO_Transmit(1, GYR, 0x2B, 0x17, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00);

        // Initialize the controller
        // Controller heartbeat @ 10Hz
        _CO_COMM_SDO_Transmit(2, CON, 0x2B, 0x17, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00);

        // Initialize the engine
        // Engine heartbeat @ 10Hz
        _CO_COMM_SDO_Transmit(3, ENG, 0x2B        , 0x17, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00);
        // Engine velocity
        _CO_COMM_SDO_Transmit(4, ENG, 0x22        , 0x12, 0x20, 0x05, 0x00, 0x0F, 0x00, 0x00);
        // Engine set to position mode
        _CO_COMM_SDO_Transmit(5, ENG, 0x22        , 0x12, 0x20, 0x02, 0x02, 0x00, 0x00, 0x00);
        // Engine open RPDO 21
        _CO_COMM_SDO_Transmit(6, ENG, 0x22        , 0x14, 0x14, 0x01, 0x06, 0x02, 0x00, 0x00);
        // Engine open RPDO 22
        _CO_COMM_SDO_Transmit(7, ENG, 0x22        , 0x15, 0x14, 0x01, 0x06, 0x03, 0x00, 0x00);

        if(mSDOIsGetRdy())
        {
                 if(mSDOGetReceiveStatus() == 0x60)
                {
                    mSDORead();
                    SDOs_processed++;
                }
        }
}
#endif

#ifdef OPENLOOP_TEST
void Master_Process_Initialization_Events(void)
{
        // Initialize the controller
        // Controller heartbeat @ 10Hz
        _CO_COMM_SDO_Transmit(2, CON, 0x2B, 0x17, 0x10, 0x00, 0x64, 0x00, 0x00, 0x00);

        // Initialize the engine
        // Engine heartbeat @ 10Hz
        _CO_COMM_SDO_Transmit(3, ENG, 0x2B        , 0x17, 0x10, 0x00, 0x64, 0x00, 0x00, 0x00);
        // Engine velocity
        _CO_COMM_SDO_Transmit(4, ENG, 0x22        , 0x12, 0x20, 0x05, 0x00, 0x0F, 0x00, 0x00);
        // Engine set to position mode
        _CO_COMM_SDO_Transmit(5, ENG, 0x22        , 0x12, 0x20, 0x02, 0x02, 0x00, 0x00, 0x00);
        // Engine open RPDO 21
        _CO_COMM_SDO_Transmit(6, ENG, 0x22        , 0x14, 0x14, 0x01, 0x06, 0x02, 0x00, 0x00);
        // Engine open RPDO 22
        _CO_COMM_SDO_Transmit(7, ENG, 0x22        , 0x15, 0x14, 0x01, 0x06, 0x03, 0x00, 0x00);

        if(mSDOIsGetRdy())
        {
                 if(mSDOGetReceiveStatus() == 0x60)
                {
                    mSDORead();
                    SDOs_processed++;
                }
        }
}
#endif

#ifdef RUN_APP
// Heartbeats:
// E8 03 == 3000 ms
// 0x64 == 100ms
        // Check the heartbeats
        //_CO_COMM_SDO_Transmit(0, 0x02, 0x40, 0x17, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00);
        //_CO_COMM_SDO_Transmit(1, 0x04, 0x40, 0x17, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00);

void Master_Process_Initialization_Events(void)
{
        // Initialize the Ultrasoundsensor
        // Heartbeats @ 10Hz
        _CO_COMM_SDO_Transmit(0, USS, 0x2B, 0x17, 0x10, 0x00, 0x64, 0x00, 0x00, 0x00);
        // Set limit
        //_CO_COMM_SDO_Transmit(1, USS, 0x22, 0x00, 0x12, 0x03, 0xE8, 0x03, 0x00, 0x00);
        _CO_COMM_SDO_Transmit(1, USS, 0x22, 0x00, 0x12, 0x03, 0x00, 0x00, 0x00, 0x00);
        // Set to limit mode
        _CO_COMM_SDO_Transmit(2, USS, 0x22, 0x00, 0x12, 0x05, 0x01, 0x00, 0x00, 0x00);
        // Disable distance mode
        _CO_COMM_SDO_Transmit(3, USS, 0x22, 0x00, 0x12, 0x06, 0x00, 0x00, 0x00, 0x00);

        // Initialize the GPS
        // Set the heartbeat for the GPS @ no heartbeats
        _CO_COMM_SDO_Transmit(4, GPS, 0x2B, 0x17, 0x10, 0x00, 0x64, 0x00, 0x00, 0x00);

        // Initialize the Gyro
        // Set the heartbeat for the Gyro @ 10Hz
        _CO_COMM_SDO_Transmit(5, GYR, 0x2B, 0x17, 0x10, 0x00, 0x64, 0x00, 0x00, 0x00);

        // Initialize the Controller
        // Set the heartbeat for the controller @ 10Hz
        _CO_COMM_SDO_Transmit(6, CON, 0x2B, 0x17, 0x10, 0x00, 0x64, 0x00, 0x00, 0x00);

        // Initialize the engine
        // Engine heartbeat @ 10Hz
        _CO_COMM_SDO_Transmit(7, ENG, 0x2B, 0x17, 0x10, 0x00, 0x64, 0x00, 0x00, 0x00);
        // Engine velocity
        _CO_COMM_SDO_Transmit(8, ENG, 0x22, 0x12, 0x20, 0x05, VELOCITY_BYTE0, VELOCITY_BYTE1, 0x00, 0x00);
        // Engine acc
        _CO_COMM_SDO_Transmit(9, ENG, 0x22, 0x12, 0x20, 0x06, ACC_BYTE0, ACC_BYTE1, 0x00, 0x00);
        // Engine torque
        _CO_COMM_SDO_Transmit(10, ENG, 0x22, 0x12, 0x20, 0x07, TORQUE_BYTE0, TORQUE_BYTE1, 0x00, 0x00);
        // Engine set to position mode
        _CO_COMM_SDO_Transmit(11, ENG, 0x22, 0x12, 0x20, 0x02, 0x02, 0x00, 0x00, 0x00);
        // Engine open RPDO 21
        _CO_COMM_SDO_Transmit(12, ENG, 0x22, 0x14, 0x14, 0x01, 0x06, 0x02, 0x00, 0x00);
        // Engine open RPDO 22
        _CO_COMM_SDO_Transmit(13, ENG, 0x22, 0x15, 0x14, 0x01, 0x06, 0x03, 0x00, 0x00);
        

        if(mSDOIsGetRdy())
        {
                 if(mSDOGetReceiveStatus() == 0x60)
                {
                    mSDORead();
                    SDOs_processed++;
                }
        }
}
#endif

#if defined FEEDBACK_TEST || defined OPENLOOP_TEST
void Master_ProcessEvents(void)
{
        
}
#endif

#ifdef RUN_APP
void Master_ProcessEvents(void)
{
        if(mRPDOIsGetRdy())
        {
            if(APPLICATION_STATE == PREMANEUVER)
            {
                //if PDO from ultrasoundsensor
                if (RPDO_Receive_Buffer[0] == USS_RPDO_MSG && RPDO_COBID == USS_RPDO_COBID)
                {
                    mAppGoToMANEUVERstate();
                }
            }

            if(APPLICATION_STATE == MANEUVER)
            {
                //if PDO from controller
                if (RPDO_Receive_Buffer[0] == CON_RPDO_MSG && RPDO_COBID == CON_RPDO_COBID)
                {
                    if(GyroscopeIsWorking)
                    {
                        // Tell the application to go to state POSTMANEUVER.
                        _CO_COMM_PDO_PutTxData(TO_POSTMANEUVER_TPDO_COBID,1,TO_POSTMANEUVER_TPDO_MSG,0,0,0,0,0,0,0);
                        mPDOWritten();
                        mAppGoToPOSTMANEUVERstate();
                    }
                    else
                    {
                        // Stop the application.
                        mCO_COMM_NMT_PutTxData(0x00, CMD_STOP);
                        mNMTWritten();
                        mNMT_Stop();
                    }
                }
            }

            mRPDORead();
        }
}
#endif

unsigned char INITIALIZATION_FINISHED(void)
{
    return SDOs_processed == nSDOs;
}

void onHeartbeatTimeout(unsigned char nodeid)
{
    if (COMM_HEARTBEAT_RECEIVE_MASTER_EN)
        ResolveHeartbeatEvent(nodeid);
}

void onHeartbeatReceive(signed long nodeid, unsigned char status)
{
    switch(status)
    {
        case OPERATIONAL:
            // Do nothing.
            break;
        case PREOPERATIONAL:
            // If we are not in the initialization state something has gone wrong with
            // the node if it is in PREOPERATIONAL.
            if(APPLICATION_STATE != INITIALIZATION)
                ResolveHeartbeatEvent(nodeid);
            break;
        case STOPPED:
            if(APPLICATION_STATE == INITIALIZATION)
            {
                mCO_COMM_NMT_PutTxData(0x00, CMD_STOP);
                mNMTWritten();
                mNMT_Stop();
            }
            else
                ResolveHeartbeatEvent(nodeid);
            break;
        case BOOTUP:
            // If all units are powered up at the same time, BOOTUP might be
            // missed by the master so we do not validate the network here.
            // Instead the application will not start if not all SDOs are
            // are processed correctly.

            // If we are not in the initialization state something has gone
            // wrong with the node if it reboots.
            if(APPLICATION_STATE != INITIALIZATION)
                ResolveHeartbeatEvent(nodeid);
            break;
    }
}


void ResolveHeartbeatEvent(signed long nodeid)
{
    if(mNMT_StateIsOperational())
    {
        switch(APPLICATION_STATE)
        {
            case(INITIALIZATION):
                // Do nothing.
                break;
            case(PREMANEUVER):
                // Stop the application
                mCO_COMM_NMT_PutTxData(0x00, CMD_STOP);
                mNMTWritten();
                mNMT_Stop();
                break;
            case(MANEUVER):
                switch(nodeid)
                {
                    case(CON):
                    case(ENG):
                        // Stop the application
                        mCO_COMM_NMT_PutTxData(0x00, CMD_STOP);
                        mNMTWritten();
                        mNMT_Stop();
                        break;
                    case(USS):
                    case(GPS):
                        // Do nothing.
                        break;
                    case(GYR):
                        // Store that the GYRO does not work and stop the application after maneuver finished.
                        GyroscopeIsWorking = 0;
                        // Notify the controller that the gyroscope is not working.
                        _CO_COMM_PDO_PutTxData(GYRO_ERROR_TPDO_COBID,1,GYRO_ERROR_TPDO_MSG,0,0,0,0,0,0,0);
                        mPDOWritten();
                        break;
                }
                break;
            case(POSTMANEUVER):
                switch(nodeid)
                {
                    case(GYR):
                    case(CON):
                    case(ENG):
                        // Stop the application.
                        mCO_COMM_NMT_PutTxData(0x00, CMD_STOP);
                        mNMTWritten();
                        mNMT_Stop();
                        break;
                    case(USS):
                    case(GPS):
                        //Do nothing
                        break;
                }
                break;
        }
    }
}

void onEmergencyReceive(unsigned char nodeid, unsigned char ErrorCodeMSB,
        unsigned char ErrorCodeLSB, unsigned char Errorregister,
        unsigned char ERR_STAT_MSB, unsigned char ERR_STAT_LSB,
        unsigned char Reserved1, unsigned char Reserved2,
        unsigned char Reserved3)
{
#ifdef SHUTDOWN_ON_ENGINE_EMCY
    if (nodeid == 0x06)
    {
        mCO_COMM_NMT_PutTxData(0x00, CMD_STOP);
        mNMTWritten();
        mNMT_Stop();

        // if motor error
        if( ( ErrorCodeMSB == 0x01 ) && ( ErrorCodeLSB == 0x10 ) )
            LED = 1;
    }
#endif
}

