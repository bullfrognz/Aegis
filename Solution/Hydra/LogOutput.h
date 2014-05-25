//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2011 Media Design School
//
//  File Name   :   LogOutput.h
//  Description :   Template for declaration of CLogfile files
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//
#pragma once

#ifndef __IGFEB11_IG500_LOGOUTPUT_H__
#define __IGFEB11_IG500_LOGOUTPUT_H__

// Library Includes
#include <fstream>

// Local Includes
#include "logtarget.h"

// Types

// Constants

// Prototypes

class CLogOutput : public ILogTarget
{
// Member Functions
public:
	CLogOutput()
	{
	}

	~CLogOutput()
	{
	}

	void Write (const char* _pcMessage);

protected:

private:

// Member Variables
public:

protected:

private:

};

#endif // __IGFEB11_MODULE_TEMPLATE_H__
