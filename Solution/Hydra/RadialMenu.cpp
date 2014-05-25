//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	RadialMenu.cpp
//	Description	:	Definition of CRadialMenu
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// This include.
#include "RadialMenu.h"

// Local includes.
#include "Utility.h"
#include "D3DRenderer.h"
#include "Vertex1TexSCSP.h"
#include "VertexSCSP.h"
#include "HudDataManager.h"
#include "Hud.h"
#include "DeviceManager.h"
#include "TextureManager.h"
#include "VertexBufferManager.h"
#include "Application.h"
#include "Window.h"
#include "Scene.h"
#include "InputManager.h"
#include "XInputController.h"

// Library includes.
#include <cassert>
#include <d3dx9.h>

// Defines.
#define FLG_RAD_REDOSTENCIL Utility::B1		/* Stencil must be reconstructed									*/
#define FLG_RAD_REDOIMAGE Utility::B2		/* Image in the Render Target must be reconstructed					*/
#define FLG_RAD_STATES Utility::B3			/* Render states applied, stencil and render targets set on device	*/
#define FLG_RAD_OPEN Utility::B4			/* Radial Menu is currently open (in use)							*/

CRadialMenu::CRadialMenu()
: m_pLine(0)
, m_pRenderer(0)
, m_pHud(0)
, m_uiStencilID(Utility::INVALID_ID)
, m_iRadiantTextureID(Utility::INVALID_ID)
, m_uiRenderTargetID(Utility::INVALID_ID)
, m_iFinalTextureID(Utility::INVALID_ID)
, m_uiVertexBufferQuadID(Utility::INVALID_ID)
, m_uiVertexBufferMaskID(Utility::INVALID_ID)
, m_uiDiameter(0)
, m_fInnerRadius(0.0f)
, m_fOuterPlanarLength(0.0f)
, m_fDrawPositionX(0.0f)
, m_fDrawPositionY(0.0f)
, m_pLineVertices(0)
, m_uiNumLineVertices(0)
, m_pkOldHudData(0)
, m_arrButtonData(0)
, m_ucNumButtons(0)
, m_ucButtonSelected(MathUtility::kMaxUC)
, m_ucFlags(0)
, m_dwOriginalStencilState(0)
, m_iOpenPositionX(0)
, m_iOpenPositionY(0)
{

}

CRadialMenu::~CRadialMenu()
{
	if (m_pLine)
	{
		m_pLine->Release();
		m_pLine = 0;
	}

	delete[] m_pLineVertices;
	m_pLineVertices = 0;
	m_uiNumLineVertices = 0;

	delete[] m_arrButtonData;
	m_arrButtonData = 0;
	m_ucNumButtons = 0;

	if (m_pRenderer)
	{
		m_pRenderer->GetSurfaceManager().DestroySurface(m_uiStencilID);
		m_pRenderer->GetSurfaceManager().DestroySurface(m_uiRenderTargetID);
	}
}

/**
*
* Sets up the radial menu.
*
* @author Jade Abbott
* @param _pRenderer Required for the surface manager, device manager, etc.
* @param _pHud The Heads Up Display, which will be told to display certain information when the Radial Menu is open.
* @param _uiMaximumDiameter Maximum diameter the radial menu can be (but is capped at 512); Must be even.
* @param _uiMaxLines Maximum nuimber of lines used to define the shape of the inner circle.
* @param _fLineWidth The width of the dividing lines drawn.
* @param _fInnerCircleScalar Scalar value to set how much of the Radial Menu is taken by the centre button.
* @param _fDrawPositionX The centre X coordinate where the Radial Menu will be drawn on screen.
* @param _fDrawPositionY The centre Y coordinate where the Radial Menu will be drawn on screen.
* @return True if initialisation was successful.
*
*/
bool
CRadialMenu::Initialise(CD3DRenderer* _pRenderer,
						CHud* _pHud,
						unsigned int _uiMaximumDiameter,
						unsigned int _uiMaxLines,
						float _fLineWidth,
						float _fInnerCircleScalar,
						float _fDrawPositionX,
						float _fDrawPositionY)
{
	assert(_pRenderer);
	assert(!m_pRenderer);

	m_pRenderer = _pRenderer;
	m_pHud = _pHud;

	// Get default data; This is only to breakproof it.
	m_dwOriginalStencilState = _pRenderer->GetDeviceManager().GetRenderStateValue(D3DRS_STENCILENABLE);

	// Initialise resolution-based data.
	bool bSuccess = OnResolutionChange(_uiMaximumDiameter, _fDrawPositionX, _fDrawPositionY);

	// Set the radius of the inner circle.
	SetInnerCircleRadius(_fInnerCircleScalar * (m_uiDiameter * 0.5f));

	// Create vertex buffer so ID3DXLine can draw into the stencil.
	bSuccess = SetMaxLines(_uiMaxLines) ? bSuccess : false;

	// Create line for stencil masking.
	bSuccess = CreateLine(_fLineWidth) ? bSuccess : false;
	assert(bSuccess);

	// Create dynamic vertex buffer, which is a screen-space textured quad.
	bSuccess = CreateVertexBufferQuad() ? bSuccess : false;
	assert(bSuccess);

	// Create dynamic vertex buffer for masking.
	bSuccess = CreateVertexBufferMask(_uiMaxLines) ? bSuccess : false;
	assert(bSuccess);

	return bSuccess;
}

/**
*
* Resizes the Radial Menu for when the resolution changes.
*
* @author Jade Abbott
*
*/
bool
CRadialMenu::OnResolutionChange(unsigned int _uiMaximumDiameter,
								float _fDrawPositionX,
								float _fDrawPositionY)
{
	m_uiDiameter = _uiMaximumDiameter < 512 ? _uiMaximumDiameter : 512;	// Max diameter is >= 512 pixels.
	m_fDrawPositionX = _fDrawPositionX;
	m_fDrawPositionY = _fDrawPositionY;

	bool bSuccess = CreateStencil();
	bSuccess = CreateRenderTarget() ? bSuccess : false;
	bSuccess = CreateFinalTexture() ? bSuccess : false;
	return CreateRadiance() ? bSuccess : false;
}

