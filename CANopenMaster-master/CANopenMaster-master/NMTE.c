#include	"CO_DEFS.DEF"			// Global definitions
#include	"CO_TYPES.H"			// Data types
#include	"CO_CANDRV.H"			// Driver services
#include	"CO_COMM.H"			// Object
#include	"CO_DICT.H"			// Dictionary Object Services
#include	"NMTE.H"			// Network Management Error services
#include	"CO_TOOLS.H"			// COB ID tools
#include        "IOutils.h"
#include        "Heartbeat.h"


UNSIGNED32 		_uNMTE_COBID;

short long 		_uNMTETimer;
UNSIGNED8		_uNMTEState;
UNSIGNED8		_uNMTELocalState;

UNSIGNED16		_uNMTEHeartBeat;
UNSIGNED16		_uNMTEGuardTime;
UNSIGNED8		_uNMTELifeFactor;


unsigned char 	_hNMTE;


//void CO_NMTENodeGuardErrEvent(void);


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
void _CO_COMM_NMTE_Open(void)
{
	// Set the COB ID and convert it to MCHP
	_uNMTE_COBID.word = 0x700L + _uCO_nodeID.byte;
	mTOOLS_CO2MCHP(_uNMTE_COBID.word);
	_uNMTE_COBID.word = mTOOLS_GetCOBID();

	_uNMTEState.byte = 0;

	// If the heartbeat is greater than 0 then enable heartbeat
	if (_uNMTEHeartBeat.word)
	{
		NMTE_TMR_LOCAL_EN = 1;
		COMM_NETCTL_NMTE_EN = 1;
		_uNMTETimer = _uNMTEHeartBeat.word;
	}
}



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
void _CO_COMM_NMTE_Close(void)
{
	// Call the driver, request to close the receive endpoint
	mCANCloseMessage(_hNMTE);
	COMM_NETCTL_NMTE_EN = 0;
}



/*********************************************************************
 * Function:        void _CO_COMM_NMTE_TXEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *
 * Output:         	none
 *
 * Side Effects:    none
 *
 * Overview:        This is the transmit event handler for the NMTE
 *					endpoint. Node guarding and heartbeat
 *					transmissions are handled.
 *
 * Note:
 ********************************************************************/
void _CO_COMM_NMTE_TXEvent(void)
{
	{
		// Set the COB
		*(unsigned long *)(mCANGetPtrTxCOB()) = _uNMTE_COBID.word;

		// Set the length
		mCANPutDataLen(1);


		// Send the state or the boot
		if (!NMTE_BOOT_SERVICE)
		{
			// Toggle and strip old state (also known as bootup state)
			_uNMTELocalState.byte = _uNMTELocalState.byte & 0x80;
			_uNMTELocalState.bits.b7 = 0;

			// Set the data
			if (COMM_STATE_STOP) _uNMTELocalState.byte = _uNMTELocalState.byte | 4;
			else
			if (COMM_STATE_OPER) _uNMTELocalState.byte = _uNMTELocalState.byte | 5;
			else
			if (COMM_STATE_PREOP) _uNMTELocalState.byte = _uNMTELocalState.byte | 127;

			// Load the data
			mCANPutDataByte0(_uNMTELocalState.byte);
		}
		else
		{
			NMTE_BOOT_SERVICE = 0;
			mCANPutDataByte0(0);
		}
	}
}


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
void _CO_COMM_NMTE_LSTimerEvent(void)
{
	// Process only if the local timer is enabled
	if (NMTE_TMR_LOCAL_EN)
	{
		// Adjust the time
		_uNMTETimer -= CO_TICK_PERIOD;

		// If the timer is zero then
		//if (_uNMTETimer == 0)
		if (_uNMTETimer <= 0)
		{
			// If the heartbeat protocol is enabled
			//if (!NMTE_NODE_GUARD_EN)
                        if(mNMTE_HeartbeatEnabled() )
			{
				// Reset the timer
				_uNMTETimer = _uNMTETimer + _uNMTEHeartBeat.word;

				// Queue the endpoint to send a heartbeat
				COMM_NETCTL_NMTE_TF = 1;
			}
		}
	}
}

