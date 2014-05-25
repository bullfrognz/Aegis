//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   Weapon.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <cmath>


// Local Includes
#include "INIParser.h"
#include "D3DRenderer.h"
#include "StrUtilities.h"
#include "Projectile.h"
#include "Utility.h"
#include "Tower.h"

// This Include
#include "Weapon.h"


// Static Variables
unsigned int CWeapon::s_uiWeaponReffCount = 0;


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Weapon class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWeapon::CWeapon()
: m_pProjectiles(0)
, m_uiMaxActiveProjectileId(0)
, m_uiCriticalRating(0)
, m_fMinDamage(0)
, m_fMaxDamage(0)
, m_fCriticalMultiplier(0)
{
	//Add reff
	++ s_uiWeaponReffCount;
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Weapon class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWeapon::~CWeapon()
{
	Deinitialise();


	//Remove reff
	-- s_uiWeaponReffCount;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialisings the class instance before use.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CWeapon::Initialise(CD3DRenderer* _pRenderer, TWeaponData& _trWeaponData, TProjectileData& _trProjectileData)
{
	//Set member variables
	m_fMinDamage = _trWeaponData.m_fMinDamage;
	m_fMaxDamage = _trWeaponData.m_fMaxDamage;
	m_uiCriticalRating = _trWeaponData.m_uiCritialRating;
	m_fCriticalMultiplier = _trWeaponData.m_fCriticalMultiplier;
	m_uiMaxProjectiles = _trWeaponData.m_uiMaxProjectiles;


	//Run initialsie functions
	InitialiseProjectilies(_pRenderer, _trProjectileData);


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function processes the class instance for the current frame.
*
* @author Bryce Booth
* @param  _fDeltaTick	The time elasped since last process
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWeapon::Process(float _fDeltaTick)
{
	//Set default variables
	unsigned int uiLastActiveProjectileId = 0;
	CProjectile* pProjectile = 0;
	

	//Loop through 0 -> max active projectile id
	for (unsigned int i = 0; i <= m_uiMaxActiveProjectileId; ++ i)
	{
		//Set current projectile
		pProjectile = &m_pProjectiles[i];


		//Check projectile active
		if (pProjectile->IsActive() == true)
		{
			//Process the projectile
			pProjectile->Process(_fDeltaTick);


			//Update last active projectile id
			uiLastActiveProjectileId = i;
		}
	}


	//Check last active projectile id is lower then
	//current max active projectile id
	if (uiLastActiveProjectileId < m_uiMaxActiveProjectileId)
	{
		//Update max active projectile id
		m_uiMaxActiveProjectileId =  uiLastActiveProjectileId;
	}

}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will call on the renderer to draw meshes.
*
* @author Bryce Booth
* @param _pRenderer		The renderer for the window
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWeapon::Draw(CD3DRenderer* _pRenderer)
{
	//Set default variables
	CProjectile* pProjectile = 0;


	//Loop through 0 -> max active projectile id
	for (unsigned int i = 0; i <= m_uiMaxActiveProjectileId; ++ i)
	{
		//Set current projectile
		pProjectile = &m_pProjectiles[i];


		//Check projectile active
		if (pProjectile->IsActive() == true)
		{
			//Process the projectile
			pProjectile->Draw(_pRenderer);
		}
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will fire a projectile at an enemy.
*
* @author Bryce Booth
* @param _kv3rEmitPosition		The start position of the projectile
* @param _pTargetEnemy			The enemy instance that the projectile will track
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWeapon::Fire(const CVector3& _kv3rEmitPosition, CEnemy* _pTargetEnemy)
{
	//Set default variables
	float fBulletDamage = 0.0f;
	bool bCritical = false;


	//Loop through to max projectile number
	for (unsigned int i = 0; i < m_uiMaxProjectiles; ++ i)
	{
		//Set current projectile
		CProjectile* pProjectile = &m_pProjectiles[i];

	
		//Check projectile is active
		if (pProjectile->IsActive() == false)
		{
			//Generate random number min -> max damage
			fBulletDamage = MathUtility::RandomNumber(m_fMinDamage, m_fMaxDamage);


			//Check profile has critical rating
			if (m_uiCriticalRating != 0.0f)
			{
				//Generate random number
				unsigned int uiRandomNumber = MathUtility::RandomNumber(0, 100);


				//Check if critical rating is higher or equal then random number
				if (uiRandomNumber <= m_uiCriticalRating)
				{
					//Multiply bullet damage
					fBulletDamage *= m_fCriticalMultiplier;


					bCritical = true;
				}
			}
		

			//Set projectile variables
			pProjectile->Activate(_kv3rEmitPosition, _pTargetEnemy, fBulletDamage, bCritical);


			//Check if current projectile id is higher then the 
			//current highest active projectile id
			if (i > m_uiMaxActiveProjectileId)
			{
				//Update new highest active projectile id
				m_uiMaxActiveProjectileId = i;
			}


			break;
		}
	}
}











/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will instance and initialise the projectiles for the weapon.
*
* @author Bryce Booth
* @param _pRenderer				The renderer for the window
* @param _trProjectileData		Container for the projectile data
* @return bool					States function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CWeapon::InitialiseProjectilies(CD3DRenderer* _pRenderer, TProjectileData& _trProjectileData)
{
	//Allocate memory for projectiles
	m_pProjectiles = new CProjectile[m_uiMaxProjectiles];

	
	//Loop through 0 -> number max projectiles
	for (unsigned int i = 0; i < m_uiMaxProjectiles; ++ i)
	{
		//Initialise projectile
		m_pProjectiles[i].Initialise(_pRenderer, _trProjectileData);
	}


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will process all active projectiles that the weapon owns.
*
* @author Bryce Booth
* @param  _fDeltaTick	The time elasped since last process
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWeapon::ProcessProjectiles(float _fDeltaTick)
{
	//Set default variables
	unsigned int uiLastActiveProjectileId = 0;
	CProjectile* pProjectile = 0;
	

	//Loop through 0 -> max active projectile id
	for (unsigned int i = 0; i <= m_uiMaxActiveProjectileId; ++ i)
	{
		//Set current projectile
		pProjectile = &m_pProjectiles[i];


		//Check projectile active
		if (pProjectile->IsActive() == true)
		{
			//Process the projectile
			pProjectile->Process(_fDeltaTick);


			//Update last active projectile id
			uiLastActiveProjectileId = i;
		}
	}


	//Check last active projectile id is lower then
	//current max active projectile id
	if (uiLastActiveProjectileId < m_uiMaxActiveProjectileId)
	{
		//Update max active projectile id
		m_uiMaxActiveProjectileId =  uiLastActiveProjectileId;
	}
}








/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWeapon::Deinitialise()
{
	FW_ADELETE(m_pProjectiles);
}