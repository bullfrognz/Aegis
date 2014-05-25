//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   GameSceneData.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "GameScene.h"
#include "StrUtilities.h"


// This Include
#include "GameSceneData.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* GameSceneData class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CGameSceneData::CGameSceneData()
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* GameSceneData class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CGameSceneData::~CGameSceneData()
{
	delete m_cpMapFile;
	m_cpMapFile = 0;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the difficulty member variable.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameSceneData::SetDifficulty(EDifficulty _eDifficulty)
{
	m_eDifficulty = _eDifficulty;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the map file member variable.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameSceneData::SetMapFile(char* _cpMapFile)
{
	m_cpMapFile = _cpMapFile;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the player start gold member variable.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameSceneData::SetPlayerStartGold(unsigned int _uiNumGold)
{
	m_uiPlayerStartGold = _uiNumGold;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the player start lives member variable.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameSceneData::SetPlayerStartLives(unsigned int _uiNumLives)
{
	m_uiPlayerStartLives = _uiNumLives;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the difficulty member variable.
*
* @author Bryce Booth
*
* @return _eDifficulty	Difficulty level.
*
*---------------------------------------------------------------------------------------------------------------------------*/

EDifficulty
CGameSceneData::GetDifficulty() const
{
	return (m_eDifficulty);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the map file member variable.
*
* @author Bryce Booth
*
* @return _eDifficulty	Map file value.
*
*---------------------------------------------------------------------------------------------------------------------------*/

char*
CGameSceneData::GetMapFile()
{
	return (m_cpMapFile);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the player start gold member variable.
*
* @author Bryce Booth
*
* @return m_uiPlayerStartGold	Gold amount.
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CGameSceneData::GetPlayerStartGold() const
{
	return (m_uiPlayerStartGold);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the player start lives member variable.
*
* @author Bryce Booth
*
* @return _eDifficulty	Lives amount.
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CGameSceneData::GetPlayerStartLives() const
{
	return (m_uiPlayerStartLives);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Correctly copies game scene data between containers.
*
* @author Bryce Booth
*
* @return *this		Self instance as reference.
*
*---------------------------------------------------------------------------------------------------------------------------*/

CGameSceneData&
CGameSceneData::operator = (const CGameSceneData& _rGameSceneData) 
{
	//Copy member variables
	m_eDifficulty        = _rGameSceneData.m_eDifficulty;
	m_uiPlayerStartGold  = _rGameSceneData.m_uiPlayerStartGold;
	m_uiPlayerStartLives = _rGameSceneData.m_uiPlayerStartLives;
	StrUtilities::Copy(_rGameSceneData.m_cpMapFile, m_cpMapFile);


	return (*this);
}







/********************************
            Protected
*********************************/









/********************************
            Private
*********************************/