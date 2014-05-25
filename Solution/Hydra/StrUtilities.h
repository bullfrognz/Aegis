//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   StrUtilities.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_STRUTILITIES_H__
#define __IGFEB11_IG500_STRUTILITIES_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes


namespace StrUtilities
{


	void Copy(const char* _kcpInput, char*& _cprOutput);
	void Copy(const char* _kcpInput, const char*& _kcprOutput);


	void Copy(const wchar_t* _kwcpInput, wchar_t*& _wcprOutput);
	void Copy(const wchar_t* _kwcpInput, const wchar_t*& _kwcprOutput);


	void Trim(char*& _cprString);
	void TrimLeft(char*& _crpString);
	void TrimRight(char*& _cprString);


	void ConvertToWChar(const char* _kcpInput, wchar_t*& _wcprOutput);
	void ConvertToChar(const wchar_t* _kwcpInput, char*& _cprOutput);


	void ToUpperCase(char* _cpString);
	void ToLowerCase(char* _cpString);


	void AddPrefix(const char* _kcpInput, char*& _cprOutput);
	void AddSuffix(const char* _kcpInput, char*& _cprOutput);


	void GetNumCharEntries(const char* _kcpInput, const char* _kcpCharacter, int& _irNumEntries);


	unsigned int GetStringValue(const char* _kcpString);
	unsigned int GetStringValue(const wchar_t* _kwcpString);


}


#endif //__IGFEB11_IG500_STRUTILITIES_H__