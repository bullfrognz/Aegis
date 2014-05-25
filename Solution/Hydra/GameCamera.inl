//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   GameCamera.inl
//  Description :   for inline implementation file
//  Author      :   Jamie.Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Include

// Static Variables

// Static Function Prototypes

// Implementation
float CGameCamera::GetNearPlane() const
{
	return (m_fNearClip);
}

float CGameCamera::GetFarPlane() const
{
	return (m_fFarClip);
}

D3DXMATRIX* CGameCamera::GetViewMatrix()
{
	return (&m_matView);
}

D3DXMATRIX* CGameCamera::GetProjMatrix()
{
	return (&m_matProj);
}