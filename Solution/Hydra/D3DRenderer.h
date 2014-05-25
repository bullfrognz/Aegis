//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   D3DRenderer.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_D3DRENDERER_H__
#define __IGFEB11_IG500_D3DRENDERER_H__


// Library Includes
#include <d3dx9.h>
#include <vector>


// Local Includes


// Types


// Constants


// Prototypes
class CVertexBufferManager;
class CParticleManager;
class CSurfaceManager;
class CTextureManager;
class CDeviceManager;
class CSpriteManager;
class CLightManager;
class CMeshManager;
class CFogManager;
class CLogWindow;
class CWorldMatrix;
class CMatrix;
class vector;


class CD3DRenderer
{

	// Member Functions
public:


	 CD3DRenderer();
	~CD3DRenderer();


	bool Initialise(HWND _hWindoHandle, unsigned char _ucDisplayAdapter,
					unsigned int _uiMultisampleType, int _iBufferWidth,
					int _iBufferHeight,  bool _bFullscreen);


	void StartRendering(bool _bTarget, bool _bDepth, bool _bStencil);
	void EndRendering(); 


	void TakeScreenShot(wchar_t* _wcpFileName);


	void SetBackbufferDimentions(unsigned int _uiWidth, unsigned int _uiHeight);
	void SetFullscreen(bool _bFullscreen, unsigned int _uiRefreshRate);
	void SetMultisampleType(D3DMULTISAMPLE_TYPE _ed3dMultisampleType, bool _bFullscreen);


	DWORD GetMultisampleTypeLevel(D3DMULTISAMPLE_TYPE _ed3dMultisampleType, bool _bFullscreen);
	void  GetSupportedMultiSamplingTypes(std::vector<D3DMULTISAMPLE_TYPE>& _vecrMultisamplingTypes, bool _bFullscreen);
	void  GetSupportedDisplayModes(std::vector<D3DDISPLAYMODE>& _vecrDisplayModes);
	bool  IsDeviceReady();


	// Inline Functions
	inline void SetClearColour(unsigned int _uiRed, unsigned int _uiGreen, unsigned int _uiBlue); 
	inline void SetWorldMatrix(const CWorldMatrix* _kmtxpWorldMatrix);
	inline void SetViewMatrix(const CMatrix* _kmtxpViewMatrix);
	inline void SetProjectionMatrix(const CMatrix* _kmtxpProjectionMatrix);
	inline const D3DPRESENT_PARAMETERS& GetPresentParameters() const;
	inline const D3DPRESENT_PARAMETERS& GetToBePresentParameters() const;
	inline void DeviceHasBeenReset();


	inline CVertexBufferManager& GetVertexBufferManager();
	inline CParticleManager& GetParticleManager();
	inline CSurfaceManager& GetSurfaceManager();
	inline CTextureManager& GetTextureManager();
	inline CDeviceManager& GetDeviceManager();
	inline CSpriteManager& GetSpriteManager();
	inline CLightManager& GetLightManager();
	inline CMeshManager& GetMeshManager();
	inline CFogManager& GetFogManager();
	inline CLogWindow& GetLogWindow();


protected:


	void ClearBackbuffer(bool _bTarget, bool _bDepth, bool _bStencil);
	void SaveBackBufferToFile();
	void SaveMultisampleToINI();


private:


	bool InitialiseDirect3D9();
	bool InitialiseDirect3DDevice();
	bool InitialiseManagers();
	bool IntiailiseLogWindow();


	void Deinitialise();


	CD3DRenderer(const CD3DRenderer& _krD3DRenderer);
	CD3DRenderer& operator = (const CD3DRenderer& _krD3DRenderer);


	// Member Variables
protected:


private:


	D3DPRESENT_PARAMETERS m_td3dPresentParameters;
	D3DPRESENT_PARAMETERS m_td3dToBePresentParameters;


	D3DDISPLAYMODE m_td3dDisplayMode;
	D3DCAPS9 m_td3dCaps;


	D3DDEVTYPE m_ed3dDeviceType;


	IDirect3DDevice9* m_pDirect3DDevice;
	IDirect3D9* m_pDirect3D9;


	CVertexBufferManager* m_pVertexBufferManager;
	CParticleManager* m_pParticleManager;
	CSurfaceManager* m_pSurfaceManager;
	CTextureManager* m_pTextureManager;
	CDeviceManager* m_pDeviceManager;
	CSpriteManager* m_pSpriteManager;
	CLightManager* m_pLightManager;
	CMeshManager*  m_pMeshManager;
	CFogManager* m_pFogManager;
	CLogWindow*  m_pLogWindow;


	DWORD m_dwClearColor;


	unsigned char m_ucDisplayAdapter;


	wchar_t* m_wcpScreenshotFilename;


	bool m_bTakeScreenshot;
	bool m_bScreenshotFrameSkipped;
	bool m_bForceDeviceReset;


};


#include "D3DRenderer.inl"


#endif //__IGFEB11_IG500_D3DRENDERER_H__