//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	ParticleManager.cpp
//	Description	:	Definition of CParticleManager
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// Library includes.
#include <cassert>

// This include.
#include "ParticleManager.h"

// Local includes.
#include "Particle.h"
#include "Utility.h"
#include "Vertex1Textured.h"
#include "VertexBuffer.h"
#include "D3DRenderer.h"
#include "DeviceManager.h"
#include "WorldMatrix.h"
#include "VertexBufferManager.h"
#include "TextureManager.h"
#include "ParticleInterface.h"
#include "Application.h"
#include "Scene.h"

// Library includes.
#include <d3dx9.h>
#include <queue>
#include <cassert>

//struct TFunctorAlphaComp
//{
//	TFunctorAlphaComp() :m_rkVecPos(reinterpret_cast<const D3DXVECTOR3&>(m_rkVecPos)) {}
//	TFunctorAlphaComp(float _fComp, const D3DXVECTOR3& _rkVecPos) :m_fComp(_fComp), m_rkVecPos(_rkVecPos) {}
//
//	bool operator() (const TFunctorAlphaComp& _Lhs, const TFunctorAlphaComp& _Rhs)
//	{
//		return _Lhs.m_fComp < _Rhs.m_fComp;
//	}
//
//	float m_fComp;
//	const D3DXVECTOR3& m_rkVecPos;
//};

struct TFunctorAlphaComp
{
	TFunctorAlphaComp() {}
	TFunctorAlphaComp(float _fComp, const D3DXVECTOR3* _pkVecPos) :m_fComp(_fComp), m_pkVecPos(_pkVecPos) {}

	bool operator() (const TFunctorAlphaComp& _Lhs, const TFunctorAlphaComp& _Rhs)
	{
		return _Lhs.m_fComp < _Rhs.m_fComp;
	}

	float m_fComp;
	const D3DXVECTOR3* m_pkVecPos;
};

#define FLG_SUPPORTS_PSIZE Utility::B1
#define FLG_MAPENTIRETEXTURE Utility::B2
#define FLG_SCALEBYDISTANCE Utility::B3

CParticleManager::CParticleManager()
: m_pRenderer(0)
, m_pDeviceManager(0)
, m_pParticleInterface(0)
, m_arrGroups(0)
, m_uiNumGroups(0)
, m_uiVertexBufferSize(0)
, m_uiVertexBufferID(Utility::INVALID_ID)
, m_fPointScaleConstant(1.0f)
, m_fPointScaleLinear(1.0f)
, m_fPointScaleQuadratic(1.0f)
, m_ucFlags(0)
{

}

CParticleManager::~CParticleManager()
{
	Shutdown();
}

