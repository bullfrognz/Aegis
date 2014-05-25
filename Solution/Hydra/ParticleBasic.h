//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	ParticleBasic.h
//	Description	:	Declaration of CParticleBasic, inheriting from pure virtual CParticle
//	Author		:	Jamie Smith
//	Mail		:	jamie.smith@mediadesign.school.nz
//

#pragma once
#ifndef __HYDRA_PARTICLEBASIC_H__
#define __HYDRA_PARTICLEBASIC_H__

// Local includes.
#include "Particle.h"

// Library includes.
#include <d3dx9.h>

class CParticleBasic : public CParticle
{
	// Member functions.
public:
	inline CParticleBasic(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fLifetime);
	virtual ~CParticleBasic();

	virtual bool Process(float _fDeltaTick);	// Returns true if this particle needs to be destroyed.

protected:
	CParticleBasic(const CParticleBasic&);

private:

	// Member data.
public:

protected:
	D3DXVECTOR3 m_vecMovement;	// Direction and speed the particle is moving.
	float m_fLifetime;	// Used to cap how long this particle can exist for.

private:
};

#include "ParticleBasic.inl"

#endif	// __HYDRA_PARTICLEBASIC_H__