/**
*
* This handles the selection of buttons using a mouse.
*
* @author Jade Abbott
* @param _uiX, _uiY Screen coordinates where the mouse is.
*
*/
void
CRadialMenu::Process(unsigned int _uiX, unsigned int _uiY)
{
	if (!(m_ucFlags & FLG_RAD_OPEN))	// If the radial menu is not open...
		return;

	assert(m_ucNumButtons);	// Must be non-zero.

	unsigned char ucButtonSelected = MathUtility::kMaxUC;

	const float kfRelativeX = _uiX - m_fDrawPositionX;
	const float kfRelativeY = -(_uiY - m_fDrawPositionY);	// Y is turned over so the top half is positive.
	const float kfDistanceSq = (kfRelativeX * kfRelativeX) + (kfRelativeY * kfRelativeY);

	// Check if the coordinates are within range of the radial menu (between the inner circle and the outer radius).
	if (kfDistanceSq > m_fInnerRadius * m_fInnerRadius && kfDistanceSq < m_uiDiameter * m_uiDiameter * 0.25f)
	{
		// Find which button is being hovered over.
		switch (m_ucNumButtons)
		{
		case 1:
			ucButtonSelected = 0;
			break;

		case 2:
			ucButtonSelected = kfRelativeY >= 0.0f ? 0 : 1;	// Top half is first button, bottom half is second button.
			break;

		default:	// Every other number of buttons.
			{
				float fRadians = MathUtility::AngleFromDeltaPos(kfRelativeX, kfRelativeY);	// Square root performed 75% of the time.
				if (fRadians < 0.0f)
					fRadians += MathUtility::PI + MathUtility::PI;

				// Find which button the angle resides in.
				const float kfFraction((2.0f * MathUtility::PI) / m_ucNumButtons);	// m_ucNumButtons guaranteed >= 3, so no div/0.

				ucButtonSelected = static_cast<unsigned char>(fRadians / kfFraction);	// floor(kfRadians / kfFraction) == buttonIteration.
			}
			break;
		}
	}
	// Else the mouse is not hovering over a button.

	if (ucButtonSelected != m_ucButtonSelected)	// If this is a change in button...
	{
		// TODO: Play sound.
		m_ucFlags = m_ucFlags | FLG_RAD_REDOIMAGE;	// The image must be redrawn.
		m_ucButtonSelected = ucButtonSelected;

		if (m_pHud)
		{
			m_pHud->SetSelectionData(ucButtonSelected == MathUtility::kMaxUC ? m_pkOldHudData : m_arrButtonData[ucButtonSelected].m_pkReferenceData);
		}
	}
}

/**
*
* This handles the selection of buttons using an Xbox 360 controller.
*
* @author Jade Abbott
* @param _pfRadians The angle of the analog stick (provide null pointer when in centre).
* @return Void.
*
*/
void
CRadialMenu::Process(float* _pfRadians)
{
	if (!(m_ucFlags & FLG_RAD_OPEN))	// If the radial menu is not open...
		return;

	assert(m_ucNumButtons);	// Must be non-zero.

	unsigned char ucButtonSelected = _pfRadians ? m_ucNumButtons > 1 ? static_cast<unsigned char>((*_pfRadians < 0.0f ? *_pfRadians + MathUtility::PI + MathUtility::PI : *_pfRadians) / ((2.0f * MathUtility::PI) / m_ucNumButtons))
																	 : 0
												: MathUtility::kMaxUC;

	if (ucButtonSelected != m_ucButtonSelected)	// If this is a change in button...
	{
		// TODO: Play sound.
		m_ucFlags = m_ucFlags | FLG_RAD_REDOIMAGE;	// The image must be redrawn.
		m_ucButtonSelected = ucButtonSelected;

		if (m_pHud)
		{
			m_pHud->SetSelectionData(ucButtonSelected == MathUtility::kMaxUC ? m_pkOldHudData : m_arrButtonData[ucButtonSelected].m_pkReferenceData);
		}
	}
}

/**
*
* When Process() determines a button has been clicked, this function executes the commands involved.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CRadialMenu::ExecuteButton()
{
	assert(m_ucFlags & FLG_RAD_OPEN);

	// Execute the button if it was clicked.
	if (m_ucButtonSelected != MathUtility::kMaxUC)
	{
		assert(m_arrButtonData);

		if (!m_arrButtonData[m_ucButtonSelected].m_bDisabled && m_arrButtonData[m_ucButtonSelected].m_pStaticMemberFunction)
			m_arrButtonData[m_ucButtonSelected].m_pStaticMemberFunction(m_arrButtonData[m_ucButtonSelected].m_pInstanceMemberData, m_ucButtonSelected);
	}
	else
		Close();
}

/**
*
* Draws the Radial Menu.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CRadialMenu::Draw()
{
	if (m_ucFlags & FLG_RAD_REDOSTENCIL)	// If the stencil needs to be reassembled...
	{
		AssembleStencil();	// Turns off flag.
		m_ucFlags = m_ucFlags | FLG_RAD_REDOIMAGE;
	}

	if (m_ucFlags & FLG_RAD_REDOIMAGE)	// If the image needs to be reconstructed...
	{
		m_ucFlags = m_ucFlags ^ FLG_RAD_REDOIMAGE;

		DrawRadianceITS();
		DrawHighlightITS();
		DrawIconsITS();
		CopyTargetSurfaceIFT();

		// Undo custom render states (return device to original condition).
		PrepareDeviceData(false);
	}

	assert(!(m_ucFlags & FLG_RAD_STATES));	// Custom render states must not be applied at this point.

	RenderFinalTextureToScreen();	// Render the back buffer's image to the game scene.
}

/**
*
* Begins a new Radial Menu.
*
* @author Jade Abbott
* @param _ucNumButtons The number of buttons to exist in the Radial menu.
* @return True if creation was successful.
*
*/
bool
CRadialMenu::Open(unsigned char _ucNumButtons)
{
	assert(_ucNumButtons);	// Must be non-zero.
	assert(!(m_ucFlags & FLG_RAD_OPEN));	// Must not be open already.
	assert(!m_arrButtonData);

	// Create button array.
	TRadialMenuButtonData* arrData = new TRadialMenuButtonData[_ucNumButtons];
	if (!arrData)
		return false;
	
	m_ucFlags = m_ucFlags | FLG_RAD_REDOSTENCIL;	// Will delay creation of stencil until absolutely necessary.

	m_ucNumButtons = _ucNumButtons;
	m_ucButtonSelected = MathUtility::kMaxUC;

	m_arrButtonData = arrData;

	ZeroMemory(m_arrButtonData, sizeof(TRadialMenuButtonData) * _ucNumButtons);

	// Calculate (if necessary) the outer planar line length.
	if (_ucNumButtons >= 3)
		CalculateOuterPlanarLength();
	
	// Stop the HUD from displaying information about a specific tower.
	if (m_pHud)
	{
		m_pkOldHudData = m_pHud->GetSelectionData();
		m_pHud->SetExtendedInfo(0);
	}

	// Radial Menu is now open.
	m_ucFlags = m_ucFlags | FLG_RAD_OPEN;


	//Center mouse cursor
	if (CApplication::GetInstance().GetGameWindow().GetCurrentMainScene().GetInputManager().GetXInputController().IsPluggedIn() == false)
	{
		//Backup current position
		POINT pntPosition;
		::GetCursorPos(&pntPosition);


		m_iOpenPositionX = pntPosition.x;
		m_iOpenPositionY = pntPosition.y;


		CApplication::GetInstance().GetGameWindow().SetCursorPosition(static_cast<int>(m_fDrawPositionX),
																	  static_cast<int>(m_fDrawPositionY));
	}

	return true;
}

