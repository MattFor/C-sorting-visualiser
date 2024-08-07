#ifndef VERSION_H
#define VERSION_H

	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 3;
	static const long MINOR  = 1;
	static const long BUILD  = 62;
	static const long REVISION  = 354;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 178;
	#define RC_FILEVERSION 3,1,62,354
	#define RC_FILEVERSION_STRING "3, 1, 62, 354\0"
	static const char FULLVERSION_STRING [] = "3.1.62.354";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 62;
	

#endif //VERSION_H
