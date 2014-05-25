//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Vertex1TexSCSP.cpp
//	Description	:	Definition of CVertex1TexSCSP
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// This include.
#include "Vertex1TexSCSP.h"

CVertex1TexSCSP::CVertex1TexSCSP()
: m_fRHW(0.0f)
, m_fU(0.0f)
, m_fV(0.0f)
{
	m_vecPos.x = 0.0f;
	m_vecPos.y = 0.0f;
	m_vecPos.z = 0.0f;
}

CVertex1TexSCSP::CVertex1TexSCSP(const D3DXVECTOR3& krVecPos, float _fU, float _fV)
: m_fRHW(0.0f)
, m_fU(_fU)
, m_fV(_fV)
{
	m_vecPos = krVecPos;
}

CVertex1TexSCSP::~CVertex1TexSCSP()
{

}
	
DWORD
CVertex1TexSCSP::GetFVF() const
{
	return D3DFVF_XYZRHW | D3DFVF_TEX1;
}

unsigned int
CVertex1TexSCSP::GetSizeOf() const
{
	return sizeof(CVertex1TexSCSP);
}

void
CVertex1TexSCSP::SetTextureCoordinates(float _fHorzU, float _fVertV)
{
	m_fU = _fHorzU;
	m_fV = _fVertV;
}

float
CVertex1TexSCSP::GetTextureCoordHorzU() const
{
	return m_fU;
}

float
CVertex1TexSCSP::GetTextureCoordVertV() const
{
	return m_fV;
}

void
CVertex1TexSCSP::SetPos(float _fX, float _fY)
{
	m_vecPos.x = _fX;
	m_vecPos.y = _fY;
}

void
CVertex1TexSCSP::operator=(const CVertex1TexSCSP& _rhs)
{
	m_vecPos = _rhs.m_vecPos;
	m_fRHW = _rhs.m_fRHW;
	m_fU = _rhs.m_fU;
	m_fV = _rhs.m_fV;
}