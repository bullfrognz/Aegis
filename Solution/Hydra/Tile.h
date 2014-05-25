//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Tile.h
//  Description :   Declaration of CTile files
//  Author      :   Daniel Langsford, Jade Abbott
//  Mail        :   daniel.langsford@mediadesign.school.nz
//				:	jade.abbott@mediadesign.school.nz
//
#pragma once

#ifndef __IGFEB11_IG500_TILE_H__
#define __IGFEB11_IG500_TILE_H__

// Library Includes

// Local Includes
#include "WorldMatrix.h"

// Types
enum ETileType
{
	TILETYPE_BLANK	= 0,
	TILETYPE_RAISED	= 1,
	TILETYPE_WATER	= 2,
	TILETYPE_PATH	= 3,
	TILETYPE_START	= 4,
	TILETYPE_END	= 5,

	TILETYPE_MAX	= 32	// 0-31 are supported.
};

enum ETileObject
{
	TILEOBJ_NONE	= 0,
	TILEOBJ_TOWER	= 1,
	TILEOBJ_TREE	= 2,
	
	TILEOBJ_MAX	= 8	// 0-7 are supported.
};

class CStaticObject;

class CTile
{
// Member Functions
public:
	inline CTile();
	inline CTile(ETileType _eTileType, ETileObject _eObjectType);
	inline CTile(unsigned char _ucRawData);
	inline ~CTile();

	inline void SetTileType(ETileType _eTileType);
	inline ETileType GetTileType() const;

	inline void SetObjectType(ETileObject _eObjectType);
	inline ETileObject GetObjectType() const;

	inline void SetObjectID(unsigned int _uiID);
	inline unsigned int GetObjectID() const;

	inline void SetRawData(unsigned char _ucRawData);
	inline unsigned char GetRawData() const;

	inline void SetPosition(const CWorldMatrix& _rkRhs);
	inline const CWorldMatrix& GetWorldMatrix() const;
	inline D3DXVECTOR3& GetPosition(D3DXVECTOR3& _rVecOut) const;

protected:

private:

// Member Variables
public:

protected:
	CWorldMatrix m_matWorld;

	unsigned int m_uiObjectID;	// Object on top of this tile.
	unsigned char m_ucData;	// Raw data (bit flags).
	// 3 bytes padding.

private:
};

#include "Tile.inl"

#endif // __IGFEB11_IG500_TILE_H__
