//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	MeshManager.cpp
//	Description	:	Definition of CMeshManager
//	Author		:	Jade Abbott, Bryce Booth
//	Mail		:	jade.abbott@mediadesign.school.nz
//				:	bryce.booth@mediadesign.school.nz
//

// Library includes.
#include <cassert>
#include <d3dx9.h>

// Local includes.
#include "Application.h"
#include "Window.h"
#include "Utility.h"
#include "TextureManager.h"
#include "DeviceManager.h"
#include "StrUtilities.h"
#include "Macros.h"
#include "AllocateHierarchy.h"
#include "AnimatedMesh.h"
#include "Frame.h"

// This include.
#include "MeshManager.h"

CMeshManager::CMeshManager()
: m_pDevice(0)
, m_pDeviceManager(0)
, m_pTextureManager(0)
, m_arrpMeshes(0)
, m_uiNumMeshes(0)
{
	m_EmptyBuffer.m_eIndexType = D3DFMT_UNKNOWN;
	m_EmptyBuffer.m_fBoundingSphereRadius = 0.0f;
	m_EmptyBuffer.m_pIndices = 0;
	m_EmptyBuffer.m_pVertices = 0;
	m_EmptyBuffer.m_uiNumIndices = 0;
	m_EmptyBuffer.m_uiNumVerts = 0;
	m_EmptyBuffer.m_uiVertexStride = 0;
}

CMeshManager::~CMeshManager()
{
	if (m_pDevice)
	{
		m_pDevice->Release();
	}

	for (unsigned int ui = 0; ui < m_uiNumMeshes; ++ui)
	{
		DeleteMesh(ui);
	}
	delete[] m_arrpMeshes;


	FW_DELETEMAP(int, CAnimatedMesh*, m_mapAniamtedMeshes);
}

/**
*
* Initialises the mesh manager.
*
* @author Jade Abbott
* @param _pDevice Interface to the GPU, which will be held on to for the duration of the program.
* @param _pDeviceManager Will be held on to for the duration of the program, and is used to set rtates on the device indirectly.
* @param _pTextureManager Held on to for the duration of the program, and is used to set the texture on the device when drawing meshes.
* @return True if initialisation was successful.
*
*/
bool
CMeshManager::Initialise(IDirect3DDevice9* _pDevice, CDeviceManager* _pDeviceManager, CTextureManager* _pTextureManager)
{
	assert(_pDevice);
	assert(_pDeviceManager);
	assert(_pTextureManager);

	if (m_pDevice)
	{
		m_pDevice->Release();
	}
	m_pDevice = _pDevice;
	m_pDevice->AddRef();

	if (!m_pTextureManager)
	{
		m_pTextureManager = _pTextureManager;
	}

	m_pDeviceManager = _pDeviceManager;

	return true;
}

