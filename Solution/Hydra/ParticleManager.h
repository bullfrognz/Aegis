//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	ParticleManager.h
//	Description	:	Declaration of CParticleManager
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef	__PARTICLEMANAGER_H__
#define __PARTICLEMANAGER_H__

// Library includes.
#include <d3dx9.h>

// Local includes.
class CDeviceManager;
class CD3DRenderer;
class CParticle;
class CParticleInterface;

struct TParticleGroup
{
	int m_iTextureID;
	CParticle** m_arrpParticles;
	unsigned int m_uiNumParticles;

	DWORD m_dwFloatPointSize;	// Float in DWORD form so it can be jammed into the renderer easily.
};

class CParticleManager
{
	// Member functions.
public:
	CParticleManager();
	~CParticleManager();

	void Shutdown();

	bool Initialise(CD3DRenderer* _pRenderer,
					DWORD _FvfCaps,
					unsigned int _uiMaxParticles);

	void Process(float _fDeltaTick);
	void Draw(const D3DXVECTOR3* _pkVecCameraPosition = 0);

	bool IsParticleResizingSupported() const;
	bool IsEntireTextureBeingMapped() const;
	bool IsParticleScaledByDistance() const;

	unsigned int AddGroup(int _iTextureID, float _fImageScale = 0.2f);
	void AddParticle(unsigned int _uiGroup, CParticle* _pParticle);
	inline unsigned int GetNumParticles(unsigned int _uiGroup);

	void DeleteAllParticles();

	inline CParticleInterface& GetParticleInterface();

protected:
	bool IncreaseParticleBufferSize(unsigned int _uiGroup);

private:

	// Member data.
public:

protected:
	CD3DRenderer* m_pRenderer;
	CDeviceManager* m_pDeviceManager;

	CParticleInterface* m_pParticleInterface;

	TParticleGroup* m_arrGroups;
	unsigned int m_uiNumGroups;

	unsigned int m_uiVertexBufferSize;
	unsigned int m_uiVertexBufferID;

	float m_fPointScaleConstant;
	float m_fPointScaleLinear;
	float m_fPointScaleQuadratic;

	unsigned char m_ucFlags;

private:
};

#include "ParticleManager.inl"

#endif	// __PARTICLEMANAGER_H__