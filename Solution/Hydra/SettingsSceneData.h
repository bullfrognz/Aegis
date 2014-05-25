//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   SettingsSceneData.h
//  Description :   Stores data to be transfered to the game scene.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_SETTINGSSCNEDATA_H__
#define __IGFEB11_IG500_SETTINGSSCNEDATA_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes
enum EDifficulty;


class CSettingsSceneData
{

	// Member Functions
public:


	 CSettingsSceneData();
	~CSettingsSceneData();


	void SetSceneTypeId(int _iSceneTypeId);
	void SetSceneTypeMainScene(bool _bMainScene);


	int  GetSceneTypeId() const;
	bool GetSceneTypeMainScene() const;


	// Inline Functions


protected:


private:


	// Member Variables
protected:


private:


	int m_iSceneTypeId;


	bool m_bSceneTypeMainScene;


};


#endif //__IGFEB11_IG500_SETTINGSSCNEDATA_H__