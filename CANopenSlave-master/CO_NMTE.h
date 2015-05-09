
/*****************************************************************************
 *
 * Microchip CANopen Stack (Network Management Error Communications Handler)
 *
 *****************************************************************************
 * FileName:        CO_NMTE.C
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
 * 
 * 
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ross Fosler			11/13/03	...	
 * 
 *****************************************************************************/



#ifndef	__CO_NMTE_H
#define	__CO_NMTE_H


#define NMTE_BOOT_SERVICE	_uNMTEState.bits.b0
#define NMTE_TMR_LOCAL_EN	_uNMTEState.bits.b1
#define NMTE_NODE_GUARD_EN	_uNMTEState.bits.b2



/*********************************************************************
 * Function:        void _CO_COMM_NMTE_HeartBeatAccessEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Process access events to the heartbeat.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMTE_HeartBeatAccessEvent(void);


/*********************************************************************
 * Function:        void _CO_COMM_NMTE_GuardTimeAccessEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Process access events to the guard time.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMTE_GuardTimeAccessEvent(void);


/*********************************************************************
 * Function:        void _CO_COMM_NMTE_GuardTimeAccessEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Process access events to the life time factor.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMTE_LifeFactorAccessEvent(void);



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


/*********************************************************************
 * Function:        void _CO_COMM_NMTE_RXEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This is the receive event handler for the NMTE
 *					endpoint. 
 *
 * Note:          	This is only used for nodeguard.
 ********************************************************************/
void _CO_COMM_NMTE_RXEvent(void);


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
extern UNSIGNED16 _uNMTEGuardTime;
extern UNSIGNED8 _uNMTELifeFactor;



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


/*********************************************************************
 * Function:        void mNMTE_SetGuardTime(UNSIGNED16 GuardTime)
 *
 * PreCondition:    none
 *
 * Input:       	UNSIGNED16 GuardTime
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Set the guardtime time. 
 *
 * Note:          	
 ********************************************************************/
#define mNMTE_SetGuardTime(GuardTime)	_uNMTEGuardTime.word = GuardTime;


/*********************************************************************
 * Function:        UNSIGNED16 mNMTE_GetGuardTime(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	UNSIGNED16 GuardTime  
 *
 * Side Effects:    none
 *
 * Overview:        Get the GuardTime time. 
 *
 * Note:          	
 ********************************************************************/
#define mNMTE_GetGuardTime()			_uNMTEGuardTime.word


/*********************************************************************
 * Function:        void mNMTE_SetLifeFactor(UNSIGNED8 LifeFactor)
 *
 * PreCondition:    none
 *
 * Input:       	UNSIGNED16 LifeFactor
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        Set the life factor. 
 *
 * Note:          	
 ********************************************************************/
#define mNMTE_SetLifeFactor(LifeFactor)	_uNMTELifeFactor.byte = LifeFactor;


/*********************************************************************
 * Function:        UNSIGNED8 mNMTE_GetLifeFactor(void)
 *
 * PreCondition:    none
 *
 * Input:       	none
 *                  
 * Output:         	UNSIGNED8 LifeFactor  
 *
 * Side Effects:    none
 *
 * Overview:        Get the Life Factor. 
 *
 * Note:          	
 ********************************************************************/
#define mNMTE_GetLifeFactor()			_uNMTELifeFactor.byte


#endif	//__CO_NMTE_H
