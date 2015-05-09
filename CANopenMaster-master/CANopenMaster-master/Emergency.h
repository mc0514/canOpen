#ifndef EMERGENCY_H
#define	EMERGENCY_H

/**
 * Called by _CO_COMMRXEventManager automatically if an emergency message is
 * received.
 * The application programmer should never call this function directly but must
 * instead implement the function onEmergencyReceive in the interface
 * EmergencyEvent.
 * @param ACCEPTED_COBID
 */
void _CO_COMM_EMERGENCY_RXEvent(signed long ACCEPTED_COBID);

#endif	/* EMERGENCY_H */

