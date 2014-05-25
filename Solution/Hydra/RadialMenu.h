//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	RadialMenu.h
//	Description	:	Declaration of CRadialMenu
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __HYDRA_RADIALMENU_H__
#define __HYDRA_RADIALMENU_H__

// Library includes.
struct ID3DXLine;
struct D3DXVECTOR2;

// Local includes.
#include "DeviceResetTarget.h"
class CD3DRenderer;
class CHud;
struct THudData;

struct TRadialMenuButtonData
{
	typedef void (* VPRadialButton)(void* _pMemberData, unsigned char _ucButton);	// When a button is clicked, this function is called.

	const THudData* m_pkReferenceData;	// The reference data contains information about every selectable object.

	void* m_pInstanceMemberData;	// Function pointer points to static functions. This void pointer points to actual instance data (provide "this" when creating).
	VPRadialButton m_pStaticMemberFunction;	// Function to call when the button is clicked.

	bool m_bDisabled;	// Set to true to make this button unclickable.
	bool m_bNoDisable;	// Prevents button from being automatically disabled (for buttons that have no value).
};

class CRadialMenu : public CDeviceResetTarget
{
	// Member functions.
public:
	CRadialMenu();
	virtual ~CRadialMenu();

	bool Initialise(CD3DRenderer* _pRenderer,
					CHud* _pHud,
					unsigned int _uiMaximumDiameter,
					unsigned int _uiMaxLines,
					float _fLineWidth,
					float _fInnerCircleScalar,
					float _fDrawPositionX,
					float _fDrawPositionY);

	bool OnResolutionChange(unsigned int _uiMaximumDiameter,
							float _fDrawPositionX,
							float _fDrawPositionY);

	void Process(unsigned int _uiX, unsigned int _uiY);

	void Process(float* _pfRadians);

	void ExecuteButton();

	void Draw();

	bool Open(unsigned char _ucNumButtons);	// Do not use Radial Menu if this function returns false.
	void Close();
	bool IsOpen() const;

	void AutoDisableButtons(unsigned int _uiMaximumAffordable);

	inline TRadialMenuButtonData& GetButtonData(unsigned char _ucButton);	// Use immediately after opening menu.

	bool SetMaxLines(unsigned int _uiMaxLines);
	void SetInnerCircleRadius(float _fRadius);

	inline float GetDrawPositionX() const;
	inline float GetDrawPositionY() const;

protected:
	bool CreateStencil();				// Called at initialisation, and when the device is lost.
	inline bool CreateRenderTarget();	// Called at initialisation, and when the device is lost.
	bool CreateFinalTexture();			// Called at initialisation.
	bool CreateLine(float _fWidth);		// Called at initialisation.
	bool CreateRadiance();				// Called at initialisation; Creates radiant light.
	bool CreateVertexBufferQuad();		// Called at initialisation.
	bool CreateVertexBufferMask(unsigned int _uiNumFaces);		// Called at initialisation, and when the max lines for the inner circle has increased.

	void AssembleStencil();				// Called at runtime.
	void DrawRadianceITS();				// Called at runtime; Copies the radiant light image Into Target Surface.
	void DrawHighlightITS();			// Called at runtime; Draws selected button highlight Into Target Surface.
	void DrawIconsITS();				// Called at runtime; Draws button icons Into Target Surface.
	void CopyTargetSurfaceIFT();		// Called at runtime; Copies Target Surface Into Final Texture.
	void RenderFinalTextureToScreen();	// Called at runtime; Renders the Radial Menu.

	void CalculateOuterPlanarLength();
	void PrepareDeviceData(bool _bEnable);
	void EnsureTexturedAlphaBlending();

	virtual void OnDeviceLost();
	virtual void OnDeviceReset();

private:

	// Member data.
public:

protected:
	ID3DXLine* m_pLine;

	CD3DRenderer* m_pRenderer;

	CHud* m_pHud;

	unsigned int m_uiStencilID;			// Stencil surface.
	int m_iRadiantTextureID;	// The radiant light image.
	unsigned int m_uiRenderTargetID;	// Render target.
	int m_iFinalTextureID;	// Render target is copied into this, which is rendered to screen.

	unsigned int m_uiVertexBufferQuadID;	// For rendering textured screen-space quads (D3DFVF_XYZRHW).
	unsigned int m_uiVertexBufferMaskID;	// For defining certain areas of an image and applying effects.

	unsigned int m_uiDiameter;
	float m_fInnerRadius;
	float m_fOuterPlanarLength;	// Used in construction of a polygon that will cover an entire button.

	float m_fDrawPositionX;	// Centre of draw position.
	float m_fDrawPositionY;	// Centre of draw position.


	int m_iOpenPositionX; // Cursor position X on open
	int m_iOpenPositionY; // Cursor position Y on open


	D3DXVECTOR2* m_pLineVertices;	// For rendering with ID3DXLine;
	unsigned int m_uiNumLineVertices;

	const THudData* m_pkOldHudData;	// When mouse over the centre button, the old data will be shown (when upgrading towers, this will be the current tower data).

	TRadialMenuButtonData* m_arrButtonData;
	unsigned char m_ucNumButtons;
	unsigned char m_ucButtonSelected;

	unsigned char m_ucFlags;

	// For restoring original render states.
	unsigned long m_dwOriginalStencilState;

private:
};

#include "RadialMenu.inl"

#endif	// __HYDRA_RADIALMENU_H__