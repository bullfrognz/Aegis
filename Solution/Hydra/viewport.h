//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   viewport.h
//  Description :   Viewport declaration (header) file
//  Author      :   Jamie Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_VIEWPORT_H__
#define __IGFEB11_VIEWPORT_H__


// Library Includes
#include <map>

// Local Includes
#include "Utility.h"
#include "enemy.h"
#include "terrain.h"

// Types

// Constants

typedef enum TEIgShadeMode 
{
	INVALID_IGSM, 
	IGSM_FLAT, 
	IGSM_GOURAUD, 
	IGSM_PHONG, 
	MAX_IGSM 

} IGShadeMode, EIgShadeMode;

// Prototypes
class CScene;
class CCamera;
class CGameCamera;
class CRunThroughCamera;
class CD3DRenderer;
class CXInputController;
class CDirectInput;

class CViewport
{
	// Member Functions
	public:
		CViewport();
		~CViewport();

		bool Initialise(unsigned int _uiX,
								unsigned int _uiY,
								unsigned int _uiWidth,
								unsigned int _uiHeight,
								unsigned int _uiId, 
								CD3DRenderer* _pRenderer);

		int CreateGameCamera(float _fFOV,
									float _fNearClip,
									float _fFarClip,
									CDirectInput* _pDirectInput,
									CXInputController* _pXInput, 
									CTerrain* _pTerrain);

		int CreateCamera(float _fFOV,
									float _fNearClip,
									float _fFarClip);


		void Process(float _fDeltaTick);

		void Draw(CD3DRenderer* _pRenderer);

		unsigned int GetID() const;

		D3DVIEWPORT9* GetD3DViewport();

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		float GetFOV() const;

		unsigned int GetPosX() const;
		unsigned int GetPosY() const;

		CCamera* GetCamera(int _iCamId);

		CCamera* GetLastCreatedCamera();

		void SetActiveCamera(CCamera* _pCamera);
		void SetActiveCamera(int _CameraId);
		CCamera* GetActiveCamera();

	protected:

	private:

	// Member Variables
	public:

	protected:
		unsigned int m_uiId;

		int m_iActiveCameraID;
		
		float m_fFOV;

		std::map<int, CCamera*> m_mapCameras;

		CCamera* m_pTempCamera;

		CD3DRenderer* m_pRenderer;

		D3DVIEWPORT9 m_D3DViewPort;

		int m_iCameraIDHolder;

	private:

};

#endif // __IGFEB11_VIEWPORT_H__

