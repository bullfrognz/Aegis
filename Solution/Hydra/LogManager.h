//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2011 Media Design School
//
//  File Name   :   clogmanager.h
//  Description :   Template for declaration of CClogmanager files
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//
#pragma once

#ifndef __IGFEB11_IG500_CLOGMANAGER_H__
#define __IGFEB11_IG500_CLOGMANAGER_H__

// Library Includes
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <d3dx9.h>

// Local Includes
#include "LogTarget.h"

// Types

// Constants

// Prototypes

using namespace std;

class CLogManager
{
// Member Functions
public:
CLogManager();

~CLogManager();

bool Initialise();

bool AddLogTarget(ILogTarget* pLogTarget);

bool RemoveLogTarget(ILogTarget* _pTarget);

void Write (const char* _pcMessage);

void WriteLine (const char* _pcMesaage);

void Track(char* _kcpVariableName, int* _piVariable);
void Track(char* _kcpVariableName, UINT* _piVariable);
void Track(char* _kcpVariableName, float* _pfVariable);
void Track(char* _kcpVariableName, char* _pcVariable);
void Track(char* _kcpVariableName, bool* _pbVariable);
void Track(char* _kcpVariableName, D3DXVECTOR3* _pVector);

void Process(float _fDeltaTick);

void Untrack(int* _piVariable);
void Untrack(float* _pfVariable);
void Untrack(char* _pcVariable);
void Untrack(bool* _pbVariable);
void Untrack(D3DXVECTOR3* _rVector);


protected:

private:

// Member Variables
public:

protected:

private:
	vector<ILogTarget*> m_TargetVector;

	std::map<int*, char*> m_vecTrackInts;
	std::map<UINT*, char*> m_vecTrackUnsignedInts;
	std::map<float*, char*> m_vecTrackFloats;
	std::map<char*, char*> m_vecTrackChars;
	std::map<bool*, char*> m_vecTrackBools;
	std::map<const D3DXVECTOR3*, char*> m_vecTrackVectors;

	static const int s_iMaxBuffer = 256;
	char* m_pcMessage;

};

#endif // __IGFEB11_MODULE_TEMPLATE_H__
