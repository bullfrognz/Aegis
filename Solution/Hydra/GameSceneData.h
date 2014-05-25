//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   GameSceneData.h
//  Description :   Stores data to be transfered to the game scene.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_GAMESCNEDATA_H__
#define __IGFEB11_IG500_GAMESCNEDATA_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes
enum EDifficulty;


class CGameSceneData
{

	// Member Functions
public:


	 CGameSceneData();
	~CGameSceneData();


	void SetDifficulty(EDifficulty _eDifficulty);
	void SetMapFile(char* _cpMapFile);
	void SetPlayerStartGold(unsigned int _uiNumGold);
	void SetPlayerStartLives(unsigned int _uiNumLives);


	EDifficulty GetDifficulty() const;
	char* GetMapFile();
	unsigned int GetPlayerStartGold() const;
	unsigned int GetPlayerStartLives() const;


	CGameSceneData& operator = (const CGameSceneData& _rGameSceneData);


	// Inline Functions


protected:


private:


	// Member Variables
protected:


private:


	EDifficulty m_eDifficulty;


	char* m_cpMapFile;


	unsigned int m_uiPlayerStartGold;
	unsigned int m_uiPlayerStartLives;


};


#endif //__IGFEB11_IG500_GAMESCNEDATA_H__