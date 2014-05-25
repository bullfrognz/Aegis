//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   AnimatedObject.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"
#include "Utility.h"
#include "D3DRenderer.h"
#include "MeshManager.h"
#include "Camera.h"


// This Include
#include "AnimatedObject.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* AnimatedObject class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CAnimatedObject::CAnimatedObject()
: m_vpPreDrawCallback(0)
, m_vpPostDrawCallback(0)
, m_uiAnimatedMeshId(Utility::INVALID_ID)
, m_pRenderer(0)
, m_bVisible(true)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* AnimatedObject class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CAnimatedObject::~CAnimatedObject()
{
	Deinitialise();
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Initialises object with mesh id.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CAnimatedObject::Initialise(char* _cpEntityName, CD3DRenderer* _pRenderer, unsigned int _uiMeshId)
{
	//Set member variables
	m_uiAnimatedMeshId = _uiMeshId;
	m_pRenderer = _pRenderer;


	//Initialise super class CEntity
	CEntity::Initialise(_cpEntityName);


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Initialises object and loads model it self.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CAnimatedObject::Initialise(char* _cpEntityName, CD3DRenderer* _pRenderer, const char* _kcpMeshFile)
{
	//Set member variables
	m_pRenderer = _pRenderer;


	//Load mesh file
	m_uiAnimatedMeshId = _pRenderer->GetMeshManager().CreateNewMeshHeirarchy(_kcpMeshFile);


	//Initialise super class CEntity
	CEntity::Initialise(_cpEntityName);


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Processes super class.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CAnimatedObject::Process(float _fDeltaTick)
{
	//Process super class CEntity
	CEntity::Process(_fDeltaTick);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Draws the object.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CAnimatedObject::Draw(CD3DRenderer* _pRenderer, void* _pClassInstance)
{
	//Check object is visible
	//Check mesh id is not invalid
	if (m_bVisible == true && m_uiAnimatedMeshId != Utility::INVALID_ID)
	{
		//Pre-draw
		if (m_vpPreDrawCallback)
		{
			m_vpPreDrawCallback(_pClassInstance, _pRenderer);
		}

		if(CCamera::IsInFrustum(m_mtxWorldMatrix.GetPosition(CVector3()), m_fRadius))
		{
			//Draw animated mesh
			_pRenderer->SetWorldMatrix(&(CEntity::m_mtxWorldMatrix));
			_pRenderer->GetMeshManager().RenderAnimatedMesh(m_uiAnimatedMeshId, _pRenderer);
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


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CAnimatedObject::PreDraw(CD3DRenderer* _pRenderer)
{
	//Empty
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void 
CAnimatedObject::PostDraw(CD3DRenderer* _pRenderer)
{
	//Empty
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
CAnimatedObject::Deinitialise()
{
	//Empty
}