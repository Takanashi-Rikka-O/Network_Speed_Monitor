//	nsm.h
//	Version : 0.1.1
//	Date : Fri Nov  6 10:41:10 2020
//	Last revise : Sat Nov  7 20:23:19 2020
//	Symbol-Constraint :
//			_Xx..._ - Function Symbol
//			Xx...|x|X - Variable Symbol
//	Description :
//		This is the header of Network_Speed_Monitor,it contains some definations.
//
//	Functions :
//		<none>
//
//	Header :
//		<iostream>	# C++ I/O
//		<fstream>	# C++ File I/O
//		<string>	# C++ string class
//		<unistd>	# Unix stdandard functions
//		<cstring>	# C string func
//
//	Fix : 
//		1> Deleted useless macro defination BTOMB.
//		2> new name hsm to nsm.


#ifndef _NSM_H_
#define _NSM_H_

#include<unistd.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>

#define DEFAULTSIZE 1024

#define NSUCC 0

// Error code
#define ENORM 1
#define EFOPEN 2
#define EFMEM 3
#define ENFIND 4
#define EFORMAT 5
#define EOREAD 6
#define EPNULL 7
#define EONODEF 8

extern "C"{

	unsigned int sleep(unsigned int);	// Import prototype.

}

namespace NSM{

	extern short int NSM_ERROR;	// Import name.


	using namespace std;	// Import names.

	class Monitor{

		private:
			string Dev;		// For device name.
			char *InputInfo;	// For output message in received.
			char *OutputInfo;	// For output message in sent.
			ifstream Reader;	// For file reading.
			const char *TargetFile;	// /proc/net/dev
			char *InfoBuff;		// File reading data buff.

			long long IFlowN1;	// Flow at the i time.
			long long IFlowN2;	// Flow at the j time.
			long long OFlowN1;
			long long OFlowN2;

		protected:

		public:
			Monitor();
			Monitor(const char * const & Device);	// Overload.
			~Monitor();

			short int _ResolvInfo_(void);	// Responing information format.
			void _Main_Proreduce_(void);	// Main working.

			long long _STN_Base10_(const char *Target);	// Convering.

	};



}	// namespace end



#endif // Header end
