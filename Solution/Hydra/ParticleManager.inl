//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	ParticleManager.inl
//	Description	:	Definition of inline CParticleManager functions.
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

//library includes.
#include <cassert>

/**
*
* @author Jade Abbott
*
*/
unsigned int
CParticleManager::GetNumParticles(unsigned int _uiGroup)
{
	assert(_uiGroup < m_uiNumGroups);
	return m_arrGroups[_uiGroup].m_uiNumParticles;
}

/**
*
* @author Jade Abbott
*
*/
CParticleInterface&
CParticleManager::GetParticleInterface()
{
	assert(m_pParticleInterface);	// Should not be called if initialisation failed.
	return *m_pParticleInterface;
}