/**
*
* Closes the Radial Menu, if it is open.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CRadialMenu::Close()
{
	m_ucFlags = (m_ucFlags | FLG_RAD_OPEN) ^ FLG_RAD_OPEN;
	delete[] m_arrButtonData;
	m_arrButtonData = 0;
	// m_ucNumButtons remains the same, as it specifies the number of divisions in the stencil.

	// Stop the HUD from displaying information about a button.
	if (m_pHud)
	{
		m_pHud->SetSelectionData(0);
	}


	////Center mouse cursor
	//if (CApplication::GetInstance().GetGameWindow().GetCurrentMainScene().GetInputManager().GetXInputController().IsPluggedIn() == false)
	//{
	//	CApplication::GetInstance().GetGameWindow().SetCursorPosition(static_cast<int>(m_iOpenPositionX),
	//																  static_cast<int>(m_iOpenPositionY));
	//}
}

/**
*
* Returns true if the Radial Menu is open (in use); False if not.
*
* @author Jade Abbott
* @return True if the Radial Menu is open (in use); False if not.
*
*/
bool
CRadialMenu::IsOpen() const
{
	return !!(m_ucFlags & FLG_RAD_OPEN);
}

/**
*
* Will automatically disable buttons if the button's value is greater than the maximum affordable.
* Enables buttons too.
*
* @author Jade Abbott
*
*/
void
CRadialMenu::AutoDisableButtons(unsigned int _uiMaximumAffordable)
{
	assert(m_ucFlags & FLG_RAD_OPEN);	// Radial Menu must be open.
	
	for (unsigned char uc = 0; uc < m_ucNumButtons; ++uc)
	{
		if (m_arrButtonData[uc].m_pkReferenceData && !m_arrButtonData[uc].m_bNoDisable)
		{
			bool bShouldBe = m_arrButtonData[uc].m_pkReferenceData->m_uiValue > _uiMaximumAffordable;
			if (m_arrButtonData[uc].m_bDisabled != bShouldBe)
			{
				m_arrButtonData[uc].m_bDisabled = bShouldBe;
				m_ucFlags = m_ucFlags | FLG_RAD_REDOIMAGE;
			}
		}
	}
}

/**
*
* Sets the number of vertices used to draw the inner circle.
*
* @author Jade Abbott
* @param _uiNumVertices The number of vertices to use in drawing a circle.
* @return True if the count could be changed.
*
*/
bool
CRadialMenu::SetMaxLines(unsigned int _uiMaxLines)
{
	assert(m_pRenderer);

	if (!_uiMaxLines)
		_uiMaxLines = 1;

	// Update the vertex mask if necessary.
	CreateVertexBufferMask(_uiMaxLines);

	++_uiMaxLines;	// _uiMaxLines is now the number of vertices.

	// Escape if this number of vertices is already set.
	if (m_uiNumLineVertices == _uiMaxLines)
		return true;

	D3DXVECTOR2* pVertices = new D3DXVECTOR2[_uiMaxLines];
	if (pVertices)
	{
		delete[] m_pLineVertices;
		m_pLineVertices = pVertices;
		m_uiNumLineVertices = _uiMaxLines;
		m_ucFlags = m_ucFlags | FLG_RAD_REDOSTENCIL;
		return true;
	}

	return false;
}

/**
*
* Sets the distance from the centre the inner circle will appear.
*
* @author Jade Abbott
* @param _fRadius Distance from the centre of the image to the inner circle.
* @return Void.
*
*/
void
CRadialMenu::SetInnerCircleRadius(float _fRadius)
{
	m_fInnerRadius = _fRadius;
	m_ucFlags = m_ucFlags | FLG_RAD_REDOSTENCIL;
}

/**
*
* Creates the stencil surface used to prevent drawing of certain areas of the radiant light.
*
* @author Jade Abbott
* @return True if creation of the stencil was successful.
*
*/
bool
CRadialMenu::CreateStencil()
{
	assert(m_pRenderer);

	CSurfaceManager& rSurfaceManager = m_pRenderer->GetSurfaceManager();

	if (m_uiStencilID != Utility::INVALID_ID)
	{
		rSurfaceManager.DestroySurface(m_uiStencilID);
	}

	m_uiStencilID = rSurfaceManager.CreateStencil(m_uiDiameter, m_uiDiameter, D3DFMT_D24S8, false);

	if (m_uiStencilID == Utility::INVALID_ID)
	{
		m_uiStencilID = rSurfaceManager.CreateStencil(m_uiDiameter, m_uiDiameter, D3DFMT_D24X4S4, false);

		if (m_uiStencilID == Utility::INVALID_ID)
		{
			assert(false);	// Something wrong with the format?
			return false;	// Could not create surface.
		}
	}

	return true;	// Successfully created surface.
}

