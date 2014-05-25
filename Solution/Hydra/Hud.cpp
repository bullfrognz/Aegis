//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Hud.cpp
//	Description	:	Definition of CHud
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// Library includes.
#include <cassert>

// Local includes.
#include "Utility.h"
#include "Vertex1TexSCSP.h"
#include "VertexDiffuseSCSP.h"
#include "D3DRenderer.h"
#include "Enemy.h"
#include "Tower.h"
#include "Terrain.h"
#include "HudDataManager.h"
#include "Player.h"
#include "EnemySpawner.h"
#include "WaveManager.h"
#include "TextureManager.h"
#include "LogWindow.h"
#include "DeviceManager.h"
#include "VertexBufferManager.h"

// This include.
#include "Hud.h"

CHud::CHud()
: m_pRenderer(0)
, m_pPlayer(0)
, m_pWaveManager(0)
, m_pkSelectionData(0)
, m_pkExtendedInfo(0)
, m_fHudWidth(0.0f)
, m_fHudHeight(0.0f)
, m_uiBaseVertexID(Utility::INVALID_ID)
, m_iBaseTextureID(Utility::INVALID_ID)
, m_uiMapVertexID(Utility::INVALID_ID)
, m_iMapTextureID(Utility::INVALID_ID)
, m_uiIconVertexID(Utility::INVALID_ID)
, m_uiMarkerVertexID(Utility::INVALID_ID)
, m_fMarkerPosScalar(0.0f)
, m_uiTextTitleID(Utility::INVALID_ID)
, m_uiTextBodyID(Utility::INVALID_ID)
, m_uiBoxNameID(Utility::INVALID_ID)
, m_uiBoxTooltipID(Utility::INVALID_ID)
, m_uiBoxStatsID(Utility::INVALID_ID)
, m_uiBoxPlayerID(Utility::INVALID_ID)
{
	ZeroMemory(&m_rectBaseBounds, sizeof(THudRect));
	ZeroMemory(&m_rectMapBounds, sizeof(THudRect));
	ZeroMemory(&m_rectIconBounds, sizeof(THudRect));
}

CHud::~CHud()
{
	
}

/**
*
* Initialises the HUD.
*
* @author Jade Abbott
*
*/
bool
CHud::Initialise(CD3DRenderer* _pRenderer,
				 const CPlayer* _pPlayer,
				 const CWaveManager* _pWaveManager,
				 unsigned int _uiScreenWidth,
				 unsigned int _uiScreenHeight,
				 const wchar_t* _pkwMiniMapTextureFile)
{
	assert(_pRenderer);

	m_pRenderer = _pRenderer;
	m_pPlayer = _pPlayer;
	m_pWaveManager = _pWaveManager;

	// Get the base texture for the HUD.
	m_iBaseTextureID = m_pRenderer->GetTextureManager().LoadTextureFile(L"Assets\\Textures\\HudTexture.png");

	// Get the texture for the mini map.
	if (_pkwMiniMapTextureFile)
		m_iMapTextureID = m_pRenderer->GetTextureManager().LoadTextureFile(_pkwMiniMapTextureFile);

	// Handle everything that requires scaling.
	if (!OnResolutionChange(_uiScreenWidth, _uiScreenHeight))
		return false;

	return true;
}

/**
*
* Call this after the map has been loaded.
*
* @author Jade Abbott
*
*/
void
CHud::InitialiseTerrain(const CTerrain& _rTerrain)
{
	float fSpacing = _rTerrain.GetTileSpacing();
	unsigned int uiX = _rTerrain.GetGridWidth();
	unsigned int uiY = _rTerrain.GetGridHeight();
	m_fMarkerPosScalar = 1.0f / ((uiX > uiY ? uiX : uiY) * fSpacing);
}

