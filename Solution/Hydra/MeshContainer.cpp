//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   MeshContainer.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"
#include "StrUtilities.h"
#include "D3DRenderer.h"
#include "TextureManager.h"
#include "Matrix.h"
#include "Utility.h"


// This Include
#include "MeshContainer.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* MeshContainer class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMeshContainer::CMeshContainer()
: m_ipTextures(0)
, m_d3dpMaterials(0)
, m_d3dpSkinMesh(0)
, m_d3dpBoneMatrices(0)
, m_d3dpBoneOffsets(0)
, m_d3dppFrameMatrices(0)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* MeshContainer class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMeshContainer::~CMeshContainer()
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
CMeshContainer::Initialise(CD3DRenderer* _pRenderer,
						   const char* _kcpContainerName,
						   D3DXMESHDATATYPE _d3dMeshType,
						   const D3DXMESHDATA* _kd3dpMeshData,
						   const DWORD* _kdwpAdjacency,
						   const D3DXMATERIAL* _kd3dpMeshMaterial,
						   unsigned int _uiNumMaterials,
						   ID3DXSkinInfo* _d3dpSkinInfo)
{
	//Set member variables
	D3DXMESHCONTAINER::MeshData.Type = _d3dMeshType;


	//Run initialise functions
	InitialiseName(_kcpContainerName);
	IntiailiseMeshData(_kd3dpMeshData);
	InitialiseAdjacency(_kdwpAdjacency);
	InitialiseTexturesMaterials(_pRenderer, _kd3dpMeshMaterial, _uiNumMaterials);
	IntiialiseSkinInfo(_d3dpSkinInfo);


	return (true);
}









