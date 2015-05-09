#include	"CO_DEFS.DEF"			// Global definitions
#include	"CO_TYPES.H"			// Data types
#include	"CO_CANDRV.H"			// Driver services
#include	"CO_COMM.H"			// Object

#include	"NMT.H"                         // Network Management
#include	"NMTE.H"			// Error protocols: heartbeat, node-guard
#include        "SDO.h"
#include        "Globals.h"
#include        "NMTextension.h"
#include        "IOutils.h"
#include        "Heartbeat.h"
#include        "PDO.h"
#include        "Emergency.h"
#include        "Master.h"

// The node ID for this device, 1 - 127 is valid.
UNSIGNED8 _uCO_nodeID;		

// State flags, 
UNSIGNED8 _uCO_state;

// Baudrate
UNSIGNED8 _uCO_baud;

// Flags used to verify certain connections are enabled
UNSIGNED8 _net_en;
UNSIGNED8 _sdo_en;
UNSIGNED8 _rpdo_en;
UNSIGNED8 _tpdo_en;

// Transmit queue flags, if a flag is set then an object is ready to send a message
UNSIGNED8 _tx_net_que;
UNSIGNED8 _tx_sdo_que;
UNSIGNED8 _tx_pdo_que;

// Receive flag
UNSIGNED8 _rx_net_flg;
UNSIGNED8 _rx_sdo_flg;
UNSIGNED8 _rx_pdo_flg;


// Heartbeat reception enabled
unsigned char _master_heartbeat_receive_en = 0;


unsigned char COMM_SDO_MASTER_TF = 0;


