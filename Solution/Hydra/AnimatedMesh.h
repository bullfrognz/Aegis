//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   AnimatedMesh.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_ANIMATEDMESH_H__
#define __IGFEB11_IG500_ANIMATEDMESH_H__


// Library Includes
#include <d3dx9.h>
#include <windows.h>


// Local Includes
#include "Matrix.h"


// Types


// Constants


// Prototypes
class CAllocateHierarchy;
class CFrame;
class CMatrix;
class CMeshContainer;


class CAnimatedMesh
{

	// Member Functions
public:


	 CAnimatedMesh();
	 CAnimatedMesh(CAnimatedMesh& _rAnimatedMesh);
	~CAnimatedMesh();


	bool Initialise(IDirect3DDevice9* _pD3DDevice, CFrame* _pFrameHeirarchy, ID3DXAnimationController* _d3dpAnimController);
	void Process(float _fDeltaTick);
	void Draw(CD3DRenderer* _pRenderer);
	void DrawFrame(CD3DRenderer* _pRenderer, CFrame* _pFrame);


	void SetCurrentAnimation(DWORD _dwAnimationFlag);


	ID3DXAnimationController* GetAnimationController();


	// Inline Functions


protected:


	bool InitialiseBoneMatrices(CFrame* _pFrame, CMatrix* _pParentMatrix = NULL);


	void UpdateFrameMatrices(CFrame* _pFrame, CMatrix* _pParentMatrix = NULL);


	void DrawFrame(CD3DRenderer* _pRenderer);


private:


	void Deinitialise();


	// Member Variables
protected:


private:


	IDirect3DDevice9* m_pD3DDevice;


	unsigned int m_uiMaxBones;


	CMeshContainer* m_pFirstMeshContainer;			// The first mesh in the hierarchy
	CFrame*	 m_d3dpFrameHeirarchy;					// Frame hierarchy of the model
	CMatrix* m_pBoneMatrices;						// Used when calculating the bone position
	ID3DXAnimationController* m_d3dpAnimController;
	DWORD m_dwAnimationSetCount;
	DWORD m_dwCurrentAnimation;



};


#endif //__IGFEB11_IG500_ANIMATEDMESH_H__