/**
*
* Registers a new mesh using the filename provided, and returns an ID to the mesh.
* But just to foolproof it, this checks if the mesh already exists.
*
* @author Jade Abbott
* @param File name and directory of the .x file mesh.
* @return ID of the new mesh; Returns mathUtils::INVALID_ID if failed.
*
*/
unsigned int
CMeshManager::CreateNewMesh(const wchar_t* _pwFileName)
{
	assert(m_pDevice);
	assert(m_pTextureManager);
	assert(_pwFileName);

	// Foolproofing.
	for (unsigned int uiMesh = 0; uiMesh < m_uiNumMeshes; ++uiMesh)
	{
		assert(m_arrpMeshes);

		if (!m_arrpMeshes[uiMesh])
			continue;

		if (!m_arrpMeshes[uiMesh]->m_pFileName)
			continue;

		// Compare provided file name with existing meshes file name.
		unsigned int uiString = 0;
		do
		{
			if (m_arrpMeshes[uiMesh]->m_pFileName[uiString] == _pwFileName[uiString])	// If characters are equal...
			{
				// Check if this is the end of the string (null terminator).
				if (_pwFileName[uiString] == 0)
				{
					// File names match, so return the ID of this mesh.
					return uiMesh;
				}
			}
			else	// File names do not match...
			{
				break;	// Stop checking this string, and continue with the others.
			}
		}
		while (++uiString);	// Prevent infinite loop.
	}
	// Else this mesh has not been loaded before.

	// Get a free element in the array.
	unsigned int uiData = Utility::INVALID_ID;
	for (unsigned int ui = 0; ui < m_uiNumMeshes; ++ui)
	{
		assert(m_arrpMeshes);

		if (!m_arrpMeshes[ui])
		{
			uiData = ui;
			break;
		}
	}

	if (uiData == Utility::INVALID_ID)
	{
		if (IncreaseMeshArraySize())
		{
			uiData = m_uiNumMeshes - 1;
		}
		else
		{
			return Utility::INVALID_ID;
		}
	}

	m_arrpMeshes[uiData] = new TMeshManagerData();
	TMeshManagerData*& rpData = m_arrpMeshes[uiData];
	if (!rpData)
	{
		return Utility::INVALID_ID;
	}

	ZeroMemory(m_arrpMeshes[uiData], sizeof(TMeshManagerData));

	ID3DXBuffer* pMaterialBuffer = 0;
	HRESULT hr = D3DXLoadMeshFromX(_pwFileName, D3DXMESH_MANAGED, m_pDevice, 0, &pMaterialBuffer, 0, &rpData->m_dwNumMaterials, &rpData->m_pMesh);
	if (FAILED(hr))
	{
		delete rpData;
		rpData = 0;
		return Utility::INVALID_ID;
	}

	assert(rpData->m_pMesh);
	assert(pMaterialBuffer);

	D3DXMATERIAL* pMaterial = reinterpret_cast<D3DXMATERIAL*>(pMaterialBuffer->GetBufferPointer());

	// If the mesh does not have normals, create a mesh that does.
	if (!(rpData->m_pMesh->GetFVF() & D3DFVF_NORMAL))
	{
		// Add normals to the mesh.
		ID3DXMesh* pTempMesh = 0;
		rpData->m_pMesh->CloneMeshFVF(D3DXMESH_MANAGED, rpData->m_pMesh->GetFVF() | D3DFVF_NORMAL, m_pDevice, &pTempMesh);

		D3DXComputeNormals(pTempMesh, 0);

		rpData->m_pMesh->Release();
		rpData->m_pMesh = pTempMesh;
	}

	// Copy data from pMaterialBuffer to own buffer.
	if (rpData->m_dwNumMaterials)
	{
		rpData->m_arrMaterials = new D3DMATERIAL9[rpData->m_dwNumMaterials];
		if (!rpData->m_arrMaterials)
		{
			pMaterialBuffer->Release();
			rpData->m_pMesh->Release();
			delete rpData;
			rpData = 0;
			return Utility::INVALID_ID;
		}

		for (DWORD dw = 0; dw < rpData->m_dwNumMaterials; ++dw)
		{
			rpData->m_arrMaterials[dw] = pMaterial[dw].MatD3D;
		}
	}

	// Texture ID's.
	rpData->m_iArrTextureID = new int[rpData->m_dwNumMaterials];
	if (!rpData->m_iArrTextureID)
	{
		pMaterialBuffer->Release();
		rpData->m_pMesh->Release();
		delete[] rpData->m_arrMaterials;
		delete rpData;
		rpData = 0;
		return Utility::INVALID_ID;
	}

	// File address.
	size_t uiStringLength = 0;
	std::wstring strFileAddr = _pwFileName;
	
	// Find the last backslash or forward slash (if any).
	for (size_t ui = strFileAddr.length() - 1; ui >= 0; --ui)
	{
		if (strFileAddr[ui] == '\\' || strFileAddr[ui] == '/')
		{
			uiStringLength = ui + 1;	// + 1 for null terminator.
			break;
		}

		if (!ui)
			break;
	}

	strFileAddr.resize(uiStringLength);

	for (DWORD dw = 0; dw < rpData->m_dwNumMaterials; ++dw)
	{
		if (pMaterial[dw].pTextureFilename)
		{
			// Check if the texture has already been registered.
			std::string strThisName = pMaterial[dw].pTextureFilename;
			bool bExists = false;

			for (DWORD dw2 = 0; dw2 < dw; ++dw2)
			{
				if (pMaterial[dw2].pTextureFilename)
				{
					if (strThisName.compare(pMaterial[dw2].pTextureFilename) == 0)	// Match...
					{
						bExists = true;
						rpData->m_iArrTextureID[dw] = rpData->m_iArrTextureID[dw2];
						break;
					}
				}
			}

			if (!bExists)	// If the texture doesn't exist...
			{
				std::wstring strFile = strFileAddr;

				uiStringLength = 0;
				while (*(pMaterial[dw].pTextureFilename + uiStringLength++));	// Includes null terminator.

				wchar_t* pwFileName = new wchar_t[uiStringLength];
				if (!pwFileName)
				{
					rpData->m_iArrTextureID[dw] = Utility::INVALID_ID;
					continue;
				}

				MultiByteToWideChar(CP_UTF8,
									0,
									pMaterial[dw].pTextureFilename,
									static_cast<int>(uiStringLength),
									pwFileName,
									static_cast<int>(uiStringLength));

				strFile += pwFileName;

				delete[] pwFileName;
				pwFileName = 0;

				rpData->m_iArrTextureID[dw] = m_pTextureManager->LoadTextureFile(strFile.c_str());
			}
		}
		else
		{
			rpData->m_iArrTextureID[dw] = Utility::INVALID_ID;
		}
	}

	pMaterialBuffer->Release();
	pMaterialBuffer = 0;

	// Get a copy of the vertex data.
	{
		rpData->m_VertexData.m_uiVertexStride = rpData->m_pMesh->GetNumBytesPerVertex();
		rpData->m_VertexData.m_uiNumVerts = rpData->m_pMesh->GetNumVertices();

		IDirect3DVertexBuffer9* pVertexBuffer = 0;
		rpData->m_pMesh->GetVertexBuffer(&pVertexBuffer);
		if (pVertexBuffer)
		{
			void* pTempVertexAccess = 0;
			hr = pVertexBuffer->Lock(0, rpData->m_VertexData.m_uiNumVerts * rpData->m_VertexData.m_uiVertexStride, &pTempVertexAccess, 0);
			if (SUCCEEDED(hr))
			{
				rpData->m_VertexData.m_pVertices = new BYTE[rpData->m_VertexData.m_uiNumVerts * rpData->m_VertexData.m_uiVertexStride];
				if (rpData->m_VertexData.m_pVertices)
				{
					memcpy(rpData->m_VertexData.m_pVertices, pTempVertexAccess, rpData->m_VertexData.m_uiNumVerts * rpData->m_VertexData.m_uiVertexStride);
				}

				pVertexBuffer->Unlock();
			}

			pVertexBuffer->Release();
			pVertexBuffer = 0;
		}

		MathUtility::CalculateBoundingSphere(rpData->m_VertexData.m_fBoundingSphereRadius,
											 rpData->m_VertexData.m_pVertices,
											 rpData->m_VertexData.m_uiVertexStride,
											 rpData->m_VertexData.m_uiNumVerts);
	}

	// Get file name length.
	unsigned int uiLength = 0;
	while(_pwFileName[uiLength++]);	// Includes null terminator.

	// Create string for file name.
	rpData->m_pFileName = new wchar_t[uiLength];
	if (rpData->m_pFileName)
	{
		memcpy(rpData->m_pFileName, _pwFileName, sizeof(wchar_t) * uiLength);
	}

	return uiData;
}