/*********************************************************************
 * Function:        void _CO_COMMResetEventManager(void)
 *
 * PreCondition:    All driver and CANopen initialization must be 
 *					complete before calling this function.
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function resets communications.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMMResetEventManager(void)
{
	// Kill any existing states
	_uCO_state.byte = 0;
	
	// Disable all COMM objects
	_net_en.byte = 0;
	_sdo_en.byte = 0;
	_rpdo_en.byte = 0;
	_tpdo_en.byte = 0;
	_tx_net_que.byte = 0;
	_tx_sdo_que.byte = 0;
	_tx_pdo_que.byte = 0;
	_rx_net_flg.byte = 0;
	_rx_sdo_flg.byte = 0;
	_rx_pdo_flg.byte = 0;
	
	// Issue a reset to the driver then open communications
	mCANReset(_uCO_baud.byte);		// Issue a driver reset
		
	// Call all object reset handlers. All objects go online except PDOs. PDOs go
	// online when the appropriate parameter is enabled.
	_CO_COMM_NMT_Open();		// Start network management
	_CO_COMM_NMTE_Open();		// Start the error protocol, heartbeat or node-guard
		
	// Process driver events for the first time
	_CANEventManager();

	// Request to open communications
	mCANOpenComm();

	// Send boot-up message
	NMTE_BOOT_SERVICE = 1;
	mCANIsPutReady(0);
	_CO_COMM_NMTE_TXEvent();
	mCANSendMessage();
	
	// Finished, so enter into preop state
	COMM_STATE_PREOP = 1;
}




/*********************************************************************
 * Function:        void _CO_COMMRXEventManager(void)
 *
 * PreCondition:    
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function dispatches any receive events.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMMRXEventManager(void)
{
	// Call the driver for any received messages, if there are any then
	// determine which object the message is for
	mCANIsGetReady();

	// If at least in a pre-operational state and
	// if the handle is valid then decode and generate the appropriate event
	if (COMM_STATE_PREOP)
	if (MESSAGE_RECEIVED)
	{
		switch(_CO_COMM_GET_RX_MSG_TYPE(ACCEPTED_COBID))
		{
                    case HEARTBEAT_RX_EVENT:
                        if(COMM_HEARTBEAT_RECEIVE_MASTER_EN)
                            _CO_COMM_NMTE_HEARTBEAT_RXEvent(ACCEPTED_COBID);
                        break;
                    case SDO_RX_EVENT:
                        _CO_COMM_SDO_RXEvent(ACCEPTED_COBID);
                        break;
                    case PDO_RX_EVENT:
                        //if operational mode
                        if (COMM_STATE_OPER)
                        {
                            if (!COMM_STATE_STOP)
                            {
                                if(mRPDOIsFreeToAccept())
                                    _CO_COMM_PDO_RXEvent(ACCEPTED_COBID);
                            }
                        }
                        break;
                    case EMERGENCY_RX_EVENT:
                        _CO_COMM_EMERGENCY_RXEvent(ACCEPTED_COBID);
                        break;
                    default:
                        break;
		}
                
		// Release the driver's receive buffer
		mCANReadMessage();
                MESSAGE_RECEIVED = 0;
	}
}

/*********************************************************************
 * Function:        void _CO_COMMTXRdyEventManager(void)
 *
 * PreCondition:    
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function dispatches any transmit events.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMMTXRdyEventManager(void)
{
	// Call the driver to check buffer availability, an arbitrairy 
	// handle is used to get status
 	mCANIsPutReady(1)
	
	// If at least in a pre-operational state and
	// If the buffer is available then generate the tx event
	if (COMM_STATE_PREOP)
	if (mCANFetchRetStat())
	{
		if (COMM_NETCTL_TF)
		{
                        if (COMM_NETCTL_NMT_MASTER_TF)
                        {
                                //mCANIsPutReady(0);
                                mCANIsPutReady(COMM_MSGGRP_NETCTL | COMM_NETCTL_NMT_PRODUCER);
                                _CO_COMM_NMT_TXEvent();
                                mCANSendMessage();
                                COMM_NETCTL_NMT_MASTER_TF = 0;
                        }
                        else
			if (COMM_NETCTL_NMTE_TF) 
			{
				if (COMM_NETCTL_NMTE_EN)
                                {
                                    mCANIsPutReady(COMM_MSGGRP_NETCTL | COMM_NETCTL_NMTE);
                                    _CO_COMM_NMTE_TXEvent();
                                    mCANSendMessage();
                                }
				COMM_NETCTL_NMTE_TF = 0;
			}
			else
//			if (COMM_NETCTL_EMCY_TF) 
//			{
//				if (COMM_NETCTL_EMCY_EN) 
//				{
//					if (!COMM_STATE_STOP) {mCANIsPutReady(COMM_MSGGRP_NETCTL | COMM_NETCTL_EMCY); _CO_COMM_EMCY_TXEvent(); mCANSendMessage();}
//				} 
//				
//				COMM_NETCTL_EMCY_TF = 0;
//			}
//			else
			//Error, a message was queued in an object that does not exist
			{COMM_NETCTL_TF = 0;}
		}
		else
                if (COMM_SDO_MASTER_TF)
                {
                    if (!COMM_STATE_STOP)
                    {
                        mCANIsPutReady(COMM_MSGGRP_SDO | COMM_SDO_MASTER);
                        _CO_COMM_SDO_TXEvent();
                    }
                }
                else
		if (COMM_PDO_TF)
		{
			if (COMM_STATE_OPER)
			if (!COMM_STATE_STOP)
			{
                                mCANIsPutReady(COMM_MSGGRP_PDO | COMM_PDO);
                                _CO_COMM_PDO_TXEvent();
                                mCANSendMessage();
                                COMM_PDO_TF = 0;
			}	
		}		
	}
}



/*********************************************************************
 * Function:        void _CO_COMMTXFinEventManager(void)
 *
 * PreCondition:    
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function dispatches any transmit finish events.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMMTXFinEventManager(void)
{
	// Call the driver to determine if a message has been place on the bus
	mCANIsPutFin();
	
	// If a message has been placed on the bus, then who's message
	// was it and generate an appropriate event
	if (COMM_STATE_PREOP)
	if (mCANFetchRetHandle())
	{	
		// Test the group of the message 
		switch(mCANFetchRetHandle() & COMM_MSGGRP_MASK)
		{
			case COMM_MSGGRP_NETCTL:		// Network management
				switch(mCANFetchRetHandle() & COMM_MSG_MASK)
				{
//					case COMM_NETCTL_NMTE: 
//						if (COMM_NETCTL_NMTE_EN) _CO_COMM_NMTE_TXFinEvent();
//						break;
//					case COMM_NETCTL_EMCY: 
//						if (COMM_NETCTL_EMCY_EN) {if (!COMM_STATE_STOP) _CO_COMM_EMCY_TXFinEvent();}
//						break;
					default:
						// Driver error: driver sent a message that has no endpoint	
						/*call func*/
						break;
				}
				break;
							
			case COMM_MSGGRP_SDO:		// Addressed messages
				if (!COMM_STATE_STOP)
				{
					switch(mCANFetchRetHandle() & COMM_MSG_MASK)
					{
//						case COMM_SDO_1:	//SDO1
//							if (COMM_SDO_1_EN) _CO_COMM_SDO1_TXFinEvent();
//							break;
//						case COMM_SDO_2:	//SDO1
//							if (COMM_SDO_2_EN) _CO_COMM_SDO2_TXFinEvent();
//							break;
//						case COMM_SDO_3:	//SDO1
//							if (COMM_SDO_3_EN) _CO_COMM_SDO3_TXFinEvent();
//							break;
//						case COMM_SDO_4:	//SDO1
//							if (COMM_SDO_4_EN) _CO_COMM_SDO4_TXFinEvent();
//							break;			
						default:
							// not valid, driver error	
							/*call func*/
							break;
					}
				}
				break;
										
			case COMM_MSGGRP_PDO:		// Direct messages
				if (COMM_STATE_OPER)
				if (!COMM_STATE_STOP)
				{
					switch(mCANFetchRetHandle() & COMM_MSG_MASK)
					{
						case COMM_PDO_1:	//TPDO1
							if (COMM_TPDO_1_EN){
                                                            //CO_PDO1TXFinEvent();
                                                        }
							break;
						#if CO_NUM_OF_PDO > 1
						case COMM_PDO_2:	//RPDO1
							if (COMM_TPDO_2_EN){
                                                            //CO_PDO2TXFinEvent();
                                                        }
							break;
						#endif
						#if CO_NUM_OF_PDO > 2
						case COMM_PDO_3:	//TPDO2
							if (COMM_TPDO_3_EN){
                                                            //CO_PDO3TXFinEvent();
                                                        }
							break;
						#endif
						#if CO_NUM_OF_PDO > 3
						case COMM_PDO_4:	//RPDO2
							if (COMM_TPDO_4_EN){
                                                            //CO_PDO4TXFinEvent();
                                                        }
							break;
						#endif
//						case COMM_PDO_5:	//RPDO2
//							if (COMM_PDO_5_EN){CO_PDO5TXFinEvent();}
//							break;
//						case COMM_PDO_6:	//RPDO2
//							if (COMM_PDO_6_EN){CO_PDO6TXFinEvent();}
//							break;
//						case COMM_PDO_7:	//RPDO2
//							if (COMM_PDO_7_EN){CO_PDO7TXFinEvent();}
//							break;
//						case COMM_PDO_8:	//RPDO2
//							if (COMM_PDO_8_EN){CO_PDO8TXFinEvent();}
//							break;
						default:
							// not valid, driver error
							/*call func*/		
							break;
					}
				}
				break;
			
			default:
				// not valid, driver error
				/*call func*/
				break;
		}
	}
}