/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CMeshContainer::InitialiseName(const char* _kcpContainerName)
{
	D3DXMESHCONTAINER::Name = 0;


	//Check name exists
	if (strlen(_kcpContainerName) == 0)
	{
		//Set default name
		StrUtilities::Copy("<Unnamed Mesh Container>", D3DXMESHCONTAINER::Name);
	}
	else
	{
		///Copy mesh container name
		StrUtilities::Copy(_kcpContainerName, D3DXMESHCONTAINER::Name);
	}


	return (true);
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CMeshContainer::IntiailiseMeshData(const D3DXMESHDATA* _kd3dpMeshData)
{
	//Copy mesh data
	D3DXMESHCONTAINER::MeshData.pMesh = _kd3dpMeshData->pMesh;


	//Add ref to mesh
	D3DXMESHCONTAINER::MeshData.pMesh->AddRef();


	return (true);
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CMeshContainer::InitialiseAdjacency(const DWORD* _kdwpAdjacency)
{
	//Get number mesh faces
	DWORD dwNumFaces = D3DXMESHCONTAINER::MeshData.pMesh->GetNumFaces();


	//Instace adjacency varaibles
	D3DXMESHCONTAINER::pAdjacency = new DWORD[3 * dwNumFaces];


	//Copy adjacency data into container
	CopyMemory(D3DXMESHCONTAINER::pAdjacency, _kdwpAdjacency, 3 * sizeof(DWORD) * dwNumFaces);


	return (true);
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CMeshContainer::InitialiseTexturesMaterials(CD3DRenderer* _pRenderer, const D3DXMATERIAL* _kd3dpMeshMaterial, unsigned int _uiNumMaterials)
{
	//Set default variables
	std::vector<const D3DMATERIAL9*> vecMaterials;
	std::vector<int> vecTextures;
	wchar_t* wcpTextureFile = 0;
	int		 iTextureId		= 0;


	if (_uiNumMaterials != 0)
	{
		//Loop thorugh number of materials
		for (unsigned int i = 0; i < _uiNumMaterials; ++i)
		{
			//Add material
			vecMaterials.push_back(&_kd3dpMeshMaterial[i].MatD3D);

			
			//Check texture exists for material
			if (_kd3dpMeshMaterial[i].pTextureFilename != 0)
			{
				//Convert texture file to wchar
				StrUtilities::ConvertToWChar(_kd3dpMeshMaterial[i].pTextureFilename, wcpTextureFile);


				//Load texture file
				iTextureId = _pRenderer->GetTextureManager().LoadTextureFile(wcpTextureFile);
				

				//Check texture was found
				LOG_ERROR(iTextureId == Utility::INVALID_ID, "Could not load texture.");


				//Add valid texture id
				vecTextures.push_back(iTextureId);
			}
			else
			{
				//Add invalid texture id
				vecTextures.push_back(-1);
			}
		}


		//Save materials
		SaveMaterials(vecMaterials);


		//Save textures
		SaveTextures(vecTextures);
	}


	//Fix broken models
	D3DXMESHCONTAINER::NumMaterials = max(_uiNumMaterials, 1);


	return (true);
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CMeshContainer::IntiialiseSkinInfo(ID3DXSkinInfo* _d3dpSkinInfo)
{
	//Check skin info for model is valid
	if (_d3dpSkinInfo)
	{
		//Copy mesh skin data
		D3DXMESHCONTAINER::pSkinInfo = _d3dpSkinInfo;


		//Add ref to skin data
	    D3DXMESHCONTAINER::pSkinInfo->AddRef();


	    //Get number of bones
	   m_uiNumBones = _d3dpSkinInfo->GetNumBones();


		//Instance matrices for bone offsets
	    m_d3dpBoneOffsets = new CMatrix[m_uiNumBones];

		//Create the arrays for the bones and the frame matrices
		m_d3dppFrameMatrices = new CMatrix*[m_uiNumBones];


	    //Loop through number of bones
	    for (unsigned int i = 0; i < m_uiNumBones; ++i)
		{
			//Copy bone offset matrix
			m_d3dpBoneOffsets[i] = *(D3DXMESHCONTAINER::pSkinInfo->GetBoneOffsetMatrix(i));
		}
	}


	return (true);
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMeshContainer::SaveMaterials(std::vector<const D3DMATERIAL9*>& _vecrMaterials)
{
	//Set default variables
	std::vector<const D3DMATERIAL9*>::iterator iterMaterial;
	iterMaterial = _vecrMaterials.begin();
	unsigned int uiCount = 0;


	//Instance materials
	m_d3dpMaterials = new D3DMATERIAL9[_vecrMaterials.size()];


	//Loop through material vector
	while (iterMaterial != _vecrMaterials.end())
	{
		//Copy material data
		m_d3dpMaterials[uiCount] = *(*iterMaterial);


		//Increment current count and iter
		++ uiCount;
		++ iterMaterial;
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMeshContainer::SaveTextures(std::vector<int>& _vecrTextures)
{
	//Extract number of textures
	unsigned int uiNumTextures = static_cast<unsigned int>(_vecrTextures.size());


	//Instance ints
	m_ipTextures = new int[uiNumTextures];

	
	//Loop through number of textures
	for (unsigned int i = 0; i < uiNumTextures; ++i)
	{
		//Copy int value
		m_ipTextures[i] = _vecrTextures[i];
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
CMeshContainer::Deinitialise()
{
	delete[] D3DXMESHCONTAINER::Name;
	D3DXMESHCONTAINER::Name = 0;


	FW_ADELETE(D3DXMESHCONTAINER::pAdjacency);
	FW_ADELETE(m_d3dpBoneOffsets);
	FW_ADELETE(m_d3dppFrameMatrices);
	FW_ADELETE(m_ipTextures);
	FW_ADELETE(m_d3dpMaterials);
	

	FW_RELEASE(D3DXMESHCONTAINER::pSkinInfo);
	FW_RELEASE(m_d3dpSkinMesh);
	FW_RELEASE(D3DXMESHCONTAINER::MeshData.pMesh);
}