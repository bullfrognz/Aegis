// This include.
#include "Vertex2TexturedNormal.h"

CVertex2TexturedNormal::CVertex2TexturedNormal()
: m_fU2(0.0f)
, m_fV2(0.0f)
{

}

CVertex2TexturedNormal::CVertex2TexturedNormal(const D3DXVECTOR3& krVecPos,
						   const D3DXVECTOR3& _krVecNormal,
						   float _fHorzU1, float _fVertV1,
						   float _fHorzU2, float _fVertV2)
: m_fU2(_fHorzU2)
, m_fV2(_fVertV2)
{
	m_fU1 = _fHorzU1;
	m_fV1 = _fVertV1;
	m_vecPos = krVecPos;
	m_vecNormal = _krVecNormal;
}

CVertex2TexturedNormal::~CVertex2TexturedNormal()
{

}

DWORD
CVertex2TexturedNormal::GetFVF() const
{
	return D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2;
}

unsigned int
CVertex2TexturedNormal::GetSizeOf() const
{
	return sizeof(CVertex2TexturedNormal);
}

void
CVertex2TexturedNormal::SetTextureCoordinates(float _fHorzU1, float _fVertV1, float _fHorzU2, float _fVertV2)
{
	m_fU1 = _fHorzU1;
	m_fV1 = _fVertV1;
	m_fU2 = _fHorzU2;
	m_fV2 = _fVertV2;
}

void
CVertex2TexturedNormal::ScaleTextureCoordinates2(const float _kfScale)
{
	m_fU2 *= _kfScale;
	m_fV2 *= _kfScale;
}

float
CVertex2TexturedNormal::GetTextureCoordHorzU2() const
{
	return m_fU2;
}

float
CVertex2TexturedNormal::GetTextureCoordVertV2() const
{
	return m_fV2;
}

void
CVertex2TexturedNormal::operator=(const CVertex2TexturedNormal& _rhs)
{
	m_vecPos = _rhs.m_vecPos;
	m_vecNormal = _rhs.m_vecNormal;
	m_fU1 = _rhs.m_fU1;
	m_fV1 = _rhs.m_fV1;
	m_fU2 = _rhs.m_fU2;
	m_fV2 = _rhs.m_fV2;
}