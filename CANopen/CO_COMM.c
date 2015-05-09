/*****************************************************************************
 *
 * Microchip CANopen Stack (Communications Management)
 *
 *****************************************************************************
 * FileName:        CO_COMM.C
 * Dependencies:    
 * Processor:       PIC18F with CAN
 * Compiler:       	C18 02.30.00 or higher
 * Linker:          MPLINK 03.70.00 or higher
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the "Company") is intended and supplied to you, the Company's
 * customer, for use solely and exclusively with products manufactured
 * by the Company. 
 *
 * The software is owned by the Company and/or its supplier, and is 
 * protected under applicable copyright laws. All rights are reserved. 
 * Any use in violation of the foregoing restrictions may subject the 
 * user to criminal sanctions under applicable laws, as well as to 
 * civil liability for the breach of the terms and conditions of this 
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES, 
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT, 
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR 
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * This is the primary communications management. Within this file all events
 * are received and dispached to the appropriate handling functions.
 * 
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ross Fosler			11/13/03	...	
 * 
 *****************************************************************************/

#include	"CO_DEFS.DEF"			// Global definitions
#include	"CO_TYPES.H"			// Data types
#include	"CO_CANDRV.H"			// Driver services
#include	"CO_COMM.H"				// Object

#include	"CO_NMT.H"				// Networm Management
#include	"CO_SYNC.H"				// SYNC Object support
#include	"CO_SDO1.H"				// SDO1, the default SDO
#include	"CO_NMTE.H"				// Error protocols: heartbeat, node-guard
//#include	"CO_EMCY.H"				// EMCY Object support
//#include	"CO_TIME.H"				// Time Stamp Object Support
#include	"CO_PDO.H"				// PDOs



void CO_PDO1LSTimerEvent(void);
void CO_PDO1TXFinEvent(void);
#if CO_NUM_OF_PDO > 1
void CO_PDO2LSTimerEvent(void);
void CO_PDO2TXFinEvent(void);
#endif
#if CO_NUM_OF_PDO > 2
void CO_PDO3LSTimerEvent(void);
void CO_PDO3TXFinEvent(void);
#endif
#if CO_NUM_OF_PDO > 3
void CO_PDO4LSTimerEvent(void);
void CO_PDO4TXFinEvent(void);
#endif


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
	_CO_COMM_SYNC_Open();		// Start SYNC support
	_CO_COMM_SDO1_Open();		// Start the default SDO
