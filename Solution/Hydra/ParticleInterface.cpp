//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	ProjectileInterface.cpp
//	Description	:	Definition of CParticleInterface, the creator of particles.
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// This include.
#include "ParticleInterface.h"

// Local includes.
#include "ParticleManager.h"
#include "TextureManager.h"
#include "Utility.h"

// Library includes.
#include <cassert>
#include <d3dx9.h>

CParticleInterface::CParticleInterface(CParticleManager& _rParticleManager)
: m_rParticleManager(_rParticleManager)
, m_fBasicLifetime(1.8f)	// Being non-zero means bullets will (at least) exist.
{
	for (unsigned int ui = 0; ui < PROJINT_MAX; ++ui)
	{
		m_arruiParticleGroupID[ui] = Utility::INVALID_ID;
	}
}

CParticleInterface::~CParticleInterface()
{

}

bool
CParticleInterface::Initialise(CTextureManager& _rTextureManager)
{
	// Set up particle stuff.
	int iTextureID = _rTextureManager.LoadTextureFile(L"Assets/Textures/WaterTexture.png");
	m_arruiParticleGroupID[PROJINT_BASIC] = m_rParticleManager.AddGroup(iTextureID);

	iTextureID = _rTextureManager.LoadTextureFile(L"Assets/Textures/Game_SmokeParticle.png");
	m_arruiParticleGroupID[PROJINT_SMOKE] = m_rParticleManager.AddGroup(iTextureID, 0.4f);

	iTextureID = _rTextureManager.LoadTextureFile(L"Assets/Textures/FireTexture.png");
	m_arruiParticleGroupID[PROJINT_FIRE] = m_rParticleManager.AddGroup(iTextureID);

	iTextureID = _rTextureManager.LoadTextureFile(L"Assets/Textures/WaterParticle.png");
	m_arruiParticleGroupID[PROJINT_WATER] = m_rParticleManager.AddGroup(iTextureID);

	iTextureID = _rTextureManager.LoadTextureFile(L"Assets/Textures/PoisonParticle.png");
	m_arruiParticleGroupID[PROJINT_POISON] = m_rParticleManager.AddGroup(iTextureID);

	iTextureID = _rTextureManager.LoadTextureFile(L"Assets/Textures/FrostParticle.png");
	m_arruiParticleGroupID[PROJINT_FROST] = m_rParticleManager.AddGroup(iTextureID);

	iTextureID = _rTextureManager.LoadTextureFile(L"Assets/Textures/FrostTowerParticle.png");
	m_arruiParticleGroupID[PROJINT_FROSTTOWER] = m_rParticleManager.AddGroup(iTextureID);

	iTextureID = _rTextureManager.LoadTextureFile(L"Assets/Textures/FireTowerParticle.png");
	m_arruiParticleGroupID[PROJINT_FIRETOWER] = m_rParticleManager.AddGroup(iTextureID);

	iTextureID = _rTextureManager.LoadTextureFile(L"Assets/Textures/CannonParticle.png");
	m_arruiParticleGroupID[PROJINT_CANNON] = m_rParticleManager.AddGroup(iTextureID);

	iTextureID = _rTextureManager.LoadTextureFile(L"Assets/Textures/SunsWrathParticle.png");
	m_arruiParticleGroupID[PROJINT_SUNSWRATH] = m_rParticleManager.AddGroup(iTextureID);

	return true;
}