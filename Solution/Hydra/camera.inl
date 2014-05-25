//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   camera.inl
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
float CCamera::GetNearPlane() const
{
	return (m_fNearClip);
}

float CCamera::GetFarPlane() const
{
	return (m_fFarClip);
}

D3DXMATRIX* CCamera::GetViewMatrix()
{
	return (&m_matView);
}

D3DXMATRIX* CCamera::GetProjMatrix()
{
	return (&m_matProj);
}

void
CCamera::SetProjMatrix(CMatrix* _ProjMat)
{
	m_matProj = *_ProjMat;
}


CObject*
CCamera::GetSkyBox()
{
	return (m_pSkyBox);
}