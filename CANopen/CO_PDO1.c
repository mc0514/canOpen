

// The communications conducted in this object incorporates 
// one transmit and one receive endpoint


									// Global definitions
#include	"CO_TYPES.H"			// Data types
#include	"CO_DICT.H"				
#include	"CO_COMM.H"				// Communications
#include	"CO_PDO.H"				// PDO functions



rom unsigned long uRPDOMap1 = 0x02292312L;
rom unsigned long uRPDOMap2 = 0x38947928L;
rom unsigned long uRPDOMap3 = 0x02292312L;
rom unsigned long uRPDOMap4 = 0x38947928L;


// Process access events to the COB ID
void _CO_COMM_RPDO1_COBIDAccessEvent(void)
{
	switch (mCO_DictGetCmd())
	{
		case DICT_OBJ_INFO:		// Get information about the object
			// The application should use this to load the 
			// structure with legth, access, and mapping.
			break;

		case DICT_OBJ_READ: 	// Read the object
			// The application should use this to load the buffer 
			// with the requested data.
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			// The application should use this to write the object  
			// with the specified data.
			break;
	}	
}


// Process access events to the transmission type
void _CO_COMM_RPDO1_TypeAccessEvent(void)
{
	switch (mCO_DictGetCmd())
	{
		case DICT_OBJ_INFO:		// Get information about the object
			// The application should use this to load the 
			// structure with legth, access, and mapping.
			break;

		case DICT_OBJ_READ: 	// Read the object
			// The application should use this to load the buffer 
			// with the requested data.
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			// The application should use this to write the object  
			// with the specified data.
			break;
	}	
}






// Process access events to the COB ID
void _CO_COMM_TPDO1_COBIDAccessEvent(void)
{
	switch (mCO_DictGetCmd())
	{
		case DICT_OBJ_INFO:		// Get information about the object
			// The application should use this to load the 
			// structure with legth, access, and mapping.
			break;

		case DICT_OBJ_READ: 	// Read the object
			// The application should use this to load the buffer 
			// with the requested data.
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			// The application should use this to write the object  
			// with the specified data.
			break;
	}	
}


// Process access events to the transmission type
void _CO_COMM_TPDO1_TypeAccessEvent(void)
{
	switch (mCO_DictGetCmd())
	{
		case DICT_OBJ_INFO:		// Get information about the object
			// The application should use this to load the 
			// structure with legth, access, and mapping.
			break;

		case DICT_OBJ_READ: 	// Read the object
			// The application should use this to load the buffer 
			// with the requested data.
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			// The application should use this to write the object  
			// with the specified data.
			break;
	}	
}


// Process access events to the inhibit time
void _CO_COMM_TPDO1_ITimeAccessEvent(void)
{
	switch (mCO_DictGetCmd())
	{
		case DICT_OBJ_INFO:		// Get information about the object
			// The application should use this to load the 
			// structure with legth, access, and mapping.
			break;

		case DICT_OBJ_READ: 	// Read the object
			// The application should use this to load the buffer 
			// with the requested data.
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			// The application should use this to write the object  
			// with the specified data.
			break;
	}	
}


// Process access events to the event timer
void _CO_COMM_TPDO1_ETimeAccessEvent(void)
{
	switch (mCO_DictGetCmd())
	{
		case DICT_OBJ_INFO:		// Get information about the object
			// The application should use this to load the 
			// structure with legth, access, and mapping.
			break;

		case DICT_OBJ_READ: 	// Read the object
			// The application should use this to load the buffer 
			// with the requested data.
			break;

		case DICT_OBJ_WRITE: 	// Write the object
			// The application should use this to write the object  
			// with the specified data.
			break;
	}	
}







