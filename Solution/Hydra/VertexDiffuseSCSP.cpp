//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	VertexDiffuseSCSP.cpp
//	Description	:	Definition of CVertexDiffuseSCSP (Screen Space)
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// This include.
#include "VertexDiffuseSCSP.h"

CVertexDiffuseSCSP::CVertexDiffuseSCSP()
: m_fRHW(0.0f)
, m_dwDiffuse(0)
{
	m_vecPos.x = 0.0f;
	m_vecPos.y = 0.0f;
	m_vecPos.z = 0.0f;
}

CVertexDiffuseSCSP::CVertexDiffuseSCSP(const D3DXVECTOR3& krVecPos, D3DCOLOR _dwDiffuse)
: m_fRHW(0.0f)
, m_dwDiffuse(_dwDiffuse)
{
	m_vecPos = krVecPos;
}

CVertexDiffuseSCSP::~CVertexDiffuseSCSP()
{

}
	
DWORD
CVertexDiffuseSCSP::GetFVF() const
{
	return D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
}

unsigned int
CVertexDiffuseSCSP::GetSizeOf() const
{
	return sizeof(CVertexDiffuseSCSP);
}

void
CVertexDiffuseSCSP::SetPos(float _fX, float _fY)
{
	m_vecPos.x = _fX;
	m_vecPos.y = _fY;
}
	
void
CVertexDiffuseSCSP::SetDiffuse(D3DCOLOR _dwDiffuse)
{
	m_dwDiffuse = _dwDiffuse;
}

void
CVertexDiffuseSCSP::operator=(const CVertexDiffuseSCSP& _rhs)
{
	m_vecPos = _rhs.m_vecPos;
	m_fRHW = _rhs.m_fRHW;
}