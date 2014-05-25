//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2011 Media Design School
//
//  File Name   :   ciniparser.h
//  Description :   Template for declaration of CINIparser files
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//
#pragma once

#ifndef __IGFEB11_IG120_CINIPARSER_H__
#define __IGFEB11_IG120_CINIPARSER_H__

// Library Includes
#include <map>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <d3dx9.h>

// Local Includes

// Types
enum ELineType
{
	LINE_INVALID,
	LINE_EMPTY,
	LINE_COMMENT,
	LINE_SECTION,
	LINE_MAX
};

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
	
	bool GetStringValue(const char* _pcSection, const char* _pcKey,
		std::string& _rStrValue);

	bool GetIntValue(const char* _pcSection, const char* _pcKey,
					 int& _riValue);
	
	bool GetFloatValue(const char* _pcSection, const char* _pcKey,
						float& _rfValue);

	bool GetBoolValue(const char* _pcSection, const char* _pcKey,
						bool& _rbValue);

	bool GetVectorValue(const char* _pcSection, const char* _pcKey,
						D3DXVECTOR3& _rvecValue);

	
protected:

private:

// Member Variables
public:

protected:

private:
	map<string, string> m_mapPairs;

	map<int, string, string> m_map;

	string m_strFileName;

	fstream m_filestream;

	string m_CurrentSection;

	int m_iComment;
	
};

#endif // __IGFEB11_MODULE_TEMPLATE_H__