/**
*
* Cleans up the entire Particle Manager so it can be re-initialised.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CParticleManager::Shutdown()
{
	for (unsigned int ui = 0; ui < m_uiNumGroups; ++ui)
	{
		for (unsigned int ui2 = 0; ui2 < m_arrGroups[ui].m_uiNumParticles; ++ui2)
		{
			delete m_arrGroups[ui].m_arrpParticles[ui2];	// Deletes all particles in a group.
		}

		delete[] m_arrGroups[ui].m_arrpParticles;
	}
	
	delete[] m_arrGroups;	// Deletes all groups.
	m_arrGroups = 0;
	m_uiNumGroups = 0;

	delete m_pParticleInterface;
	m_pParticleInterface = 0;
}

/**
*
* Initialises the particle manager.
*
* @author Jade Abbott
* @return True if initialisation was successful.
*
*/
bool
CParticleManager::Initialise(CD3DRenderer* _pRenderer,
							 DWORD _FvfCaps,
							 unsigned int _uiMaxParticles)
{
	Shutdown();
	
	assert(_pRenderer);
	m_pRenderer = _pRenderer;

	m_pDeviceManager = &_pRenderer->GetDeviceManager();

	if (_FvfCaps & D3DFVFCAPS_PSIZE)
	{
		// Particle size is supported.
		m_ucFlags = m_ucFlags | FLG_SUPPORTS_PSIZE;
	}
	
	m_pDeviceManager->SetRenderState(D3DRS_POINTSCALE_A, *reinterpret_cast<DWORD*>(&m_fPointScaleConstant));
	m_pDeviceManager->SetRenderState(D3DRS_POINTSCALE_B, *reinterpret_cast<DWORD*>(&m_fPointScaleLinear));
	m_pDeviceManager->SetRenderState(D3DRS_POINTSCALE_C, *reinterpret_cast<DWORD*>(&m_fPointScaleQuadratic));

	m_pParticleInterface = new CParticleInterface(*this);
	if (!m_pParticleInterface)
		return false;
	
	if (!m_pParticleInterface->Initialise(_pRenderer->GetTextureManager()))
		return false;

	// Set up dynamic vertex buffer, if it hasn't been already.
	if (m_uiVertexBufferID == Utility::INVALID_ID)
	{
		// Create vertex buffer for particles.
		CVertex1Textured* pVertices = new CVertex1Textured[_uiMaxParticles];
		if (!pVertices)
			return false;

		m_uiVertexBufferSize = _uiMaxParticles;

		ZeroMemory(pVertices, sizeof(CVertex1Textured) * _uiMaxParticles);

		// Create static buffer to hold particles on device.
		D3DMATERIAL9 particleMaterial;
		particleMaterial.Ambient.a = 1.0f;
		particleMaterial.Ambient.r = 1.0f;
		particleMaterial.Ambient.g = 1.0f;
		particleMaterial.Ambient.b = 1.0f;
		particleMaterial.Diffuse.a = 1.0f;
		particleMaterial.Diffuse.r = 1.0f;
		particleMaterial.Diffuse.g = 1.0f;
		particleMaterial.Diffuse.b = 1.0f;
		particleMaterial.Emissive.a = 1.0f;
		particleMaterial.Emissive.r = 0.0f;
		particleMaterial.Emissive.g = 0.0f;
		particleMaterial.Emissive.b = 0.0f;
		particleMaterial.Specular.a = 1.0f;
		particleMaterial.Specular.r = 1.0f;
		particleMaterial.Specular.g = 1.0f;
		particleMaterial.Specular.b = 1.0f;
		particleMaterial.Power = 5.0f;

		m_uiVertexBufferID = _pRenderer->GetVertexBufferManager().CreateVertexBuffer(pVertices->GetFVF(),
																					D3DPT_POINTLIST,
																					_uiMaxParticles,
																					0,
																					sizeof(CVertex1Textured),
																					pVertices,
																					0,
																					D3DFMT_UNKNOWN,	// No indices.
																					particleMaterial,
																					true);
	}

	return m_uiVertexBufferID != Utility::INVALID_ID;
}

/**
*
* Processes every particle in the game.
*
* @author Jade Abbott
* @param _fDeltaTick The time since the last process.
* @return Void.
*
*/
void
CParticleManager::Process(float _fDeltaTick)
{
	for (unsigned int uiGroup = 0; uiGroup < m_uiNumGroups; ++uiGroup)	// For every group...
	{
		TParticleGroup& rParticleGroup = m_arrGroups[uiGroup];

		if (rParticleGroup.m_iTextureID != Utility::INVALID_ID)	// If this group is valid...
		{
			for (unsigned int uiParticle = 0; uiParticle < rParticleGroup.m_uiNumParticles; ++uiParticle)	// For every particle...
			{
				CParticle*& rpParticle = rParticleGroup.m_arrpParticles[uiParticle];

				if (rpParticle)	// If this particle is valid...
				{
					if (rpParticle->Process(_fDeltaTick))	// If this particle needs to be destroyed...
					{
						delete rpParticle;
						rpParticle = 0;
					}
				}
			}
		}
	}
}

