//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   SettingsSceneData.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "GameScene.h"
#include "StrUtilities.h"


// This Include
#include "SettingsSceneData.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* SettingsSceneData class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSettingsSceneData::CSettingsSceneData()
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* SettingsSceneData class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSettingsSceneData::~CSettingsSceneData()
{
	//Empty
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the scene id that will be changed to when user quits of settings scene
*
* @author Bryce Booth
* @param _iSceneTypeId		The id of the scene that converts to enum.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsSceneData::SetSceneTypeId(int _iSceneTypeId)
{
	m_iSceneTypeId = _iSceneTypeId;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Tells if the scene id is a main scene or overlay scene.
*
* @author Bryce Booth
* @return _bMainScene	True if main scene else false for overlay scene.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsSceneData::SetSceneTypeMainScene(bool _bMainScene)
{
	m_bSceneTypeMainScene = _bMainScene;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the scene id.
*
* @author Bryce Booth
* @param m_iSceneTypeId	Id of scne eto change to.
*
*---------------------------------------------------------------------------------------------------------------------------*/

int
CSettingsSceneData::GetSceneTypeId() const
{
	return (m_iSceneTypeId);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the type of scene the id belongs to.
*
* @author Bryce Booth
* @param m_bSceneTypeMainScene	True for main scene or is voerlay scene.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSettingsSceneData::GetSceneTypeMainScene() const
{
	return (m_bSceneTypeMainScene);
}







/********************************
            Protected
*********************************/









/********************************
            Private
*********************************/