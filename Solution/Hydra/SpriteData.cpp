#include "SpriteData.h"

CSpriteData::CSpriteData()
:m_bWorldCords(false)
,m_uiTextureID(0)
,m_uiIconID(0)
,m_bVisible(true)
,m_uiModulateColour(0xFFFFFFFF)
{
	m_vecCenter.x = 0;
	m_vecCenter.y = 0;
	m_vecCenter.z = 0;

	m_Rect.bottom = 1;
	m_Rect.left = 0;
	m_Rect.right = 1;
	m_Rect.top = 0;

	D3DXMatrixScaling(&m_matxWorldMatrix,(1.0f/32.0f),(1.0f/128.0f),(1.0f/128.0f));
}

CSpriteData::~CSpriteData()
{
}

void CSpriteData::SetID(unsigned int _uiID)
{
	m_uiIconID = _uiID;
}

unsigned int CSpriteData::GetID()
{
	return m_uiIconID;
}

void CSpriteData::SetTextureID(unsigned int _uiID)
{
	m_uiTextureID = _uiID;
}

unsigned int CSpriteData::GetTextureID()
{
	return m_uiTextureID;
}

void
CSpriteData::SetWorldMatrix(CWorldMatrix& _rWorldMatrix)
{
	m_matxWorldMatrix = _rWorldMatrix;
}

CWorldMatrix& CSpriteData::GetWorldMatrix()
{
	return (m_matxWorldMatrix);
}

void CSpriteData::SetCenter(D3DXVECTOR3* _vecCenter)
{
	m_vecCenter = *_vecCenter;
}

D3DXVECTOR3* CSpriteData::GetCenter()
{
	return &m_vecCenter;
}

void CSpriteData::SetRECT(RECT* _pRect)
{
	m_Rect = *_pRect;
}

RECT* CSpriteData::GetRect()
{
	return &m_Rect;
}

void CSpriteData::SetCordSpace(bool _bWorldCoords)
{
	m_bWorldCords = _bWorldCoords;
}

bool CSpriteData::IsWorldCords()
{
	return m_bWorldCords;
}

void CSpriteData::SetMaxRect(RECT* _pRect)
{
	m_MaxRect = *_pRect;
	D3DXVECTOR3 Centre((static_cast<float>(_pRect->right - _pRect->left) / 2.0f), (static_cast<float>(_pRect->bottom - _pRect->top) / 2.0f), 0.0f);

	SetCenter(&Centre);
}

RECT* CSpriteData::GetMaxRect()
{
	return &m_MaxRect;
}

void CSpriteData::SetVisible(bool _bVisible)
{
	m_bVisible = _bVisible;
}


bool CSpriteData::IsVisible() const
{
	return (m_bVisible);
}

void CSpriteData::SetModulate(UINT _uiModulate)
{
	m_uiModulateColour = _uiModulate;
}

UINT CSpriteData::GetModulate()
{
	return m_uiModulateColour;
}