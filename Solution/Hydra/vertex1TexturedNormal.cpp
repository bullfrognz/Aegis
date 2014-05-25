// This include.
#include "Vertex1TexturedNormal.h"

CVertex1TexturedNormal::CVertex1TexturedNormal()
: m_fU1(0.0f)
, m_fV1(0.0f)
{

}

CVertex1TexturedNormal::CVertex1TexturedNormal(const D3DXVECTOR3& krVecPos, const D3DXVECTOR3& _krVecNormal, float _fHorzU1, float _fVertV1)
: m_fU1(_fHorzU1)
, m_fV1(_fVertV1)
{
	m_vecPos = krVecPos;
	m_vecNormal = _krVecNormal;
}

CVertex1TexturedNormal::~CVertex1TexturedNormal()
{

}

DWORD
CVertex1TexturedNormal::GetFVF() const
{
	return D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
}

unsigned int
CVertex1TexturedNormal::GetSizeOf() const
{
	return sizeof(CVertex1TexturedNormal);
}

void
CVertex1TexturedNormal::SetTextureCoordinates(float _fHorzU1, float _fVertV1)
{
	m_fU1 = _fHorzU1;
	m_fV1 = _fVertV1;
}

void
CVertex1TexturedNormal::ScaleTextureCoordinates1(const float _kfScale)
{
	m_fU1 *= _kfScale;
	m_fV1 *= _kfScale;
}

float
CVertex1TexturedNormal::GetTextureCoordHorzU1() const
{
	return m_fU1;
}

float
CVertex1TexturedNormal::GetTextureCoordVertV1() const
{
	return m_fV1;
}

void
CVertex1TexturedNormal::operator=(const CVertex1TexturedNormal& _rhs)
{
	m_vecPos = _rhs.m_vecPos;
	m_vecNormal = _rhs.m_vecNormal;
	m_fU1 = _rhs.m_fU1;
	m_fV1 = _rhs.m_fV1;
}