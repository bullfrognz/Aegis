//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2011 Media Design School
//
//  File Name   :   TextureManager.h
//  Description :   Class that holds, sets and destroys CTextureSet objects
//  Author      :   Joshua Print
//  Mail        :   joshua.print@mediadesign.school.nz
//

#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <vector>
#include <d3dx9.h>
#include <map>
#include <string>
class CD3DRenderer;

struct TextureItem
{
	LPDIRECT3DTEXTURE9 m_pTexture;
	unsigned int m_uiID;
};

class CTextureManager
{
public:
	CTextureManager();
	~CTextureManager();

	bool Initalise(IDirect3DDevice9* _pDevice, CD3DRenderer* _pRenderer);
	void ShutDown();

	void RemoveTexture(int _iID);

	LPDIRECT3DTEXTURE9 GetTexture(int _iID);

	int LoadTextureFile(LPCWSTR _pcFileName);
	int LoadTextureMemory(LPDIRECT3DTEXTURE9 _pTexture);

	bool SetTexture(int _iID);


	bool HasTextureBeenLoaded(LPCWSTR _wcpTextureFile, unsigned int& _uirLoadedTextureId);
	void CacheTextureFile(LPCWSTR _wcpTextureFile, unsigned int _uiTextureId);


private:
	std::vector<TextureItem*> m_pTexture;

	CD3DRenderer* m_pRenderer;
	IDirect3DDevice9* m_pDevice;

	unsigned int m_uiNextTextureID;

	unsigned int m_uiTotalTextures;


	std::map<std::string, unsigned int> m_mapLoadedTextures;
	

};

#endif // __TEXTUREMANAGER_H__