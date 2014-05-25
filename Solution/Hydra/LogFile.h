//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2010 Media Design School
//
//  File Name   :   LogFile.h
//  Description :   Template for declaration of CLogfile files
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//
#pragma once

#ifndef __IGFEB11_IG500_LOGFILE_H__
#define __IGFEB11_IG500_LOGFILE_H__

// Library Includes
#include <fstream>
#include <cassert>

// Local Includes
#include "LogTarget.h"

// Types

// Constants

// Prototypes

using namespace std;

class CLogFile : public ILogTarget
{
// Member Functions
public:
	CLogFile()
	{
	}

	~CLogFile()
	{
	}

	bool Initialise (const char* _pcFileName);

	void Write (const char* _pcMessage);

protected:

private:

// Member Variables
public:

protected:

private:
	const char* kpcFileName;

};

#endif // __IGFEB11_MODULE_TEMPLATE_H__
