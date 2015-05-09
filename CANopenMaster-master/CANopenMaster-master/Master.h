#ifndef MASTER_H
#define	MASTER_H


#define USS     2
#define GPS     3
#define GYR     4
#define CON     5
#define ENG     6


#define USS_RPDO_COBID                      0x0182L
#define USS_RPDO_MSG                        0x01

#define CON_RPDO_COBID                      0x0185L
#define CON_RPDO_MSG                        0x01

#define GYRO_ERROR_TPDO_COBID               0x0281L
#define GYRO_ERROR_TPDO_MSG                 0xFF

#define TO_POSTMANEUVER_TPDO_COBID          0x0181L
#define TO_POSTMANEUVER_TPDO_MSG            0x01


enum ApplicationState
{
    INITIALIZATION,
    PREMANEUVER,
    MANEUVER,
    POSTMANEUVER
};

extern enum ApplicationState APPLICATION_STATE;

#define mAppGoToPREMANEUVERstate() APPLICATION_STATE = PREMANEUVER
#define mAppGoToMANEUVERstate() APPLICATION_STATE = MANEUVER
#define mAppGoToPOSTMANEUVERstate() APPLICATION_STATE = POSTMANEUVER

/**
 * Defines what happens when a heartbeat is received.
 * @param nodeid The nodeid that sent the heartbeat.
 */
void ResolveHeartbeatEvent(signed long nodeid);

/**
 * Inititalizes the application by sending SDO:s to all slave nodes.
 */
void Master_Process_Initialization_Events(void);

/**
 * Is called by the mainloop in every round and defines the logic for
 * the master node.
 */
void Master_ProcessEvents(void);

unsigned char INITIALIZATION_FINISHED(void);

//void _CO_COMM_MASTER_PDO_LSTimerEvent(void);


void Master_Process_ControllerTest_Initialization_Events(void);

#endif	/* MASTER_H */

