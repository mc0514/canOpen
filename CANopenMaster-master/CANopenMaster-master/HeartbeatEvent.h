#ifndef HEARTBEATEVENT_H
#define	HEARTBEATEVENT_H

/**
 * This function needs to be implemented by the application programmer.
 * Defines what happens when a heartbeat is not received from the node withtin
 * its given timeout.
 * @param nodeid 
 */
void onHeartbeatTimeout(unsigned char nodeid);

/**
 * This function needs to be implemented by the application programmer.
 * Defines what happens when a heartbeat is received from the node.
 * @param nodeid
 * @param status
 */
void onHeartbeatReceive(signed long nodeid, unsigned char status);

#endif	/* HEARTBEATEVENT_H */

