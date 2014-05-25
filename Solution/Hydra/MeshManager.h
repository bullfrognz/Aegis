//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	MeshManager.h
//	Description	:	Declaration of CMeshManager
//	Author		:	Jade Abbott, Bryce Booth
//	Mail		:	jade.abbott@mediadesign.school.nz
//				:	bryce.booth@mediadesign.school.nz
//

#pragma once
#ifndef __MESHMANAGER_H__
#define __MESHMANAGER_H__

// Library includes.
#include <d3dx9.h>
#include <map>
#include <string>

// Local includes.
#include "VertexBuffer.h"	// For the TStaticBufferData structure.
class CTextureManager;
class CDeviceManager;
class CAnimatedMesh;

struct TMeshManagerData
{
	wchar_t* m_pFileName;	// Required for foolproofing.
	ID3DXMesh* m_pMesh;

	D3DMATERIAL9* m_arrMaterials;
	DWORD m_dwNumMaterials;	// Num materials = num subsets.

	int* m_iArrTextureID;	// Array of texture ID's used by the texture manager; One for each material (array size == m_dwNumMaterials).

	TVertexBufferData m_VertexData;	// Copy of the vertices, for processing the AABB, bounding sphere, etc.

	// Adjacency / 3 = number of polygons.
	// Each material refers to a texture.
};

class CMeshManager
{
	// Member functions.
public:
	CMeshManager();
	~CMeshManager();

	bool Initialise(IDirect3DDevice9* _pDevice, CDeviceManager* _pDeviceManager, CTextureManager* _pTextureManager);

	unsigned int CreateNewMesh(const wchar_t* _pwFileName);
	void DeleteMesh(unsigned int _uiID);

	void Render(unsigned int _uiID);

	const TVertexBufferData& GetVertexData(unsigned int _uiID);

	void DrawBoundingSphere(unsigned int _uiID);

	void ChangeTexture(unsigned int _uiMeshID, unsigned int _uiTextureIteration, unsigned int _uiNewTextureID);



	void Process(float _fDeltaTick);


	unsigned int CreateNewMeshHeirarchy(const char* _kcpMeshFile);
	void ProcessAnimatedMesh(unsigned int _uiAnimatedMeshId, float _fDeltaTick);
	void RenderAnimatedMesh(unsigned int _uiAnimatedMeshId, CD3DRenderer* _pRenderer);

	bool CheckLoadedAnimatedMesh(const char* _kcpMeshFile, unsigned int& _uirAnimatedMeshId);
	void LoadAnimatedMesh(const char* _kcpMeshFile,
						  D3DXFRAME*& _d3drpFrameHeirarchy,
					      ID3DXAnimationController*& _d3dprAnimationController);



	CAnimatedMesh* CloneAnimatedMesh(unsigned int _uiAnimatedMeshId);
	unsigned int   StoreAdimatedMesh(const char* _kcpMeshFile, CAnimatedMesh* _pAnimatedMesh);
	CAnimatedMesh* GetAnimatedMesh(unsigned int _uiAnimatedMeshId);


protected:
	bool IncreaseMeshArraySize();

private:

	// Member data.
public:

protected:
	IDirect3DDevice9* m_pDevice;
	CDeviceManager* m_pDeviceManager;
	CTextureManager* m_pTextureManager;	// Uses CRenderer's texture manager.

	TMeshManagerData** m_arrpMeshes;	// Array of mesh data.
	unsigned int m_uiNumMeshes;

	TVertexBufferData m_EmptyBuffer;	// When invalid data is requested, a template container is provided.


	std::map<int, CAnimatedMesh*> m_mapAniamtedMeshes;
	std::map<std::string, int>    m_mapAnimatedMesheFiles;


private:
};

#endif	// __MESHMANAGER_H__