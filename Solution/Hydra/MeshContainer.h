//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   MeshContainer.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_MESHCONTAINER_H__
#define __IGFEB11_IG500_MESHCONTAINER_H__


// Library Includes
#include <d3dx9.h>
#include <vector>


// Local Includes


// Types


// Constants


// Prototypes
class CD3DRenderer;
class CMatrix;


class CMeshContainer : public D3DXMESHCONTAINER
{

	// Member Functions
public:


	 CMeshContainer();
	~CMeshContainer();


	bool Initialise(CD3DRenderer* _pRenderer,
					const char* _kcpContainerName,
					D3DXMESHDATATYPE _d3dMeshType,
					const D3DXMESHDATA* _kd3dpMeshData,
					const DWORD* _kdwpAdjacency, 
					const D3DXMATERIAL* _kd3dpMeshMaterial,
					unsigned int _uiNumMaterials,
					ID3DXSkinInfo* _d3dpSkinInfo);


	// Inline Functions


protected:


	bool InitialiseName(const char* _kcpContainerName);
	bool IntiailiseMeshData(const D3DXMESHDATA* _kd3dpMeshData);
	bool InitialiseAdjacency(const DWORD* _kdwpAdjacency);
	bool InitialiseTexturesMaterials(CD3DRenderer* _pRenderer, const D3DXMATERIAL* _kd3dpMeshMaterial, unsigned int _uiNumMaterials);
	bool IntiialiseSkinInfo(ID3DXSkinInfo* _d3dpSkinInfo);


	void SaveMaterials(std::vector<const D3DMATERIAL9*>& _vecrMaterials);
	void SaveTextures(std::vector<int>& _vecrTextures);


private:


	void Deinitialise();


	CMeshContainer(const CMeshContainer& _krMeshContainer);
	CMeshContainer& operator = (const CMeshContainer& _krMeshContainer);


	// Member Variables
protected:


public:

		
	int* m_ipTextures;					// Array of texture pointers 
	D3DMATERIAL9* m_d3dpMaterials;		// Array of materials


	// Skinned mesh variables
	ID3DXMesh* m_d3dpSkinMesh;			// The skin mesh
	CMatrix*   m_d3dpBoneMatrices;		// The bones for the mesh 
	CMatrix*   m_d3dpBoneOffsets;		// The bone matrix Offsets, offset matrices to move the vertices from the figure space to the bone's space
	CMatrix**  m_d3dppFrameMatrices;		// Array of frame matrix


	unsigned int m_uiNumBones;


};


#endif //__IGFEB11_IG500_MESHCONTAINER_H__