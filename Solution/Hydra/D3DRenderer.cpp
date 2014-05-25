//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   D3DRenderer.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "StrUtilities.h"
#include "Macros.h"
#include "INIParser.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "ParticleManager.h"
#include "SurfaceManager.h"
#include "VertexBufferManager.h"
#include "FogManager.h"
#include "LogWindow.h"
#include "SpriteManager.h"
#include "LightManager.h"


// This Include
#include "D3DRenderer.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* D3DRenderer class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD3DRenderer::CD3DRenderer()
: m_ed3dDeviceType(D3DDEVTYPE_NULLREF)
, m_pDirect3DDevice(0)
, m_pDirect3D9(0)
, m_pVertexBufferManager(0)
, m_pParticleManager(0)
, m_pSurfaceManager(0)
, m_pTextureManager(0)
, m_pDeviceManager(0)
, m_pSpriteManager(0)
, m_pLightManager(0)
, m_pMeshManager(0)
, m_pFogManager(0)
, m_pLogWindow(0)
, m_dwClearColor(0)
, m_ucDisplayAdapter(0)
, m_wcpScreenshotFilename(0)
, m_bTakeScreenshot(false)
, m_bScreenshotFrameSkipped(false)
, m_bForceDeviceReset(true)
{
	//Clean memory
	ZeroMemory(&m_td3dPresentParameters, sizeof(D3DPRESENT_PARAMETERS));
	ZeroMemory(&m_td3dToBePresentParameters, sizeof(D3DPRESENT_PARAMETERS));
	ZeroMemory(&m_td3dDisplayMode, sizeof(D3DDISPLAYMODE));
	ZeroMemory(&m_td3dCaps, sizeof(D3DCAPS9));
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* D3DRendererclass deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD3DRenderer::~CD3DRenderer()
{
	Deinitialise();
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialisings the class instance before use.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CD3DRenderer::Initialise(HWND _hWindoHandle, unsigned char _ucDisplayAdapter,
						 unsigned int _uiMultisampleType, int _iBufferWidth,
						 int _iBufferHeight,  bool _bFullscreen)
{
	//Set member variables
	m_ucDisplayAdapter = _ucDisplayAdapter;
	m_ed3dDeviceType = D3DDEVTYPE_HAL;
	m_td3dPresentParameters.hDeviceWindow = _hWindoHandle;
	m_td3dPresentParameters.BackBufferWidth = _iBufferWidth;
	m_td3dPresentParameters.BackBufferHeight = _iBufferHeight;
	m_td3dPresentParameters.Windowed = (_bFullscreen == false);


	//Initialise direct 3d
	FW_VALIDATE(InitialiseDirect3D9(), "Renderer Direct 3d 9 interface initialise failed.");


	//Set member variables
	m_td3dPresentParameters.MultiSampleType = static_cast<D3DMULTISAMPLE_TYPE>(_uiMultisampleType);
	m_td3dPresentParameters.MultiSampleQuality = GetMultisampleTypeLevel(static_cast<D3DMULTISAMPLE_TYPE>(_uiMultisampleType), _bFullscreen);


	//Run initialise functions
	FW_VALIDATE(InitialiseDirect3DDevice(), "Renderer Direct 3d device initialise failed.");
	FW_VALIDATE(InitialiseManagers(), "Renderer managers initialise failed.");
	FW_VALIDATE(IntiailiseLogWindow(), "Renderer Log window inititialise failed.");


	//Copy final present parameters
	m_td3dToBePresentParameters = m_td3dPresentParameters;


	//Return successful
	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Gets the backbuffer ready to be renderered on.
*
* @author Bryce Booth
* @param _bTarget	To clear target.
* @param _bDepth	To clear depth.
* @param _bStencil	To clear stencil.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::StartRendering(bool _bTarget, bool _bDepth, bool _bStencil)
{
	//Clear back buffer
	m_pDeviceManager->DeviceClear(_bTarget, _bDepth, _bStencil, m_dwClearColor, 1.0f, 0);


	//Begin device scene 
	m_pDirect3DDevice->BeginScene();
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Runs functionality to finish renderering and present the final back buffer to the user.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::EndRendering()
{
	//End the scene on the device
	m_pDirect3DDevice->EndScene();


	//Check if renderer is set to take screenshot
	if (m_bTakeScreenshot == true)
	{
		//Check if a frame has been skipped
		if (m_bScreenshotFrameSkipped == true)
		{
			SaveBackBufferToFile();
		}
		else
		{
			m_bScreenshotFrameSkipped = true;
		}
	}


	//Present backbuffer to user
	m_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);


	//Tell device manager the renderering has finished
	m_pDeviceManager->EndRenderering();
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the renderer to save the next presented back buffer to file.
*
* @author Bryce Booth
* @param _wcpFileName	The file name that will be given to the image file.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::TakeScreenShot(wchar_t* _wcpFileName)
{
	//Set renderer to take screenshot
	m_bTakeScreenshot = true;


	//Set renderer to skip a frame before taking the screenshot
	m_bScreenshotFrameSkipped = false;


	//Copy screnshot file name
	StrUtilities::Copy(_wcpFileName, m_wcpScreenshotFilename);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the width and height of the back buffer after next reset.
*
* @author Bryce Booth
* @param _uiWidth	New width of back buffer.
* @param _uiHeight	New height of back buffer.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::SetBackbufferDimentions(unsigned int _uiWidth, unsigned int _uiHeight)
{
	//Set parameters
	m_td3dToBePresentParameters.BackBufferWidth  = _uiWidth;
	m_td3dToBePresentParameters.BackBufferHeight = _uiHeight;
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets fullscreen or window mode for the renderer on next reset
*
* @author Bryce Booth
* @param _bFullscreen		If the window will be fullscreen.
* @param _uiRefreshRate		The refreshrate of renderer if in fullscreen mode.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::SetFullscreen(bool _bFullscreen, unsigned int _uiRefreshRate)
{
	//Set parameters
	m_td3dToBePresentParameters.Windowed = (_bFullscreen == false);
	m_td3dToBePresentParameters.FullScreen_RefreshRateInHz = (_bFullscreen == true) ? _uiRefreshRate : 0;
	m_td3dToBePresentParameters.PresentationInterval = (_bFullscreen == true)? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the multisample type for the renderer on next reset.
*
* @author Bryce Booth
* @param _ed3dMultisampleType	Multisample type to be set.
* @param _bFullscreen			If the window will be fullscreen.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::SetMultisampleType(D3DMULTISAMPLE_TYPE _ed3dMultisampleType, bool _bFullscreen)
{
	//Default varaibles
	HRESULT hResult = S_OK;
	DWORD dwQualityLevel = 0;


	//Get supported multi sample level for type
	dwQualityLevel = GetMultisampleTypeLevel(_ed3dMultisampleType, _bFullscreen);


	//Check multisample type is valid
	LOG_FATALERROR(dwQualityLevel == -1, "Invalid mulisample type.");


	//Set parameters
	if (dwQualityLevel != -1)
	{
		m_td3dToBePresentParameters.MultiSampleType = _ed3dMultisampleType;
		m_td3dToBePresentParameters.MultiSampleQuality = dwQualityLevel;


		SaveMultisampleToINI();
	}
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Gets the highest supported level for multisample type or returns -1 if not supported.
*
* @author Bryce Booth
* @param _ed3dMultisampleType	Multisample type to query for.
* @param _bFullscreen			If the window will be fullscreen.
*
*---------------------------------------------------------------------------------------------------------------------------*/

DWORD
CD3DRenderer::GetMultisampleTypeLevel(D3DMULTISAMPLE_TYPE _ed3dMultisampleType, bool _bFullscreen)
{
	//Default variables
	DWORD dwSupportedLevel = -1;
	HRESULT hResult = S_OK;


	//Check multisample type
	hResult = m_pDirect3D9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
													   m_ed3dDeviceType, 
													   D3DFMT_X8R8G8B8, 
												       !_bFullscreen, 
												       _ed3dMultisampleType,
													   &dwSupportedLevel);

	//Return supported level
	return (dwSupportedLevel - 1);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Scans the adapter for all supported multi sampling types.
*
* @author Bryce Booth
* @param std::vector<D3DDISPLAYMODE>&	Container of supported multisample types.
* @param _bFullscreen	If the window will be fullscreen.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::GetSupportedMultiSamplingTypes(std::vector<D3DMULTISAMPLE_TYPE>& _vecrMultisamplingTypes, bool _bFullscreen)
{
	//Default variables
	DWORD dwSupportedLevel;
	HRESULT hResult = S_OK;


	//Loop through multisample types
	for (unsigned int i = 0; i <= D3DMULTISAMPLE_16_SAMPLES; ++i)
	{
		//Check multisample type
		hResult = m_pDirect3D9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
														   m_ed3dDeviceType, 
														   D3DFMT_X8R8G8B8, 
													       !_bFullscreen, 
													       static_cast<D3DMULTISAMPLE_TYPE>(i),
														   &dwSupportedLevel);

		//Check type is supported
		if (SUCCEEDED(hResult))
		{
			//Add supported multisample type
			_vecrMultisamplingTypes.push_back(static_cast<D3DMULTISAMPLE_TYPE>(i));
		}
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Scans the adapter for all supported display modes.
*
* @author Bryce Booth
* @param std::vector<D3DDISPLAYMODE>&	Container of display mode information.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::GetSupportedDisplayModes(std::vector<D3DDISPLAYMODE>& _vecrDisplayModes)
{
	//Default variables
	D3DDISPLAYMODE ed3dDisplayMode;
	unsigned int uiNumSupportedModes = 0;


	//Get number of modes
	uiNumSupportedModes = m_pDirect3D9->GetAdapterModeCount(m_ucDisplayAdapter, D3DFMT_X8R8G8B8);


	//Loop through number of supported modes
	for (unsigned int i = 0; i < uiNumSupportedModes; ++i)
	{
		//Retrieve display mode information
		m_pDirect3D9->EnumAdapterModes(m_ucDisplayAdapter, D3DFMT_X8R8G8B8, i, &ed3dDisplayMode);


		//Add supported display mode to container
		_vecrDisplayModes.push_back(ed3dDisplayMode);
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Checks if the device is ready to be used.
*
* @author Bryce Booth
* @return bReady	If the device is ready.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CD3DRenderer::IsDeviceReady()
{
	//Set variables
	HRESULT hResult = m_pDirect3DDevice->TestCooperativeLevel();
	bool bReady = true;


	//Check if device is lost or not reset
	if(hResult == D3DERR_DEVICELOST || hResult == D3DERR_DEVICENOTRESET)
	{
		//Set ready false
		bReady = false;
	}


	//Return if ready
	return (bReady);
}







/********************************
            Protected
*********************************/



/*---------------------------------------------------------------------------------------------------------------------------
*
* Saves the back buffer to image file.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::SaveBackBufferToFile()
{
	//Default variables
	unsigned int iExtStrLength = static_cast<int>(wcslen(m_wcpScreenshotFilename)) + 5;
	wchar_t* wcpFileNameExt = new wchar_t[iExtStrLength];
	IDirect3DSurface9* pSurfaceTemp = 0;
	IDirect3DSurface9* pSurfaceBackBuffer = 0;
	unsigned int uiSurfaceId = 0;


	//Add extension to map file
	swprintf_s(wcpFileNameExt, iExtStrLength, L"%spng", m_wcpScreenshotFilename);


	//Create surface
	uiSurfaceId = m_pSurfaceManager->CreatePlainSurface(512, 512, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT);


	//Get surface interface
	pSurfaceTemp = m_pSurfaceManager->GetSurface(uiSurfaceId);


	//Get back buffer surface
	m_pDirect3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &(pSurfaceBackBuffer));


	//Loaded surface 
	D3DXLoadSurfaceFromSurface(pSurfaceTemp, 0, 0, pSurfaceBackBuffer, 0, 0, D3DX_FILTER_TRIANGLE, 0);


	//Save surface to file
	D3DXSaveSurfaceToFile(wcpFileNameExt, D3DXIFF_PNG, pSurfaceTemp, NULL, NULL);


	//Destroy temp surface
	m_pSurfaceManager->DestroySurface(uiSurfaceId);


	//Destory buffer surface
	FW_RELEASE(pSurfaceBackBuffer);


	//Set take screenshot to false
	m_bTakeScreenshot = false;


	//Set frame skipped to true
	m_bScreenshotFrameSkipped = false;


	//Delete screenshot filename
	FW_ADELETE(m_wcpScreenshotFilename);
	FW_ADELETE(wcpFileNameExt);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Saves the current set multisample type to ini file.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::SaveMultisampleToINI()
{
	//convert multisample type to char
	char* cpBuffer = new char[128];
	sprintf_s(cpBuffer, 128, "%d", static_cast<int>(m_td3dToBePresentParameters.MultiSampleType));


	//Instance ini parser
	CINIParser RendererINI;


	//Loaded engine ini file
	RendererINI.LoadINIFile("Ini Files/Engine.ini");


	//Edit multisample type value
	RendererINI.AddValue("Renderer", "MultisampleType", cpBuffer);


	//Save changes
	RendererINI.SaveINIFile("Ini Files/Engine.ini");


	//Clean up
	FW_DELETE(cpBuffer);
}









/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Created direct 3d interface and gathers display mode and device caps information.
*
* @author Bryce Booth
* @return true	States the direct 3d9 interface was created.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CD3DRenderer::InitialiseDirect3D9()
{
	//Get direct 3d interface
	m_pDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);


	//Get adapter display mode
	FW_HVALIDATE(m_pDirect3D9->GetAdapterDisplayMode(m_ucDisplayAdapter, &m_td3dDisplayMode),
				 "Could not get display mode. Check that the display adapter setting is correct.");


	//Get adapter device caps
	FW_HVALIDATE(m_pDirect3D9->GetDeviceCaps(m_ucDisplayAdapter, m_ed3dDeviceType, &m_td3dCaps), 
				 "Could not get direct 3d caps. Check that the display adapter setting is correct.");


	//Return successful
	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates direct 3d device interface to be used to render the game.
*
* @author Bryce Booth
* @return bDeviceCreated	States if the device was created.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CD3DRenderer::InitialiseDirect3DDevice()
{	
	//Default variables
	HRESULT hResult = S_OK;
	DWORD dwVertProcessing = 0;
	bool bDeviceCreated = false;


	//Check if fullscreen
	if (m_td3dPresentParameters.Windowed == false)
	{
		//Set fullscreen parameters
		m_td3dPresentParameters.FullScreen_RefreshRateInHz = m_td3dDisplayMode.RefreshRate;
		m_td3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	}
	else
	{
		//Set windowed parameters
		m_td3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}


	//Set display mode format
	m_td3dPresentParameters.BackBufferFormat = m_td3dDisplayMode.Format;


	//Get number of back buffers
	m_td3dPresentParameters.BackBufferCount = 1;


	//Set auto depth stencil
	m_td3dPresentParameters.EnableAutoDepthStencil = TRUE;


	//Set auto depth stencil format
	m_td3dPresentParameters.AutoDepthStencilFormat = D3DFMT_D24X8;


	//Set swap effect
	m_td3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;


	//Check if vertex processing is supported
	if(m_td3dCaps.VertexProcessingCaps != 0)
	{
		//Set hardware processing and pure device
		dwVertProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
	}
	else
	{
		//Set software proccessing
		dwVertProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}


	//Create device
	hResult = m_pDirect3D9->CreateDevice(m_ucDisplayAdapter, m_ed3dDeviceType, m_td3dPresentParameters.hDeviceWindow,
									     dwVertProcessing, &m_td3dPresentParameters, &m_pDirect3DDevice);


	//Check if device was created
	if (FAILED(hResult))
	{
		//Display error
		LOG_FATALERROR(true, "Could not create direct 3d device. Ensure that your graphics card is working correctly.");


		//Set failed
		bDeviceCreated = false;
	}
	else
	{
		//Set successful
		bDeviceCreated = true;
	}


	//Return if the device created
	return (bDeviceCreated);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Instances all required managers for the renderer.
*
* @author Bryce Booth
* @return true/false	States if all managers were successfully created.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool 
CD3DRenderer::InitialiseManagers()
{
	//Instance manager classes
	m_pVertexBufferManager = new CVertexBufferManager;
	m_pParticleManager = new CParticleManager;
	m_pSurfaceManager = new CSurfaceManager;
	m_pTextureManager = new CTextureManager;
	m_pDeviceManager = new CDeviceManager;
	m_pSpriteManager = new CSpriteManager;
	m_pLightManager = new CLightManager;
	m_pMeshManager = new CMeshManager;
	m_pFogManager = new CFogManager;


	//Initialise device manager
	FW_VALIDATE(m_pDeviceManager->Initialise(m_pDirect3DDevice, m_td3dCaps), "Renderer device manager initialise failed.");


	//Initialise fog manager
	FW_VALIDATE(m_pFogManager->Initialise(m_pDeviceManager, m_td3dCaps.RasterCaps), "Renderer fog manager initialise failed.");


	//Initialise texture manager
	FW_VALIDATE(m_pTextureManager->Initalise(m_pDirect3DDevice, this), "Renderer texture manager initialise failed.");


	//Initialise surface manager
	FW_VALIDATE(m_pSurfaceManager->Initialise(m_pDirect3DDevice,
											  m_td3dPresentParameters.MultiSampleType,
											  m_td3dPresentParameters.MultiSampleQuality), "Renderer surface manager initialise failed.");


	//Initialise vertex buffer manager
	FW_VALIDATE(m_pVertexBufferManager->Initialise(m_pDirect3DDevice, m_pDeviceManager), "Renderer vertex buffer manager initialise failed.");


	//Initialise mesh manager
	FW_VALIDATE(m_pMeshManager->Initialise(m_pDirect3DDevice, m_pDeviceManager, m_pTextureManager), "Renderer mesh manager initialise failed.");


	//Initialise particle manager
	FW_VALIDATE(m_pParticleManager->Initialise(this, m_td3dCaps.FVFCaps, 999999),"Renderer particle manager initialise failed.");


	//Initiaise sprite manager
	ID3DXSprite* d3dpSprite;
	D3DXCreateSprite(m_pDirect3DDevice, &d3dpSprite);


	FW_VALIDATE(m_pSpriteManager->Initalise(m_pTextureManager, this, d3dpSprite), "Renderer sprite manager initialise failed.");


	//Initialise light manager
	FW_VALIDATE(m_pLightManager->Initalise(this, m_td3dCaps.MaxActiveLights), "Renderer light manager initialise failed.");


	//Return successful
	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Instances and initialise log window.
*
* @author Bryce Booth
* @return true/false	States if the log window was successfully created.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CD3DRenderer::IntiailiseLogWindow()
{
	//Create log window bounds rect
	RECT rectBounds;
	rectBounds.top = 10;
	rectBounds.bottom = m_td3dPresentParameters.BackBufferHeight;
	rectBounds.left = 10;
	rectBounds.right = m_td3dPresentParameters.BackBufferHeight;


	//Instance log window
	m_pLogWindow = new CLogWindow();


	//Initilaise log window
	FW_VALIDATE(m_pLogWindow->Initialise(m_pDirect3DDevice), "Renderer log window initialise failed.");


	//Set log window bounds
	m_pLogWindow->SetErrorMessagePosition(rectBounds);


	//Return successful
	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::Deinitialise()
{
	FW_RELEASE(m_pDirect3DDevice);
	FW_RELEASE(m_pDirect3D9);


	FW_DELETE(m_pVertexBufferManager);
	FW_DELETE(m_pParticleManager);
	FW_DELETE(m_pSurfaceManager);
	FW_DELETE(m_pTextureManager);
	FW_DELETE(m_pDeviceManager);
	FW_DELETE(m_pSpriteManager);
	FW_DELETE(m_pLightManager);
	FW_DELETE(m_pMeshManager);
	FW_DELETE(m_pFogManager);
	FW_DELETE(m_pLogWindow);


	FW_ADELETE(m_wcpScreenshotFilename);
}