/**
*
* Deletes the mesh matching the provided ID.
*
* @author Jade Abbott
* @param _uiID The ID of the mesh to delete.
* @return Void.
*
*/
void
CMeshManager::DeleteMesh(unsigned int _uiID)
{
	if (_uiID >= m_uiNumMeshes)	// Covers Utility::INVALID_ID too.
		return;

	assert(_uiID != Utility::INVALID_ID);	// Should have been caught by the above statement.
	assert(m_arrpMeshes);	// Should exist if m_uiNumMeshes is greater than zero (which allowed the above statement to pass).

	if (m_arrpMeshes[_uiID])
	{
		delete[] m_arrpMeshes[_uiID]->m_pFileName;
		
		delete[] m_arrpMeshes[_uiID]->m_arrMaterials;
		
		delete[] m_arrpMeshes[_uiID]->m_iArrTextureID;

		if (m_arrpMeshes[_uiID]->m_pMesh)
		{
			m_arrpMeshes[_uiID]->m_pMesh->Release();
		}
		
		delete[] m_arrpMeshes[_uiID]->m_VertexData.m_pVertices;
		delete[] m_arrpMeshes[_uiID]->m_VertexData.m_pIndices;

		delete m_arrpMeshes[_uiID];
		m_arrpMeshes[_uiID] = 0;
	}
}

