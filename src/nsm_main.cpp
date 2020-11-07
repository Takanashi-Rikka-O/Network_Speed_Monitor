//	nsm_main.c
//	Version : 0.1.1
//	Date : Fri Nov  6 10:41:30 2020
//	Last revise : Sat Nov  7 20:23:19 2020
//	Symbol-Constraint :
//			_Xx..._ - Function Symbol
//			Xx...|x|X - Variable Symbol
//	Description :
//		Program entrance.
//
//	Functions :
//		void _HELP_MSG_(void);		// inline
//		unsigned short int _ERROR_ANA_(void);		// Invoke
//
//	Header :
//
//	Fix : 
//		1> Adding error code analyzing function.
//		2> new name hsm to nsm.

#include"nsm.h"

// Function define

void _HELP_MSG_(void);
unsigned short int _ERROR_ANA_(short int & errorcode);

using namespace NSM;

int main(int argc,char *argv[])
{
	const char *Devname(NULL);

	//	Env

	// Checking arguments
	if (argc < 2)
	{
		cerr<<"Syntax error!"<<endl;
		_HELP_MSG_();
		return ENORM;
	}
	else if (0 == strncmp(argv[1],"-h\0",3))
	{
		_HELP_MSG_();
		return ENORM;
	}
	else if (0 == strncmp(argv[1],"-i\0",3))
		if (NULL == argv[2])
		{
			cerr<<"Device not given!"<<endl;
			return EPNULL;
		}
		else
			Devname=argv[2];
	else
	{
		cerr<<"Option no defined!"<<endl;
		return EONODEF;
	}

	NSM_ERROR=0;		// Reset error value.
	// Create monitor
	Monitor m1(Devname);
	
	// Check error.
	if (NSUCC != _ERROR_ANA_(NSM_ERROR))
		return NSM_ERROR;
	else;


	NSM_ERROR=0;		// Reset error value.
	m1._Main_Proreduce_();

	if (NSUCC != _ERROR_ANA_(NSM_ERROR))
		return NSM_ERROR;
	else;

	//	Primary

	return 0;
	//	Return
}

inline void _HELP_MSG_(void)
{

	//	Env

	cout<<"Syntax : nsm -i <dev name> # Start monitor"<<endl;
	cout<<"Syntax : nsm -h # Get this message"<<endl;


	//	Primary

	//	Return
}

unsigned short int _ERROR_ANA_(short int & errorcode)
{
	unsigned short int InvokeReturn(NSUCC);	// For invoke return.

	//	Env

	// Output error info
	switch (errorcode)
	{
		case NSUCC:
			break;

		case ENORM:
			cerr<<"Normally error!"<<endl;
			InvokeReturn=errorcode;
			break;

		case EFOPEN:
			cerr<<"Monitor can not open the file /proc/net/dev!"<<endl;
			InvokeReturn=errorcode;
			break;

		case EFMEM:
			cerr<<"Monitor can not to get memory!"<<endl;
			InvokeReturn=errorcode;
			break;
	
		case ENFIND:
			cerr<<"Monitor failed to find out the device from the information!"<<endl;
			InvokeReturn=errorcode;
			break;

		case EFORMAT:
			cerr<<"Monitor failed to transinformes the information!"<<endl;
			InvokeReturn=errorcode;
			break;

		case EOREAD:
			cerr<<"Monitor failed to reading!"<<endl;
			InvokeReturn=errorcode;
			break;

		case EPNULL:
			cerr<<"NULL pointer!"<<endl;
			InvokeReturn=EPNULL;
			break;

		case EONODEF:

		default:
			cerr<<"Option not be defined!"<<endl;
			InvokeReturn=EONODEF;
	}

	//	Primary


	return InvokeReturn;
	//	Return
}
