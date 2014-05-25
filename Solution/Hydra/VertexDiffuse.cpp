//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	VertexDiffuse.cpp
//	Description	:	Definition of CVertexDiffuse
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// This include.
#include "VertexDiffuse.h"

CVertexDiffuse::CVertexDiffuse()
{
	
}

CVertexDiffuse::CVertexDiffuse(const D3DXVECTOR3& krVecPos, D3DCOLOR _Diffuse)
: m_Diffuse(_Diffuse)
{
	m_vecPos = krVecPos;
}

CVertexDiffuse::~CVertexDiffuse()
{
	
}

DWORD
CVertexDiffuse::GetFVF() const
{
	return D3DFVF_XYZ | D3DFVF_DIFFUSE;
}

unsigned int
CVertexDiffuse::GetSizeOf() const
{
	return sizeof(CVertexDiffuse);
}

void
CVertexDiffuse::SetDiffuseColour(D3DCOLOR _Diffuse)
{
	m_Diffuse = _Diffuse;
}

void
CVertexDiffuse::operator=(const CVertexDiffuse& _rhs)
{
	m_vecPos = _rhs.m_vecPos;
	m_Diffuse = _rhs.m_Diffuse;
}