/**
*
* @author Jade Abbott
*
*/
bool
CRadialMenu::CreateFinalTexture()
{
	assert(m_pRenderer);

	IDirect3DTexture9* pTexture = 0;
	if (FAILED(m_pRenderer->GetSurfaceManager().CreateTexture(m_uiDiameter,
																m_uiDiameter,
																D3DFMT_A8R8G8B8,
																D3DPOOL_MANAGED,
																&pTexture)))
	{
		return false;
	}

	CTextureManager& rTextureManager = m_pRenderer->GetTextureManager();

	if (m_iFinalTextureID != Utility::INVALID_ID)
	{
		rTextureManager.RemoveTexture(m_iFinalTextureID);
	}

	m_iFinalTextureID = rTextureManager.LoadTextureMemory(pTexture);

	if (m_iFinalTextureID == Utility::INVALID_ID)
	{
		pTexture->Release();
		return false;
	}

	return true;
}

/**
*
* Creates the ID3DXLine ued to mask areas of the stencil when drawing the radial menu.
*
* @author Jade Abbott
* @param _fWidth The width of the line.
* @return True if initialisation was successful.
*
*/
bool
CRadialMenu::CreateLine(float _fWidth)
{
	assert(!m_pLine);
	assert(m_pRenderer);

	if(SUCCEEDED(m_pRenderer->GetDeviceManager().CreateLine(&m_pLine)))
	{
		m_pLine->SetAntialias(FALSE);
		m_pLine->SetWidth(_fWidth);
		m_pLine->SetPattern(0);	// Opaque.

		return true;
	}

	return false;
}

/**
*
* Sets up the radiant light surface and texture.
* Since this surface exists in the scratch pool, it does not need to be restored when the device is lost.
*
* @author Jade Abbott
* @return True if creation was successful.
*
*/
bool
CRadialMenu::CreateRadiance()
{
	assert(m_pRenderer);

	CSurfaceManager& rSurfaceManager = m_pRenderer->GetSurfaceManager();

	IDirect3DTexture9* pTexture = 0;
	if (FAILED(rSurfaceManager.CreateTexture(m_uiDiameter,
											 m_uiDiameter,
											 D3DFMT_A8R8G8B8,
											 D3DPOOL_MANAGED,
											 &pTexture)))
	{
		return false;
	}

	// Get the texture's surface.
	IDirect3DSurface9* pSurface = 0;
	if (FAILED(pTexture->GetSurfaceLevel(0, &pSurface)))
	{
		pTexture->Release();
		return false;
	}

	const float kfRadius = m_uiDiameter * 0.5f;
	const float kfRadiusFraction = 1.0f / kfRadius;

	D3DLOCKED_RECT surfaceRect;
	HRESULT hr = pSurface->LockRect(&surfaceRect, 0, 0);
	if (SUCCEEDED(hr))
	{
		D3DCOLOR* pPixels = reinterpret_cast<D3DCOLOR*>(surfaceRect.pBits);
		unsigned int uiNumPixelsWide = surfaceRect.Pitch / 4;	// Includes dirty region.

		// set the colour and alpha for every texel.
		for (unsigned int uiWidth = 0; uiWidth < m_uiDiameter; ++uiWidth)
		{
			for (unsigned int uiHeight = 0; uiHeight < m_uiDiameter; ++uiHeight)
			{
				D3DXVECTOR2 vecRelativePixelPos(static_cast<float>(uiWidth) - kfRadius,
												static_cast<float>(uiHeight) - kfRadius);	// This texel's position relative to the centre of the image.

				float fTexelAlpha = D3DXVec2Length(&vecRelativePixelPos) * kfRadiusFraction;	// Scalar value between 0.0f and 1.0f (capped at 1.0f).
				fTexelAlpha = 1.0f - (fTexelAlpha * fTexelAlpha);	// Squaring the value makes the radiant light stand out more.

				pPixels[(uiHeight * uiNumPixelsWide) + uiWidth] = D3DCOLOR_ARGB(fTexelAlpha <= 0.0f ? 0 : static_cast<unsigned char>(fTexelAlpha * MathUtility::kMaxUC), 192, 128, 32);
			}
		}

		pSurface->UnlockRect();
	}
	else
	{
		assert(false);
		pSurface->Release();
		pTexture->Release();
		return false;
	}

	// Release the surface (texture has it's own reference).
	pSurface->Release();

	// Save the texture to the texture manager.
	CTextureManager& rTextureManager = m_pRenderer->GetTextureManager();

	if (m_iRadiantTextureID != Utility::INVALID_ID)
	{
		rTextureManager.RemoveTexture(m_iRadiantTextureID);
	}

	m_iRadiantTextureID = m_pRenderer->GetTextureManager().LoadTextureMemory(pTexture);

	if (m_iRadiantTextureID == Utility::INVALID_ID)
	{
		pTexture->Release();
		return false;
	}

	return true;
}

/**
*
* Handles initialiisation of the dynamic vertex buffer used to render screen-space textured quads.
* Position each vertex in the shape of a Z.
*
* @author Jade Abbott
* @return True if creation was successful.
*
*/
bool
CRadialMenu::CreateVertexBufferQuad()
{
	assert(m_pRenderer);
	assert(m_uiVertexBufferQuadID == Utility::INVALID_ID);

	CVertex1TexSCSP* pVertices = new CVertex1TexSCSP[4];
	if (!pVertices)
		return false;

	pVertices[0].SetTextureCoordinates(0.0f, 0.0f);
	pVertices[1].SetTextureCoordinates(1.0f, 0.0f);
	pVertices[2].SetTextureCoordinates(0.0f, 1.0f);
	pVertices[3].SetTextureCoordinates(1.0f, 1.0f);

	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Emissive.r = 1.0f;

	CVertexBufferManager& rManager = m_pRenderer->GetVertexBufferManager();

	m_uiVertexBufferQuadID = rManager.CreateVertexBuffer(pVertices->GetFVF(),
														 D3DPT_TRIANGLESTRIP,
														 4,
														 0,
														 pVertices->GetSizeOf(),
														 pVertices,
														 0,
														 D3DFMT_UNKNOWN,
														 material,
														 true);

	if (m_uiVertexBufferQuadID == Utility::INVALID_ID)
	{
		assert(false);
		return false;
	}

	return true;
}

