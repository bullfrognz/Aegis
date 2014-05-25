//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   CPlanes.h
//  Description :  
//
//  Author      :   Jamie Smith
//  Mail        :   jamie.smith@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_PLANE_H__
#define __IGFEB11_IG500_PLANE_H__


// Library Includes


// Local Includes
#include "vector3.h"

// Types


// Constants
enum NumPlanes
{
	PLANE_INVALID = -1,
	PLANE_LEFT,
	PLANE_RIGHT,	
	PLANE_BOTTOM,
	PLANE_TOP,	
	PLANE_FAR,
	PLANE_NEAR,
	PLANE_MAX
};


// Prototypes


class CPlane
{

	// Member Functions
public:
	CPlane();
	~CPlane();


protected:	


private:

	
	// Member Variables
public:
	CVector3 m_VectorNormal;

	float m_fDistance;


protected:


private:


};


#endif //__IGFEB11_IG500_STATICStaticObject_H__