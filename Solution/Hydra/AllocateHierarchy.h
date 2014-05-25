//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   AllocateHierarchy.h
//  Description :   -------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_ALLOCATEHIERARCHY_H__
#define __IGFEB11_IG500_ALLOCATEHIERARCHY_H__


// Library Includes
#include <d3dx9.h>
#include <d3dx9anim.h>


// Local Includes


// Types


// Constants


// Prototypes
class CD3DRenderer;


class CAllocateHierarchy : public ID3DXAllocateHierarchy
{


	// Member Functions
public:


	 CAllocateHierarchy();
	~CAllocateHierarchy();


	bool Intiailise(CD3DRenderer* _pRenderer);


	// Create a frame
    //1. The name of the frame
	//2. The output new frame
	STDMETHOD(CreateFrame)(LPCSTR _kcpFrameName,
						   D3DXFRAME** _d3dppNewFrame);
    
	// Create a Mesh Container
	//1. Name of the Mesh
	//2. The mesh Data
	//3. that materials of the mesh
	//4. the effects on the mesh
	//5. the number of meterials in the mesh
	//6. the adjacency array for the mesh
	//7. the skin information for the mesh
	//8. the output mesh container
	STDMETHOD(CreateMeshContainer)(LPCSTR _wcName, 
								   const D3DXMESHDATA* _kd3dpMeshData, 
								   const D3DXMATERIAL* _kd3dpMaterials, 
								   const D3DXEFFECTINSTANCE* _kd3dpEffectInstances, 
								   DWORD _dwNumMaterials, 
								   const DWORD* _kdwpAdjacency, 
								   ID3DXSkinInfo* _d3dpSkinInfo, 
								   D3DXMESHCONTAINER** _d3dppNewMeshContainer);
    
	// Destroy a frame
	//1. The frame to delete
	STDMETHOD(DestroyFrame)(D3DXFRAME* _d3dpFrameToFree);
    
	// Destroy a mesh container
	//1. The container to destroy
	STDMETHOD(DestroyMeshContainer)(D3DXMESHCONTAINER* _d3dpMeshContainerBase);


	// Inline Functions


protected:


private:


	void Deinitialise();


	// Member Variables
protected:


private:


	CD3DRenderer* m_pRenderer;


};


#endif //__IGFEB11_IG500_ALLOCATEHIERARCHY_H__