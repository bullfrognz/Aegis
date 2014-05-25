// This include
#include "Vertex.h"

CVertex::CVertex()
: m_vecPos(0.0f, 0.0f, 0.0f)
{

}

CVertex::~CVertex()
{

}

D3DXVECTOR3&
CVertex::GetPos()
{
	return m_vecPos;
}

void
CVertex::SetPos(const D3DXVECTOR3 &_rhs)
{
	m_vecPos = _rhs;	// Shallow copy.
}

void
CVertex::SetPos(const float _kfX, const float _kfY, const float _kfZ)
{
	m_vecPos.x = _kfX;
	m_vecPos.y = _kfY;
	m_vecPos.z = _kfZ;
}