/**
*
* Renders the specified mesh to screen.
*
* @author Jade Abbott
* @param _iID the ID of the mesh to render.
* @return Void.
*
*/
void
CMeshManager::Render(unsigned int _uiID)
{
	assert(m_pDeviceManager);
	assert(m_pTextureManager);

	if (_uiID == Utility::INVALID_ID)
		return;
	
	assert(_uiID < m_uiNumMeshes);
	assert(m_arrpMeshes);
	assert(m_arrpMeshes[_uiID]);

	TMeshManagerData& rData = *m_arrpMeshes[_uiID];	// Only valid pointers are stored.


	for (DWORD dw = 0; dw < rData.m_dwNumMaterials; ++dw)	// Number of materials = number of subsets.
	{
		m_pDeviceManager->SetMaterial(&rData.m_arrMaterials[dw]);
		m_pTextureManager->SetTexture(rData.m_iArrTextureID[dw]);
		rData.m_pMesh->DrawSubset(dw);
	}
}

/**
*
* Returns the container of data for the mesh requested.
* Returns an empty buffer if an invalid buffer is requested.
*
* @author Jade Abbott
* @param _uiID The ID of the mesh whose data buffer will be returned.
* @return Const reference to the mesh buffer data.
*
*/
const TVertexBufferData&
CMeshManager::GetVertexData(unsigned int _uiID)
{
	if (_uiID == Utility::INVALID_ID)
	{
		return m_EmptyBuffer;
	}

	assert(_uiID < m_uiNumMeshes);
	assert(m_arrpMeshes);
	assert(m_arrpMeshes[_uiID]);

	return m_arrpMeshes[_uiID]->m_VertexData;
}

/**
*
* Draws a bounding sphere for the mesh specified.
*
* @author Jade Abbott
* @param _iID the ID of the mesh that will have a bounding spehere rendered for.
* @return Void.
*
*/
void
CMeshManager::DrawBoundingSphere(unsigned int _uiID)
{
	assert(m_pDevice);
	assert(m_pTextureManager);
	assert(m_pDeviceManager);

	if (_uiID == Utility::INVALID_ID)
		return;

	assert(_uiID < m_uiNumMeshes);
	assert(m_arrpMeshes);
	assert(m_arrpMeshes[_uiID]);

	ID3DXMesh* pTempMesh = 0;
	HRESULT hr = D3DXCreateSphere(m_pDevice, m_arrpMeshes[_uiID]->m_VertexData.m_fBoundingSphereRadius, 25, 25, &pTempMesh, 0);
	if(pTempMesh)
	{
		if (SUCCEEDED(hr))
		{
			m_pTextureManager->SetTexture(Utility::INVALID_ID);
			m_pDeviceManager->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
			pTempMesh->DrawSubset(0);
			m_pDeviceManager->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		}

		pTempMesh->Release();
		pTempMesh = 0;
	}
}

