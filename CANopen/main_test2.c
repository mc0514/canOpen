
#include 	"CO_TYPES.H"
#include	"CO_MAIN.H"
#include	"Timer.H"
#include	"DemoObj.h"
#include	"CO_DICT.h"
#include	"CO_ABERR.H"			// Abort types
#include	<P18F8680.H>


unsigned char test3[0x20];
unsigned long msgID;
unsigned char hMsg;

DICT_OBJ	_uObjRef;			// Local dictionary object, loaded during inits

void main(void)
{
	
	
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
		// Set the buffer
		_uObjRef.pReqBuf = test3;

		// Set the offset into the buffer
		_uObjRef.reqOffst = 0;

		// Set the index and sub-index
//		_uObjRef.index = 0x1005L;
		_uObjRef.index = 0x1008L;
		_uObjRef.subindex = 0x00;

		// Find the object in the dictionary
		mCO_DictObjectDecode(_uObjRef);

		// If in the dictionary, then read the object
		if (mCO_DictGetRet() == E_SUCCESS)
		{
			_uObjRef.reqLen = _uObjRef.len;
			mCO_DictObjectRead(_uObjRef);
		}
	}
}