/**
*
* Draws every particle in the game.
*
* @author Jade Abbott
* @param _pkVecCameraPosition If valid, alpha ordering is performed on the particles, using the vector provided as the camera's position.
* @return Void.
*
*/
void
CParticleManager::Draw(const D3DXVECTOR3* _pkVecCameraPosition)
{
	// Verify information.
	assert(m_pRenderer);
	assert(m_pDeviceManager);

	if (!m_uiNumGroups || !m_uiVertexBufferSize || m_uiVertexBufferID == Utility::INVALID_ID)	// If there are no particles, or there is no buffer...
		return;

	assert(m_arrGroups);	// Should be valid if m_uiNumGroups is non-zero.

	CTextureManager& rTextureManager = m_pRenderer->GetTextureManager();

	// Set the information on the device.
	if (!(m_ucFlags & FLG_MAPENTIRETEXTURE))
	{
		m_ucFlags = m_ucFlags | FLG_MAPENTIRETEXTURE;
		m_pDeviceManager->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	}

	if (!(m_ucFlags & FLG_SCALEBYDISTANCE))
	{
		m_ucFlags = m_ucFlags | FLG_SCALEBYDISTANCE;
		m_pDeviceManager->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	}

	m_pDeviceManager->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDeviceManager->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pDeviceManager->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDeviceManager->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	// Set world matrix to identity.
	m_pRenderer->SetWorldMatrix(&CWorldMatrix());	// Initialises to identity.

	// Copy particles in RAM to static buffer.
	CVertexBufferManager& rVertexBufferManager = m_pRenderer->GetVertexBufferManager();
	CVertexBuffer* pBuffer = rVertexBufferManager.GetVertexBuffer(m_uiVertexBufferID);
	assert(pBuffer);
	assert(pBuffer->IsVerticesDynamic());

	CVertex1Textured* pVertices = reinterpret_cast<CVertex1Textured*>(pBuffer->GetDynamicVertices());
	assert(pVertices);

	for (unsigned int uiGroup = 0; uiGroup < m_uiNumGroups; ++uiGroup)	// For every group...
	{
		TParticleGroup& rParticleGroup = m_arrGroups[uiGroup];

		if (rParticleGroup.m_iTextureID != Utility::INVALID_ID && rParticleGroup.m_uiNumParticles)	// If this group is valid...
		{
			unsigned int uiValidVertices = 0;	// Used to measure how many vertices have been populated in the vertex buffer.

			// Perform alpha ordering if necessary.
			if (_pkVecCameraPosition)	// If there is alpha ordering...
			{
				std::priority_queue<TFunctorAlphaComp, std::vector<TFunctorAlphaComp>, TFunctorAlphaComp> priqueOrder;

				for (unsigned int uiParticle = 0; uiParticle < rParticleGroup.m_uiNumParticles; ++uiParticle)
				{
					if (rParticleGroup.m_arrpParticles[uiParticle])
					{
						const D3DXVECTOR3& rkVecPos = rParticleGroup.m_arrpParticles[uiParticle]->GetPosition();
						priqueOrder.push(TFunctorAlphaComp(D3DXVec3LengthSq(&(rkVecPos - *_pkVecCameraPosition)), &rkVecPos));
					}
				}

				size_t uiSize = priqueOrder.size();
				while (uiValidVertices < m_uiVertexBufferSize && uiSize)
				{
					pVertices[uiValidVertices++].SetPos(*priqueOrder.top().m_pkVecPos);
					priqueOrder.pop();
					--uiSize;
				}
			}
			else	// Render without alpha ordering...
			{
				for (unsigned int uiParticle = 0; uiParticle < rParticleGroup.m_uiNumParticles; ++uiParticle)	// For every particle...
				{
					if (rParticleGroup.m_arrpParticles[uiParticle])	// If this particle is valid...
					{
						assert(uiValidVertices < m_uiVertexBufferSize);	// Should have stopped adding when the cap was hit.
						pVertices[uiValidVertices++].SetPos(rParticleGroup.m_arrpParticles[uiParticle]->GetPosition());	// Add particle to the vertex buffer.

						if (uiValidVertices >= m_uiVertexBufferSize)	// If this was the last available slot in the vertex buffer...
							break;	// Stop populating the vertex buffer.
					}
				}
			}

			if (!uiValidVertices)
				continue;	// No live particles in this group.

			pBuffer->UpdateDynamicVertices(uiValidVertices);	// Will update only the modified vertices.

			rTextureManager.SetTexture(rParticleGroup.m_iTextureID);	// Set the texture on the device.
			m_pDeviceManager->SetRenderState(D3DRS_POINTSIZE, rParticleGroup.m_dwFloatPointSize);

			rVertexBufferManager.Render(*pBuffer, uiValidVertices);	// Draw all valid particles.
		}
	}
	
	// Clean up.
	m_pDeviceManager->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	m_ucFlags = m_ucFlags ^ FLG_MAPENTIRETEXTURE;

	m_pDeviceManager->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	m_ucFlags = m_ucFlags ^ FLG_SCALEBYDISTANCE;
}

/**
*
* @author Jade Abbott
*
*/
bool
CParticleManager::IsParticleResizingSupported() const
{
	return !!(m_ucFlags & FLG_SUPPORTS_PSIZE);
}

/**
*
* @author Jade Abbott
*
*/
bool
CParticleManager::IsEntireTextureBeingMapped() const
{
	return !!(m_ucFlags & FLG_MAPENTIRETEXTURE);
}

/**
*
* @author Jade Abbott
*
*/
bool
CParticleManager::IsParticleScaledByDistance() const
{
	return !!(m_ucFlags & FLG_SCALEBYDISTANCE);
}

