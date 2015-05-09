#ifndef EMERGENCYEVENT_H
#define	EMERGENCYEVENT_H

/**
 * This function has to be implemented by the application programmer and defines
 * what should happen when emergency messages are received.
 * @param nodeid The node that transmitted the message.
 * @param ErrorCodeMSB Most significant byte of the errorcode.
 * @param ErrorCodeLSB Least significant byte of the errorcode.
 * @param Errorregister The OD entry to which the error is written in the
 * transmitting node.
 * @param ERR_STAT_MSB Vendor specific error field.
 * @param ERR_STAT_LSB Vendor specific error field.
 * @param Reserved1 Vendor specific error field.
 * @param Reserved2 Vendor specific error field.
 * @param Reserved3 Vendor specific error field.
 */
void onEmergencyReceive(unsigned char nodeid, unsigned char ErrorCodeMSB,
        unsigned char ErrorCodeLSB, unsigned char Errorregister,
        unsigned char ERR_STAT_MSB, unsigned char ERR_STAT_LSB,
        unsigned char Reserved1, unsigned char Reserved2,
        unsigned char Reserved3);

#endif	/* EMERGENCYEVENT_H */

