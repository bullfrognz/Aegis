//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Particle.h
//	Description	:	Declaration of pure virtual CParticle
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __HYDRA_PARTICLE_H__
#define __HYDRA_PARTICLE_H__

// Library includes.
#include <d3dx9.h>

class CParticle
{
	// Member functions.
public:
	CParticle();
	virtual ~CParticle();
	virtual bool Process(float _fDeltaTick) = 0;	// Returns true if this particle needs to be destroyed.

	inline void SetPosition(const D3DXVECTOR3& _rkVecPos);
	inline const D3DXVECTOR3& GetPosition() const;

protected:
	CParticle(const CParticle&);

private:

	// Member data.
public:

protected:
	D3DXVECTOR3 m_vecPos;	// Current position of the particle.

private:
};

#include "Particle.inl"

#endif	// __HYDRA_PARTICLE_H__