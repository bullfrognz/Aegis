//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Tile.inl
//  Description :   Implementation of CTile files
//  Author      :   Daniel Langsford, Jade Abbott
//  Mail        :   daniel.langsford@mediadesign.school.nz
//				:	jade.abbott@mediadesign.school.nz
//

// Local includes.
#include "Matrix.h"
#include "Utility.h"

// [8|7|6|5|4|3|2|1] : Bit number.
// [O|O|O|T|T|T|T|T] : O = Object type; T = Tile Type.
#define GET_TILETYPE(data) (static_cast<ETileType>(data & 31))			/* Get tile type	*/
#define GET_TILEOBJ(data) (static_cast<ETileObject>(data >> 5))	/* Get object type on tile	*/
#define SET_TILETYPE(data, flag) (data = ((data & 224) | flag))			/* Set tile type	*/
#define SET_TILEOBJ(data, flag) (data = ((data & 31) | (flag << 5)))	/* Set type of object on tile	*/

CTile::CTile()
: m_uiObjectID(Utility::INVALID_ID)
, m_ucData(0)
{

}

CTile::CTile(ETileType _eTileType, ETileObject _eObjectType)
: m_uiObjectID(Utility::INVALID_ID)
, m_ucData(0)
{
	SET_TILETYPE(m_ucData, _eTileType);
	SET_TILEOBJ(m_ucData, _eObjectType);
}

CTile::CTile(unsigned char _ucRawData)
: m_uiObjectID(Utility::INVALID_ID)
, m_ucData(_ucRawData)
{

}

CTile::~CTile()
{

}

/**
*
* @author Daniel Langsford, Jade Abbott
*
*/
void
CTile::SetTileType(ETileType _eTileType)
{
	SET_TILETYPE(m_ucData, _eTileType);
}

/**
*
* @author Daniel Langsford, Jade Abbott
*
*/
void
CTile::SetObjectType(ETileObject _eObjectType)
{
	SET_TILEOBJ(m_ucData, _eObjectType);
}

/**
*
* @author Daniel Langsford, Jade Abbott
*
*/
void
CTile::SetObjectID(unsigned int _uiID)
{
	m_uiObjectID = _uiID;
}

/**
*
* @author Daniel Langsford, Jade Abbott
*
*/
unsigned int
CTile::GetObjectID() const
{
	return m_uiObjectID;
}

/**
*
* For loading from .ini file.
*
* @author Daniel Langsford, Jade Abbott
*
*/
void
CTile::SetRawData(unsigned char _ucRawData)
{
	m_ucData = _ucRawData;
}

/**
*
* For saving to .ini file.
*
* @author Daniel Langsford, Jade Abbott
*
*/
unsigned char
CTile::GetRawData() const
{
	CMatrix mat;
	mat._41 = 2.0f;
	return m_ucData;
}

/**
*
* @author Daniel Langsford, Jade Abbott
*
*/
void
CTile::SetPosition(const CWorldMatrix& _rkRhs)
{
	m_matWorld = _rkRhs;
}

/**
*
* @author Daniel Langsford, Jade Abbott
*
*/
const CWorldMatrix&
CTile::GetWorldMatrix() const
{
	return m_matWorld;
}

/**
*
* @author Daniel Langsford, Jade Abbott
*
*/
D3DXVECTOR3&
CTile::GetPosition(D3DXVECTOR3& _rVecOut) const
{
	return reinterpret_cast<D3DXVECTOR3&>(m_matWorld.GetPosition(reinterpret_cast<CVector3&>(_rVecOut)));
}

/**
*
* @author Daniel Langsford, Jade Abbott
*
*/
ETileType
CTile::GetTileType() const
{
	return GET_TILETYPE(m_ucData);
}

/**
*
* @author Daniel Langsford, Jade Abbott
*
*/
ETileObject
CTile::GetObjectType() const
{
	return GET_TILEOBJ(m_ucData);
}