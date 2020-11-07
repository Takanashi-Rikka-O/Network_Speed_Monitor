//	nsm.cpp
//	Version : 0.1.1
//	Date : Fri Nov  6 10:41:26 2020
//	Last revise : Sat Nov  7 20:23:26 2020
//	Symbol-Constraint :
//			_Xx..._ - Function Symbol
//			Xx...|x|X - Variable Symbol
//	Description :
//		Class Monitor'defination.
//
//	Functions :
//		Class method defination.
//
//	Header :
//		"nsm.h"
//
//	Fix :
//		1> Fixed seekg failed.
//		2> new name hsm to nsm. 

#include"nsm.h"

namespace NSM{

// Error var.Prevent ambiguity.
short int NSM_ERROR(0);

Monitor::Monitor():TargetFile("/proc/net/dev")
{
	Dev="lo";	// Init. Default use loop network device.
	Reader.open(TargetFile,ios_base::in);	// Open file.
	InputInfo=new char[DEFAULTSIZE];	// Get memory.
	OutputInfo=new char[DEFAULTSIZE];	// Get memory.
	InfoBuff=new char[DEFAULTSIZE];		// Get memory.
	IFlowN1=IFlowN2=OFlowN1=OFlowN2=0;

	//	Env

	// Checking.
	
	if (! Reader.is_open())
		NSM_ERROR=EFOPEN;
	else;

	if (NULL == InfoBuff || NULL == InputInfo || NULL == OutputInfo)
		NSM_ERROR=EFMEM;
	else;

	//	Primary


	//	Return
}

Monitor::Monitor(const char * const & Device):TargetFile("/proc/net/dev")
{
	Dev=Device;
	Reader.open(TargetFile,ios_base::in);
	InputInfo=new char[DEFAULTSIZE];
	OutputInfo=new char[DEFAULTSIZE];
	InfoBuff=new char[DEFAULTSIZE];
	IFlowN1=IFlowN2=OFlowN1=OFlowN2=0;

	//	Env

	// Checking.
	if ( ! Reader.is_open())
		NSM_ERROR=EFOPEN;
	else;

	if (NULL == InfoBuff || NULL == InputInfo || NULL == OutputInfo)
		NSM_ERROR=EFMEM;
	else;

	//	Primary

	//	Return
}


Monitor::~Monitor()
{
	//	Env

	delete[] InfoBuff;	// Recyle.
	delete[] InputInfo;
	delete[] OutputInfo;
	InputInfo=OutputInfo=InfoBuff=NULL;

	(void)Reader.close();	// Close file.

	//	Primary


	//	Return
}


short int Monitor::_ResolvInfo_(void)
{
	// Can use sscanf to format data.

	const char *FindDev(NULL);	// strstr return.

	//	Env

	if (NULL == (FindDev=strstr(InfoBuff,Dev.c_str())))
	{
		NSM_ERROR=ENFIND;
		return 1;
	}
	else;

	//	Primary
	
	if (sscanf(FindDev+Dev.length()+1," %[^' '] %*[^' '] %*[^' '] %*[^' '] %*[^' '] %*[^' '] %*[^' '] %*[^' '] %[^' ']",InputInfo,OutputInfo) < 2)
	{
		NSM_ERROR=EFORMAT;
		return 1;
	}
	else;
	
	
	return 0;
	//	Return
}

void Monitor::_Main_Proreduce_(void)
{

	float Up=0.00,Down=0.00;	// For network speed calculation.

	//	Env

	// set output style.
	cout<<fixed;
	cout.precision(2);	// x.yy

	// First reading.


	Reader.read(InfoBuff,DEFAULTSIZE);
	if (Reader.bad())
	{
		Reader.clear();
		NSM_ERROR=EOREAD;
		goto _Main_Proreduce_Exit;
	}
	else
	{
		Reader.clear();
		Reader.seekg(0L,ios_base::beg);
	}

	

	if (0 == _ResolvInfo_())
	{
		IFlowN1=_STN_Base10_(InputInfo);
		OFlowN1=_STN_Base10_(OutputInfo);
	}
	else
		goto _Main_Proreduce_Exit;

	// Entry work cycle.
	do
	{
		Reader.read(InfoBuff,DEFAULTSIZE);	// Read info.
		if (Reader.bad())
		{
			Reader.clear();	// Clean bad bit.
			NSM_ERROR=EOREAD;
			goto _Main_Proreduce_Exit;
		}
		else
		{
			Reader.clear();
			Reader.seekg(0L,ios_base::beg);	// To head.
		}

		// Analyzing.
		switch (_ResolvInfo_())
		{
			case 0:
				IFlowN2=_STN_Base10_(InputInfo);
				OFlowN2=_STN_Base10_(OutputInfo);

				Down=(IFlowN2-IFlowN1)/1024;
				Up=(OFlowN2-OFlowN1)/1024;

				IFlowN1=IFlowN2;
				OFlowN1=OFlowN2;

				cout<<"Device: "<<Dev<<"\t\tUp: "<<Up<<" KiB/s"<<"\t\tDown: "<<Down<<" KiB/s"<<endl;
				break;
			case 1:
				goto _Main_Proreduce_Exit;

			default:
				NSM_ERROR=EONODEF;
				goto _Main_Proreduce_Exit;
		}

		sleep(2);	// Sleep 1sec,not precision.

	} while (1);	// Unlimit cycle.

	//	Primary

	_Main_Proreduce_Exit:

		return;
	//	Return
}

long long Monitor::_STN_Base10_(const char *Target)
{
	long long Result(0);	// For calculation result.
	unsigned short int Negative;	// + -.
					// 1 -> -
					// 0 -> +
	const char *End(NULL);

	//	Env

	// Checking pointer.
	if (NULL == Target)
	{
		NSM_ERROR=EPNULL;
	}
	else
	{

		// Find end.
		for (End=Target; *End != '\0'; ++End);
		--End;


		// Checking + -.
		Negative=('-' == *Target)?++Target,1:0;

		for (long long Base(1); End != Target-1; --End,Base*=10)
			Result+=(*End - '0')*Base;
	}		

	//	Primary


	return (1 == Negative)?Result*(-1):Result;
	//	Return
}













}	// namespace end.