/**
*
* Creates the dynamic mesh that will be used to mask areas of the Radial Menu.
* Can be called multiple times to change the size of the mesh, but will only increase in size.
* Minimum size allowed is four vertices.
*
* @author Jade Abbott
* @param _uiNumFaces The number of polygons to exist in the mesh (minimum two).
* @return Void.
*
*/
bool
CRadialMenu::CreateVertexBufferMask(unsigned int _uiNumFaces)
{
	assert(m_pRenderer);
	
	if (_uiNumFaces < 2)
		_uiNumFaces = 2;

	// Convert number of faces to number of vertices.
	_uiNumFaces += 2;

	// If the vertex buffer already exists, escape if it has more vertices.
	CVertexBufferManager& rVertexBufferManager = m_pRenderer->GetVertexBufferManager();

	if (m_uiVertexBufferMaskID != Utility::INVALID_ID)
	{
		if (rVertexBufferManager.GetVertexBuffer(m_uiVertexBufferMaskID)->GetVertexBufferData().m_uiNumVerts >= _uiNumFaces)
		{
			return true;	// Mesh already created, and is has the minimum required vertices.
		}
		// Else the current buffer doesn't have enough vertices.
	}

	// Create new mesh.
	CVertexSCSP* pVertices = new CVertexSCSP[_uiNumFaces];
	if (!pVertices)
		return false;

	// Create material.
	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));

	// Create dynamic mesh.
	unsigned int uiMeshID = rVertexBufferManager.CreateVertexBuffer(pVertices->GetFVF(),
																	D3DPT_TRIANGLEFAN,
																	_uiNumFaces,
																	0,
																	pVertices->GetSizeOf(),
																	pVertices,
																	0,
																	D3DFMT_UNKNOWN,
																	material,
																	true);

	if (uiMeshID != Utility::INVALID_ID)	// If the mesh is valid...
	{
		if (m_uiVertexBufferMaskID != Utility::INVALID_ID)	// If the mesh already exists...
		{
			rVertexBufferManager.DeleteVertexBuffer(m_uiVertexBufferMaskID);	// Delete the old mesh first.
		}

		m_uiVertexBufferMaskID = uiMeshID;	// Set the new mesh.

		return true;
	}
	else	// Failed to create mesh...
	{
		return false;	// eturn failure, but keep the old mesh if one exists.
	}
}

/**
*
* Sets up the stencil for the number of buttons provided.
* Should only be called in Draw().
* Invalidates the render target surface, as redrawing with the new stencil will not overwrite all of the old image.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CRadialMenu::AssembleStencil()
{
	assert(m_ucNumButtons);	// Must be non-zero.
	assert(m_pLine);
	assert(m_pRenderer);
	assert(m_uiNumLineVertices >= 2);
	assert(m_pLineVertices);
	assert(m_ucFlags & FLG_RAD_REDOSTENCIL);	// Should only be called when the stencil needs updating.

	m_ucFlags = m_ucFlags ^ FLG_RAD_REDOSTENCIL;	// Turn off flag.

	// Set the render target, stencil surface, and render states.
	PrepareDeviceData(true);
	
	// Clear all surfaces, as a change in stencil requires a redraw of everything.
	CDeviceManager& rDeviceManager = m_pRenderer->GetDeviceManager();
	rDeviceManager.DeviceClear(true, false, true, 0x00000000, 0.0f, 0);

	rDeviceManager.SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);	// Always...
	rDeviceManager.SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);	// Replace the existing stencil values.
	
	const float kfFraction((2.0f * MathUtility::PI) / (m_uiNumLineVertices - 1));	// m_uiNumVertices guaranteed >= 2, so no div/0.
	const float kfOuterRadius(0.5f * m_uiDiameter);

	// Draw lines into the stencil.
	if(SUCCEEDED(m_pLine->Begin()))
	{
		// Set render states so the line can draw into the stencil.
		rDeviceManager.SetRenderState(D3DRS_STENCILREF, 0x2);	// With 0x2.

		// Draw shapes into stencil, beginning with the circle.

		for (unsigned int ui = 0; ui < m_uiNumLineVertices; ++ui)
		{
			m_pLineVertices[ui].x = kfOuterRadius + (cosf(kfFraction * ui) * m_fInnerRadius);
			m_pLineVertices[ui].y = kfOuterRadius + (sinf(kfFraction * ui) * m_fInnerRadius);
		}

		// Draw circle.
		m_pLine->Draw(m_pLineVertices, m_uiNumLineVertices, 0x00000000);	// Writes 0x2 into the stencil.

		// Draw each dividing line, if greater than one.
		if (m_ucNumButtons > 1)
		{
			const float kfFraction((2.0f * MathUtility::PI) / m_ucNumButtons);	// m_ucNumButtons guaranteed non-zero.

			for (unsigned char uc = 0; uc < m_ucNumButtons; ++uc)
			{
				m_pLineVertices[0].x = kfOuterRadius + (cosf(kfFraction * uc) * m_fInnerRadius);
				m_pLineVertices[0].y = kfOuterRadius + (sinf(kfFraction * uc) * m_fInnerRadius);

				m_pLineVertices[1].x = kfOuterRadius + (cosf(kfFraction * uc) * kfOuterRadius);
				m_pLineVertices[1].y = kfOuterRadius + (sinf(kfFraction * uc) * kfOuterRadius);

				m_pLine->Draw(m_pLineVertices, 2, 0x00000000);	// Writes 0x2 into the stencil.
			}
		}
		// Else there is only one button, so do not draw any dividers.

		m_pLine->End();
	}

	// Draw stencil'd circle in the middle.
	CVertexBuffer* pBuffer = m_pRenderer->GetVertexBufferManager().GetVertexBuffer(m_uiVertexBufferMaskID);
	if (pBuffer)
	{
		if (pBuffer->IsVerticesDynamic())
		{
			CVertexSCSP* pVertices = reinterpret_cast<CVertexSCSP*>(pBuffer->GetDynamicVertices());
			assert(pVertices);
			
			pVertices->SetPos(m_uiDiameter * 0.5f, m_uiDiameter * 0.5f);

			for (unsigned int ui = 1; ui < pBuffer->GetVertexBufferData().m_uiNumVerts; ++ui)
			{
				pVertices[ui].SetPos(kfOuterRadius + (cosf(kfFraction * ui) * m_fInnerRadius), kfOuterRadius + (sinf(kfFraction * ui) * m_fInnerRadius));
			}
			
			rDeviceManager.SetRenderState(D3DRS_STENCILREF, 0x1);
			pBuffer->UpdateDynamicVertices();
			pBuffer->Render(rDeviceManager);
		}
	}
}

/**
*
* ITS = Into Target Surface (render target).
* The radiant light surface is drawn into the render target surface, using the stencil surface for masking.
* m_ucButtonSelected is then highlighted (Utility::INVALID_ID highlights the centre).
*
* @author Jade Abbott
* @return Void.
*
*/ 
void
CRadialMenu::DrawRadianceITS()
{
	assert(m_pRenderer);
	assert(m_uiVertexBufferQuadID != Utility::INVALID_ID);

	// Replace the backbuffer with the Radial Menu's render target and stencil, disabling Z-buffer and enabling stencil.
	PrepareDeviceData(true);

	CDeviceManager& rDeviceManager = m_pRenderer->GetDeviceManager();

	// Set render states that will prevent drawing of the radiant light where the stencil has been marked out.
	rDeviceManager.SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATER);	// Greater is less, and less is greater (no friggin idea why).
	rDeviceManager.SetRenderState(D3DRS_STENCILREF, 0x2);	// When less than 0x2...
	rDeviceManager.SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	// Do not edit stencil, just draw.

	// Render the radiant light surface on to the back buffer.
	m_pRenderer->GetTextureManager().SetTexture(m_iRadiantTextureID);	// Set the texture to the radiant light.

	CVertexBufferManager& rBufferManager = m_pRenderer->GetVertexBufferManager();

	CVertexBuffer* pBuffer = rBufferManager.GetVertexBuffer(m_uiVertexBufferQuadID);	// Get the dynamic quad mesh.
	if (pBuffer)
	{
		if (pBuffer->IsVerticesDynamic())
		{
			// Update the position of each vertex in the mesh.
			CVertex1TexSCSP* pVertices = reinterpret_cast<CVertex1TexSCSP*>(pBuffer->GetDynamicVertices());

			// Rasterisation rules require minimum values have 0.5 subtracted, and maximum values have 0.5 added.
			float fDiameter = static_cast<float>(m_uiDiameter) + 0.5f;
			pVertices[0].SetPos(-0.5f, -0.5f);
			pVertices[1].SetPos(fDiameter, -0.5f);
			pVertices[2].SetPos(-0.5f, fDiameter);
			pVertices[3].SetPos(fDiameter, fDiameter);

			pBuffer->UpdateDynamicVertices();	// Will update the mesh only when necessary.
		}

		rDeviceManager.SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// Have the radiant light replace the entire image.

		rBufferManager.Render(m_uiVertexBufferQuadID);
	}
}

