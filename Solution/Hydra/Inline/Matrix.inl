//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Matrix.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMatrix::Inverse()
{
	//Get matrix determinant
	float fDeterminant = D3DXMatrixDeterminant(this);


	//Inverse matrix
	D3DXMatrixInverse(this, &fDeterminant, this);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CMatrix::GetDeterminant() const
{
	//Get matrix determinant
	float fDeterminant = D3DXMatrixDeterminant(this);


	return (fDeterminant);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMatrix::operator = (const D3DXMATRIX& _kmtxrMatrix)
{
	memcpy(this, &_kmtxrMatrix, sizeof(D3DXMATRIX));
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMatrix::operator = (const CMatrix& _kmtxrMatrix)
{
	memcpy(this, &_kmtxrMatrix, sizeof(CMatrix));
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CMatrix::operator == (const CMatrix& _kmtxrMatrix) const
{
	//Compare memory of the two matrix
	int iMemResult = memcmp(this, &_kmtxrMatrix, sizeof(CMatrix));


	return (iMemResult == 0);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CMatrix::operator != (const CMatrix& _kmtxrMatrix) const
{
	//Compare memory of the two matrix
	int iMemResult = memcmp(this, &_kmtxrMatrix, sizeof(CMatrix));


	return (iMemResult != 0);;
}