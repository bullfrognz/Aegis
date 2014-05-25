//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   AnimatedMesh.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"
#include "AllocateHierarchy.h"
#include "Frame.h"
#include "D3DRenderer.h"
#include "MeshContainer.h"
#include "TextureManager.h"
#include "DeviceManager.h"


// This Include
#include "AnimatedMesh.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* AnimatedMesh class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CAnimatedMesh::CAnimatedMesh()
: m_d3dpAnimController(0)
, m_pFirstMeshContainer(0)
, m_d3dpFrameHeirarchy(0)
, m_pBoneMatrices(0)
, m_uiMaxBones(0)
, m_dwCurrentAnimation(0)
, m_dwAnimationSetCount(0)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* AnimatedMesh class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CAnimatedMesh::CAnimatedMesh(CAnimatedMesh& _rAnimatedMesh)
{

}


/*---------------------------------------------------------------------------------------------------------------------------
*
* AnimatedMesh class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CAnimatedMesh::~CAnimatedMesh()
{
	Deinitialise();
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Intiialises the class by setting member varaibles and calling on other initialise functions.
*
* @author Bryce Booth
*
* @param _pD3DDevice			Device interface of the renderer.
* @param _pFrameHeirarchy		Frame heirarchy of teh anamimated mesh.
* @param _d3dpAnimController	Animation controller for teh mesh
*	
* @return true	Initialise was sucessful
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CAnimatedMesh::Initialise(IDirect3DDevice9* _pD3DDevice, CFrame* _pFrameHeirarchy, ID3DXAnimationController* _d3dpAnimController)
{
	//Set member variables
	m_pD3DDevice = _pD3DDevice;
	m_d3dpFrameHeirarchy = _pFrameHeirarchy;
	m_d3dpAnimController = _d3dpAnimController;


	if(m_d3dpAnimController)
	{
		m_dwAnimationSetCount = m_d3dpAnimController->GetMaxNumAnimationSets();
	}


	//Run initialise functions
	InitialiseBoneMatrices(m_d3dpFrameHeirarchy);


	//Setup the bone matrices array 
	m_pBoneMatrices = new CMatrix[m_uiMaxBones];
	ZeroMemory(m_pBoneMatrices, sizeof(CMatrix)*m_uiMaxBones);


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function processes the class instance for the current frame by advancing time on the mesh and updating
* the mesh's bone matrices for the new pose.
*
* @author Bryce Booth
* @param  _fDeltaTick	The time elasped since last process
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CAnimatedMesh::Process(float _fDeltaTick)
{
	//Check animation was set
	if(m_dwCurrentAnimation != -1)
	{
		//Advance time on animation container
		m_d3dpAnimController->AdvanceTime(_fDeltaTick, NULL);
	}


	//Update the frame hierarchy
	UpdateFrameMatrices(static_cast<CFrame*>(m_d3dpFrameHeirarchy));
	

	//Get first mesh container
	CMeshContainer* pMeshContainer = m_pFirstMeshContainer;


	//Check mesh container skin info is valid
	if(pMeshContainer->pSkinInfo)
	{
		//Get skin number of bones
		unsigned int uiBones = pMeshContainer->pSkinInfo->GetNumBones();


		//Loop through number of bones
		for (unsigned int i = 0; i < uiBones; ++i)
		{	
			D3DXMatrixMultiply(&m_pBoneMatrices[i], &pMeshContainer->m_d3dpBoneOffsets[i],  pMeshContainer->m_d3dppFrameMatrices[i]);
		}

		//Set default variables
		void* pSource = 0;
		void* pDestination = 0;

		//Lock mesh vertex buffer
		pMeshContainer->MeshData.pMesh->LockVertexBuffer(D3DLOCK_READONLY, static_cast<void**>(&pSource));


		//Lock skin mesh vertex buffer
		pMeshContainer->m_d3dpSkinMesh->LockVertexBuffer(0, static_cast<void**>(&pDestination));


		//Update the skinned mesh using provided transformations
		pMeshContainer->pSkinInfo->UpdateSkinnedMesh(m_pBoneMatrices, NULL, pSource, pDestination);


		//Unlock buffers
		pMeshContainer->m_d3dpSkinMesh->UnlockVertexBuffer();
		pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function draws the mesh from the first mesh container to the last
*
* @author Bryce Booth
*
* @param _pRenderer		Renderer instance of the window.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CAnimatedMesh::Draw(CD3DRenderer* _pRenderer)
{
	//Set default varaibles
	ID3DXMesh* pDrawMesh = 0;


	//Set current mesh container to first mesh container
	CMeshContainer* pMeshContainer = m_pFirstMeshContainer;


	//Loop through mesh containers within frame
	while(pMeshContainer)
	{
		//Check mesh container has skin info
		if (pMeshContainer->pSkinInfo)
		{
			//Set mesh to be drawn to the skin mesh
			pDrawMesh = pMeshContainer->m_d3dpSkinMesh;
		}
		else
		{
			//Set mesh to default
			pDrawMesh = pMeshContainer->MeshData.pMesh;
		}
		

		//Loop through number of materials
		for (DWORD i = 0; i < pMeshContainer->NumMaterials; ++i)
		{
			//Set material on device
			_pRenderer->GetDeviceManager().SetMaterial(&pMeshContainer->m_d3dpMaterials[i]);


			//Set texture on device
			_pRenderer->GetTextureManager().SetTexture(pMeshContainer->m_ipTextures[i]);


			//Draw mesh subset
			pDrawMesh->DrawSubset(i);
		}

		
		//Set mesh container
		pMeshContainer = static_cast<CMeshContainer*>(pMeshContainer->pNextMeshContainer);
	}
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the current animation for the mesh
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CAnimatedMesh::SetCurrentAnimation(DWORD _dwAnimationFlag)
{
	//Set default variables
	ID3DXAnimationSet* d3dpAnimationSet = 0;


	//Check animation is not current animation
	//Check animation exists
	if(_dwAnimationFlag != m_dwCurrentAnimation && _dwAnimationFlag < m_dwAnimationSetCount) 
	{ 
		//Set current animation
		m_dwCurrentAnimation = _dwAnimationFlag;


		//Get and set animation set
		m_d3dpAnimController->GetAnimationSet(m_dwCurrentAnimation, &d3dpAnimationSet);
		m_d3dpAnimController->SetTrackAnimationSet(0, d3dpAnimationSet);


		//Clean up
		FW_RELEASE(d3dpAnimationSet);
	}
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns animation controller of mesh.
*
* @author Bryce Booth
* @param ID3DXAnimationController	Animation controller.
*
*---------------------------------------------------------------------------------------------------------------------------*/

