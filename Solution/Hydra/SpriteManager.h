#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__

#include <vector>
#include <map>

#include "SpriteData.h"
#include "TextureManager.h"
#include "DeviceResetTarget.h"

class CD3DRenderer;
class CVector3;

class CSpriteManager : public CDeviceResetTarget
{
public:
	CSpriteManager();
	~CSpriteManager();

	bool Initalise(CTextureManager* _pTextureSource, CD3DRenderer* _pRenderer, LPD3DXSPRITE _pSprite);
	void ShutDown();

	void EraseAll();

	void Draw();
	void DrawScreen();
	void DrawWorld();

	int AddSprite(LPWSTR _pFileName);
	bool RemoveSprite(unsigned int _iID);

	bool SetRect(RECT* _pRect, unsigned int _iID);
	bool SetCenter(D3DXVECTOR3* _pCenter, unsigned int _iID);
	bool SetPosition(CVector3& _rv3Position, unsigned int _iID);
	bool SetWorldMatrix(CWorldMatrix& _rWorldMatrix, unsigned int _iID);
	bool SetPosition(float _fX, float _fY, float _fZ, unsigned int _iID);
	bool SetVisible(bool _bVisible, unsigned int _iID);
	bool SetObjectSpace(bool _bIsObjectSpace, unsigned int _iID);
	bool SetModulate(UINT _uiModulate, unsigned int _iID);

	int Duplicate(unsigned int _iID);

	CVector3 GetPositionScaled(unsigned int _iID);
	RECT GetRect(unsigned int _iID);
	CVector3 GetPosition(unsigned int _iID);
	CVector3& GetCentre(unsigned int _uiID);

	virtual void OnDeviceLost();
	virtual void OnDeviceReset();
private:
	CTextureManager* m_pTextureSource;
	CD3DRenderer* m_pRenderer;

	LPD3DXSPRITE m_pSpriteInterface;

	std::map<LPWSTR,unsigned int> m_LoadedSprites;

	unsigned int m_uiTotalSprites;
	std::vector<CSpriteData*> m_SpriteData;
	static unsigned int m_uiNextID;
};

#endif //__SPRITEMANAGER_H__