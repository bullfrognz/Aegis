//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	ParticleBullet.cpp
//	Description	:	Definition of CParticleBullet, inheriting from pure virtual CParticle
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// This include.
#include "ParticleBullet.h"

CParticleBullet::CParticleBullet()
: m_vecMovement(0.0f, 0.0f, 0.0f)
, m_fLifetime(0.0f)
{

}

CParticleBullet::~CParticleBullet()
{
	
}

/**
*
* Processes this bullet (all bullet-like behaviour is defined here).
*
* @author Jade Abbott
* @param Delta time since last process.
* @return True if this bullet must be destroyed.
*
*/
bool
CParticleBullet::Process(float _fDeltaTick)
{
	// Decrease lifetime.
	m_fLifetime -= _fDeltaTick;

	if (m_fLifetime <= 0.0f)	// If this bullet is too old...
	{
		return true; // Destroy the bullet.
	}

	// Process movement of this bullet.
	// TODO: Handle collision with objects (this is currently a demonstration of particles, so functionality is not present).
	m_vecPos += m_vecMovement * _fDeltaTick;

	return false;
}