/**
*
* Renders the HUD image, text, icons, mini map, etc.
* That which makes up the HUD is rendered in this call, excluding the dots that indicate where towers and enemies are.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CHud::Draw()
{
	assert(m_pRenderer);

	CTextureManager& rTextureManager = m_pRenderer->GetTextureManager();
	CVertexBufferManager& rVertexBufferManager = m_pRenderer->GetVertexBufferManager();

	// Ensure alpha blending is enabled.
	CDeviceManager& rDeviceManager = m_pRenderer->GetDeviceManager();
	
	rDeviceManager.SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	rDeviceManager.SetTextureStageState(0, D3DTSS_COLOROP, D3DTA_TEXTURE);
	rDeviceManager.SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	rDeviceManager.SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Draw base image.
	rTextureManager.SetTexture(m_iBaseTextureID);
	rVertexBufferManager.Render(m_uiBaseVertexID);

	// Draw mini map.
	rTextureManager.SetTexture(m_iMapTextureID);
	rVertexBufferManager.Render(m_uiMapVertexID);

	// Draw player status.
	CLogWindow& rLogWindow = m_pRenderer->GetLogWindow();
	if (m_uiTextTitleID != Utility::INVALID_ID)
		rLogWindow.SetFont(m_uiTextBodyID);

	rLogWindow.EmptyBuffer();
	rLogWindow.WriteToBuffer("Lives:");
	rLogWindow.WriteToBuffer("Gold:");
	rLogWindow.WriteToBuffer("Wave:");
	rLogWindow.PrintToScreen(m_uiBoxPlayerID);
	
	rLogWindow.EmptyBuffer();

	if (m_pPlayer)
	{
		rLogWindow.WriteToBuffer("%i", m_pPlayer->GetLives());
		rLogWindow.WriteToBuffer("%i", m_pPlayer->GetGold());
	}

	if (m_pWaveManager)
	{
		rLogWindow.WriteToBuffer("%i / %i", (m_pWaveManager->GetCurrentWaveCount() + 1), m_pWaveManager->m_uiWaveAmount);
	}

	rLogWindow.PrintToScreen(m_uiBoxPlayerID, 0xFFFFFFFF, DT_TOP | DT_RIGHT);

	// Draw selected object information.
	if (m_pkSelectionData)
	{
		// Object's icon.
		rTextureManager.SetTexture(m_pkSelectionData->m_iIconTextureID);
		rVertexBufferManager.Render(m_uiIconVertexID);

		// Object's name (gets put up like a title).
		if (m_pkSelectionData->m_pcName && m_uiBoxNameID != Utility::INVALID_ID)
		{
			if (m_uiTextTitleID != Utility::INVALID_ID)
				rLogWindow.SetFont(m_uiTextTitleID);

			rLogWindow.EmptyBuffer();
			rLogWindow.WriteToBuffer("%s", m_pkSelectionData->m_pcName);
			rLogWindow.PrintToScreen(m_uiBoxNameID);
		}

		// Object's tooltip (appears on right).
		if (m_pkSelectionData->m_pcTooltip && m_uiBoxTooltipID != Utility::INVALID_ID)
		{
			if (m_uiTextBodyID != Utility::INVALID_ID)
				rLogWindow.SetFont(m_uiTextBodyID);

			rLogWindow.EmptyBuffer();
			rLogWindow.WriteToBuffer("%s", m_pkSelectionData->m_pcTooltip);
			rLogWindow.PrintToScreen(m_uiBoxTooltipID);
		}

		// Object's stats, and extended info (if any).
		rLogWindow.EmptyBuffer();
		rLogWindow.WriteToBuffer("Value:");

		if (m_pkExtendedInfo || m_pkSelectionData->m_pExtraData)
		{
			rLogWindow.WriteToBuffer("Damage:");
			rLogWindow.WriteToBuffer("Range:");
			rLogWindow.WriteToBuffer("Fire Rate:");
			//rLogWindow.WriteToBuffer("Targets:");
		}

		rLogWindow.PrintToScreen(m_uiBoxStatsID);

		rLogWindow.EmptyBuffer();
		rLogWindow.WriteToBuffer("$%i", m_pkSelectionData->m_uiValue);

		if (m_pkSelectionData->m_pExtraData)
		{
			rLogWindow.WriteToBuffer("%.0f-%.0f", m_pkSelectionData->m_pExtraData->m_fMinDamage, m_pkSelectionData->m_pExtraData->m_fMaxDamage);
			rLogWindow.WriteToBuffer("%.1f", m_pkSelectionData->m_pExtraData->m_fRange);
			rLogWindow.WriteToBuffer("%.1f/s", m_pkSelectionData->m_pExtraData->m_fFireRate);
		}
		else if (m_pkExtendedInfo)
		{
			rLogWindow.WriteToBuffer("%.0f-%.0f", m_pkExtendedInfo->GetMinDamage(), m_pkExtendedInfo->GetMaxDamage());
			rLogWindow.WriteToBuffer("%.1f", m_pkExtendedInfo->GetRange());

			float fFireDelay = m_pkExtendedInfo->GetFireRate();	// The value returned is actually the time between each shot.
			rLogWindow.WriteToBuffer("%.1f/s", fFireDelay ? 1 / fFireDelay : 0.0f);
		}

		rLogWindow.PrintToScreen(m_uiBoxStatsID, 0xFFFFFFFF, DT_TOP | DT_RIGHT);
	}
}

/**
*
* Renders markers for towers on the mini-map.
*
* @author Jade Abbott
*
*/
void
CHud::DrawTowerMarkers(const CTower* const* const _arrpTowers, unsigned int _uiNumTowers)
{
	assert(sizeof(CVector3) == sizeof(D3DXVECTOR3));
	assert(m_pRenderer);

	if (m_uiMarkerVertexID == Utility::INVALID_ID || !_uiNumTowers || !_arrpTowers)
		return;
	
	CVertexBuffer* pBuffer = m_pRenderer->GetVertexBufferManager().GetVertexBuffer(m_uiMarkerVertexID);
	assert(pBuffer);

	if (!pBuffer->IsVerticesDynamic())
		return;

	CVertexDiffuseSCSP* pVertices = reinterpret_cast<CVertexDiffuseSCSP*>(pBuffer->GetDynamicVertices());
	assert(pVertices);

	// Set the colour of the vertices.
	pVertices[0].SetDiffuse(D3DCOLOR_XRGB(0, 32, 255));
	pVertices[1].SetDiffuse(D3DCOLOR_XRGB(0, 32, 255));
	pVertices[2].SetDiffuse(D3DCOLOR_XRGB(0, 32, 255));
	pVertices[3].SetDiffuse(D3DCOLOR_XRGB(0, 32, 255));

	//Ensure there is no colour blending with the markers and the mini map.
	m_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLOROP, D3DTA_CURRENT);

	for (unsigned int ui = 0; ui < _uiNumTowers; ++ui)
	{
		if (_arrpTowers[ui])
		{
			D3DXVECTOR3 vecPos;
			_arrpTowers[ui]->GetWorldMatrix_s().GetPosition(*reinterpret_cast<CVector3*>(&vecPos));

			float fWidth = m_rectMapBounds.m_fRight - m_rectMapBounds.m_fLeft;
			float fHeight = m_rectMapBounds.m_fBottom - m_rectMapBounds.m_fTop;

			// Translate the enemy's position into scalar values for use on the mini map.
			vecPos.x = (m_rectMapBounds.m_fLeft + (fWidth * 0.5f)) + ((vecPos.x * m_fMarkerPosScalar) * fWidth);
			vecPos.y = (m_rectMapBounds.m_fBottom - (fHeight * 0.5f)) - ((vecPos.z * m_fMarkerPosScalar) * fHeight);

			// Do not draw if outside the mini-map.
			if (vecPos.x < m_rectMapBounds.m_fLeft || vecPos.x > m_rectMapBounds.m_fRight || vecPos.y < m_rectMapBounds.m_fTop || vecPos.y > m_rectMapBounds.m_fBottom)
				continue;

			// Set the location of the vertices.
			pVertices[0].SetPos(vecPos.x, vecPos.y - 6.0f);
			pVertices[1].SetPos(vecPos.x + 6.0f, vecPos.y);
			pVertices[2].SetPos(vecPos.x - 6.0f, vecPos.y);
			pVertices[3].SetPos(vecPos.x, vecPos.y + 6.0f);

			pBuffer->UpdateDynamicVertices();
			pBuffer->Render(m_pRenderer->GetDeviceManager());
		}
	}
}