ID3DXAnimationController*
CAnimatedMesh::GetAnimationController()
{
	return (m_d3dpAnimController);
}






/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Calculates the matrices for each individual bone.
*
* @author Bryce Booth
*
* @param _pFrame			Current frame data container.
* @param _pParentMatrix		Parent matrix that is handed down.
*
* @param true Initialise was successful
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CAnimatedMesh::InitialiseBoneMatrices(CFrame* _pFrame, CMatrix* _pParentMatrix)
{
	//Setup default variables
	CFrame* pTempFrame = 0;
	unsigned int uiSkinNumNones = 0;


	//Get frame mesh container
	CMeshContainer* pMeshContainer = static_cast<CMeshContainer*>(_pFrame->pMeshContainer);


	//Check mesh container is valid
	if(pMeshContainer)
	{
		//Check if first mesh cantainer is valid
		if(m_pFirstMeshContainer == 0)
		{
			//Set first mesh container to current mesh container
			m_pFirstMeshContainer = pMeshContainer;
		}

	
		//Check mesh container has skin info
		if(pMeshContainer->pSkinInfo)
		{
			//Clone the mesh
			pMeshContainer->MeshData.pMesh->CloneMeshFVF(D3DXMESH_MANAGED, 
														 pMeshContainer->MeshData.pMesh->GetFVF(),
														 m_pD3DDevice, 
														 &pMeshContainer->m_d3dpSkinMesh);

			
			//Get mesh skin number of bones
			uiSkinNumNones = pMeshContainer->pSkinInfo->GetNumBones();

			
			//Check if skin number of bones is nigher then current maxium
			if(m_uiMaxBones < uiSkinNumNones)
			{
				//Set max number of bones on whole mesh
				m_uiMaxBones = uiSkinNumNones;
			}

			
			//Loop through number of skin bones
			for (unsigned int i = 0; i < uiSkinNumNones; i++)
			{   
				//Frind the frame within the mesh frame heirarchy
				pTempFrame = static_cast<CFrame*>(D3DXFrameFind(m_d3dpFrameHeirarchy, pMeshContainer->pSkinInfo->GetBoneName(i)));


				//Set combined maxrix to the mesh container
				pMeshContainer->m_d3dppFrameMatrices[i] = &pTempFrame->m_mtxCombined;
			}
		}
	}

	//Recursion for sibling
	if(_pFrame->pFrameSibling)
	{
		InitialiseBoneMatrices(static_cast<CFrame*>(_pFrame->pFrameSibling), _pParentMatrix);
	}


	//Recursion for first child
	if(_pFrame->pFrameFirstChild)
	{
		InitialiseBoneMatrices(static_cast<CFrame*>(_pFrame->pFrameFirstChild), &_pFrame->m_mtxCombined);
	}


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Updates the frame's matrixes for the current frame set by teh animation controller
*
* @author Bryce Booth
*
* @param _pFrame			Current fraem to update.
* @param _pParentMatrix		Parent matrix that is handed down.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CAnimatedMesh::UpdateFrameMatrices(CFrame* _pFrame, CMatrix* _pParentMatrix)
{
	//Check parent matrix exists
	if (_pParentMatrix)
	{
		//Set combined 
		D3DXMatrixMultiply(&_pFrame->m_mtxCombined, &_pFrame->TransformationMatrix, _pParentMatrix);
	}
	else
	{
		_pFrame->m_mtxCombined = _pFrame->TransformationMatrix;
	}


	//Recursion for sibling
	if (_pFrame->pFrameSibling)
	{
		UpdateFrameMatrices(static_cast<CFrame*>(_pFrame->pFrameSibling), _pParentMatrix);
	}


	//Recursion for first child
	if (_pFrame->pFrameFirstChild)
	{
		UpdateFrameMatrices(static_cast<CFrame*>(_pFrame->pFrameFirstChild),  &_pFrame->m_mtxCombined);
	}
}








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
CAnimatedMesh::Deinitialise()
{
	FW_RELEASE(m_d3dpAnimController);

	CAllocateHierarchy Alloc;
	D3DXFrameDestroy(m_d3dpFrameHeirarchy, &Alloc);

	FW_ADELETE(m_pBoneMatrices);
}