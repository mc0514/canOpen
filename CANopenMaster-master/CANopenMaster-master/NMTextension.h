#ifndef NMTEXTENSION_H
#define	NMTEXTENSION_H

/**
 * Needs to be implemented by the application programmer. Defines what happens
 * if the application changes state.
 */
void CO_NMTStateChangeEvent(void);

void CO_NMTResetEvent(void);

void CO_NMTAppResetRequest(void);

void CO_NMTENodeGuardErrEvent(void);

#endif

