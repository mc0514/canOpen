/*****************************************************************************
 *
 * Timer 
 *
 *****************************************************************************
 * FileName:        Timer.c
 * Dependencies:    
 * Processor:       PIC18F with CAN
 * Compiler:       	C18 02.10.02 or higher
 * Linker:          MPLINK 03.20.01 or higher
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
 * This is a simple timer function used within the DeviceNet Stack for
 * demonstration.
 * 
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ross Fosler			04/28/03	...	
 * 
 *****************************************************************************/


//#include	"P18F458.H"			// Hardware specific header
#include <p18F4680.h>



#define	TIMER_PERIOD_MS		8					// Period in milliseconds
#define	TIMER_FOSC		20000000L                               // Frequency of the processor clock
#define	TIMER_PRESCALE		7					// The desired prescale


#if 	TIMER_PRESCALE == 0
	#define	TIMER_PRESCALE_VALUE	2
#elif 	TIMER_PRESCALE == 1
	#define	TIMER_PRESCALE_VALUE	4
#elif	TIMER_PRESCALE == 2
	#define	TIMER_PRESCALE_VALUE	8
#elif	TIMER_PRESCALE == 3
	#define	TIMER_PRESCALE_VALUE	16
#elif	TIMER_PRESCALE == 4
	#define	TIMER_PRESCALE_VALUE	32
#elif 	TIMER_PRESCALE == 5
	#define	TIMER_PRESCALE_VALUE	64
#elif	TIMER_PRESCALE == 6
	#define	TIMER_PRESCALE_VALUE	128
#elif	TIMER_PRESCALE == 7
	#define	TIMER_PRESCALE_VALUE	256
#else
	#define	TIMER_PRESCALE_VALUE	1
	#define	TIMER_PRESCALE	8
#endif


/*********************************************************************
 * Function:        void TimerInit(void)
 *
 * PreCondition:    none
 *
 * Input:       	none	
 *                  
 * Output:      	none
 *
 * Side Effects:    None
 *
 * Overview:        Initializes Timer0 for use.
 *
 * Note:            None
 ********************************************************************/
void TimerInit(void)
{	
	T0CON = 0x40 | TIMER_PRESCALE;

	TMR0L = 255L - ((TIMER_PERIOD_MS * TIMER_FOSC) / 1000L / 4 / TIMER_PRESCALE_VALUE);
	
	T0CONbits.TMR0ON = 1;
	INTCONbits.TMR0IF = 0;
}



/*********************************************************************
 * Function:        unsigned char TimerIsOverflowEvent(void)
 *
 * PreCondition:    none
 *
 * Input:       	none	
 *                  
 * Output:      	unsigned char status
 *
 * Side Effects:    None
 *
 * Overview:        Checks for an overflow event, returns TRUE if 
 *					an overflow occured.
 *
 * Note:            This function should be checked at least twice
 *					per overflow period.
 ********************************************************************/
unsigned char TimerIsOverflowEvent(void)
{
	static unsigned char temp;
	
	if (INTCONbits.TMR0IF)
	{
		temp = 256L - ((TIMER_PERIOD_MS * TIMER_FOSC) / 1000L / 4 / TIMER_PRESCALE_VALUE);
		TMR0L += temp;
		
		INTCONbits.TMR0IF = 0;
		return(1);
	}
	return(0);
}
