//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Vertex1Textured.cpp
//	Description	:	Definition of CVertex1Textured
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// This include.
#include "Vertex1Textured.h"

CVertex1Textured::CVertex1Textured()
: m_fU(0.0f)
, m_fV(0.0f)
{

}

CVertex1Textured::CVertex1Textured(const D3DXVECTOR3& krVecPos, float _fHorzU, float _fVertV)
: m_fU(_fHorzU)
, m_fV(_fVertV)
{
	m_vecPos = krVecPos;
}

CVertex1Textured::~CVertex1Textured()
{

}

DWORD
CVertex1Textured::GetFVF() const
{
	return D3DFVF_XYZ | D3DFVF_TEX1;
}

unsigned int
CVertex1Textured::GetSizeOf() const
{
	return sizeof(CVertex1Textured);
}

void
CVertex1Textured::SetTextureCoordinates(float _fHorzU, float _fHorzV)
{
	m_fU = _fHorzU;
	m_fV = _fHorzV;
}

float
CVertex1Textured::GetTextureCoordHorzU() const
{
	return m_fU;
}

float
CVertex1Textured::GetTextureCoordVertV() const
{
	return m_fV;
}

void
CVertex1Textured::operator=(const CVertex1Textured& _rhs)
{
	m_vecPos = _rhs.m_vecPos;
	m_fU = _rhs.m_fU;
	m_fV = _rhs.m_fV;
}