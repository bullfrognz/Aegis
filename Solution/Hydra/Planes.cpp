//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   camera.cpp
//  Description :   for implementation file
//  Author      :   Jamie.Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//


// Library includes.

// Local Includes

// This Include
#include "planes.h"

// Static Variables

// Static Function Prototypes

// Implementation
CPlane::CPlane()
{
	m_VectorNormal.x = 0;
	m_VectorNormal.y = 0;
	m_VectorNormal.z = 0;

	m_fDistance = 0;
}

CPlane::~CPlane()
{

}

