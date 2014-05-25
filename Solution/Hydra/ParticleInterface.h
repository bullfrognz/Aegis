//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	ParticleInterface.h
//	Description	:	Declaration of CParticleInterface, the creator of particles.
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __HYDRA_PARTICLEINTERFACE_H__
#define __HYDRA_PARTICLEINTERFACE_H__

// Local includes.
class CParticleManager;
class CTextureManager;
struct D3DXVECTOR3;

enum EParticleInterfaceData
{
	PROJINT_BASIC = 0,
	PROJINT_SMOKE,
	PROJINT_FIRE,
	PROJINT_WATER,
	PROJINT_POISON,
	PROJINT_FROST,
	PROJINT_FROSTTOWER,
	PROJINT_FIRETOWER,
	PROJINT_CANNON,
	PROJINT_SUNSWRATH,
	PROJINT_MAX
};

class CParticleInterface
{
	// Member functions.
public:
	CParticleInterface(CParticleManager& _rParticleManager);
	~CParticleInterface();

	bool Initialise(CTextureManager& _rTextureManager);

	inline void CreateBasic(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement);
	inline void CreateSmoke(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer);
	inline void CreateFire(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer);
	inline void CreateFrost(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer);
	inline void CreateWater(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer);	
	inline void CreatePoison(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer);		
	inline void CreateFrostTower(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer);
	inline void CreateFireTower(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer);
	inline void CreateCannon(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer);
	inline void CreateSunsWrath(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fDeathTimer);
	inline void SetBasicLifetime(float _fLifetime);

protected:

private:

	// Member data.
public:

protected:
	CParticleManager& m_rParticleManager;

	unsigned int m_arruiParticleGroupID[PROJINT_MAX];

	float m_fBasicLifetime;	// The lifetime that all bullets will have.

private:
};

#include "ParticleInterface.inl"

#endif	// __HYDRA_PARTICLEINTERFACE_H__