/**
*
* Renders markers for all the enemies.
*
* @author Jade Abbott
*
*/
void
CHud::DrawEnemyMarkers()
{
	assert(sizeof(CVector3) == sizeof(D3DXVECTOR3));
	assert(m_pRenderer);

	std::vector<CEnemy*>& vecEnemyInstances = CEnemySpawner::GetEnemyInstances();
	unsigned int _uiNumEnemies = static_cast<unsigned int>(vecEnemyInstances.size());

	if (m_uiMarkerVertexID == Utility::INVALID_ID || !_uiNumEnemies)
		return;
	
	CVertexBuffer* pBuffer = m_pRenderer->GetVertexBufferManager().GetVertexBuffer(m_uiMarkerVertexID);
	assert(pBuffer);

	if (!pBuffer->IsVerticesDynamic())
		return;

	CVertexDiffuseSCSP* pVertices = reinterpret_cast<CVertexDiffuseSCSP*>(pBuffer->GetDynamicVertices());
	assert(pVertices);

	// Set the colour of the vertices.
	pVertices[0].SetDiffuse(D3DCOLOR_XRGB(255, 0, 0));
	pVertices[1].SetDiffuse(D3DCOLOR_XRGB(255, 0, 0));
	pVertices[2].SetDiffuse(D3DCOLOR_XRGB(255, 0, 0));
	pVertices[3].SetDiffuse(D3DCOLOR_XRGB(255, 0, 0));

	//Ensure there is no colour blending with the markers and the mini map.
	m_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLOROP, D3DTA_CURRENT);

	for (unsigned int ui = 0; ui < _uiNumEnemies; ++ui)
	{
		if (vecEnemyInstances[ui])
		{
			if (!vecEnemyInstances[ui]->IsAlive())
				continue;

			D3DXVECTOR3 vecPos;
			vecEnemyInstances[ui]->GetWorldMatrix_s().GetPosition(*reinterpret_cast<CVector3*>(&vecPos));

			float fWidth = m_rectMapBounds.m_fRight - m_rectMapBounds.m_fLeft;
			float fHeight = m_rectMapBounds.m_fBottom - m_rectMapBounds.m_fTop;

			// Translate the enemy's position into scalar values for use on the mini map.
			vecPos.x = (m_rectMapBounds.m_fLeft + (fWidth * 0.5f)) + ((vecPos.x * m_fMarkerPosScalar) * fWidth);
			vecPos.y = (m_rectMapBounds.m_fBottom - (fHeight * 0.5f)) - ((vecPos.z * m_fMarkerPosScalar) * fHeight);

			// Do not draw if outside the mini-map.
			if (vecPos.x < m_rectMapBounds.m_fLeft || vecPos.x > m_rectMapBounds.m_fRight || vecPos.y < m_rectMapBounds.m_fTop || vecPos.y > m_rectMapBounds.m_fBottom)
				continue;

			// Set the location of the vertices.
			pVertices[0].SetPos(vecPos.x, vecPos.y - 4.0f);
			pVertices[1].SetPos(vecPos.x + 4.0f, vecPos.y);
			pVertices[2].SetPos(vecPos.x - 4.0f, vecPos.y);
			pVertices[3].SetPos(vecPos.x, vecPos.y + 4.0f);

			pBuffer->UpdateDynamicVertices();
			pBuffer->Render(m_pRenderer->GetDeviceManager());
		}
	}
}

