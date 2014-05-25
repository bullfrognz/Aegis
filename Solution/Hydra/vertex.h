#pragma once
#ifndef __IVERTEX_H__
#define __IVERTEX_H__

// Library includes.
#include <d3dx9.h>

class CVertex
{
	// Member functions.
public:
	CVertex();
	~CVertex();

	D3DXVECTOR3& GetPos();
	void SetPos(const D3DXVECTOR3& _rhs);
	void SetPos(const float _kfX, const float _kfY, const float _kfZ);

protected:

private:

	// Member data.
public:

protected:
	D3DXVECTOR3 m_vecPos;

private:
};

#endif	// __IVERTEX_H__