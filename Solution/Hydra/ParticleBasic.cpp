//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	ParticleBasic.cpp
//	Description	:	Definition of CParticleBasic, inheriting from pure virtual CParticle
//	Author		:	Jamie Smith
//	Mail		:	jamie.smith@mediadesign.school.nz
//

// This include.
#include "ParticleBasic.h"

CParticleBasic::~CParticleBasic()
{
	
}

bool
CParticleBasic::Process(float _fDeltaTick)
{
	// Decrease lifetime.
	m_fLifetime -= _fDeltaTick;

	if (m_fLifetime <= 0.0f)	// If this particle is too old...
	{
		return true; // Destroy the particle.
	}

	m_vecPos += m_vecMovement * _fDeltaTick;

	return false;
}