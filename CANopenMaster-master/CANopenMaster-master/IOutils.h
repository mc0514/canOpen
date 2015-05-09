#ifndef IOUTILS_H
#define	IOUTILS_H

#include <P18F4680.h>

#define BTN             PORTEbits.RE2
#define LED             PORTAbits.RA0
#define STOPLED         PORTAbits.RA1
#define PREOPLED        PORTAbits.RA2
#define OPLED           PORTAbits.RA3


#define PRESSED         1

extern unsigned char buttonWasPressed;

/**
 * Initialize the LEDs and the button.
 */
void IO_Init(void);

/**
 * Test if the button has been pressed.
 * @return TRUE/1 or FALSE/0
 */
unsigned char ButtonPressed(void);

#endif	/* IOUTILS_H */

