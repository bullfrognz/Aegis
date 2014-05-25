// This include.
#include "VertexNormal.h"

CVertexNormal::CVertexNormal()
: m_vecNormal(0.0f, 0.0f, 0.0f)
{

}

CVertexNormal::CVertexNormal(const D3DXVECTOR3& krVecPos, const D3DXVECTOR3& krVecNormal)
: m_vecNormal(krVecNormal)
{
	m_vecPos = krVecPos;
}

CVertexNormal::~CVertexNormal()
{

}

DWORD
CVertexNormal::GetFVF() const
{
	return D3DFVF_XYZ | D3DFVF_NORMAL;
}

unsigned int
CVertexNormal::GetSizeOf() const
{
	return sizeof(CVertexNormal);
}

void
CVertexNormal::SetNormal(const D3DXVECTOR3& _krVecNormal)
{
	m_vecNormal = _krVecNormal;
}

void
CVertexNormal::SetNormal(const float _kfX, const float _kfY, const float _kfZ)
{
	m_vecNormal.x = _kfX;
	m_vecNormal.y = _kfY;
	m_vecNormal.z = _kfZ;
}

void
CVertexNormal::AddNormal(const D3DXVECTOR3& _krVecNormal)
{
	m_vecNormal += _krVecNormal;
}

void
CVertexNormal::NormaliseNormal()
{
	D3DXVec3Normalize(&m_vecNormal, &m_vecNormal);
}

void
CVertexNormal::operator=(const CVertexNormal& _rhs)
{
	m_vecPos = _rhs.m_vecPos;
	m_vecNormal = _rhs.m_vecNormal;
}