//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	ParticleInterface.inl
//	Description	:	Definition of inline CParticleInterface functions.
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// Library includes.
#include <cassert>

// Local includes.
#include "ParticleManager.h"
#include "ParticleBasic.h"
#include "ParticleBasic.h"

/**
*
* Handles creation of a bullet.
*
* @author Jade Abbott
* @param _rkVecPos Initial position of the bullet.
* @param _rkVecMovement Direction and speed of the bullet.
* @return Void.
*
*/
void
CParticleInterface::CreateBasic(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement)
{
	m_rParticleManager.AddParticle(m_arruiParticleGroupID[PROJINT_BASIC], new CParticleBasic(_rkVecPos, _rkVecMovement, m_fBasicLifetime));
}

/**
*
* Handles creation Smoke.
*
* @author Jamie Smith
* @param _rkVecPos Initial position of the bullet.
* @param _rkVecMovement Direction and speed of the bullet.
* @return Void.
*
*/
void
CParticleInterface::CreateSmoke(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer)
{
	m_rParticleManager.AddParticle(m_arruiParticleGroupID[PROJINT_SMOKE], new CParticleBasic(_rkVecPos, _rkVecMovement, _fDeathTimer));
}

/**
*
* Handles creation Fire.
*
* @author Jamie Smith
* @param _rkVecPos Initial position of the bullet.
* @param _rkVecMovement Direction and speed of the bullet.
* @return Void.
*
*/
void
CParticleInterface::CreateFire(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer)
{
	m_rParticleManager.AddParticle(m_arruiParticleGroupID[PROJINT_FIRE], new CParticleBasic(_rkVecPos, _rkVecMovement, _fDeathTimer));
}

/**
*
* Handles creation Water.
*
* @author Jamie Smith
* @param _rkVecPos Initial position of the bullet.
* @param _rkVecMovement Direction and speed of the bullet.
* @return Void.
*
*/
void
CParticleInterface::CreateWater(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer)
{
	m_rParticleManager.AddParticle(m_arruiParticleGroupID[PROJINT_WATER], new CParticleBasic(_rkVecPos, _rkVecMovement, _fDeathTimer));
}

/**
*
* Handles creation Water.
*
* @author Jamie Smith
* @param _rkVecPos Initial position of the bullet.
* @param _rkVecMovement Direction and speed of the bullet.
* @return Void.
*
*/
void
CParticleInterface::CreatePoison(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer)
{
	m_rParticleManager.AddParticle(m_arruiParticleGroupID[PROJINT_POISON], new CParticleBasic(_rkVecPos, _rkVecMovement, _fDeathTimer));
}

/**
*
* Handles creation Frost.
*
* @author Jamie Smith
* @param _rkVecPos Initial position of the bullet.
* @param _rkVecMovement Direction and speed of the bullet.
* @return Void.
*
*/
void
CParticleInterface::CreateFrost(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer)
{
	m_rParticleManager.AddParticle(m_arruiParticleGroupID[PROJINT_FROST], new CParticleBasic(_rkVecPos, _rkVecMovement, _fDeathTimer));
}

/**
*
* Handles creation FrostTower.
*
* @author Jamie Smith
* @param _rkVecPos Initial position of the bullet.
* @param _rkVecMovement Direction and speed of the bullet.
* @return Void.
*
*/
void
CParticleInterface::CreateFrostTower(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer)
{
	m_rParticleManager.AddParticle(m_arruiParticleGroupID[PROJINT_FROSTTOWER], new CParticleBasic(_rkVecPos, _rkVecMovement, _fDeathTimer));
}

/**
*
* Handles creation FireTower.
*
* @author Jamie Smith
* @param _rkVecPos Initial position of the bullet.
* @param _rkVecMovement Direction and speed of the bullet.
* @return Void.
*
*/
void
CParticleInterface::CreateFireTower(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer)
{
	m_rParticleManager.AddParticle(m_arruiParticleGroupID[PROJINT_FIRETOWER], new CParticleBasic(_rkVecPos, _rkVecMovement, _fDeathTimer));
}

/**
*
* Handles creation Cannon.
*
* @author Jamie Smith
* @param _rkVecPos Initial position of the bullet.
* @param _rkVecMovement Direction and speed of the bullet.
* @return Void.
*
*/
void
CParticleInterface::CreateCannon(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer)
{
	m_rParticleManager.AddParticle(m_arruiParticleGroupID[PROJINT_CANNON], new CParticleBasic(_rkVecPos, _rkVecMovement, _fDeathTimer));
}

/**
*
* Handles creation SunsWrath.
*
* @author Jamie Smith
* @param _rkVecPos Initial position of the bullet.
* @param _rkVecMovement Direction and speed of the bullet.
* @return Void.
*
*/
void
CParticleInterface::CreateSunsWrath(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer)
{
	m_rParticleManager.AddParticle(m_arruiParticleGroupID[PROJINT_SUNSWRATH], new CParticleBasic(_rkVecPos, _rkVecMovement, _fDeathTimer));
}

/**
*
* Sets how long all basic particles in the game will live for.
*
* @author Jade Abbott
* @param _fLifetime How long each basic particle can live for (only applies to newly created particles).
* @return Void.
*
*/
void
CParticleInterface::SetBasicLifetime(float _fLifetime)
{
	m_fBasicLifetime = _fLifetime;
}