/**
*
* @author Jade Abbott
*
*/
void
CHud::SetSelectionData(const THudData* _pkData)
{
	m_pkSelectionData = _pkData;
}

/**
*
* @author Jade Abbott
*
*/
const THudData*
CHud::GetSelectionData() const
{
	return m_pkSelectionData;
}

/**
*
* @author Jade Abbott
*
*/
void
CHud::SetExtendedInfo(const CTower* _pTower)
{
	m_pkExtendedInfo = _pTower;
}

/**
*
* @author Jade Abbott
*
*/
float
CHud::GetUsedScreenHeight() const
{
	return m_rectBaseBounds.m_fBottom - m_rectBaseBounds.m_fTop;
}

/**
*
* This function handles everything to do with the screen resolution.
* This function should be called when the resolution changes in-game.
*
* @author Jade bbott
*
*/
bool
CHud::OnResolutionChange(unsigned int _uiScreenWidth, unsigned int _uiScreenHeight)
{
	assert(m_pRenderer);

	CLogWindow& rLogWindow = m_pRenderer->GetLogWindow();

	// Set the scaling of the HUD.
	m_fHudWidth = static_cast<float>(_uiScreenWidth);
	m_fHudHeight = _uiScreenHeight * 0.2f;	// 20% of the screen is occupied.
	float fSpaceX = m_fHudWidth * 0.01f;
	float fSpaceY = m_fHudHeight * 0.05f;

	// Calculate bounds of the base HUD, mini map, and icon.
	m_rectBaseBounds.m_fTop = _uiScreenHeight - m_fHudHeight;
	m_rectBaseBounds.m_fBottom = static_cast<float>(_uiScreenHeight);
	m_rectBaseBounds.m_fLeft = 0;
	m_rectBaseBounds.m_fRight = m_fHudWidth;

	m_rectMapBounds.m_fTop = m_rectBaseBounds.m_fTop + fSpaceY;
	m_rectMapBounds.m_fBottom = m_rectBaseBounds.m_fBottom - fSpaceY;
	m_rectMapBounds.m_fLeft = m_rectBaseBounds.m_fLeft + fSpaceX;
	m_rectMapBounds.m_fRight = m_rectMapBounds.m_fLeft + (m_rectMapBounds.m_fBottom - m_rectMapBounds.m_fTop);	// Ensures squared-ness.

	RECT rectPlayer;
	rectPlayer.top = static_cast<LONG>(m_rectMapBounds.m_fTop);
	rectPlayer.bottom = static_cast<LONG>(m_rectMapBounds.m_fBottom);
	rectPlayer.left = static_cast<LONG>(m_rectMapBounds.m_fRight + fSpaceX);
	rectPlayer.right = rectPlayer.left + static_cast<LONG>(m_rectMapBounds.m_fBottom - m_rectMapBounds.m_fTop);

	m_rectIconBounds.m_fTop = m_rectMapBounds.m_fTop;
	m_rectIconBounds.m_fBottom = m_rectMapBounds.m_fBottom;
	m_rectIconBounds.m_fLeft = rectPlayer.right + fSpaceX;
	m_rectIconBounds.m_fRight = m_rectIconBounds.m_fLeft + (m_rectMapBounds.m_fBottom - m_rectMapBounds.m_fTop);

	RECT rectTooltip;
	RECT rectName;
	rectTooltip.right = static_cast<LONG>(m_rectBaseBounds.m_fRight - fSpaceX);
	rectTooltip.left = static_cast<LONG>(rectTooltip.right - ((m_rectMapBounds.m_fRight - m_rectMapBounds.m_fLeft) * 2.0f));
	rectName.left = static_cast<LONG>(m_rectIconBounds.m_fRight + fSpaceX);
	rectName.right = rectTooltip.right;
	rectName.top = static_cast<LONG>(m_rectMapBounds.m_fTop);
	rectName.bottom = rectName.top + static_cast<LONG>(fSpaceY * 4.0f);
	rectTooltip.top = rectName.bottom;
	rectTooltip.bottom = rectPlayer.bottom;

	RECT rectStats;
	rectStats.left = static_cast<LONG>(m_rectIconBounds.m_fRight + fSpaceX);
	rectStats.right = static_cast<LONG>(rectTooltip.left - fSpaceX);
	rectStats.top = rectTooltip.top;
	rectStats.bottom = rectTooltip.bottom;

	if (m_uiBoxPlayerID != Utility::INVALID_ID)
	{
		rLogWindow.DeleteLogBox(m_uiBoxPlayerID);
	}

	if (m_uiBoxTooltipID != Utility::INVALID_ID)
	{
		rLogWindow.DeleteLogBox(m_uiBoxTooltipID);
	}

	if (m_uiBoxNameID != Utility::INVALID_ID)
	{
		rLogWindow.DeleteLogBox(m_uiBoxNameID);
	}

	if (m_uiBoxStatsID != Utility::INVALID_ID)
	{
		rLogWindow.DeleteLogBox(m_uiBoxStatsID);
	}

	m_uiBoxPlayerID = rLogWindow.CreateNewLogBox(D3DCOLOR_XRGB(192, 128, 0), rectPlayer, DT_TOP | DT_LEFT);
	m_uiBoxTooltipID = rLogWindow.CreateNewLogBox(0xFFFFFFFF, rectTooltip, DT_TOP | DT_RIGHT | DT_WORDBREAK);
	m_uiBoxNameID = rLogWindow.CreateNewLogBox(D3DCOLOR_XRGB(192, 128, 0), rectName, DT_LEFT);
	m_uiBoxStatsID = rLogWindow.CreateNewLogBox(D3DCOLOR_XRGB(192, 128, 0), rectStats, DT_TOP | DT_LEFT);

	// Create text fonts.
	if (m_uiTextTitleID != Utility::INVALID_ID)
	{
		rLogWindow.DeleteFont(m_uiTextTitleID);
	}

	if (m_uiTextBodyID != Utility::INVALID_ID)
	{
		rLogWindow.DeleteFont(m_uiTextBodyID);
	}

	m_uiTextTitleID = rLogWindow.CreateNewFont(static_cast<unsigned int>(fSpaceX * 2.0f), rectName.bottom - rectName.top, 1000, L"Arial Black");
	m_uiTextBodyID = rLogWindow.CreateNewFont(static_cast<unsigned int>(fSpaceX), static_cast<unsigned int>(m_fHudHeight * 0.15f), 0, L"Arial");

	// Align base image and minimap.
	CVertexBufferManager& rBufferManager = m_pRenderer->GetVertexBufferManager();

	// Create base image vertices.
	CVertex1TexSCSP* pVertices = new CVertex1TexSCSP[4];
	if (!pVertices)
		return false;

	pVertices[0].SetTextureCoordinates(0.0f, 0.0f);
	pVertices[1].SetTextureCoordinates(1.0f, 0.0f);
	pVertices[2].SetTextureCoordinates(0.0f, 1.0f);
	pVertices[3].SetTextureCoordinates(1.0f, 1.0f);
	pVertices[0].SetPos(m_rectBaseBounds.m_fLeft, m_rectBaseBounds.m_fTop);
	pVertices[1].SetPos(m_rectBaseBounds.m_fRight, m_rectBaseBounds.m_fTop);
	pVertices[2].SetPos(m_rectBaseBounds.m_fLeft, m_rectBaseBounds.m_fBottom);
	pVertices[3].SetPos(m_rectBaseBounds.m_fRight, m_rectBaseBounds.m_fBottom);

	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));

	CVertexBufferManager& rVertexManager = m_pRenderer->GetVertexBufferManager();

	if (m_uiBaseVertexID != Utility::INVALID_ID)
		rVertexManager.DeleteVertexBuffer(m_uiBaseVertexID);

	m_uiBaseVertexID = rVertexManager.CreateVertexBuffer(pVertices->GetFVF(), D3DPT_TRIANGLESTRIP, 4, 0, pVertices->GetSizeOf(), pVertices, 0, D3DFMT_UNKNOWN, material, false);

	// Create mini map vertices.
	pVertices = new CVertex1TexSCSP[4];
	if (!pVertices)
		return false;

	pVertices[0].SetTextureCoordinates(0.0f, 0.0f);
	pVertices[1].SetTextureCoordinates(1.0f, 0.0f);
	pVertices[2].SetTextureCoordinates(0.0f, 1.0f);
	pVertices[3].SetTextureCoordinates(1.0f, 1.0f);
	pVertices[0].SetPos(m_rectMapBounds.m_fLeft, m_rectMapBounds.m_fTop);
	pVertices[1].SetPos(m_rectMapBounds.m_fRight, m_rectMapBounds.m_fTop);
	pVertices[2].SetPos(m_rectMapBounds.m_fLeft, m_rectMapBounds.m_fBottom);
	pVertices[3].SetPos(m_rectMapBounds.m_fRight, m_rectMapBounds.m_fBottom);

	if (m_uiMapVertexID != Utility::INVALID_ID)
		rVertexManager.DeleteVertexBuffer(m_uiMapVertexID);

	m_uiMapVertexID = rVertexManager.CreateVertexBuffer(pVertices->GetFVF(), D3DPT_TRIANGLESTRIP, 4, 0, pVertices->GetSizeOf(), pVertices, 0, D3DFMT_UNKNOWN, material, false);

	// Create icon vertices.
	pVertices = new CVertex1TexSCSP[4];
	if (!pVertices)
		return false;

	pVertices[0].SetTextureCoordinates(0.0f, 0.0f);
	pVertices[1].SetTextureCoordinates(1.0f, 0.0f);
	pVertices[2].SetTextureCoordinates(0.0f, 1.0f);
	pVertices[3].SetTextureCoordinates(1.0f, 1.0f);
	pVertices[0].SetPos(m_rectIconBounds.m_fLeft, m_rectIconBounds.m_fTop);
	pVertices[1].SetPos(m_rectIconBounds.m_fRight, m_rectIconBounds.m_fTop);
	pVertices[2].SetPos(m_rectIconBounds.m_fLeft, m_rectIconBounds.m_fBottom);
	pVertices[3].SetPos(m_rectIconBounds.m_fRight, m_rectIconBounds.m_fBottom);

	if (m_uiIconVertexID != Utility::INVALID_ID)
		rVertexManager.DeleteVertexBuffer(m_uiIconVertexID);

	m_uiIconVertexID = rVertexManager.CreateVertexBuffer(pVertices->GetFVF(), D3DPT_TRIANGLESTRIP, 4, 0, pVertices->GetSizeOf(), pVertices, 0, D3DFMT_UNKNOWN, material, false);
	
	// Create marker vertices.
	CVertexDiffuseSCSP* pMarkers = new CVertexDiffuseSCSP[4];
	if (!pMarkers)
		return false;

	if (m_uiMarkerVertexID != Utility::INVALID_ID)
		rVertexManager.DeleteVertexBuffer(m_uiMarkerVertexID);

	m_uiMarkerVertexID = rVertexManager.CreateVertexBuffer(pMarkers->GetFVF(), D3DPT_TRIANGLESTRIP, 4, 0, pMarkers->GetSizeOf(), pMarkers, 0, D3DFMT_UNKNOWN, material, true);

	return true;
}