/**
*
* Creates a particle group (for particles using the same texture).
* Returns an unsigned int to use for accessing the group (is used as an ID).
* Returns Utility::INVALID_ID if the group could not be created.
* Note: Groups should only be created at initialisation, as 
*
* @author Jade Abbott
* @param Texture ID for the Texture Manager (the texture used to represent this group of particles).
* @return ID for accessing the group, is Utility::INVALID_ID if the group could not be created.
*
*/
unsigned int
CParticleManager::AddGroup(int _iTextureID, float _fImageScale)
{
	TParticleGroup* arrGroups = new TParticleGroup[m_uiNumGroups + 1];
	if (!arrGroups)
		return Utility::INVALID_ID;

	memcpy(arrGroups, m_arrGroups, sizeof(TParticleGroup) * m_uiNumGroups);
	arrGroups[m_uiNumGroups].m_iTextureID = _iTextureID;
	arrGroups[m_uiNumGroups].m_arrpParticles = 0;
	arrGroups[m_uiNumGroups].m_uiNumParticles = 0;
	arrGroups[m_uiNumGroups].m_dwFloatPointSize = *reinterpret_cast<DWORD*>(&_fImageScale);

	delete[] m_arrGroups;
	m_arrGroups = arrGroups;
	++m_uiNumGroups;

	return m_uiNumGroups - 1;
}

/**
*
* Inserts the provided particle pointer into the particle pointer array.
*
* @author Jade Abbott
* @param The particle group which the particle will be added to.
* @param Pointer to the particle to add to the array (must be freestore allocation).
* @return Void, the particle is owned by the particle manager, so what happens to it should not interest the caller.
*
*/
void
CParticleManager::AddParticle(unsigned int _uiGroup, CParticle* _pParticle)
{
	if (!_pParticle)
		return;

	if (_uiGroup >= m_uiNumGroups)	// Also covers Utility::INVALID_ID
	{
		delete _pParticle;
		return;
	}

	TParticleGroup& rParticleGroup = m_arrGroups[_uiGroup];

	if (rParticleGroup.m_iTextureID == Utility::INVALID_ID)	// If this group is invalid...
	{
		delete _pParticle;
		return;
	}

	// Find a free slot in the array to place the particle.
	for (unsigned int ui = 0; ui < rParticleGroup.m_uiNumParticles; ++ui)
	{
		if (!rParticleGroup.m_arrpParticles[ui])	// If this slot is free...
		{
			rParticleGroup.m_arrpParticles[ui] = _pParticle;
			return;
		}
	}

	// Else there is not enough room in array.
	unsigned int uiFreeSlot = rParticleGroup.m_uiNumParticles;	// Will increase buffer size by at least one, so the next slot will be free.
	if (!IncreaseParticleBufferSize(_uiGroup))	// If resizing was unsuccessful...
	{
		delete _pParticle;
	}
	else
	{
		rParticleGroup.m_arrpParticles[uiFreeSlot] = _pParticle;
	}
	// EOF!
}

/**
*
* Removes all particles from the game.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CParticleManager::DeleteAllParticles()
{
	for (unsigned int uiGroup = 0; uiGroup < m_uiNumGroups; ++uiGroup)
	{
		TParticleGroup& rParticleGroup = m_arrGroups[uiGroup];

		for (unsigned int uiParticle = 0; uiParticle < rParticleGroup.m_uiNumParticles; ++uiParticle)
		{
			delete rParticleGroup.m_arrpParticles[uiParticle];
			rParticleGroup.m_arrpParticles[uiParticle] = 0;
		}
		rParticleGroup.m_uiNumParticles = 0;
	}
}

/**
*
* Increases the size of the particle array,
* allowing for more particles (this does not affect the static buffer size (number of particles that can be rendered at once)).
*
* @author Jade Abbott
* @param The buffer whose size will be increased.
* @return True if the resize was successful.
*
*/
bool
CParticleManager::IncreaseParticleBufferSize(unsigned int _uiGroup)
{
	assert(_uiGroup < m_uiNumGroups);

	TParticleGroup& rParticleGroup = m_arrGroups[_uiGroup];
	const unsigned int kuiNumNewParticles = rParticleGroup.m_uiNumParticles + 10;
	CParticle** ppTempArray = new CParticle*[kuiNumNewParticles];
	if (!ppTempArray)
		return false;

	// Copy pointers into new array.
	memcpy(ppTempArray, rParticleGroup.m_arrpParticles, sizeof(CParticle*) * rParticleGroup.m_uiNumParticles);

	// Set new (remaining) pointers to null.
	ZeroMemory(&ppTempArray[rParticleGroup.m_uiNumParticles], sizeof(CParticle*) * (kuiNumNewParticles - rParticleGroup.m_uiNumParticles));

	delete[] rParticleGroup.m_arrpParticles;	// Delete old array.
	rParticleGroup.m_arrpParticles = ppTempArray;	// Point to new array.
	rParticleGroup.m_uiNumParticles = kuiNumNewParticles;

	return true;
}