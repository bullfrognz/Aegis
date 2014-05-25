//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Weapon.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_WEAPON_H__
#define __IGFEB11_IG500_WEAPON_H__


// Library Includes


// Local Includes
#include "Vector3.h"


// Types
struct TWeaponData
{
	TWeaponData()
	{
		ZeroMemory(this, sizeof(TWeaponData));
	}


	unsigned int m_uiCritialRating;
	unsigned int m_uiMaxProjectiles;


	float m_fMinDamage;
	float m_fMaxDamage;
	float m_fCriticalMultiplier;
};


// Constants


// Prototypes
struct TProjectileData;

class CProjectile;
class CD3DRenderer;
class CVector3;
class CEnemy;
class CTower;


class CWeapon
{

	// Member Functions
public:


	 CWeapon();
	~CWeapon();


	bool Initialise(CD3DRenderer* _pRenderer, TWeaponData& _trWeaponData, TProjectileData& _trProjectileData);


	void Process(float _fDeltaTick);


	void Draw(CD3DRenderer* _pRenderer);


	void Fire(const CVector3& _kv3rEmitPosition, CEnemy* _pTargetEnemy);


	// Inline Functions
	inline void SetDamageMultiplier(float _fMultiplier);


	inline float GetMinDamage() const;
	inline float GetMaxDamage() const;
	inline unsigned int GetProjectileEffects() const;


protected:


	bool InitialiseProjectilies(CD3DRenderer* _pRenderer, TProjectileData& _trProjectileData);


	void ProcessProjectiles(float _fDeltaTick);


private:


	void Deinitialise();


	CWeapon(const CWeapon& _krWeapon);
	CWeapon& operator = (const CWeapon& _krWeapon);


	// Member Variables
protected:


	CProjectile* m_pProjectiles;


	unsigned int m_uiMaxProjectiles;
	unsigned int m_uiMaxActiveProjectileId;
	unsigned int m_uiCriticalRating;


	float m_fMinDamage;
	float m_fMaxDamage;
	float m_fCriticalMultiplier;


private:


	static unsigned int s_uiWeaponReffCount;


};

#include "Weapon.inl"

#endif //__IGFEB11_IG500_WEAPON_H__