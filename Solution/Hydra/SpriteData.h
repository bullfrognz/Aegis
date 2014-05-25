#ifndef __SPRITEDATA_H__
#define __SPRITEDATA_H__

#include <d3dx9.h>
#include "WorldMatrix.h"

class CSpriteData
{
public:
	CSpriteData();
	~CSpriteData();

	void SetID(unsigned int _uiID);
	unsigned int GetID();

	void SetTextureID(unsigned int _uiID);
	unsigned int GetTextureID();

	void SetWorldMatrix(CWorldMatrix& _rWorldMatrix);
	CWorldMatrix& GetWorldMatrix();

	void SetCenter(D3DXVECTOR3* _vecCenter);
	D3DXVECTOR3* GetCenter();

	void SetRECT(RECT* _pRect);
	RECT* GetRect();

	void SetMaxRect(RECT* _pRect);
	RECT* GetMaxRect();

	void SetCordSpace(bool _bWorldCoords);
	bool IsWorldCords();

	void SetVisible(bool _bVisible);
	bool IsVisible() const;

	void SetModulate(UINT _uiModulate);
	UINT GetModulate();

private:
	bool m_bWorldCords;
	RECT m_Rect;
	RECT m_MaxRect;
	CWorldMatrix m_matxWorldMatrix;
	D3DXVECTOR3 m_vecCenter;
	unsigned int m_uiTextureID;
	unsigned int m_uiIconID;
	bool m_bVisible;
	UINT m_uiModulateColour;
};

#endif //__SPRITEDATA_H__