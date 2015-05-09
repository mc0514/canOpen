#include <p18F4680.h>
#include "IOutils.h"
#include "Globals.h"


unsigned char buttonWasPressed = 0;

void IO_Init(void)
{
    ADCON1 = 0x0F; // Port as Digital IO
    TRISAbits.TRISA0 = 0; // Led pin as output
    TRISAbits.TRISA1 = 0; // Led pin as output
    TRISAbits.TRISA2 = 0; // Led pin as output
    TRISAbits.TRISA3 = 0; // Led pin as output
    TRISEbits.TRISE2 = 1; // Button as input
    LED         = 0; // LED off
    STOPLED     = 0; // LED off
    PREOPLED    = 0; // LED off
    OPLED       = 0; // LED off
}

unsigned char ButtonPressed(void)
{
    unsigned char buttonPressedState = FALSE;

    // Check to see if the pushbutton is pressed
    if(BTN == PRESSED)
    {
        // If button wasn't previously pressed, then set current button pressed state to true
        if(buttonWasPressed == FALSE)
        {
            buttonPressedState = TRUE;
        }

        // Set flag to say button was previously pressed
        buttonWasPressed = TRUE;
    }
    else
    {
        // Clear flag to say button was previously not pressed
        buttonWasPressed = FALSE;
    }

    // Return button pressed state
    return buttonPressedState;
}

