/*****************************************************************************
 *
 * Microchip CANopen Stack (Network Management and Communications)
 *
 *****************************************************************************
 * FileName:        CO_NMT.C
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
 * This is the network management object.
 * 
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ross Fosler			11/13/03	...	
 * 
 *****************************************************************************/

#ifndef __CO_NMT_H
#define __CO_NMT_H


//#include	"CO_DEFS.DEF"			// Global definitions
#include	"CO_TYPES.H"			// Data types
//#include	"CO_CANDRV.H"			// Driver services
#include	"CO_COMM.H"				// Object

/*********************************************************************
 * Function:        void _CO_COMM_NMT_RXEvent(void)
 *
 * PreCondition:    The ECAN driver must be initialized.
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function processes receive events for this 
 *					endpoint, in particular network management.
 *
 * Note:          	
 ********************************************************************/
void _CO_COMM_NMT_RXEvent(void);


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


/*********************************************************************
 * Function:        void mNMT_Start(void)
 *
 * PreCondition:    The CANopen stack must be initialized prior to
 *					using this function.
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function places the node in an operational
 *					state.
 *
 * Note:          	none
 ********************************************************************/
#define mNMT_Start()					COMM_STATE_STOP = 0


/*********************************************************************
 * Function:        void mNMT_Stop(void)
 *
 * PreCondition:    The CANopen stack must be initialized prior to
 *					using this function.
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function places the node in a stopped
 *					state.
 *
 * Note:          	none
 ********************************************************************/
#define mNMT_Stop()						COMM_STATE_STOP = 1


/*********************************************************************
 * Function:        void mNMT_GotoPreopState(void)
 *
 * PreCondition:    The CANopen stack must be initialized prior to
 *					using this function.
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function places the node in a pre-operational
 *					state.
 *
 * Note:          	none
 ********************************************************************/
#define mNMT_GotoPreopState()			{COMM_STATE_PREOP = 1; COMM_STATE_OPER = 0; COMM_STATE_STOP = 0;}


/*********************************************************************
 * Function:        void mNMT_GotoOperState(void)
 *
 * PreCondition:    The CANopen stack must be initialized prior to
 *					using this function.
 *
 * Input:       	none
 *                  
 * Output:         	none  
 *
 * Side Effects:    none
 *
 * Overview:        This function places the node in an operational
 *					state.
 *
 * Note:          	none
 ********************************************************************/
#define mNMT_GotoOperState()			{COMM_STATE_PREOP = 1; COMM_STATE_OPER = 1; COMM_STATE_STOP = 0;}
//#define mNMT_GotoOperState()			{COMM_STATE_PREOP = 0; COMM_STATE_OPER = 1; COMM_STATE_STOP = 0;}


/*********************************************************************
 * Function:        BOOL mNMT_StateIsStopped(void)
 *
 * PreCondition:    The CANopen stack must be initialized prior to
 *					using this function.
 *
 * Input:       	none
 *                  
 * Output:         	BOOL   
 *
 * Side Effects:    none
 *
 * Overview:        This function returns TRUE if the node is stopped.
 *
 * Note:          	none
 ********************************************************************/
#define mNMT_StateIsStopped()			COMM_STATE_STOP

/*********************************************************************
 * Function:        BOOL mNMT_StateIsOperational(void)
 *
 * PreCondition:    The CANopen stack must be initialized prior to
 *					using this function.
 *
 * Input:       	none
 *                  
 * Output:         	BOOL   
 *
 * Side Effects:    none
 *
 * Overview:        This function returns TRUE if the node is 
 *					operational.
 *
 * Note:          	none
 ********************************************************************/
#define	mNMT_StateIsOperational()		(COMM_STATE_OPER && (!COMM_STATE_STOP))


/*********************************************************************
 * Function:        BOOL mNMT_StateIsPreOperational(void)
 *
 * PreCondition:    The CANopen stack must be initialized prior to
 *					using this function.
 *
 * Input:       	none
 *                  
 * Output:         	BOOL   
 *
 * Side Effects:    none
 *
 * Overview:        This function returns TRUE if the node is 
 *					pre-operational.
 *
 * Note:          	none
 ********************************************************************/
#define	mNMT_StateIsPreOperational()	(COMM_STATE_PREOP && (!COMM_STATE_OPER) && (!COMM_STATE_STOP))

#endif

