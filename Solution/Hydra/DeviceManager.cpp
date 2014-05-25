//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   DeviceManager.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>


// Local Includes
#include "Application.h"
#include "GameWindow.h"
#include "D3DRenderer.h"
#include "Macros.h"
#include "Matrix.h"


// This Include
#include "DeviceManager.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* DeviceManager class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDeviceManager::CDeviceManager()
: m_pDirect3DDevice(0)
, m_pDefaultRenderTarget(0)
, m_pDefaultZStencilSurface(0)
, m_kpRenderTarget(0)
, m_kd3dpIndexBuffer(0)
, m_kd3dpVertexBuffer(0)
, m_kmatpMaterial(0)
, m_ulFvF(0)
, m_bDeviceResetScheduled(false)
{
	FW_FILLARRAY(m_kpStageTexture, D3D_MAXSTAGES, 0);
	FW_FILLARRAY(m_dwRenderStates, D3D_MAXRENDERSTATES, DEFAULTSTATE);
	FW_FILLARRAY(m_kmtxpTransformMatrix, D3D_MAXTRANSFORMSTATES, 0);


	FW_FILLMARRAY(m_dwTextureStageStates, D3D_MAXSTAGES, D3D_MAXTEXTURESTAGESTATES, DEFAULTSTATE);
	FW_FILLMARRAY(m_dwSamplerStageStates, D3D_MAXSTAGES, D3D_MAXSAMPLERSTAGESTATES, DEFAULTSTATE);


	ZeroMemory(&m_matDefaultMaterial, sizeof(D3DMATERIAL9));
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* DeviceManager class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDeviceManager::~CDeviceManager()
{
	Deinitialise();
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialises the device manager.
*
* @author Bryce Booth
*
* @param _pDirect3DDevice	Direct 3d device instance.
* @param _kd3drDeviceCaps	Direct 3d caps container.
*
* @return 
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDeviceManager::Initialise(IDirect3DDevice9* _pDirect3DDevice, const D3DCAPS9& _kd3drDeviceCaps)
{
	//Error check parameters
	assert(_pDirect3DDevice);


	//Set member variables
	m_pDirect3DDevice = _pDirect3DDevice;
	m_d3dDeviceCaps   = _kd3drDeviceCaps;


	//Get current render target
	m_pDirect3DDevice->GetRenderTarget(0, &m_pDefaultRenderTarget);


	//Get current stencil surface
	m_pDirect3DDevice->GetDepthStencilSurface(&m_pDefaultZStencilSurface);


	//Run class initialise functions
	FW_VALIDATE(InitialiseDefaultMaterial(), "Device manager setup default material initialise failed.");


	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will reset the device manager for the next render.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::EndRenderering()
{
	//Clear cached pointers for next render
	m_kd3dpIndexBuffer = 0;
	m_kd3dpVertexBuffer = 0;
	m_kmatpMaterial = 0;


	//Restore material to default
	SetMaterial(&m_matDefaultMaterial);


	//Reset backbuffer to default
	SetRenderTarget(m_pDefaultRenderTarget);


	//Reset view & projectile matrix cache
	m_kmtxpTransformMatrix[D3DTS_VIEW] = 0;
	m_kmtxpTransformMatrix[D3DTS_PROJECTION] = 0;
	m_ulFvF = 0;


	if (m_bDeviceResetScheduled == true)
	{
		ExecuteResetDevice();


		m_bDeviceResetScheduled = false;
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Clears one or more surfaces such as a render target, multiple render targets, a stencil buffer, and a depth buffer.
*
* @author Bryce Booth
*
* @param _bTarget	If to clear target.
* @param _bDepth	If to clear zbuffer.
* @param _bStencil	If to clear stencil.
* @param _d3dColor	The colour to clear the surface with.
* @param _fZDepth	The amount of depth to clear
* @param _dwStencil	The new stencil bit depth.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::DeviceClear(bool _bTarget, bool _bDepth, bool _bStencil, D3DCOLOR _d3dColor, float _fZDepth, DWORD _dwStencil)
{
	//Default variables
	HRESULT hResult = S_OK;
	DWORD dwClear = 0;


	//Check to clear target
	if(_bTarget)
	{
		//Add target to clear parameters
		dwClear |= D3DCLEAR_TARGET;
	}


	//Check to clear depth
	if(_bDepth)
	{
		//Add zbuffer to clear parameters
		dwClear |= D3DCLEAR_ZBUFFER;
	}


	//Check to clear stencil
	if(_bStencil)
	{
		//Add stencil to clear parameters
		dwClear |= D3DCLEAR_STENCIL;
	}


	//Clear targets
	hResult = m_pDirect3DDevice->Clear(0, NULL, dwClear, _d3dColor, _fZDepth, _dwStencil);


	//Check clear was successful
	LOG_FATALERROR(FAILED(hResult), "Could not clear device.");
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Resets the device with the new direct 3d presentation parameters
*
* @author Bryce Booth
*
* @return bSuccessful	States if the devices successfully reset
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::ScheduleDeviceReset()
{
	//Set device to be reset at end of frame
	m_bDeviceResetScheduled = true;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Resets the device with the renderer tobe present parameters
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::ExecuteResetDevice()
{
	//Default varaibles
	D3DPRESENT_PARAMETERS d3dPresentParameters = CApplication::GetInstance().GetGameWindow().GetRenderer()->GetToBePresentParameters();
	HRESULT hResult = S_OK;


	//Tell all device reset targets that device is lost
	CDeviceResetTarget::ExecuteDeviceLostFix();


	//Reset the device
	hResult = m_pDirect3DDevice->Reset(&d3dPresentParameters);


	//Check reset was unsuccessful
	if(SUCCEEDED(hResult))
	{
		//Tell all device reset targets that device is fixed
		CDeviceResetTarget::ExecuteDeviceResetFix();


		//Tell renderer about device reset
		CApplication::GetInstance().GetGameWindow().GetRenderer()->DeviceHasBeenReset();
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will create a direct 3d font instance.
*
* @author Bryce Booth
* 
* @param _d3drFontDesc	Pointer to a D3DXFONT_DESC structure, describing the attributes of the font object to create.
* @param _d3dxprFont	Returned pointer to an ID3DXFont interface, representing the created font object. 
*
* @return _d3dxprFont	Font interface pointer.
*
*---------------------------------------------------------------------------------------------------------------------------*/

ID3DXFont*
CDeviceManager::CreateFont(D3DXFONT_DESC& _d3drFontDesc, ID3DXFont*& _d3dxprFont)
{
	//Error check parameters
	assert(_d3dxprFont == 0);


	//Create font
	HRESULT hResult = D3DXCreateFontIndirect(m_pDirect3DDevice, &_d3drFontDesc, &_d3dxprFont);


	//Check font successfully created
	LOG_FATALERROR(FAILED(hResult), "Could not create font");


	//Return font instance
	return (_d3dxprFont);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets a new color buffer for the device.
*
* @author Bryce Booth
*
* @param _d3dpRenderTarget	Pointer to a new color buffer.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void 
CDeviceManager::SetRenderTarget(IDirect3DSurface9* _d3dpRenderTarget)
{
	//Error check parameters
	assert(_d3dpRenderTarget);


	//Default variables
	HRESULT hResult = S_OK;

	
	//Check render target is not already set on device
	if (_d3dpRenderTarget != m_kpRenderTarget)
	{
		//Set render target on device
		m_pDirect3DDevice->SetRenderTarget(0, _d3dpRenderTarget);


		//Cache device render target change
		m_kpRenderTarget = _d3dpRenderTarget;


		//Check device query was successful
		LOG_FATALERROR(FAILED(hResult), "Could not set render target.");
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will restore the default render target on the device.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::RestoreDefaultRenderTarget()
{
	//Set default render target on device
	SetRenderTarget(m_pDefaultRenderTarget);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the depth stencil surface.
*
* @author Bryce Booth
*
* @param _d3dpNewZStencil	Address of a pointer to an IDirect3DSurface9 interface representing the depth stencil surface.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void 
CDeviceManager::SetDepthStencilSurface(IDirect3DSurface9* _d3dpNewZStencil)
{
	//Error check parameters
	assert(_d3dpNewZStencil);


	//Default variables
	HRESULT hResult = S_OK;

	
	//Check stencil surface is not already set
	if (_d3dpNewZStencil != m_kpZStencil)
	{
		//Set new depth stencil surface
		hResult = m_pDirect3DDevice->SetDepthStencilSurface(_d3dpNewZStencil);


		//Cache device stencil surface change
		m_kpZStencil = _d3dpNewZStencil;


		//Check device query was successful
		LOG_FATALERROR(FAILED(hResult), "Could not set depth stencil surface.");
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will restore the default depth stencil surface on the device.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::RestoreDefaultDepthStencilSurface()
{
	//Set default stencil surface
	SetDepthStencilSurface(m_pDefaultZStencilSurface);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Assigns a texture to a stage for a device.
*
* @author Bryce Booth
*
* @param _dwStage		Stage which to set the texture to.
* @param _d3dpTexture	Pointer to an IDirect3DBaseTexture9 interface, representing the texture being set.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::SetStageTexture(DWORD _dwStage, IDirect3DBaseTexture9* _d3dpTexture)
{
	//Set default variables
	HRESULT hResult = S_OK;


	//Check if texture instance is different from cache
	if (_d3dpTexture != m_kpStageTexture[_dwStage])
	{
		//Set texture instance on device
		hResult = m_pDirect3DDevice->SetTexture(_dwStage, _d3dpTexture);


		//Cache device texture instance change
		m_kpStageTexture[_dwStage] = _d3dpTexture;


		//Check device query was successful
		LOG_FATALERROR(FAILED(hResult), "Could not set texture on stage.");
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the state value for the currently assigned texture on the stage.
*
* @author Bryce Booth
*
* @param _dwStage						Stage identifier of the texture for which the state value is set.
* @param _ed3dTextureStageStateType		Texture state to set.
* @param _dwValue						State value to set. 
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::SetTextureStageState(DWORD _dwStage, D3DTEXTURESTAGESTATETYPE _ed3dTextureStageStateType, DWORD _dwValue)
{
	//Set default variables
	HRESULT hResult = S_OK;


	//Check if texture stage state value is different from cache
	if (m_dwTextureStageStates[_dwStage][_ed3dTextureStageStateType] != _dwValue)
	{
		//Set texture stage state on device
		hResult = m_pDirect3DDevice->SetTextureStageState(_dwStage, _ed3dTextureStageStateType, _dwValue);


		//Cache device texture state type change
		m_dwTextureStageStates[_dwStage][_ed3dTextureStageStateType] = _dwValue;


		//Check device query was successful
		LOG_FATALERROR(FAILED(hResult), "Could not set texture stage state.");
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will reset the target texture stage back to the default.
*
* @author Bryce Booth
*
* @param _dwStage	The texture stage that will be reset.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::ResetTextureStageStates(DWORD _dwStage)
{
	//Check if first stage
	if (_dwStage == 0)
	{
		//Set texture stage states
		SetTextureStageState(_dwStage, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		SetTextureStageState(_dwStage, D3DTSS_COLORARG2, D3DTA_CURRENT);
		SetTextureStageState(_dwStage, D3DTSS_COLOROP, D3DTOP_DISABLE);
	}
	else
	{
		//Disable stage
		SetTextureStageState(_dwStage, D3DTSS_COLOROP, D3DTOP_DISABLE);
	}


	//Reset texture coord index on stage
	SetTextureStageState(_dwStage, D3DTSS_TEXCOORDINDEX, _dwStage);


	//Reset transform flags on stage
	SetTextureStageState(_dwStage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);


	//Disable texture of stage.
	SetStageTexture(_dwStage, 0);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets render states on the device.
*
* @author Bryce Booth
*
* @param _ed3dRenderStateType	Device state variable that is being modified.
* @param _dwValue				New value for the device render state to be set.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::SetRenderState(D3DRENDERSTATETYPE _ed3dRenderStateType, DWORD _dwValue)
{
	//Default variables
	HRESULT hResult = S_OK;


	//Check render state value is different from cache
	if (m_dwRenderStates[_ed3dRenderStateType] != _dwValue)
	{
		//Set render state on device
		hResult = m_pDirect3DDevice->SetRenderState(_ed3dRenderStateType, _dwValue);


		//Cache device render state change
		m_dwRenderStates[_ed3dRenderStateType] = _dwValue;


		//Check device query was successful
		LOG_FATALERROR(FAILED(hResult), "Could not set render state.");
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets sapler states on the device.
*
* @author Bryce Booth
*
* @param _dwSampler				The sampler stage index.  
* @param _ed3dSamplerStateType	The sampler state to change.
* @param _dwValue				State value to set.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::SetSamplerState(DWORD _dwSampler, D3DSAMPLERSTATETYPE _ed3dSamplerStateType, DWORD _dwValue)
{
	//Default variables
	HRESULT hResult = S_OK;


	//Check stage sampler state value is differnet from cache
	if (m_dwSamplerStageStates[_dwSampler][_ed3dSamplerStateType] != _dwValue)
	{
		//Set sampler state on device
		hResult = m_pDirect3DDevice->SetSamplerState(_dwSampler, _ed3dSamplerStateType, _dwValue);
	
		
		//Cache device sampler state change
		m_dwSamplerStageStates[_dwSampler][_ed3dSamplerStateType] = _dwValue;


		//Check device query was successful
		LOG_FATALERROR(FAILED(hResult), "Could not set sampler state");
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets a single device transformation-related state.
*
* @author Bryce Booth
*
* @param _ed3dTransformStateType	Device-state variable that is being modified. 
* @param _kmtxpTransformMatrix		The matrix for the transformation.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::SetTransform(D3DTRANSFORMSTATETYPE _ed3dTransformStateType, const CMatrix* _kmtxpTransformMatrix)
{
	//Error check parameters
	assert(_kmtxpTransformMatrix);


	//Set default variables
	HRESULT hResult = S_OK;

	
	//Check tramsform matrix is differnet from cache
	if (_kmtxpTransformMatrix != m_kmtxpTransformMatrix[_ed3dTransformStateType])
	{
		//Set transform on device
		hResult = m_pDirect3DDevice->SetTransform(_ed3dTransformStateType, _kmtxpTransformMatrix);

		
		//Cache device transform matrix change
		m_kmtxpTransformMatrix[_ed3dTransformStateType] = _kmtxpTransformMatrix;


		//Check device query was successful
		LOG_FATALERROR(FAILED(hResult), "Could not set sampler state");
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets index data on the device
*
* @author Bryce Booth
*
* @param _d3dpIndexBuffer	Pointer to an IDirect3DIndexBuffer9 interface, representing the index data to be set. 
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::SetIndices(IDirect3DIndexBuffer9* _d3dpIndexBuffer)
{
	//Error check parameters
	assert(_d3dpIndexBuffer);


	//default variables
	HRESULT hResult = S_OK;


	//Check index buffer is different from cache
	if (m_kd3dpIndexBuffer != _d3dpIndexBuffer)
	{
		//Set index buffer on device
		hResult = m_pDirect3DDevice->SetIndices(_d3dpIndexBuffer);

		
		//Cache device index buffer change
		m_kd3dpIndexBuffer = _d3dpIndexBuffer;


		//Check device query was successful
		LOG_FATALERROR(FAILED(hResult), "Could not set index buffer.");
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Binds a vertex buffer to a device data stream.
*
* @author Bryce Booth
*
* @param _d3dpVertexBuffer	Pointer to an IDirect3DVertexBuffer9 interface, representing the vertex buffer to bind to the specified data stream. 
* @param _uiStride			Stride of the component, in bytes.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::SetStreamSource(IDirect3DVertexBuffer9* _d3dpVertexBuffer, unsigned int _uiStride)
{
	//Set default variables
	HRESULT hResult = S_OK;


	//Check vertex buffer is different from cache
	if (m_kd3dpVertexBuffer != _d3dpVertexBuffer)
	{
		//Set stream source on device
		hResult = m_pDirect3DDevice->SetStreamSource(0, _d3dpVertexBuffer, 0, _uiStride);

		
		//Cache device vertex buffer change
		m_kd3dpVertexBuffer = _d3dpVertexBuffer;


		//Check device query was successful
		LOG_FATALERROR(FAILED(hResult), "Could not set vertex buffer.");
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the current vertex stream declaration.
*
* @author Bryce Booth
*
* @param _ulFVF		Data containing fixed function vertex type.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::SetFVF(unsigned long _ulFVF)
{
	//Default variables
	HRESULT hResult = S_OK;


	//Check FVF value is different from cache
	if (_ulFVF != m_ulFvF)
	{
		//Set FVF on device
		hResult = m_pDirect3DDevice->SetFVF(_ulFVF);

		
		//Cache device FVF value change
		m_ulFvF = _ulFVF;


		//Check device query was successful
		LOG_FATALERROR(FAILED(hResult), "Could not set FvF.");
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Based on indexing, renders the specified geometric primitive into an array of vertices.
*
* @author Bryce Booth
*
* @param _ed3dPrimitiveType		Member of the D3DPRIMITIVETYPE enumerated type, describing the type of primitive to render. 
* @param _uiNumVertices			Number of vertices used during this call.
* @param _uiPrimitiveCount		Number of primitives to render. The number of vertices used is a function of the primitive count
								and the primitive type.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::DrawIndexedPrimitive(D3DPRIMITIVETYPE _ed3dPrimitiveType, unsigned int _uiNumVertices, unsigned int _uiPrimitiveCount)
{
	//Set default variables
	HRESULT hResult = S_OK;


	//Call device to draw indexed primative
	hResult = m_pDirect3DDevice->DrawIndexedPrimitive(_ed3dPrimitiveType, NULL, NULL, _uiNumVertices, NULL, _uiPrimitiveCount);


	//Check device query was successful
	LOG_FATALERROR(FAILED(hResult), "Could not draw index primitive.");
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Renders a sequence of nonindexed, geometric primitives of the specified type from the current set of data input streams.
*
* @author Bryce Booth
*
* @param _ed3dPrimitiveType		Member of the D3DPRIMITIVETYPE enumerated type, describing the type of primitive to render. 
* @param _uiPrimitiveCount		Number of primitives to render.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::DrawPrimitive(D3DPRIMITIVETYPE _ed3dPrimitiveType, unsigned int _uiPrimitiveCount)
{
	//Set default variables
	HRESULT hResult = S_OK;


	//Call device to draw primitive
	hResult = m_pDirect3DDevice->DrawPrimitive(_ed3dPrimitiveType, 0, _uiPrimitiveCount);


	//Check device query was successful
	LOG_ERROR(FAILED(hResult), "Could not draw primitive.");
}



/*---------------------------------------------------------------------------------------------------------------------------
*
* Renders data specified by a user memory pointer as a sequence of geometric primitives of the specified type.
*
* @author Bryce Booth
*
* @param _d3dePrimitiveType	Member of the D3DPRIMITIVETYPE enumerated type, describing the type of primitive to render.
* @param _uiPrimitiveCount	Number of primitives to render.
* @param _kpVertexStream	User memory pointer to the vertex data.
* @param _uiVertexStride	The number of bytes of data for each vertex.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::DrawPrimitiveUP(D3DPRIMITIVETYPE _d3dePrimitiveType,
								unsigned int _uiPrimitiveCount,
								const void* _kpVertexStream,
								unsigned int _uiVertexStride)
{
	//Set default variables
	HRESULT hResult = S_OK;


	//Call device to draw primitive
	hResult = m_pDirect3DDevice->DrawPrimitiveUP(_d3dePrimitiveType, _uiPrimitiveCount, _kpVertexStream, _uiVertexStride);


	//Check device query was successful
	LOG_FATALERROR(FAILED(hResult), "Could not draw primitive UP.");
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Assigns a set of lighting properties for this device.
*
* @author Bryce Booth
*
* @param _uiLightId		Zero-based index of the set of lighting properties to set. If a set of lighting properties exists
						at this index, it is overwritten by the new properties specified in pLight. 
* @param _kd3dpLight9	Pointer to a D3DLIGHT9 structure, containing the lighting parameters to set. 
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::SetLight(unsigned int _uiLightId,  const D3DLIGHT9* _kd3dpLight9)
{
	//Set default variables
	HRESULT hResult = S_OK;


	//Call device to set light
	hResult = m_pDirect3DDevice->SetLight(_uiLightId, _kd3dpLight9);


	//Check device query was successful
	LOG_ERROR(FAILED(hResult), "Could not set light. Maxium enabled lights may have been reached.");
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Enables or disables a set of lighting parameters within a device.
*
* @author Bryce Booth
*
* @param _uiLightId		Zero-based index of the set of lighting parameters that are the target of this method. 
* @param _bEnable		Value that indicates if the set of lighting parameters are being enabled or disabled.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::SetLightEnabled(unsigned int _uiLightId, bool _bEnable)
{
	//Set default variables
	HRESULT hResult = S_OK;


	//Call device to set light enabled or disabled
	hResult = m_pDirect3DDevice->LightEnable(_uiLightId, _bEnable);


	//Check device query was successful
	LOG_FATALERROR(FAILED(hResult), "Could not enable light.");
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the material properties for the device.
*
* @author Bryce Booth
*
* @param _kmatpMaterial		Pointer to a D3DMATERIAL9 structure, describing the material properties to set.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::SetMaterial(const D3DMATERIAL9* _kmatpMaterial)
{
	//Set default variables
	HRESULT hResult = S_OK;


	//Check material is different from cache
	if (_kmatpMaterial != m_kmatpMaterial)
	{
		//Set material on device
		hResult = m_pDirect3DDevice->SetMaterial(_kmatpMaterial);


		//Cache device material change
		m_kmatpMaterial = _kmatpMaterial;
			

		//Check device query was successful
		LOG_FATALERROR(FAILED(hResult), "Could not set material.");
	}
}







/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates the default material for the device
*
* @author Bryce Booth
*
* @true		Material created successfully.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDeviceManager::InitialiseDefaultMaterial()
{
	//Set default material diffuse
	m_matDefaultMaterial.Diffuse.a = 1.0f;
	m_matDefaultMaterial.Diffuse.r = 0.9f;
	m_matDefaultMaterial.Diffuse.g = 0.9f;
	m_matDefaultMaterial.Diffuse.b = 0.9f;
	

	//Set default material ambient
	m_matDefaultMaterial.Ambient.a = 1.0f;
	m_matDefaultMaterial.Ambient.r = 0.2f;
	m_matDefaultMaterial.Ambient.g = 0.2f;
	m_matDefaultMaterial.Ambient.b = 0.2f;


	//Set default material specular
	m_matDefaultMaterial.Specular.a = 1.0f;
	m_matDefaultMaterial.Specular.r = 0.2f;
	m_matDefaultMaterial.Specular.g = 0.2f;
	m_matDefaultMaterial.Specular.b = 0.2f;
	

	//Set default material emissive
	m_matDefaultMaterial.Emissive.a = 1.0f;
	m_matDefaultMaterial.Emissive.r = 0.2f;
	m_matDefaultMaterial.Emissive.g = 0.2f;
	m_matDefaultMaterial.Emissive.b = 0.2f;
	

	//Set default material power
	m_matDefaultMaterial.Power = 1.0f;


	return (true);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Restores all previously set render states back on the device.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::RestoreRenderStates()
{
	//Default variables
	unsigned int uiMemoryBlockSize = 0;
	DWORD dwRenderStates[D3D_MAXRENDERSTATES];
	DWORD dwRenderStatesValue = DEFAULTSTATE;

	
	//Calculate memory block size
	uiMemoryBlockSize = D3D_MAXRENDERSTATES * sizeof(DWORD);


	//Copy texture states cache values
	memcpy(dwRenderStates, m_dwRenderStates, uiMemoryBlockSize);


	//Clear texture states cache
	FW_FILLARRAY(m_dwRenderStates, D3D_MAXRENDERSTATES, DEFAULTSTATE);


	//Loop through max render states
	for (unsigned int i = 0; i < D3D_MAXRENDERSTATES; ++i)
	{
		//Set render state value
		dwRenderStatesValue = dwRenderStates[i];

	
		//Check render state value
		//is not default state
		if (dwRenderStatesValue != DEFAULTSTATE)
		{
			//Set render state
			SetRenderState(static_cast<D3DRENDERSTATETYPE>(i), dwRenderStatesValue);
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Restores the previously set stage states on the device.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::RestoreStageStates()
{
	//Set default variables
	unsigned int uiMemoryBlockSize = 0;
	DWORD dwTextureStageStates[D3D_MAXSTAGES][D3D_MAXTEXTURESTAGESTATES];
	DWORD dwTextureStageStateValue = DEFAULTSTATE;

	
	//Calculate memory block size
	uiMemoryBlockSize = D3D_MAXSTAGES * D3D_MAXTEXTURESTAGESTATES * sizeof(DWORD);


	//Copy texture states cache values
	memcpy(dwTextureStageStates, m_dwTextureStageStates, uiMemoryBlockSize);


	//Clear texture states cache
	FW_FILLMARRAY(m_dwTextureStageStates, D3D_MAXSTAGES, D3D_MAXTEXTURESTAGESTATES, DEFAULTSTATE);

	
	//Loop through max stages
	for (unsigned int i = 0; i < D3D_MAXSTAGES; ++i)
	{
		//Loop through max state states
		for (unsigned int j = 0; j < D3D_MAXTEXTURESTAGESTATES; ++j)
		{
			//Set texture state state value
			dwTextureStageStateValue = dwTextureStageStates[i][j];


			//Check texture stage state value
			//is not default state
			if (dwTextureStageStateValue != DEFAULTSTATE)
			{
				//Set texture stage state
				SetTextureStageState(i, static_cast<D3DTEXTURESTAGESTATETYPE>(j), dwTextureStageStateValue);
			}
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Restores the previously set sampler states on the device.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::RestoreSamplerStates()
{
	//Set default variables
	unsigned int uiMemoryBlockSize = 0;
	DWORD dwStageSamplerStates[D3D_MAXSTAGES][D3D_MAXSAMPLERSTAGESTATES];
	DWORD dwStageSamplerStateValue = 0;

	
	//Calculate memory block size
	uiMemoryBlockSize = D3D_MAXSTAGES * D3D_MAXSAMPLERSTAGESTATES * sizeof(DWORD);


	//Copy sampler states cache values
	memcpy(dwStageSamplerStates, m_dwSamplerStageStates, uiMemoryBlockSize);


	//Clear sampler states cache
	FW_FILLMARRAY(m_dwSamplerStageStates, D3D_MAXSTAGES, D3D_MAXSAMPLERSTAGESTATES, DEFAULTSTATE);

	
	//Loop through max stages
	for (unsigned int i = 0; i < D3D_MAXSTAGES; ++i)
	{
		//Loop through max state states
		for (unsigned int j = 0; j < D3D_MAXSAMPLERSTAGESTATES; ++j)
		{
			//Set sampler state state value
			dwStageSamplerStateValue = dwStageSamplerStates[i][j];


			//Check sampler stage state value
			//is not default state
			if (dwStageSamplerStateValue != DEFAULTSTATE)
			{
				//Set sampler state
				SetSamplerState(i, static_cast<D3DSAMPLERSTATETYPE>(j), dwStageSamplerStateValue);
			}
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Configures the device manager for lost device call.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::OnDeviceLost()
{
	//Release default render target
	FW_RELEASE(m_pDefaultRenderTarget);


	//Release default stencil surface
	FW_RELEASE(m_pDefaultZStencilSurface);	
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the device backup for device reset action.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::OnDeviceReset()
{
	//Restore render states
	RestoreRenderStates();


	//Restore stage states
	RestoreStageStates();

	
	//Restore sampler states
	RestoreSamplerStates();


	//Retrieve new render target
	m_pDirect3DDevice->GetRenderTarget(0, &m_pDefaultRenderTarget);


	//Retrieve new depth stencil surface
	m_pDirect3DDevice->GetDepthStencilSurface(&m_pDefaultZStencilSurface);
}







/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceManager::Deinitialise()
{
	FW_RELEASE(m_pDefaultRenderTarget);
	FW_RELEASE(m_pDefaultZStencilSurface);
}