/**
*
* Changes the texture used to render the mesh.
*
* @author Jade Abbott
* @param _uiMeshID The mesh whose texture will be changed.
* @param _uiTextureIteration The iteration of the array of textures, to get to the required texture ID.
* @param _uiNewTextureID The ID to be placed in _uiTextureIteration.
* @return Void.
*
*/
void
CMeshManager::ChangeTexture(unsigned int _uiMeshID, unsigned int _uiTextureIteration, unsigned int _uiNewTextureID)
{
	if (_uiMeshID == Utility::INVALID_ID)
		return;

	assert(m_arrpMeshes);
	assert(m_arrpMeshes[_uiMeshID]);
	assert(_uiTextureIteration < m_arrpMeshes[_uiMeshID]->m_dwNumMaterials);

	m_arrpMeshes[_uiMeshID]->m_iArrTextureID[_uiTextureIteration] = _uiNewTextureID;
}

/**
*
* Internally used function.
* Will increase the size of the resizable array of pointers to meshes,
* increasing the cap on the number of meshes that can be held.
*
* @author Jade Abbott
* @return True if size increase was successful.
*
*/
bool
CMeshManager::IncreaseMeshArraySize()
{
	TMeshManagerData** arrpData = new TMeshManagerData*[m_uiNumMeshes + 1];
	if (!arrpData)
		return false;

	memcpy(arrpData, m_arrpMeshes, sizeof(TMeshManagerData*) * m_uiNumMeshes);
	arrpData[m_uiNumMeshes] = 0;

	delete[] m_arrpMeshes;
	m_arrpMeshes = arrpData;
	++m_uiNumMeshes;

	return true;
}




