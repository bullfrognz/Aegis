//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   GameScene.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameScene::SetShowDebugInfo(bool _bShow)
{
	m_bShowDebugInfo = _bShow;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CPlayer*
CGameScene::GetPlayer()
{
	return (m_pPlayer);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWaveManager* 
CGameScene::GetWaveManager()
{
	return (m_pWaveManager);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CTerrain*
CGameScene::GetTerrain()
{
	return (m_pTerrain);
}


CRadialMenu*
CGameScene::GetRadialMenu()
{
	return m_pRadialMenu;
}

CHud*
CGameScene::GetHud()
{
	return m_pHud;
}