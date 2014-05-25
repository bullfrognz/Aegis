//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   viewport.cpp
//  Description :   Viewport implementation (source) file
//  Author      :   Jamie.Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "camera.h"
#include "GameCamera.h"
#include "InputManager.h"
#include "XInputController.h"
#include "Macros.h"
#include "D3DRenderer.h"

// This Include
#include "viewport.h"

// Static Variables


// Static Function Prototypes

// Implementation

CViewport::CViewport()
: m_uiId(0)
, m_iActiveCameraID(0)
, m_iCameraIDHolder(0)
{
	ZeroMemory(&m_D3DViewPort, sizeof(D3DVIEWPORT9));
}

CViewport::~CViewport()
{
	FW_DELETEMAP(int, CCamera*, m_mapCameras);
}

/** 
*
* Initialises the viewport
* 
* @author Jamie.Smith  
* @Param1 _uiX the x position of the viewport
* @Param2 _uiY the y position of the viewport
* @Param3 _uiHeight the height position of the viewport
* @Param4 _uiWidth the width position of the viewport
* @Param5 _uiId the id of the viewport
* @Param6 _pRenderer the instance of the renderer
* @return void
*
*/
bool 
CViewport::Initialise(	unsigned int _uiX,
						unsigned int _uiY,
						unsigned int _uiWidth,
						unsigned int _uiHeight,
						unsigned int _uiId, 
						CD3DRenderer* _pRenderer)
{
	m_uiId = _uiId;

	m_D3DViewPort.X = 0;
	m_D3DViewPort.Y = 0;

	m_D3DViewPort.Width = _uiWidth;
	m_D3DViewPort.Height = _uiHeight;

	m_D3DViewPort.MinZ = 0.0f;
	m_D3DViewPort.MaxZ = 1.0f;

	//_pRenderer->GetDevice()->SetViewport(&m_D3DViewPort);

	m_pRenderer = _pRenderer; 

	return(true);
}

/** 
*
* Creates a camera
* 
* @author Jamie.Smith  
* @Param1 _fFOV the field of view of the camera
* @Param2 _eMode the mode of the camera
* @Param3 _fNearClip the near clip of the camerat
* @Param4 _fFarClip the far clip of the camera
* @Param5 _pPlayerInput the instance of the playerinput
* @return void
*
*/
int 
CViewport::CreateGameCamera(float _fFOV,						
							float _fNearClip,
							float _fFarClip,
							CDirectInput* _pDirectInput,
							CXInputController* _pXInput, 
							CTerrain* _pTerrain)
{
	m_fFOV = _fFOV;
	
	m_pTempCamera = new CGameCamera();

	dynamic_cast<CGameCamera*>(m_pTempCamera)->Initialise(this, _fFOV, (GetHeight() / 2), (GetWidth() / 2),
															_fNearClip, _fFarClip, m_pRenderer, _pDirectInput,
															_pXInput, _pTerrain);

	m_mapCameras[m_pTempCamera->GetCameraID()] = m_pTempCamera;

	int CameraID = m_pTempCamera->GetCameraID();

	m_iCameraIDHolder = CameraID;

	return(CameraID);
}

/** 
*
* Creates a camera
* 
* @author Jamie.Smith  
* @Param1 _fFOV the field of view of the camera
* @Param2 _eMode the mode of the camera
* @Param3 _fNearClip the near clip of the camerat
* @return void
*
*/
int 
CViewport::CreateCamera(float _fFOV,						
						float _fNearClip,
						float _fFarClip)
{
	m_fFOV = _fFOV;
	
	m_pTempCamera = new CCamera();

	m_pTempCamera->Initialise(this, _fFOV, (GetHeight() / 2), (GetWidth() / 2), _fNearClip, _fFarClip, m_pRenderer);

	m_mapCameras[m_pTempCamera->GetCameraID()] = m_pTempCamera;

	int CameraID = m_pTempCamera->GetCameraID();

	m_iCameraIDHolder = CameraID;

	return(CameraID);
}

/** 
*
* Processes the Viewport
* 
* @author Jamie.Smith
* @Param _fDeltaTick the delta tick
* @return void
*
*/
void 
CViewport::Process(float _fDeltaTick)
{	
	CCamera* pCamera = GetActiveCamera();
	if(pCamera)
	{
		pCamera->Process(_fDeltaTick);
	}
}


void
CViewport::Draw(CD3DRenderer* _pRenderer)
{
	CCamera* pCamera = GetActiveCamera();
	if(pCamera)
	{
		pCamera->Draw(_pRenderer);
	}
}

/** 
*
* returns the id
* 
* @author Jamie.Smith  
* @return unsigned int
*
*/
unsigned int 
CViewport::GetID() const
{
	return(m_uiId);
}

/** 
*
* returns the ViewPort
* 
* @author Jamie.Smith  
* @return D3DVIEWPORT9
*
*/
D3DVIEWPORT9* 
CViewport::GetD3DViewport()
{
	return(&m_D3DViewPort);
}

/** 
*
* returns the viewports width
* 
* @author Jamie.Smith  
* @return unsigned int
*
*/
unsigned int 
CViewport::GetWidth() const
{
	return(m_D3DViewPort.Width);
}

/** 
*
* returns the veiwports height
* 
* @author Jamie.Smith  
* @return unsigned int
*
*/
unsigned int 
CViewport::GetHeight() const
{
	return(m_D3DViewPort.Height);
}

/** 
*
* returns the feild of view
* 
* @author Jamie.Smith  
* @return float
*
*/
float
CViewport::GetFOV() const
{
	return(m_fFOV);
}

/** 
*
* returns the viewports x position
* 
* @author Jamie.Smith  
* @return unsigned int
*
*/
unsigned int 
CViewport::GetPosX() const
{
	return(m_D3DViewPort.X);
}

/** 
*
* returns the viewports y position
* 
* @author Jamie.Smith  
* @return unsigned int
*
*/
unsigned int 
CViewport::GetPosY() const
{
	return(m_D3DViewPort.Y);
}

/** 
*
* returns the camera
* 
* @author Jamie.Smith  
* @return CCamera
*
*/
CCamera* 
CViewport::GetCamera(int _iCamId)
{
	std::map<int, CCamera*>::iterator iter;
	iter = m_mapCameras.find(_iCamId);

	return (iter != m_mapCameras.end() ? iter->second : 0);
}

void
CViewport::SetActiveCamera(CCamera* _pCamera)
{
	m_iActiveCameraID = _pCamera->GetCameraID();
}

void
CViewport::SetActiveCamera(int _CameraId)
{
	m_iActiveCameraID = _CameraId;
}

CCamera* 
CViewport::GetActiveCamera()
{
	std::map<int, CCamera*>::iterator iter;
	iter = m_mapCameras.find(m_iActiveCameraID);

	return iter != m_mapCameras.end() ? iter->second : 0;
}

CCamera*
CViewport::GetLastCreatedCamera()
{
	std::map<int, CCamera*>::iterator iter;
	iter = m_mapCameras.find(m_iCameraIDHolder);

	return(iter->second);
}



