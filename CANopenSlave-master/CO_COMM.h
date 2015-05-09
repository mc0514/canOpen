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



#ifndef	__CO_COMM_H
#define	__CO_COMM_H


#define	COMM_MSGGRP_MASK	0xC0
#define COMM_MSG_MASK		0x3F

#define	COMM_MSGGRP_NETCTL	0x00		// Network control group (NMT, SYNC, ...)
#define	COMM_MSGGRP_SDO		0x40		// Addressed Messages group (SDO)
#define	COMM_MSGGRP_PDO		0x80		// Direct Messages group (PDO)

											// 0 is never used
#define	COMM_NETCTL_NMT		1			// NMT Consumer Only
#define	COMM_NETCTL_SYNC	2			// SYNC Consumer Only
#define	COMM_NETCTL_TMSTP	3			// Time Stamp Consumer Only
#define	COMM_NETCTL_NMTE	4			// NMT Boot Heartbeat and Node Guard
#define	COMM_NETCTL_EMCY	5			// Emergency Producer 

#define COMM_SDO_1			0			// Server SDO1
#define COMM_SDO_2			1			// Server SDO2
#define COMM_SDO_3			2
#define COMM_SDO_4			3
#define COMM_SDO_5			4		

#define	COMM_PDO_1			0			// PDO Consumer/Producer (both push and pull model)
#define	COMM_PDO_2			1
#define	COMM_PDO_3			2
#define	COMM_PDO_4			3
#define	COMM_PDO_5			4
#define	COMM_PDO_6			5
#define	COMM_PDO_7			6
#define	COMM_PDO_8			7

#define COMM_NETCTL_EN			_net_en.byte
#define	COMM_NETCTL_NMT_EN		_net_en.bits.b0			// NMT Consumer Only
#define	COMM_NETCTL_SYNC_EN		_net_en.bits.b1			// SYNC Consumer Only
#define	COMM_NETCTL_TMSTP_EN            _net_en.bits.b2			// Time Stamp Consumer Only
#define	COMM_NETCTL_NMTE_EN		_net_en.bits.b3			// NMT Boot Heartbeat and Node Guard
#define	COMM_NETCTL_EMCY_EN		_net_en.bits.b4			// Emergency Producer 

#define COMM_NETCTL_RF			_rx_net_flg.byte
#define	COMM_NETCTL_NMT_RF		_rx_net_flg.bits.b0		// NMT Consumer Only
#define	COMM_NETCTL_SYNC_RF		_rx_net_flg.bits.b1		// SYNC Consumer Only
#define	COMM_NETCTL_TMSTP_RF            _rx_net_flg.bits.b2		// Time Stamp Consumer Only
#define	COMM_NETCTL_NMTE_RF             _rx_net_flg.bits.b3		// NMT Boot Heartbeat and Node Guard

#define COMM_NETCTL_TF			_tx_net_que.byte
#define	COMM_NETCTL_NMTE_TF             _tx_net_que.bits.b3		// NMT Boot Heartbeat and Node Guard
#define	COMM_NETCTL_EMCY_TF		_tx_net_que.bits.b4		// Emergency Producer




#define COMM_SDO_EN			_sdo_en.byte
#define COMM_SDO_1_EN			_sdo_en.bits.b0			// Server SDO1
#define COMM_SDO_2_EN			_sdo_en.bits.b1			// Server SDO2
#define COMM_SDO_3_EN			_sdo_en.bits.b2
#define COMM_SDO_4_EN			_sdo_en.bits.b3
#define COMM_SDO_5_EN			_sdo_en.bits.b4			// Client SDO1

#define COMM_SDO_RF			_rx_sdo_flg.byte
#define COMM_SDO_1_RF			_rx_sdo_flg.bits.b0		// Server SDO1
#define COMM_SDO_2_RF			_rx_sdo_flg.bits.b1		// Server SDO2
#define COMM_SDO_3_RF			_rx_sdo_flg.bits.b2
#define COMM_SDO_4_RF			_rx_sdo_flg.bits.b3

#define COMM_SDO_TF			_tx_sdo_que.byte
#define COMM_SDO_1_TF			_tx_sdo_que.bits.b0		// Server SDO1
#define COMM_SDO_2_TF			_tx_sdo_que.bits.b1		// Server SDO2
#define COMM_SDO_3_TF			_tx_sdo_que.bits.b2
#define COMM_SDO_4_TF			_tx_sdo_que.bits.b3



#define	COMM_TPDO_EN			_tpdo_en.byte
#define	COMM_TPDO_1_EN			_tpdo_en.bits.b0			// PDO Consumer/Producer (both push and pull model)
#define	COMM_TPDO_2_EN			_tpdo_en.bits.b1
#define	COMM_TPDO_3_EN			_tpdo_en.bits.b2
#define	COMM_TPDO_4_EN			_tpdo_en.bits.b3
#define	COMM_TPDO_5_EN			_tpdo_en.bits.b4
#define	COMM_TPDO_6_EN			_tpdo_en.bits.b5
#define	COMM_TPDO_7_EN			_tpdo_en.bits.b6
#define	COMM_TPDO_8_EN			_tpdo_en.bits.b7

