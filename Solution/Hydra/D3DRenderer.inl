//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   D3DRenderer.inl
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "DeviceManager.h"
#include "WorldMatrix.h"


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the colour for clearing the back buffer.
*
* @author Bryce Booth
* @param _uiRed		Red amount of the colour.
* @param _uiGreen	Green amount of the colour.
* @param _uiBlue	Blue amount of the colour.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::SetClearColour(unsigned int _uiRed, unsigned int _uiGreen, unsigned int _uiBlue)
{
	m_dwClearColor = D3DCOLOR_XRGB(_uiRed, _uiGreen, _uiBlue);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Calls on the device manager to set the world matrix.
*
* @author Bryce Booth
* @param _kmtxpWorldMatrix	The matrix to be set.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::SetWorldMatrix(const CWorldMatrix* _kmtxpWorldMatrix)
{
	m_pDeviceManager->SetTransform(D3DTS_WORLD, _kmtxpWorldMatrix);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Calls on the device manager to set the view matrix.
*
* @author Bryce Booth
* @param _kmtxpViewMatrix	The matrix to be set.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::SetViewMatrix(const CMatrix* _kmtxpViewMatrix)
{
	m_pDeviceManager->SetTransform(D3DTS_VIEW, _kmtxpViewMatrix);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Calls on the device manager to set the projection matrix.
*
* @author Bryce Booth
* @param _kmtxpProjectionMatrix		The matrix to be set.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::SetProjectionMatrix(const CMatrix* _kmtxpProjectionMatrix)
{
	m_pDeviceManager->SetTransform(D3DTS_PROJECTION, _kmtxpProjectionMatrix);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the current presentation parameters.
*
* @author Bryce Booth
* @return m_td3dPresentParameters	Current presentation parameters
*
*---------------------------------------------------------------------------------------------------------------------------*/

const D3DPRESENT_PARAMETERS&
CD3DRenderer::GetPresentParameters() const
{
	return (m_td3dPresentParameters);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the to be presentation parameters.
*
* @author Bryce Booth
* @return m_td3dToBePresentParameters	Presentation parameters that are going to be set on next device reset	
*
*---------------------------------------------------------------------------------------------------------------------------*/

const D3DPRESENT_PARAMETERS&
CD3DRenderer::GetToBePresentParameters() const
{
	return (m_td3dToBePresentParameters);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Copies the to be present parameters into the current present parameters
*
* @author Bryce Booth	
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CD3DRenderer::DeviceHasBeenReset()
{
	m_td3dPresentParameters = m_td3dToBePresentParameters;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the vertex buffer manager instance.
*
* @author Bryce Booth
* @return m_pVertexBufferManager	Vertex buffer manager instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVertexBufferManager&
CD3DRenderer::GetVertexBufferManager()
{
	return (*m_pVertexBufferManager);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the particle manager instance.
*
* @author Bryce Booth
* @return m_pParticleManager	Particle manager instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

CParticleManager&
CD3DRenderer::GetParticleManager()
{
	return (*m_pParticleManager);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the surface manager instance.
*
* @author Bryce Booth
* @return m_pSurfaceManager	Surface manager instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSurfaceManager&
CD3DRenderer::GetSurfaceManager()
{
	return (*m_pSurfaceManager);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the texture manager instance.
*
* @author Bryce Booth
* @return m_pTextureManager	Particle texture instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

CTextureManager&
CD3DRenderer::GetTextureManager()
{
	return (*m_pTextureManager);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the device manager instance.
*
* @author Bryce Booth
* @return m_pDeviceManager	Device manager instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDeviceManager&
CD3DRenderer::GetDeviceManager()
{
	return (*m_pDeviceManager);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the sprite manager instance.
*
* @author Bryce Booth
* @return m_pSpriteManager	Sprite manager instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSpriteManager&
CD3DRenderer::GetSpriteManager()
{
	return (*m_pSpriteManager);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the light manager instance.
*
* @author Bryce Booth
* @return m_pLightManager	Light manager instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

CLightManager&
CD3DRenderer::GetLightManager()
{
	return (*m_pLightManager);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the mesh manager instance.
*
* @author Bryce Booth
* @return m_pMeshManager	Mesh manager instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMeshManager&
CD3DRenderer::GetMeshManager()
{
	return (*m_pMeshManager);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the fog manager instance.
*
* @author Bryce Booth
* @return m_pFogManager	Fog manager instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

CFogManager&
CD3DRenderer::GetFogManager()
{
	return (*m_pFogManager);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the log manager instance.
*
* @author Bryce Booth
* @return m_pLogWindow	Log manager instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

CLogWindow&
CD3DRenderer::GetLogWindow()
{
	return (*m_pLogWindow);
}