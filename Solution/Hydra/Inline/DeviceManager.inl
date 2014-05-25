//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   DeviceManager.inl
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the currently set view matrix
*
* @author Bryce Booth
*
* @param m_kmtxpTransformMatrix[D3DTS_VIEW]	Currently set view matrix.
*
*---------------------------------------------------------------------------------------------------------------------------*/

const CMatrix*
CDeviceManager::GetViewMatrix() const
{
	return (m_kmtxpTransformMatrix[D3DTS_VIEW]);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the currently set projectile matrix.
*
* @author Bryce Booth
*
* @param m_kmtxpTransformMatrix[D3DTS_PROJECTION]  Currently set projectile matrix.
*
*---------------------------------------------------------------------------------------------------------------------------*/

const CMatrix*
CDeviceManager::GetProjectionMatrix() const
{
	return (m_kmtxpTransformMatrix[D3DTS_PROJECTION]);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates an ID3DXLine.
*
* @author Jade Abbott
*
* @param _ppLine Holds the pointer to the interface when the function returns.
*
* @return HRESULT rreturned from calling the function.
*
*---------------------------------------------------------------------------------------------------------------------------*/
HRESULT
CDeviceManager::CreateLine(LPD3DXLINE* _ppLine)
{
	return D3DXCreateLine(m_pDirect3DDevice, _ppLine);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns set render state value.
*
* @author Bryce Booth
*
* @param _ed3dRenderStateType  Render states define set-up states for all kinds of vertex and pixel processing.
*
* @return m_dwRenderStates[_ed3dRenderStateType]  Value for the render state.
*
*---------------------------------------------------------------------------------------------------------------------------*/

DWORD
CDeviceManager::GetRenderStateValue(D3DRENDERSTATETYPE _ed3dRenderStateType)
{
	return (m_dwRenderStates[_ed3dRenderStateType]);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the texture state state value.
*
* @author Bryce Booth
*
* @param _dwStage					 Stage of the texture state.	 
* @param _ed3dTextureStageStateType	 Texture stage states define multi-blender texture operations.
*
* @return m_dwTextureStageStates[_dwStage][_ed3dTextureStageStateType]  Value currently set on the texture stage.
*
*---------------------------------------------------------------------------------------------------------------------------*/

DWORD
CDeviceManager::GetTextureStageStateValue(DWORD _dwStage, D3DTEXTURESTAGESTATETYPE _ed3dTextureStageStateType)
{
	return (m_dwTextureStageStates[_dwStage][_ed3dTextureStageStateType]);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the currently set value for the stage state.
*
* @author Bryce Booth
*
* @param _dwSampler				The sampler of the sampler stage.
* @param _ed3dSamplerStateType	Sampler states define texture sampling operations such as texture addressing and texture filtering.
*
* @return m_dwSamplerStageStates[_dwSampler][_ed3dSamplerStateType]	 Value currently set on the sampler stage.
*
*---------------------------------------------------------------------------------------------------------------------------*/

DWORD
CDeviceManager::GetSamplerStageStateValue(DWORD _dwSampler, D3DSAMPLERSTATETYPE _ed3dSamplerStateType)
{
	return (m_dwSamplerStageStates[_dwSampler][_ed3dSamplerStateType]);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the default material for the device
*
* @author Bryce Booth
*
* @return m_matDefaultMaterial	Default material interface.
*
*---------------------------------------------------------------------------------------------------------------------------*/

D3DMATERIAL9&
CDeviceManager::GetDefaultMaterial()
{
	return (m_matDefaultMaterial);
}