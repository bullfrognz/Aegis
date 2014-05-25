//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   AllocateHierarchy.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"
#include "StrUtilities.h"
#include "MeshContainer.h"
#include "Frame.h"


// This Include
#include "AllocateHierarchy.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* AllocateHierarchy class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CAllocateHierarchy::CAllocateHierarchy()
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* AllocateHierarchy class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CAllocateHierarchy::~CAllocateHierarchy()
{
	Deinitialise();
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CAllocateHierarchy::Intiailise(CD3DRenderer* _pRenderer)
{
	//Set member variables
	m_pRenderer = _pRenderer;


	return (true);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

HRESULT
CAllocateHierarchy::CreateFrame(LPCSTR _kcpFrameName,
								D3DXFRAME** _d3dppNewFrame)
{
	//Instance new frame
	CFrame* pFrame = new CFrame();


	//Initialise frame
	pFrame->Initialise(_kcpFrameName);


	//Give back frame pointer
	(*_d3dppNewFrame) = pFrame;


	//Return successful
    return (S_OK);
}

HRESULT
CAllocateHierarchy::CreateMeshContainer(LPCSTR _wcName, //
									    const D3DXMESHDATA* _kd3dpMeshData, 
									    const D3DXMATERIAL* _kd3dpMaterials, //
									    const D3DXEFFECTINSTANCE* _kd3dpEffectInstances, //
									    DWORD _dwNumMaterials, 
									    const DWORD* _kdwpAdjacency, 
									    ID3DXSkinInfo* _d3dpSkinInfo, 
									    D3DXMESHCONTAINER** _d3dppNewMeshContainer) 
{
	//Instance mesh container
	CMeshContainer* pMeshContainer = new CMeshContainer();


	//TODO
	//TODO
	//Fix uninitilialised Renderer
	//Initialise mesh container
	pMeshContainer->Initialise(m_pRenderer,
							   _wcName,
							   D3DXMESHTYPE_MESH,
							   _kd3dpMeshData,
							   _kdwpAdjacency,
							   _kd3dpMaterials,
							   _dwNumMaterials,
							   _d3dpSkinInfo);



	//Copy mesh container pointer
	(*_d3dppNewMeshContainer) = pMeshContainer;


	return (S_OK);
}

HRESULT
CAllocateHierarchy::DestroyFrame(D3DXFRAME* _d3dpFrameToFree) 
{
	//Convert to CFrame class type
	CFrame* pFrame = static_cast<CFrame*>(_d3dpFrameToFree);


	//Delete frame instance
	FW_DELETE(pFrame);


	return (S_OK);
}


HRESULT CAllocateHierarchy::DestroyMeshContainer(D3DXMESHCONTAINER* _d3dpMeshContainerBase)
{
	//Convert to CMeshContainer class type
	CMeshContainer* pMeshContainer = static_cast<CMeshContainer*>(_d3dpMeshContainerBase);


	//Delete frame instance
	FW_DELETE(pMeshContainer);


	return (S_OK);
}




/********************************
            Protected
*********************************/









/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CAllocateHierarchy::Deinitialise()
{
	//Empty
}