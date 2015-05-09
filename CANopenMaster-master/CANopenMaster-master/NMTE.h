#ifndef	__CO_NMTE_H
#define	__CO_NMTE_H


#define NMTE_BOOT_SERVICE	_uNMTEState.bits.b0
#define NMTE_TMR_LOCAL_EN	_uNMTEState.bits.b1


/*********************************************************************
 * Function:        void _CO_COMM_NMTE_Open(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *
 * Output:         	none
 *
 * Side Effects:    none
 *
 * Overview:        Open the NMTE endpoint.
 *
 * Note:
 ********************************************************************/
void _CO_COMM_NMTE_Open(void);


/*********************************************************************
 * Function:        void _CO_COMM_NMTE_Close(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *
 * Output:         	none
 *
 * Side Effects:    none
 *
 * Overview:        Close the NMTE endpoint.
 *
 * Note:
 ********************************************************************/
void _CO_COMM_NMTE_Close(void);

/**
 * Load the NMTE data for transmit.
 */
void _CO_COMM_NMTE_TXEvent(void);


/*********************************************************************
 * Function:        void _CO_COMM_NMTE_LSTimerEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *
 * Output:         	none
 *
 * Side Effects:    none
 *
 * Overview:        This is the timer event handler for the NMTE
 *					endpoint.
 *
 * Note:
 ********************************************************************/
void _CO_COMM_NMTE_LSTimerEvent(void);

extern UNSIGNED8 _uNMTEState;
extern UNSIGNED8 _uNMTELocalState;
extern UNSIGNED16 _uNMTEHeartBeat;


/*********************************************************************
 * Function:        void mNMTE_SetHeartBeat(UNSIGNED16 HeartBeat)
 *
 * PreCondition:    none
 *
 * Input:       	UNSIGNED16 HeartBeat
 *
 * Output:         	none
 *
 * Side Effects:    none
 *
 * Overview:        Set the heartbeat time.
 *
 * Note:
 ********************************************************************/
#define mNMTE_SetHeartBeat(HeartBeat)	_uNMTEHeartBeat.word = HeartBeat;


/*********************************************************************
 * Function:        UNSIGNED16 mNMTE_GetHeartBeat(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *
 * Output:         	UNSIGNED16 HeartBeat
 *
 * Side Effects:    none
 *
 * Overview:        Get the heartbeat time.
 *
 * Note:
 ********************************************************************/
#define mNMTE_GetHeartBeat()			_uNMTEHeartBeat.word

/**
 * Test if heartbeats are enabled.
 */
#define mNMTE_HeartbeatEnabled()                (_uNMTEHeartBeat.word > 0)

#endif	//__CO_NMTE_H