/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMeshManager::Process(float _fDeltaTick)
{
	std::map<int, CAnimatedMesh*>::iterator iterMesh;
	iterMesh = m_mapAniamtedMeshes.begin();


	while (iterMesh != m_mapAniamtedMeshes.end())
	{
		(*iterMesh).second->Process(_fDeltaTick);


		++ iterMesh;
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CMeshManager::CreateNewMeshHeirarchy(const char* _kcpMeshFile)
{
	//Set default variables
	D3DXFRAME* pFrameHeirarchy = 0;
	ID3DXAnimationController* pAnimationController = 0;
	unsigned int m_uiAnimatedMeshId = Utility::INVALID_ID;
	bool bLoadedMeshFile = false;
	CAnimatedMesh* pAnimatedMesh = 0;


	//Check mesh file has already been loaded
	bLoadedMeshFile = CheckLoadedAnimatedMesh(_kcpMeshFile, m_uiAnimatedMeshId);


	//Mesh has been loaded
	if (bLoadedMeshFile == true)
	{
		//pAnimatedMesh = CloneAnimatedMesh(m_uiAnimatedMeshId);

		return (m_uiAnimatedMeshId);
	}
	else
	{
		//Load mesh file
		LoadAnimatedMesh(_kcpMeshFile, pFrameHeirarchy, pAnimationController);


		//Instance new aniamted mesh
		pAnimatedMesh = new CAnimatedMesh();


		//Initialise animated mesh
		pAnimatedMesh->Initialise(m_pDevice, static_cast<CFrame*>(pFrameHeirarchy), pAnimationController);
	}


	m_uiAnimatedMeshId = StoreAdimatedMesh(_kcpMeshFile, pAnimatedMesh);


	return (m_uiAnimatedMeshId);
}











/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMeshManager::ProcessAnimatedMesh(unsigned int _uiAnimatedMeshId, float _fDeltaTick)
{
	GetAnimatedMesh(_uiAnimatedMeshId)->Process(_fDeltaTick);
}











/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMeshManager::RenderAnimatedMesh(unsigned int _uiAnimatedMeshId, CD3DRenderer* _pRenderer)
{
	GetAnimatedMesh(_uiAnimatedMeshId)->Draw(_pRenderer);
}











/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CMeshManager::CheckLoadedAnimatedMesh(const char* _kcpMeshFile, unsigned int& _uirAnimatedMeshId)
{
	std::map<std::string, int>::iterator iterMeshFile;


	std::string strMeshFile = _kcpMeshFile;
	iterMeshFile = m_mapAnimatedMesheFiles.find(strMeshFile);


	if (iterMeshFile != m_mapAnimatedMesheFiles.end())
	{
		_uirAnimatedMeshId = (*iterMeshFile).second;


		return (true);
	}
	else
	{
		return (false);
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
CMeshManager::LoadAnimatedMesh(const char* _kcpMeshFile,
							   D3DXFRAME*& _d3drpFrameHeirarchy,
							   ID3DXAnimationController*& _d3dprAnimationController)
{
	//Setup default variables
	HRESULT hResult = S_OK;


	//Convert file to wchar
	wchar_t* wcMeshFile = 0;
	StrUtilities::ConvertToWChar(_kcpMeshFile, wcMeshFile);


	//Instance Allocate Hierarchy
	CAllocateHierarchy* pAllocateHierarchy = new CAllocateHierarchy();
	pAllocateHierarchy->Intiailise(CApplication::GetInstance().GetGameWindow().GetRenderer());


	//Load animated mesh file
	hResult = D3DXLoadMeshHierarchyFromX(wcMeshFile,
										 D3DXMESH_MANAGED,
										 m_pDevice,
										 pAllocateHierarchy,
										 NULL,
										 &_d3drpFrameHeirarchy,
										 &_d3dprAnimationController);


	//Check file was loaded
	LOG_FATALERROR(FAILED(hResult), "Could not load animated mesh file.");


	//Clean up
	FW_DELETE(pAllocateHierarchy);
	delete[] wcMeshFile;
	wcMeshFile = 0;
}











/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CAnimatedMesh*
CMeshManager::CloneAnimatedMesh(unsigned int _uiAnimatedMeshId)
{
	CAnimatedMesh* pAnimatedMesh = new CAnimatedMesh();
	

	pAnimatedMesh = GetAnimatedMesh(_uiAnimatedMeshId);


	return (pAnimatedMesh);
}











/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CMeshManager::StoreAdimatedMesh(const char* _kcpMeshFile, CAnimatedMesh* _pAnimatedMesh)
{
	//Set default variables
	unsigned int uiAnimatedMeshId = 0;


	//Give animation model an id
	uiAnimatedMeshId = static_cast<unsigned int>(m_mapAniamtedMeshes.size());


	//Insert into mesh map
	m_mapAniamtedMeshes.insert( std::pair<int, CAnimatedMesh*>(uiAnimatedMeshId, _pAnimatedMesh) );


	//Remember mesh file file
	std::string strFile = _kcpMeshFile;
	m_mapAnimatedMesheFiles.insert( std::pair<std::string, int>(strFile, uiAnimatedMeshId) );


	return (uiAnimatedMeshId);
}











/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CAnimatedMesh*
CMeshManager::GetAnimatedMesh(unsigned int _uiAnimatedMeshId)
{
	std::map<int, CAnimatedMesh*>::iterator iterAnimatedMesh;


	iterAnimatedMesh = m_mapAniamtedMeshes.find(_uiAnimatedMeshId);


	LOG_FATALERROR(iterAnimatedMesh == m_mapAniamtedMeshes.end(), "Animated mesh does not exists.");


	return ((*iterAnimatedMesh).second);
}