//	_CO_COMM_EMCY_Open();		// Reset the Emergency Object
//	_CO_COMM_TIME_Open();		// Reset the Time Stamp Object
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
	if (mCANFetchRetHandle())
	{
		// Test the group of the message 
		switch(mCANFetchRetHandle() & COMM_MSGGRP_MASK)
		{
			case COMM_MSGGRP_NETCTL:		// Network management
				switch(mCANFetchRetHandle() & COMM_MSG_MASK)
				{
					case COMM_NETCTL_NMT: 
						if (COMM_NETCTL_NMT_EN) _CO_COMM_NMT_RXEvent();
						break;
					case COMM_NETCTL_SYNC: 
						if (COMM_NETCTL_SYNC_EN) {if (!COMM_STATE_STOP) _CO_COMM_SYNC_RXEvent();}
						break;
//					case COMM_NETCTL_TMSTP: 
//						if (COMM_NETCTL_TMSTP_EN) {if (!COMM_STATE_STOP) _CO_COMM_TIME_RXEvent();}
//						break;
					case COMM_NETCTL_NMTE: 
						if (COMM_NETCTL_NMTE_EN) _CO_COMM_NMTE_RXEvent();
						break;
					default:
						// Driver error: driver passed a message that has no endpoint
						/*call func*/
						break;
				}
				break;
				
				
			case COMM_MSGGRP_SDO:		// SDOs
				if (!COMM_STATE_STOP)
				{
					switch(mCANFetchRetHandle() & COMM_MSG_MASK)
					{
						case COMM_SDO_1:	//SDO1
							if (COMM_SDO_1_EN) _CO_COMM_SDO1_RXEvent();
							break;
//						case COMM_SDO_2:	//SDO1
//							if (COMM_SDO_2_EN) _CO_COMM_SDO2_RXEvent();
//							break;
//						case COMM_SDO_3:	//SDO1
//							if (COMM_SDO_3_EN) _CO_COMM_SDO3_RXEvent();
//							break;
//						case COMM_SDO_4:	//SDO1
//							if (COMM_SDO_4_EN) _CO_COMM_SDO4_RXEvent();
//							break;
						default:
							// Driver error: driver passed a message that has no endpoint	
							/*call func*/
							break;
					}
				}
				break;
							
				
			case COMM_MSGGRP_PDO:		// PDOs
				if (!COMM_STATE_STOP)
				if (COMM_STATE_OPER)
				{
					switch(mCANFetchRetHandle() & COMM_MSG_MASK)
					{
						case COMM_PDO_1:	//PDO1
							if (COMM_RPDO_1_EN) {if (!COMM_PDO_1_RF){COMM_PDO_1_RF = 1; _CO_COMM_PDO1_RXEvent();}}
							break;
						#if CO_NUM_OF_PDO > 1
						case COMM_PDO_2:	//PDO2
							if (COMM_RPDO_2_EN) {if (!COMM_PDO_2_RF){COMM_PDO_2_RF = 1; _CO_COMM_PDO2_RXEvent();}}
							break;
						#endif
						#if CO_NUM_OF_PDO > 2
						case COMM_PDO_3:	//PDO3
							if (COMM_RPDO_3_EN) {if (!COMM_PDO_3_RF){COMM_PDO_3_RF = 1; _CO_COMM_PDO3_RXEvent();}}
							break;
						#endif
						#if CO_NUM_OF_PDO > 3
						case COMM_PDO_4:	//PDO4
							if (COMM_RPDO_4_EN) {if (!COMM_PDO_4_RF){COMM_PDO_4_RF = 1; _CO_COMM_PDO4_RXEvent();}}
							break;
						#endif
//						case COMM_PDO_5:	//PDO4
//							if (COMM_PDO_5_EN) {if (!COMM_PDO_5_RF){COMM_PDO_5_RF = 1; _CO_COMM_PDO5_RXEvent();}}
//							break;
//						case COMM_PDO_6:	//PDO4
//							if (COMM_PDO_6_EN) {if (!COMM_PDO_6_RF){COMM_PDO_6_RF = 1; _CO_COMM_PDO6_RXEvent();}}
//							break;
//						case COMM_PDO_7:	//PDO4
//							if (COMM_PDO_7_EN) {if (!COMM_PDO_7_RF){COMM_PDO_7_RF = 1; _CO_COMM_PDO7_RXEvent();}}
//							break;
//						case COMM_PDO_8:	//PDO4
//							if (COMM_PDO_8_EN) {if (!COMM_PDO_8_RF){COMM_PDO_8_RF = 1; _CO_COMM_PDO8_RXEvent();}}
//							break;
						default:
							// Driver error: driver passed a message that has no endpoint
							/*call func*/		
							break;
					}
				}
				break;
			
			default:
				// Driver error: driver passed a message that has no endpoint
				/*call func*/
				break;
		}
		
		// Release the driver's receive buffer
		mCANReadMessage();
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
			if (COMM_NETCTL_NMTE_TF) 
			{
				if (COMM_NETCTL_NMTE_EN) {mCANIsPutReady(COMM_MSGGRP_NETCTL | COMM_NETCTL_NMTE); _CO_COMM_NMTE_TXEvent(); mCANSendMessage();}
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
		
		if (COMM_SDO_TF)
		{
			if (!COMM_STATE_STOP)
			{
				if (COMM_SDO_1_TF) 
				{
					if (COMM_SDO_1_EN) {mCANIsPutReady(COMM_MSGGRP_SDO | COMM_SDO_1); _CO_COMM_SDO1_TXEvent(); mCANSendMessage();} 
					COMM_SDO_1_TF = 0;
				}
				else
//				if (COMM_SDO_2_TF) 
//				{
//					if (COMM_SDO_2_EN) {mCANIsPutReady(COMM_MSGGRP_SDO | COMM_SDO_2); _CO_COMM_SDO2_TXEvent(); mCANSendMessage();} 
//					COMM_SDO_2_TF = 0;
//				}
//				else
//				if (COMM_SDO_3_TF) 
//				{
//					if (COMM_SDO_3_EN) {mCANIsPutReady(COMM_MSGGRP_SDO | COMM_SDO_3); _CO_COMM_SDO3_TXEvent(); mCANSendMessage();} 
//					COMM_SDO_3_TF = 0;
//				}
//				else
//				if (COMM_SDO_4_TF) 
//				{
//					if (COMM_SDO_4_EN) {mCANIsPutReady(COMM_MSGGRP_SDO | COMM_SDO_4); _CO_COMM_SDO4_TXEvent(); mCANSendMessage();} 
//					COMM_SDO_4_TF = 0;
//				}
//				else
			
				//Error, a message was queued in an object that does not exist
				{COMM_SDO_TF = 0;}
			}
		}
		else
		
		if (COMM_PDO_TF)
		{
			if (COMM_STATE_OPER)
			if (!COMM_STATE_STOP)
			{
				if (COMM_PDO_1_TF) 
				{
					if (COMM_TPDO_1_EN) {mCANIsPutReady(COMM_MSGGRP_PDO | COMM_PDO_1); _CO_COMM_PDO1_TXEvent(); mCANSendMessage();}
					COMM_PDO_1_TF = 0;
				}
				else
				#if CO_NUM_OF_PDO > 1
				if (COMM_PDO_2_TF) 
				{
					if (COMM_TPDO_2_EN) {mCANIsPutReady(COMM_MSGGRP_PDO | COMM_PDO_2); _CO_COMM_PDO2_TXEvent(); mCANSendMessage();}
					COMM_PDO_2_TF = 0;
				}
				else
				#endif
				#if CO_NUM_OF_PDO > 2
				if (COMM_PDO_3_TF) 
				{
					if (COMM_TPDO_3_EN) {mCANIsPutReady(COMM_MSGGRP_PDO | COMM_PDO_3); _CO_COMM_PDO3_TXEvent(); mCANSendMessage();}
					COMM_PDO_3_TF = 0;
				}
				else
				#endif
				#if CO_NUM_OF_PDO > 3
				if (COMM_PDO_4_TF) 
				{
					if (COMM_TPDO_4_EN) {mCANIsPutReady(COMM_MSGGRP_PDO | COMM_PDO_4); _CO_COMM_PDO4_TXEvent(); mCANSendMessage();}
					COMM_PDO_4_TF = 0;
				}
				else
				#endif
//				if (COMM_PDO_5_TF) 
//				{
//					if (COMM_PDO_5_EN) {mCANIsPutReady(COMM_MSGGRP_PDO | COMM_PDO_5); _CO_COMM_PDO5_TXEvent(); mCANSendMessage();}
//					COMM_PDO_5_TF = 0;
//				}
//				else
//				if (COMM_PDO_6_TF) 
//				{
//					if (COMM_PDO_6_EN) {mCANIsPutReady(COMM_MSGGRP_PDO | COMM_PDO_6); _CO_COMM_PDO6_TXEvent(); mCANSendMessage();}
//					COMM_PDO_6_TF = 0;
//				}
//				else
//				if (COMM_PDO_7_TF) 
//				{
//					if (COMM_PDO_7_EN) {mCANIsPutReady(COMM_MSGGRP_PDO | COMM_PDO_7); _CO_COMM_PDO7_TXEvent(); mCANSendMessage();}
//					COMM_PDO_7_TF = 0;
//				}
//				else
//				if (COMM_PDO_8_TF) 
//				{
//					if (COMM_PDO_8_EN) {mCANIsPutReady(COMM_MSGGRP_PDO | COMM_PDO_8); _CO_COMM_PDO8_TXEvent(); mCANSendMessage();}
//					COMM_PDO_8_TF = 0;
//				}
//				else
				//Error, a message was queued in an object that does not exist
				{COMM_PDO_TF = 0;}
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
							if (COMM_TPDO_1_EN){CO_PDO1TXFinEvent();}
							break;
						#if CO_NUM_OF_PDO > 1
						case COMM_PDO_2:	//RPDO1
							if (COMM_TPDO_2_EN){CO_PDO2TXFinEvent();}
							break;
						#endif
						#if CO_NUM_OF_PDO > 2
						case COMM_PDO_3:	//TPDO2
							if (COMM_TPDO_3_EN){CO_PDO3TXFinEvent();}
							break;
						#endif
						#if CO_NUM_OF_PDO > 3
						case COMM_PDO_4:	//RPDO2
							if (COMM_TPDO_4_EN){CO_PDO4TXFinEvent();}
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
	// If in at least a pre-operational state
	if (COMM_STATE_PREOP)
	{
		// PDO object time events
		if (COMM_TPDO_EN)
		{	
			if (COMM_TPDO_1_EN){CO_PDO1LSTimerEvent();}
			#if CO_NUM_OF_PDO > 1
			if (COMM_TPDO_2_EN){CO_PDO2LSTimerEvent();}
			#endif
			#if CO_NUM_OF_PDO > 2
			if (COMM_TPDO_3_EN){CO_PDO3LSTimerEvent();}
			#endif
			#if CO_NUM_OF_PDO > 3
			if (COMM_TPDO_4_EN){CO_PDO4LSTimerEvent();}
			#endif
//			if (COMM_PDO_5_EN){}
//			if (COMM_PDO_6_EN){}
//			if (COMM_PDO_7_EN){}
//			if (COMM_PDO_8_EN){}
		}
		
		// Network related object time events
		if (COMM_NETCTL_EN)
		{
//			if (COMM_NETCTL_NMT_EN){/*call func*/;} 	// NMT
//			if (COMM_NETCTL_SYNC_EN){/*call func*/;} 	// SYNC
//			if (COMM_NETCTL_TMSTP_EN){/*call func*/;} 	// Time Stamp
			if (COMM_NETCTL_NMTE_EN){_CO_COMM_NMTE_LSTimerEvent();} 	// NMT boot, heartbeat, node guard
//			if (COMM_NETCTL_EMCY_EN){/*call func*/;} 	// Emergency
		}
		
		// SDO object time events
		if (COMM_SDO_EN)
		{
			if (COMM_SDO_1_EN){_CO_COMM_SDO1_LSTimerEvent();}
//			if (COMM_SDO_2_EN){_CO_COMM_SDO2_LSTimerEvent();}
//			if (COMM_SDO_3_EN){_CO_COMM_SDO3_LSTimerEvent();}
//			if (COMM_SDO_4_EN){_CO_COMM_SDO4_LSTimerEvent();}
		}
	}
}































