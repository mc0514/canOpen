
#include 	"CO_TYPES.H"
#include	"CO_MAIN.H"
#include	"Timer.H"
#include	"DemoObj.h"
#include	"CO_SDO1.h"
#include	<P18F8680.H>


unsigned char test3[0x20];
unsigned long msgID;
unsigned char hMsg;

void main(void)
{
	unsigned int crap1;
	unsigned char crap2;
	unsigned char * crap3;
	
	TRISD = 0;
	
	// Perform any application specific initialization

	// Init my timer
	TimerInit();

	// Set the SYNC COB ID (MCHP format)
	mSYNC_SetCOBID(0x12);
	// Set the Node ID
	mCO_SetNodeID(0x01);
	// Set the baudrate
	mCO_SetBaud(0x00);
	// Set the initial heartbeat
	mNMTE_SetHeartBeat(0x00);
	// Set the initial guard time
	mNMTE_SetGuardTime(0x00);
	// Set the initial life time
	mNMTE_SetLifeFactor(0x00);

	// Initialize CANopen to run
	mCO_InitAll();		
	
	ECANCON = 0x50;
	
	while(1)
	{
		RXB0DLC = 8;
		RXB0D0 = 0x40;
		RXB0D1 = 0x00;
		RXB0D2 = 0x16;
		RXB0D3 = 0x01;
		RXB0D4 = 0;
		RXB0D5 = 0;
		RXB0D6 = 0;
		RXB0D7 = 0;
		_CO_COMM_SDO1_RXEvent();
		_CO_COMM_SDO1_TXEvent();
		
		RXB0DLC = 8;
		RXB0D0 = 0x60;
		RXB0D1 = 0x00;
		RXB0D2 = 0x00;
		RXB0D3 = 0x00;
		RXB0D4 = 0;
		RXB0D5 = 0;
		RXB0D6 = 0;
		RXB0D7 = 0;
		_CO_COMM_SDO1_RXEvent();
		_CO_COMM_SDO1_TXEvent();
		
		RXB0DLC = 8;
		RXB0D0 = 0x70;
		RXB0D1 = 0x00;
		RXB0D2 = 0x00;
		RXB0D3 = 0x00;
		RXB0D4 = 0;
		RXB0D5 = 0;
		RXB0D6 = 0;
		RXB0D7 = 0;
		_CO_COMM_SDO1_RXEvent();
		_CO_COMM_SDO1_TXEvent();
		
		RXB0DLC = 8;
		RXB0D0 = 0x60;
		RXB0D1 = 0x00;
		RXB0D2 = 0x00;
		RXB0D3 = 0x00;
		RXB0D4 = 0;
		RXB0D5 = 0;
		RXB0D6 = 0;
		RXB0D7 = 0;
		_CO_COMM_SDO1_RXEvent();
		_CO_COMM_SDO1_TXEvent();
		
		RXB0DLC = 8;
		RXB0D0 = 0x70;
		RXB0D1 = 0x00;
		RXB0D2 = 0x00;
		RXB0D3 = 0x00;
		RXB0D4 = 0;
		RXB0D5 = 0;
		RXB0D6 = 0;
		RXB0D7 = 0;
		_CO_COMM_SDO1_RXEvent();
		_CO_COMM_SDO1_TXEvent();
	}
}




