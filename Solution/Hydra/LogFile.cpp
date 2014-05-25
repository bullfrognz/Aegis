//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2011 Media Design School
//
//  File Name   :   LogFile.cpp
//  Description :   Template for implementation of CLogfile files
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//

#include "logfile.h"

/**
*
* This function passed in the name of a file,
* which will later be written into.
*
* @author Daniel Langsford
* @param const char* _pcFileName: Name of the file to be used later.
* @returns a bool representing function success. 
*
*/
bool
CLogFile::Initialise (const char* _pcFileName)
{
	kpcFileName = _pcFileName;
	assert(_pcFileName);

	return(true);
}

/**
*
* This function writes a message into the file
*
* @author Daniel Langsford
* @param const char* _pcMessage: The message to be logged to file.
* @return: void
*
*/
void
CLogFile::Write (const char* _pcMessage)
{
	ofstream LogFile;
	LogFile.open(kpcFileName);

	LogFile << _pcMessage;
	
	LogFile.close();
}