/**
*
* ITS = Into Target Surface (render target).
* This highlights the current button selected.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CRadialMenu::DrawHighlightITS()
{
	assert(m_pRenderer);
	assert(m_uiVertexBufferMaskID != Utility::INVALID_ID);

	// Replace the backbuffer with the Radial Menu's render target and stencil, disabling Z-buffer and enabling stencil.
	PrepareDeviceData(true);

	CDeviceManager& rDeviceManager = m_pRenderer->GetDeviceManager();

	CVertexBuffer* pBuffer = m_pRenderer->GetVertexBufferManager().GetVertexBuffer(m_uiVertexBufferMaskID);
	assert(pBuffer);

	if (pBuffer->IsVerticesDynamic())
	{
		CVertexSCSP* pVertices = reinterpret_cast<CVertexSCSP*>(pBuffer->GetDynamicVertices());
		assert(pVertices);

		// Set render states.
		rDeviceManager.SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);	// When equal to the value previously provided...
		rDeviceManager.SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	// Do not edit stencil, just draw.
		rDeviceManager.SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	// Allow blending.
		rDeviceManager.SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_ADD);	// Merge colour components for a highlight effect.
		rDeviceManager.SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_ADD);	// Merge alpha components as well, so more of the button is lit.
		rDeviceManager.SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTCOLOR);	// To the Radial Menu's colour (make brighter).

		unsigned int uiNumVerts = 0;	// Used later in the for loop.
		float fRadius = m_uiDiameter * 0.5f;	// fRadius == centre of image
		
		// Count the number of disabled buttons there are, create a highlight for each, the apply the selection highlight.
		for (unsigned char ucButton = 0; ucButton <= m_ucNumButtons; ++ucButton)
		{
			unsigned char ucButtonToHighlight = MathUtility::kMaxUC;

			if (ucButton == m_ucNumButtons)	// If this is the final run...
			{
				ucButtonToHighlight = m_ucButtonSelected;	// Apply highlight to the button the user has selected.
				rDeviceManager.SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);	// Blend the Radial Menu's colour...
			}
			else if (m_arrButtonData[ucButton].m_bDisabled)
			{
				ucButtonToHighlight = ucButton;	// Apply highlight to the disabled button.
				rDeviceManager.SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTALPHA);	// Blend the colourless mask...
			}
			else
			{
				continue;	// This button is neither disabled nor selected.
			}

			if (ucButtonToHighlight == MathUtility::kMaxUC || m_ucNumButtons == 1)
			{
				if (ucButtonToHighlight == MathUtility::kMaxUC)
					rDeviceManager.SetRenderState(D3DRS_STENCILREF, 0x1);	// The value of the centre button.
				else
					rDeviceManager.SetRenderState(D3DRS_STENCILREF, 0x0);	// The value of an ordinary button.

				// Highlight the entire area.
				uiNumVerts = 4;
				pVertices[0].SetPos(-0.5f, -0.5f);
				pVertices[1].SetPos(m_uiDiameter + 0.5f, -0.5f);
				pVertices[2].SetPos(m_uiDiameter + 0.5f, m_uiDiameter + 0.5f);
				pVertices[3].SetPos(-0.5f, m_uiDiameter + 0.5f);
			}
			else
			{
				rDeviceManager.SetRenderState(D3DRS_STENCILREF, 0x0);	// The value of an ordinary button.

				if (m_ucNumButtons == 2)	// Highlight either the top half or bottom half.
				{
					uiNumVerts = 4;
					float fTop = ucButtonToHighlight == 0 ? -0.5f : fRadius;
					float fBottom = ucButtonToHighlight == 0 ? fRadius : m_uiDiameter + 0.5f;
					pVertices[0].SetPos(-0.5f, fTop);
					pVertices[1].SetPos(m_uiDiameter + 0.5f, fTop);
					pVertices[2].SetPos(m_uiDiameter + 0.5f, fBottom);
					pVertices[3].SetPos(-0.5f, fBottom);
				}
				else	// A slice of pie.
				{
					uiNumVerts = 3;
					float fFraction = (2.0f * MathUtility::PI) / m_ucNumButtons;	// fFraction = radians per button.
					pVertices[0].SetPos(fRadius, fRadius);

					float fY = -sinf(fFraction * (ucButtonToHighlight + 1)) * m_fOuterPlanarLength;
					pVertices[1].SetPos(fRadius + (cosf(fFraction * (ucButtonToHighlight + 1)) * m_fOuterPlanarLength),
										fRadius + fY);

					fY = -sinf(fFraction * ucButtonToHighlight) * m_fOuterPlanarLength;
					pVertices[2].SetPos(fRadius + (cosf(fFraction * ucButtonToHighlight) * m_fOuterPlanarLength),
										fRadius + fY);
				}
			}

			pBuffer->UpdateDynamicVertices(uiNumVerts);
			pBuffer->Render(rDeviceManager, uiNumVerts);
		}
	}
}

/**
*
* ITS = Into Target Surface (render target).
* The icons for each button are drawn into the render target surface.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CRadialMenu::DrawIconsITS()
{
	assert(m_pRenderer);
	assert(m_ucNumButtons);

	if (m_arrButtonData)
	{
		if (m_uiVertexBufferQuadID != Utility::INVALID_ID)
		{
			CVertexBuffer* pBuffer = m_pRenderer->GetVertexBufferManager().GetVertexBuffer(m_uiVertexBufferQuadID);
			assert(pBuffer);

			if (pBuffer->IsVerticesDynamic())
			{
				CVertex1TexSCSP* pVertices = reinterpret_cast<CVertex1TexSCSP*>(pBuffer->GetDynamicVertices());
				assert(pVertices);

				CTextureManager& rTextureManager = m_pRenderer->GetTextureManager();
				CDeviceManager& rDeviceManager = m_pRenderer->GetDeviceManager();
				PrepareDeviceData(true);
				EnsureTexturedAlphaBlending();
				rDeviceManager.SetRenderState(D3DRS_STENCILREF, 0x0);
				
				float fAngle = (2.0f * MathUtility::PI) / m_ucNumButtons;
				float fRadius = m_uiDiameter * 0.5f;
				float fHalfScale = m_uiDiameter * 0.0625f;	// If diameter is 512, this equals 32 (for 64x64 images).

				for (unsigned char uc = 0; uc < m_ucNumButtons; ++uc)
				{
					if (m_arrButtonData[uc].m_pkReferenceData)
					{
						if (m_arrButtonData[uc].m_pkReferenceData->m_iIconTextureID != Utility::INVALID_ID)
						{
							float fDistance = m_fInnerRadius + ((fRadius - m_fInnerRadius) * 0.5f);
							float fPosX = fRadius + (cosf((fAngle * uc) + (fAngle * 0.5f)) * fDistance);
							float fPosY = fRadius - (sinf((fAngle * uc) + (fAngle * 0.5f)) * fDistance);

							pVertices[0].SetPos(fPosX - fHalfScale, fPosY - fHalfScale);
							pVertices[1].SetPos(fPosX + fHalfScale, fPosY - fHalfScale);
							pVertices[2].SetPos(fPosX - fHalfScale, fPosY + fHalfScale);
							pVertices[3].SetPos(fPosX + fHalfScale, fPosY + fHalfScale);

							rTextureManager.SetTexture(m_arrButtonData[uc].m_pkReferenceData->m_iIconTextureID);

							pBuffer->UpdateDynamicVertices();
							pBuffer->Render(rDeviceManager);
						}
					}
				}
			}
		}
	}
}

/**
*
* IFT = Into Final Texture.
* The Radial Menu image is assembled by drawing into the Render Target.
* But to render that image in-game, it must be copied to a texture.
* This function copies the Render Target's surface to the Final Texture's surface.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CRadialMenu::CopyTargetSurfaceIFT()
{
	assert(m_pRenderer);
	assert(m_iFinalTextureID != Utility::INVALID_ID);
	assert(m_uiRenderTargetID != Utility::INVALID_ID);

	// Get the render target's surface (which contains the assembled Radial Menu image).
	IDirect3DSurface9* pRenderTarget = m_pRenderer->GetSurfaceManager().GetSurface(m_uiRenderTargetID);
	assert(pRenderTarget);

	// Get the final texture.
	IDirect3DTexture9* pTexture = m_pRenderer->GetTextureManager().GetTexture(m_iFinalTextureID);
	assert(pTexture);

	// Get the surface from the texture, and copy the render target's surface into it.
	IDirect3DSurface9* pTextureSurface = 0;
	if (SUCCEEDED(pTexture->GetSurfaceLevel(0, &pTextureSurface)))
	{
		assert(pTextureSurface);

		D3DXLoadSurfaceFromSurface(pTextureSurface, 0, 0, pRenderTarget, 0, 0, D3DX_FILTER_NONE, 0);

		pTextureSurface->Release();
		pTextureSurface = 0;
	}
}

/**
*
* Renders the Final Texture into the game window.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CRadialMenu::RenderFinalTextureToScreen()
{
	assert(m_pRenderer);
	assert(m_iFinalTextureID != Utility::INVALID_ID);
	assert(m_uiVertexBufferQuadID != Utility::INVALID_ID);

	// Prepare the vertices on the quad for rendering.
	CVertexBuffer* pVertexBuffer = m_pRenderer->GetVertexBufferManager().GetVertexBuffer(m_uiVertexBufferQuadID);
	assert(pVertexBuffer);

	if (pVertexBuffer->IsVerticesDynamic())
	{
		CVertex1TexSCSP* pVertices = reinterpret_cast<CVertex1TexSCSP*>(pVertexBuffer->GetDynamicVertices());
		assert(pVertices);

		float fRadius = (m_uiDiameter * 0.5f) + 0.5f;	// + 0.5f for rasterisation rules.

		pVertices[0].SetPos(m_fDrawPositionX - fRadius, m_fDrawPositionY - fRadius);
		pVertices[1].SetPos(m_fDrawPositionX + fRadius, m_fDrawPositionY - fRadius);
		pVertices[2].SetPos(m_fDrawPositionX - fRadius, m_fDrawPositionY + fRadius);
		pVertices[3].SetPos(m_fDrawPositionX + fRadius, m_fDrawPositionY + fRadius);

		pVertexBuffer->UpdateDynamicVertices();
	}

	// Set the texture to render with.
	m_pRenderer->GetTextureManager().SetTexture(m_iFinalTextureID);

	// Render the quad.
	EnsureTexturedAlphaBlending();

	pVertexBuffer->Render(m_pRenderer->GetDeviceManager());
}

/**
*
* A polygon must be constructed that will cover an entire button.
* This function determines the length of each side of the polygon, to ensure complete coverage of a button.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CRadialMenu::CalculateOuterPlanarLength()
{
	assert(m_ucNumButtons >= 3);
	assert(m_uiDiameter);

	float fRadius = m_uiDiameter * 0.5f;

	// Get the distance from the centre of the Radial Menu to the outer plane that will cover an entire button (requires two, but each vertex has the same length).
	float fAngle = ((2.0f * MathUtility::PI) / m_ucNumButtons) * 0.5f;	// Angle of this line.

	// From (0.0f, -fRadius), see where fAngle intersects the Y plane.
	float fScalar = cosf(fAngle) / fRadius;	// Percentage of distance covered.
	
	m_fOuterPlanarLength = D3DXVec2Length(&D3DXVECTOR2(fRadius, sinf(fAngle) / fScalar));
}

/**
*
* Sets or restores critical render states used by the Radial Menu.
* Functionality exists here, as these settings will need to be restored to their original state when the Radial Menu is finished.
*
* When enabling:
* Sets the Radial Menu's render target as the current render target.
* Sets the Radial Menu's stencil surface as the current stencil surface.
* Disables Z-buffer usage.
* Enables stencil buffer usage.
*
* When disabling:
* Restores the original render target.
* Restores the original stencil surface.
* Enables Z-buffer usage.
* Restores original state defining whether stencil was being used or not.
*
* @author Jade Abbott
* @param _bEnable Whether to set or restore critical render states used by the Radial Menu.
* @return Void.
*
*/
void
CRadialMenu::PrepareDeviceData(bool _bEnable)
{
	assert(m_pRenderer);
	CDeviceManager& rDeviceManager = m_pRenderer->GetDeviceManager();

	if (_bEnable)
	{
		if (!(m_ucFlags & FLG_RAD_STATES))	// If states are being applied...
		{
			CSurfaceManager& rSurfaceManager = m_pRenderer->GetSurfaceManager();

			// Obtain original render states.
			m_dwOriginalStencilState = rDeviceManager.GetRenderStateValue(D3DRS_STENCILENABLE);

			// Apply new render states.
			rDeviceManager.SetRenderTarget(rSurfaceManager.GetSurface(m_uiRenderTargetID));
			rDeviceManager.SetDepthStencilSurface(rSurfaceManager.GetSurface(m_uiStencilID));
			rDeviceManager.SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			rDeviceManager.SetRenderState(D3DRS_STENCILENABLE, TRUE);

			m_ucFlags = m_ucFlags | FLG_RAD_STATES;
		}
	}
	else
	{
		if (m_ucFlags & FLG_RAD_STATES)	// If states are being reset...
		{
			// Restore original render states.
			rDeviceManager.RestoreDefaultRenderTarget();
			rDeviceManager.RestoreDefaultDepthStencilSurface();
			rDeviceManager.SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

			rDeviceManager.SetRenderState(D3DRS_STENCILENABLE, m_dwOriginalStencilState);

			m_ucFlags = m_ucFlags ^ FLG_RAD_STATES;
		}
	}
}