/*********************************************************************
 * Function:        void _CO_COMMLSTimeEventManager(void)
 *
 * PreCondition:    
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function dispatches any time events.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMMLSTimeEventManager(void)
{		
	if (COMM_STATE_PREOP)
	{
                /*
		if(mNMT_StateIsOperational()) //if (COMM_TPDO_EN)
		{	
			//if (COMM_TimerPDO_EN){
                            //CO_PDOLSTimerEvent();
                        //}
                        _CO_COMM_MASTER_PDO_LSTimerEvent();
		}
                */

		if (COMM_NETCTL_EN)
		{
//			if (COMM_NETCTL_NMT_EN){/*call func*/;} 	// NMT
//			if (COMM_NETCTL_SYNC_EN){/*call func*/;} 	// SYNC
//			if (COMM_NETCTL_TMSTP_EN){/*call func*/;} 	// Time Stamp
			if (COMM_NETCTL_NMTE_EN){_CO_COMM_NMTE_LSTimerEvent();} 	// NMT boot, heartbeat, node guard
//			if (COMM_NETCTL_EMCY_EN){/*call func*/;} 	// Emergency
                }
                if (COMM_SDO_MASTER_TF)
                    _CO_COMM_SDO_LSTimerEvent();
                if (COMM_HEARTBEAT_RECEIVE_MASTER_EN)
                    _CO_COMM_NMTE_HEARTBEAT_LSTimerEvent();
	}
}





unsigned char _CO_COMM_GET_RX_MSG_TYPE(signed long cobid)
{
    if ( (cobid > 0x0700) && (cobid < 0x0780) ) //L
        return HEARTBEAT_RX_EVENT;
    if ( (cobid > 0x0580) && (cobid < 0x0600) )
        return SDO_RX_EVENT;
    if ( ((cobid > 0x0180) && (cobid < 0x0580)) &&
            (cobid != 0x0200) && (cobid != 0x0300) &&
            (cobid != 0x0400) && (cobid != 0x0500) )
        return PDO_RX_EVENT;
    if ( (cobid > 0x80) && (cobid <= 0xFF))
    {
        if( mCANGetDataLen() == 8 )
            return EMERGENCY_RX_EVENT;
        else
            return RX_EVENT_NOT_ACCEPTED;
    }
    return RX_EVENT_NOT_ACCEPTED;
}

