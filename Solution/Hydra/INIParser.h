//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2011 Media Design School
//
//  File Name   :   INI Parser.h
//  Description :   Template for declaration of CINIparser files
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//
#pragma once

#ifndef __IGFEB11_IG500_CINIPARSER_H__
#define __IGFEB11_IG500_CINIPARSER_H__

// Library Includes
#include <map>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <d3dx9.h>

// Local Includes

// Types

// Constants

// Prototypes

using namespace std;

class CINIParser
{
// Member Functions
public:
	CINIParser();
	
	~CINIParser()
	{
	}

	bool LoadINIFile(const char* _pcFileName);

	bool SaveINIFile(const char* _pcFileName);

	bool AddValue (const char* _pcSection, const char* _pcKey,
					const char* _pcValue);

	bool AddComment (const char* _pcComment);
	
	//Get char value
	bool GetValue(const char* _pcSection, const char* _pcKey,
				  char& _cValue) const;

	//Get wide char string
	bool GetValue(const char* _pcSection, const char* _pcKey,
				  std::wstring& _rwValue) const;			  

	//Get string value
	bool GetValue(const char* _pcSection, const char* _pcKey,
				  std::string& _rStrValue) const;

	//Get int value
	bool GetValue(const char* _pcSection, const char* _pcKey,
				  int& _riValue) const;

	//Get unsigned int value
	bool GetValue(const char* _pcSection, const char* _pcKey,
				  unsigned int& _ruiValue) const;
	
	//Get float value
	bool GetValue(const char* _pcSection, const char* _pcKey,
				  float& _rfValue) const;

	//Get bool value
	bool GetValue(const char* _pcSection, const char* _pcKey,
				  bool& _rbValue) const;

	//Get vector value
	bool GetValue(const char* _pcSection, const char* _pcKey,
				  D3DXVECTOR3& _rvecValue) const;

		
protected:

private:

// Member Variables
public:

protected:

private:
	map<string, string> m_mapPairs;

	string m_strFileName;

	fstream m_filestream;

	string m_CurrentSection;

	int m_iComment;
	
};

#endif // __IGFEB11_MODULE_TEMPLATE_H__
