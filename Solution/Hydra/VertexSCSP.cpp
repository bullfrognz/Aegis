//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	VertexSCSP.cpp
//	Description	:	Definition of CVertexSCSP (Screen Space)
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// This include.
#include "VertexSCSP.h"

CVertexSCSP::CVertexSCSP()
: m_fRHW(0.0f)
{
	m_vecPos.x = 0.0f;
	m_vecPos.y = 0.0f;
	m_vecPos.z = 0.0f;
}

CVertexSCSP::CVertexSCSP(const D3DXVECTOR3& krVecPos)
: m_fRHW(0.0f)
{
	m_vecPos = krVecPos;
}

CVertexSCSP::~CVertexSCSP()
{

}
	
DWORD
CVertexSCSP::GetFVF() const
{
	return D3DFVF_XYZRHW;
}

unsigned int
CVertexSCSP::GetSizeOf() const
{
	return sizeof(CVertexSCSP);
}

void
CVertexSCSP::SetPos(float _fX, float _fY)
{
	m_vecPos.x = _fX;
	m_vecPos.y = _fY;
}

void
CVertexSCSP::operator=(const CVertexSCSP& _rhs)
{
	m_vecPos = _rhs.m_vecPos;
	m_fRHW = _rhs.m_fRHW;
}