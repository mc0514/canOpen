#ifndef	NMT_H
#define	NMT_H

#include "NMTextension.h"

#define CMD_START                       1
#define CMD_STOP                        2
#define CMD_PREOPERATIONAL              128
#define CMD_RESET                       129
#define CMD_RESET_COMMUNICATIONS        130

extern unsigned char _NMT_TxNodeID;
extern unsigned char _NMT_TxState;

/**
 * @param nodeid The nodeid you want to send the NMT message to or 0
 * to broadcast  to all nodes.
 * @param state The state the node should be put in.
 */
#define mCO_COMM_NMT_PutTxData(nodeid, state)       _NMT_TxNodeID = nodeid; _NMT_TxState = state;

/**
 * Get the nodeid that is loaded for transmit.
 */
#define mNMTGetTxNodeID()                           _NMT_TxNodeID

/**
 * Get the state loaded for transmit.
 */
#define mNMTGetTxState()                            _NMT_TxState


/**
 * Load the transmit data into the buffers.
 */
void _CO_COMM_NMT_TXEvent(void);

/**
 * Tell the stack data has been loaded for transmit.
 */
#define mNMTWritten()                               COMM_NETCTL_NMT_MASTER_TF = 1;


/*********************************************************************
 * Function:        void _CO_COMM_NMT_Open(void)
 *
 * PreCondition:    The ECAN driver must be initialized.
 *
 * Input:       	none
 *
 * Output:         	none
 *
 * Side Effects:    none
 *
 * Overview:        This function opens an in endpoint for network
 *					management.
 *
 * Note:
 ********************************************************************/
void _CO_COMM_NMT_Open(void);

/*********************************************************************
 * Function:        void _CO_COMM_NMT_Close(void)
 *
 * PreCondition:    The ECAN driver must be initialized.
 *
 * Input:       	none
 *
 * Output:         	none
 *
 * Side Effects:    none
 *
 * Overview:        This function closes the in endpoint.
 *
 * Note:
 ********************************************************************/
void _CO_COMM_NMT_Close(void);


/**
 * Start a node that previously has been stopped.
 */
#define mNMT_Start()                            {COMM_STATE_STOP = 0; CO_NMTStateChangeEvent();}

/**
 * Stop a node.
 */
#define mNMT_Stop()				{COMM_STATE_STOP = 1; CO_NMTStateChangeEvent();}

/**
 * Put the master node in preoperational mode.
 */
#define mNMT_GotoPreopState()			{COMM_STATE_PREOP = 1; COMM_STATE_OPER = 0; COMM_STATE_STOP = 0; CO_NMTStateChangeEvent();}

/**
 * Put the master node in operational mode.
 */
#define mNMT_GotoOperState()			{COMM_STATE_PREOP = 1; COMM_STATE_OPER = 1; COMM_STATE_STOP = 0; CO_NMTStateChangeEvent();}

/**
 * Test if the node is stopped.
 */
#define mNMT_StateIsStopped()			COMM_STATE_STOP

/**
 * Test if the node is in operational mode.
 */
#define	mNMT_StateIsOperational()		(COMM_STATE_OPER && (!COMM_STATE_STOP) && COMM_STATE_OPER)

/**
 * Test if the node is in preoperational mode.
 */
#define	mNMT_StateIsPreOperational()            (COMM_STATE_PREOP && (!COMM_STATE_OPER) && (!COMM_STATE_STOP))


#endif