/**
*
* Since alpha blending may not be enabled, this ensures it is enabled.
* Is necessary to render the Radial Menu properly.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CRadialMenu::EnsureTexturedAlphaBlending()
{
	assert(m_pRenderer);
	CDeviceManager& rDeviceManager = m_pRenderer->GetDeviceManager();

	rDeviceManager.SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	rDeviceManager.SetTextureStageState(0, D3DTSS_COLOROP, D3DTA_TEXTURE);
	rDeviceManager.SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	rDeviceManager.SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	rDeviceManager.SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	rDeviceManager.SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
}

/**
*
* Releases the Radial Menu's IDirect3DDevice9 resources.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CRadialMenu::OnDeviceLost()
{
	if (m_pLine)
	{
		m_pLine->OnLostDevice();
	}

	if (m_pRenderer)
	{
		m_pRenderer->GetSurfaceManager().DestroySurface(m_uiStencilID);
		m_pRenderer->GetSurfaceManager().DestroySurface(m_uiRenderTargetID);
		m_uiStencilID = Utility::INVALID_ID;
		m_uiRenderTargetID = Utility::INVALID_ID;
	}
}

/**
*
* Restores the Radial Menu's IDirect3DDevice9 resources.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CRadialMenu::OnDeviceReset()
{
	if (m_pLine)
	{
		m_pLine->OnResetDevice();
	}

	assert(m_uiStencilID == Utility::INVALID_ID);
	assert(m_uiRenderTargetID == Utility::INVALID_ID);

	CreateStencil();
	CreateRenderTarget();
}