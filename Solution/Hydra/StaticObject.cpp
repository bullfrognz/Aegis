//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   StatiCStaticObject.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"
#include "StrUtilities.h"
#include "Utility.h"
#include "D3DRenderer.h"
#include "MeshManager.h"
#include "Camera.h"


// This Include
#include "StaticObject.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* StatiCStaticObject class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CStaticObject::CStaticObject()
: m_vpPreDrawCallback(0)
, m_vpPostDrawCallback(0)
, m_uiStaticMeshId(Utility::INVALID_ID)
, m_bVisible(true)
, m_pRenderer(0)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* StatiCStaticObject class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CStaticObject::~CStaticObject()
{
	Deinitialise();
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialisings the class instance before use.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CStaticObject::Initialise(char* _cpEntityName, CD3DRenderer* _pRenderer, unsigned int _uiMeshId)
{
	//Set member variables
	m_pRenderer = _pRenderer;
	m_uiStaticMeshId = _uiMeshId;


	//Initialise super class CEntity
	CEntity::Initialise(_cpEntityName);


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialisings the class instance before use.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CStaticObject::Initialise(char* _cpEntityName, CD3DRenderer* _pRenderer, const char* _kcpMeshFile)
{
	//Convert mesh file
	m_pRenderer = _pRenderer;
	wchar_t* wcpMeshFile = 0;
	StrUtilities::ConvertToWChar(_kcpMeshFile, wcpMeshFile);


	//Load mesh file
	m_uiStaticMeshId = _pRenderer->GetMeshManager().CreateNewMesh(wcpMeshFile);
	m_fRadius = _pRenderer->GetMeshManager().GetVertexData(m_uiStaticMeshId).m_fBoundingSphereRadius;


	//Initialise super class CEntity
	CEntity::Initialise(_cpEntityName);


	//Clean up
	delete[] wcpMeshFile;
	wcpMeshFile = 0;


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
CStaticObject::Process(float _fDeltaTick)
{
	//Process super class CEntity
	CEntity::Process(_fDeltaTick);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CStaticObject::Draw(CD3DRenderer* _pRenderer, void* _pClassInstance)
{
	//Check object is visible
	//Check mesh id is not invalid
	if (m_bVisible == true && m_uiStaticMeshId != Utility::INVALID_ID)
	{
		//Pre-draw
		if (m_vpPreDrawCallback)
		{
			m_vpPreDrawCallback(_pClassInstance, _pRenderer);
		}

		if(CCamera::IsInFrustum(m_mtxWorldMatrix.GetPosition(CVector3()), m_fRadius))
		{		
			//Draw mesh
			_pRenderer->SetWorldMatrix(&(CEntity::m_mtxWorldMatrix));
			_pRenderer->GetMeshManager().Render(m_uiStaticMeshId);
		}

		//Post draw
		if (m_vpPreDrawCallback)
		{
			m_vpPostDrawCallback(_pClassInstance, _pRenderer);
		}
	}
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
CStaticObject::Deinitialise()
{
	//Empty
}