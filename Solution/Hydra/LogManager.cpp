//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2011 Media Design School
//
//  File Name   :   logmanager.cpp
//  Description :   Template for implementation of CClogmanager files
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//

#include "LogManager.h" 
using namespace std;

/**
*
* Constructor
*
* @author Daniel Langsford
*
*/
CLogManager::CLogManager()
{
	//Empty
}

/**
*
* Destructor
*
* @author Daniel Langsford
* @returns 
*
*/
CLogManager::~CLogManager()
{
	delete m_pcMessage;
	m_pcMessage = 0;
}

/**
*
* This function initialise the log manager.
*
* @author Daniel Langsford
* @returns a bool representing function success 
*
*/
bool
CLogManager::Initialise()
{
	//Creates an array to be used later.
	m_pcMessage = new char[s_iMaxBuffer];

	return(true);
}

/**
*
* This function adds a new target to be managed.
*
* @author Daniel Langsford
* @param pLogTarget: The log target to be added to the manager
* @returns a bool representing whether the target was added.
*
*/
bool
CLogManager::AddLogTarget(ILogTarget* pLogTarget)
{
	bool bTargetAdded = false;

	m_TargetVector.push_back(pLogTarget);

	for (unsigned int i = 0; i < m_TargetVector.size(); ++i)
	{
		if (m_TargetVector[i] == (pLogTarget))
		{
			bTargetAdded = true;
		}
	}
	
	return(bTargetAdded);
}

/**
*
* This function removes a target from the target container.
*
* @author Daniel Langsford
* @param pLogTarget: The log target to be removed from the manager
* @returns a bool representing whether the target was removed.
*
*/
bool
CLogManager::RemoveLogTarget(ILogTarget* _pTarget)
{
	bool bTargetRemoved = true;

	for (unsigned int i = 0; i < m_TargetVector.size(); ++i)
	{
		if (m_TargetVector[i] == _pTarget)
		{
			m_TargetVector.erase(m_TargetVector.begin()+(i-1));
			bTargetRemoved = true;	
		}
	}

	delete _pTarget;
	_pTarget = 0;

	return(bTargetRemoved);	
}
/**
*
* This function calls the write function of all log targets.
*
* @author Daniel Langsford
* @param _pcMessage: Message to be written
* @returns void
*
*/

void
CLogManager::Write (const char* _pcMessage)
{
	for (unsigned int i = 0; i < m_TargetVector.size(); ++i)
	{
		m_TargetVector[i]->Write(_pcMessage);
	}		
}

/**
*
* This function calls the write function of all log targets, followed by a new line
*
* @author Daniel Langsford
* @param _pcMessage: Message to be written
* @returns void
*
*/
void 
CLogManager::WriteLine(const char *_pcMessage)
{
	for (unsigned int i = 0; i < m_TargetVector.size(); ++i)
	{
		std::string strNew = _pcMessage;
		strNew.append("\n");
		m_TargetVector[i]->Write(strNew.c_str());
	}		
}

/**
*
* This function adds a variable to be tracked; the value of tracked variables will be updated once per frame.
*
* @author Daniel Langsford
* @param _kcpVariableName: Name of the variable to be tracked
* @param _piVariable: variable to be added
* @returns void
*
*/
void
CLogManager::Track(char* _kcpVariableName, int* _piVariable)
{
	char* cFix = 0;
	if (!m_vecTrackInts[_piVariable])
	{
		m_vecTrackInts.insert( std::pair<int*, char*>(_piVariable, cFix));

		m_vecTrackInts[_piVariable] = _kcpVariableName;
	}
}

/**
*
* This function adds a variable to be tracked; the value of tracked variables will be updated once per frame.
*
* @author Daniel Langsford
* @param _kcpVariableName: Name of the variable to be tracked
* @param _piVariable: variable to be added
* @returns void
*
*/
void
CLogManager::Track(char* _kcpVariableName, unsigned int* _puiVariable)
{
	char* cFix = 0;
	if (!m_vecTrackUnsignedInts[_puiVariable])
	{
		m_vecTrackUnsignedInts.insert( std::pair<unsigned int*, char*>(_puiVariable, cFix));

		m_vecTrackUnsignedInts[_puiVariable] = _kcpVariableName;
	}
}

/**
*
* This function adds a variable to be tracked; the value of tracked variables will be updated once per frame.
*
* @author Daniel Langsford
* @param _kcpVariableName: Name of the variable to be tracked
* @param _pfVariable: variable to be added
* @returns void
*
*/
void
CLogManager::Track(char* _kcpVariableName, float* _pfVariable)
{
	char* cFix = 0;
	if (!m_vecTrackFloats[_pfVariable])
	{
		m_vecTrackFloats.insert( std::pair<float*, char*>(_pfVariable, cFix) );

		m_vecTrackFloats[_pfVariable] = _kcpVariableName;
	}
}

/**
*
* This function adds a variable to be tracked; the value of tracked variables will be updated once per frame.
*
* @author Daniel Langsford
* @param _kcpVariableName: Name of the variable to be tracked
* @param _pcVariable: variable to be added
* @returns void
*
*/
void
CLogManager::Track(char* _kcpVariableName, char* _pcVariable)
{
	char* cFix = 0;
	if (!m_vecTrackChars[_pcVariable])
	{
		m_vecTrackChars.insert( std::pair<char*, char*>(_pcVariable, cFix) );

		m_vecTrackChars[_pcVariable] = _kcpVariableName;
	}
}

/**
*
* This function adds a variable to be tracked; the value of tracked variables will be updated once per frame.
*
* @author Daniel Langsford
* @param _kcpVariableName: Name of the variable to be tracked
* @param _pbVariable: variable to be added
* @returns void
*
*/
void
CLogManager::Track(char* _kcpVariableName, bool* _pbVariable)
{
	char* cFix = 0;
	if (!m_vecTrackBools[_pbVariable])
	{
		m_vecTrackBools.insert( std::pair<bool*, char*>(_pbVariable, cFix) );

		m_vecTrackBools[_pbVariable] = _kcpVariableName;
	}
}

/**
*
* This function adds a variable to be tracked; the value of tracked variables will be updated once per frame.
*
* @author Daniel Langsford
* @param _kcpVariableName: Name of the variable to be tracked
* @param _pVector: variable to be added
* @returns void
*
*/
void
CLogManager::Track(char* _kcpVariableName, D3DXVECTOR3* _pVector)
{
	char* cFix = 0;
	if (!m_vecTrackVectors[_pVector])
	{
		m_vecTrackVectors.insert( std::pair<const D3DXVECTOR3*, char*>(_pVector, cFix) );

		m_vecTrackVectors[_pVector] = _kcpVariableName;
	}
}

/**
*
* This function processes all tracked variables
*
* @author Daniel Langsford
* @param _fDeltaTick: Change in time since last function call
* @returns void
*
*/
void
CLogManager::Process(float _fDeltaTick)
{	
	for (unsigned int i = 0; i < m_TargetVector.size(); ++i)
	{
		m_TargetVector[i]->Process(_fDeltaTick);
	}

	std::map<int*, char*>::iterator iterInt;
	for (iterInt = m_vecTrackInts.begin(); iterInt != m_vecTrackInts.end(); ++iterInt)
	{
		//Use buffer to concatenate first and second map elements into a string (char*)
		
		int iTemp = *(iterInt->first);
		char* cTemp = iterInt->second;
		sprintf_s(m_pcMessage, 256, "%s" "%s" "%i", cTemp, " = ", iTemp);

		//Write out the string
		WriteLine(m_pcMessage);
	}
	
}