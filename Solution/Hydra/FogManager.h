//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	FogManager.h
//	Description	:	Declaration of CFogManager
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __FOGMANAGER_H__
#define __FOGMANAGER_H__

// Library includes.
#include <d3dx9.h>

// Local includes.
#include "DeviceManager.h"

class CFogManager
{
	// Member functions.
public:
	CFogManager();
	~CFogManager();

	bool Initialise(CDeviceManager* _pDeviceManager, DWORD _dwRasterCaps);

	bool IsVertexFogSupported() const;
	bool IsPixelFogSupported() const;
	bool IsRangedFogSupported() const;

	void SetFogColour(DWORD _dwColour);

	void EnableFog(bool _bEnabled);
	bool IsFogEnabled() const;

	void EnableRangedFog(bool _bEnabled);
	bool IsRangedFogEnabled() const;

	inline void SetFogStart(float _fStart);
	inline void SetFogEnd(float _fEnd);

	inline void SetFogDensity(float _fDensity);

	void SetVertexFogMode(D3DFOGMODE _eFogMode);
	void SetPixelFogMode(D3DFOGMODE _eFogMode);

protected:

private:

	// Member data.
public:

protected:
	CDeviceManager* m_pDeviceManager;

	unsigned char m_ucFlags;

private:
};

#endif	// __FOGMANAGER_H__