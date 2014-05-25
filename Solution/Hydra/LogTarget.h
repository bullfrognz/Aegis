//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2011 Media Design School
//
//  File Name   :   LogTarget.h
//  Description :   Template for declaration of CIlogtarget files
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//
#pragma once

#ifndef __IGFEB11_IG500_ILOGTARGET_H__
#define __IGFEB11_IG500_ILOGTARGET_H__

// Library Includes
#include <windows.h>

// Local Includes

// Types

// Constants

// Prototypes

class ILogTarget
{
// Member Functions
public:
	virtual void Write (const char* _pcMessage) = 0;
	virtual void Process(float _fDeltatTick) = 0;

protected:

private:

// Member Variables
public:

protected:

private:

};

#endif // __IGFEB11_MODULE_TEMPLATE_H__