#define	COMM_RPDO_EN			_rpdo_en.byte
#define	COMM_RPDO_1_EN			_rpdo_en.bits.b0			// PDO Consumer/Producer (both push and pull model)
#define	COMM_RPDO_2_EN			_rpdo_en.bits.b1
#define	COMM_RPDO_3_EN			_rpdo_en.bits.b2
#define	COMM_RPDO_4_EN			_rpdo_en.bits.b3
#define	COMM_RPDO_5_EN			_rpdo_en.bits.b4
#define	COMM_RPDO_6_EN			_rpdo_en.bits.b5
#define	COMM_RPDO_7_EN			_rpdo_en.bits.b6
#define	COMM_RPDO_8_EN			_rpdo_en.bits.b7

#define	COMM_PDO_RF			_rx_pdo_flg.byte
#define	COMM_PDO_1_RF			_rx_pdo_flg.bits.b0		// PDO Consumer/Producer (both push and pull model)
#define	COMM_PDO_2_RF			_rx_pdo_flg.bits.b1
#define	COMM_PDO_3_RF			_rx_pdo_flg.bits.b2
#define	COMM_PDO_4_RF			_rx_pdo_flg.bits.b3
#define	COMM_PDO_5_RF			_rx_pdo_flg.bits.b4
#define	COMM_PDO_6_RF			_rx_pdo_flg.bits.b5
#define	COMM_PDO_7_RF			_rx_pdo_flg.bits.b6
#define	COMM_PDO_8_RF			_rx_pdo_flg.bits.b7

#define	COMM_PDO_TF			_tx_pdo_que.byte
#define	COMM_PDO_1_TF			_tx_pdo_que.bits.b0		// PDO Consumer/Producer (both push and pull model)
#define	COMM_PDO_2_TF			_tx_pdo_que.bits.b1
#define	COMM_PDO_3_TF			_tx_pdo_que.bits.b2
#define	COMM_PDO_4_TF			_tx_pdo_que.bits.b3
#define	COMM_PDO_5_TF			_tx_pdo_que.bits.b4
#define	COMM_PDO_6_TF			_tx_pdo_que.bits.b5
#define	COMM_PDO_7_TF			_tx_pdo_que.bits.b6
#define	COMM_PDO_8_TF			_tx_pdo_que.bits.b7

#define COMM_STATE_PREOP		_uCO_state.bits.b0
#define COMM_STATE_OPER			_uCO_state.bits.b1
#define	COMM_STATE_STOP			_uCO_state.bits.b2

// Driver Handle definition
//	bit 7		- 	Valid handle
//	bit 6		-	Hardware buffer
//	bits 5:4	-	Group
//	bits 3:0	-	Number
//
//	Group	0	-	Network Control: 	
//		no#	0	- 	NMT
//			1	- 	SYNC
//			2	-	Time Stamp
//			3	-	NMT Boot
//			4	-	Emergency
//
//	Group	1	-	Addressed Messages:	
//		no#	0	-	SDO1
//
//	Group	2	-	Direct Messages:	PDO
//		no#	0	-	PDO1
//			1	-	PDO2
//			2	-	PDO3
//			4	-	PDO4


// The node ID for this device, 1 - 127 is valid.
extern UNSIGNED8 _uCO_nodeID;

// State flags, 
extern UNSIGNED8 _uCO_state;

// Baudrate
extern UNSIGNED8 _uCO_baud;

// Flags used to verify certain connections are enabled
extern UNSIGNED8 _net_en;
extern UNSIGNED8 _sdo_en;
extern UNSIGNED8 _rpdo_en;
extern UNSIGNED8 _tpdo_en;

// Transmit queue flages, if a flag is set then an object is ready to send a message
extern UNSIGNED8 _tx_net_que;
extern UNSIGNED8 _tx_sdo_que;
extern UNSIGNED8 _tx_pdo_que;

// Receive flag
extern UNSIGNED8 _rx_net_flg;
extern UNSIGNED8 _rx_sdo_flg;
extern UNSIGNED8 _rx_pdo_flg;



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
void _CO_COMMResetEventManager(void);


/*********************************************************************
 * Function:        void _CO_COMMRXEventManager(void)
 *
 * PreCondition:    The stack must be initialized.
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
void _CO_COMMRXEventManager(void);


/*********************************************************************
 * Function:        void _CO_COMMTXRdyEventManager(void)
 *
 * PreCondition:    The stack must be initialized.
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
void _CO_COMMTXRdyEventManager(void);


/*********************************************************************
 * Function:        void _CO_COMMTXFinEventManager(void)
 *
 * PreCondition:    The stack must be initialized.
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
void _CO_COMMTXFinEventManager(void);


/*********************************************************************
 * Function:        void _CO_COMMLSTimeEventManager(void)
 *
 * PreCondition:    The stack must be initialized.
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
void _CO_COMMLSTimeEventManager(void);



/*********************************************************************
 * Function:        void mCOMM_SetNodeID(UNSIGNED8 NodeID)
 *
 * PreCondition:    This should be called before init of the stack.
 *
 * Input:       	NodeID, the node ID of the device
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Sets the node ID of the device.
 *
 * Note:          	
 ********************************************************************/
#define mCOMM_SetNodeID(NodeID) 	_uCO_nodeID.byte = NodeID


/*********************************************************************
 * Function:        UNSIGNED8 mCOMM_GetNodeID(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	UNSIGNED8, the node ID  
 *
 * Side Effects:    none
 *
 * Overview:        This function returns the node ID curreently used
 * 					by the stack.
 *
 * Note:          	
 ********************************************************************/
#define mCOMM_GetNodeID()			_uCO_nodeID


#endif	//__CO_COMM_H
