#ifndef HEARTBEAT_H
#define	HEARTBEAT_H

/**
 * This define needs to be set by the application programmer.
 * The nbr is used to initialize the arrays that stores the heartbeats
 * and needs to be of the size maximum nodeid.
 */
#define HEARTBEAT_MAXID         6

extern unsigned int _HeartbeatsReceived[HEARTBEAT_MAXID];
extern unsigned int _HeartbeatTimeouts[HEARTBEAT_MAXID];
extern unsigned int _HeartbeatTickCounter;

/**
 * Add a new receive endpoint in the master which will trigger the function
 * onHeartbeatTimeout if a heartbeat is not received within the time timeout
 * and the function onHeartbeatReceive when a heartbeat is received..
 * @param nodeid The nodeif for which you want to open the endpoint.
 * @param timeout How long the master should wait for a heartbeat from a node
 * before assuming it is malfunctioning.
 */
void NMTE_OpenHeartbeatReceiveEndpoint(unsigned char nodeid, unsigned int timeout);

/**
 * Close a heartbeat receive endpoint. Heartbeats will not be processed on
 * reception and timeouts will not be handled.
 * @param nodeid
 */
void NMTE_CloseHeartbeatReceiveEndpoint(unsigned char nodeid);

/**
 * This function is called automatically by the _CO_COMMRXEventManager in CO_COMM.
 * The application programmer should never use this function directly.
 * @param acceptedcobid The COBID of the received heartbeat.
 */
void _CO_COMM_NMTE_HEARTBEAT_RXEvent(signed long acceptedcobid);

/**
 * This function is called automatically by the _CO_COMMLSTimeEventManager
 * if heartbeat reception is enabled.
 * The appliation programmer should never call this function.
 */
void _CO_COMM_NMTE_HEARTBEAT_LSTimerEvent(void);

#endif	/* HEARTBEAT_H */

