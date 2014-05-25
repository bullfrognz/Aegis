//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   DeviceManager.h
//  Description :   Manages the direct 3d device by added extra functionality for clients
//					and increasing performance by preventing duplicate device set calls.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_DEVICEMANAGAER_H__
#define __IGFEB11_IG500_DEVICEMANAGAER_H__


// Library Includes
#include <d3dx9.h>


// Local Includes
#include "DeviceResetTarget.h"


// Types


// Constants
#define DEFAULTSTATE				800
#define D3D_MAXRENDERSTATES			D3DRS_BLENDOPALPHA
#define D3D_MAXSTAGES				8
#define D3D_MAXSAMPLERSTAGESTATES	D3DSAMP_DMAPOFFSET 
#define D3D_MAXTEXTURESTAGESTATES	D3DTSS_CONSTANT
#define D3D_MAXTRANSFORMSTATES		512


// Prototypes
class CMatrix;
class IMesh;
class CD3DRenderer;


class CDeviceManager : public CDeviceResetTarget
{

	// Member Functions
public:


	 CDeviceManager();
	~CDeviceManager();


	bool Initialise(IDirect3DDevice9* _pDirect3DDevice, const D3DCAPS9& _kd3drDeviceCaps);

	void EndRenderering();


	void DeviceClear(bool _bTarget, bool _bDepth, bool _bStencil, D3DCOLOR _d3dColor, float _fZDepth, DWORD _dwStencil);


	void ScheduleDeviceReset();


	void ExecuteResetDevice();


	ID3DXFont* CreateFont(D3DXFONT_DESC& _d3drFontDesc, ID3DXFont*& _d3dxprFont);


	// Device set functions
	void ResetTextureStageStates(DWORD _dwStage);


	void SetRenderTarget(IDirect3DSurface9* _d3dpRenderTarget);
	void RestoreDefaultRenderTarget();


	void SetDepthStencilSurface(IDirect3DSurface9* _d3dpNewZStencil);
	void RestoreDefaultDepthStencilSurface();


	void SetStageTexture(DWORD _dwStage, IDirect3DBaseTexture9* _d3dpTexture);
	void SetTextureStageState(DWORD _dwStage, D3DTEXTURESTAGESTATETYPE _ed3dTextureStageStateType, DWORD _dwValue);
	void SetRenderState(D3DRENDERSTATETYPE _ed3dRenderStateType, DWORD _dwValue);
	void SetSamplerState(DWORD _dwSampler, D3DSAMPLERSTATETYPE _ed3dSamplerStateType, DWORD _dwValue);
	void SetTransform(D3DTRANSFORMSTATETYPE _ed3dTransformStateType, const CMatrix* _kmtxpTransformMatrix);


	void SetIndices(IDirect3DIndexBuffer9* _d3dpIndexBuffer);
	void SetStreamSource(IDirect3DVertexBuffer9* _d3dpVertexBuffer, unsigned int _uiStride);
	void SetFVF(unsigned long _ulFVF);


	void DrawIndexedPrimitive(D3DPRIMITIVETYPE _ed3dPrimitiveType, unsigned int _uiNumVertices, unsigned int _uiPrimitiveCount);
	void DrawPrimitive(D3DPRIMITIVETYPE _ed3dPrimitiveType, unsigned int _uiPrimitiveCount);
	void DrawPrimitiveUP(D3DPRIMITIVETYPE _d3dePrimitiveType,
						 unsigned int _uiPrimitiveCount,
						 const void* _kpVertexStream,
						 unsigned int _uiVertexStride);

	void SetLight(unsigned int _uiLightId, const D3DLIGHT9* _kd3dpLight9);
	void SetLightEnabled(unsigned int _uiLightId, bool _bEnable);


	void SetMaterial(const D3DMATERIAL9* _kmatpMaterial);


	// Inline Functions
	inline const CMatrix* GetViewMatrix() const;
	inline const CMatrix* GetProjectionMatrix() const;
	inline HRESULT CreateLine(LPD3DXLINE* _ppLine);


	inline DWORD GetRenderStateValue(D3DRENDERSTATETYPE _ed3dRenderStateType);
	inline DWORD GetTextureStageStateValue(DWORD _dwStage, D3DTEXTURESTAGESTATETYPE _ed3dTextureStageStateType);
	inline DWORD GetSamplerStageStateValue(DWORD _dwSampler, D3DSAMPLERSTATETYPE _ed3dSamplerStateType);


	inline D3DMATERIAL9& GetDefaultMaterial();


protected:


	bool InitialiseDefaultMaterial();


	void RestoreRenderStates();
	void RestoreStageStates();
	void RestoreSamplerStates();


	virtual void OnDeviceLost();
	virtual void OnDeviceReset();


private:


	void Deinitialise();


	CDeviceManager(const CDeviceManager& _krScene);
	CDeviceManager& operator = (const CDeviceManager& _krScene);


	// Member Variables
protected:


private:


	D3DCAPS9 m_d3dDeviceCaps;
	D3DMATERIAL9 m_matDefaultMaterial;


	IDirect3DDevice9* m_pDirect3DDevice;


		  IDirect3DSurface9* m_pDefaultRenderTarget;
		  IDirect3DSurface9* m_pDefaultZStencilSurface;	
	const IDirect3DSurface9* m_kpRenderTarget;
	const IDirect3DSurface9* m_kpZStencil;

	const IDirect3DBaseTexture9*  m_kpStageTexture[D3D_MAXSTAGES];
	const IDirect3DIndexBuffer9*  m_kd3dpIndexBuffer;
	const IDirect3DVertexBuffer9* m_kd3dpVertexBuffer;
	const CMatrix*		m_kmtxpTransformMatrix[D3D_MAXTRANSFORMSTATES];	// TODO: Clear world matrix at end of rendering.
	const D3DMATERIAL9* m_kmatpMaterial;


	DWORD m_dwRenderStates[D3D_MAXRENDERSTATES];
	DWORD m_dwTextureStageStates[D3D_MAXSTAGES][D3D_MAXTEXTURESTAGESTATES];
	DWORD m_dwSamplerStageStates[D3D_MAXSTAGES][D3D_MAXSAMPLERSTAGESTATES];


	unsigned long m_ulFvF;


	bool m_bDeviceResetScheduled;


};


#include "Inline/DeviceManager.inl"


#endif //__IGFEB11_IG500_DEVICEMANAGAER_H__