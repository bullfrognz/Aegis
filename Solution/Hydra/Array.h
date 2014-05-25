//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Array.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_ARRAY_H__
#define __IGFEB11_IG500_ARRAY_H__


// Library Includes
#include <vector>


// Local Includes


// Types
typedef void (*InsertCallback)(void*);


// Constants


// Prototypes


template <typename TYPE, unsigned int INCREMENTRATE, InsertCallback INSERTCALLBACK = 0>
class CArray
{

	// Member Functions
public:


	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* Array class constructor
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	CArray()
	: m_uiContainerSize(0)
	, m_uiIncrementRate(INCREMENTRATE)
	, m_pArrayData(0)
	, m_uiMaxActiveId(0)
	, m_vpInsertCallback(INSERTCALLBACK)
	{
		//Empty
	}


	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* Array class deconstructor
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	~CArray()
	{
		delete[] m_pArrayData;
		m_pArrayData = 0;
	}


	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	unsigned int Insert(TYPE _rTYPE)
	{	
		unsigned int uiIndex = 0;


		if (m_vecDeletedIndices.size() != 0)
		{
			uiIndex = m_vecDeletedIndices[0];
		}
		else
		{
			if (m_uiMaxActiveId + 1 >= m_uiContainerSize)
			{
				IncrementContainerSize();
			}


			uiIndex = m_uiMaxActiveId ++;
		}


		m_pArrayData[uiIndex] = _rTYPE;


		if (m_vpInsertCallback != 0)
		{
			m_vpInsertCallback(reinterpret_cast<void*>(m_pArrayData[uiIndex]));
		}


		return (uiIndex);
	}


	// Inline Functions


	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	inline TYPE& operator [] (int _uiIndex)
	{
		return (m_pArrayData[_uiIndex]);
	}









	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	inline void Erase(unsigned int _uiIndex)
	{
		m_pArrayData[_uiIndex] = 0;


		m_vecDeletedIndices.push_back(_uiIndex);
	}









	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	inline void SetInsertCallback(InsertCallback _vpInsertCallback)
	{
		m_vpInsertCallback = _vpInsertCallback;
	}









	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	inline unsigned int GetSize() const
	{
		return (m_uiMaxActiveId);	
	}









	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	inline unsigned int GetNextFreeIndex() const
	{
		if (m_vecDeletedIndices.size() != 0)
		{
			return (m_vecDeletedIndices[0]);
		}
		else
		{
			return (m_uiMaxActiveId);
		}
	}









	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	inline TYPE* GetContainerData()
	{
		return (m_pArrayData);
	}


protected:


	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void IncrementContainerSize()
	{
		//Calculate new array size
		const unsigned int kuiNewContainerSize = m_uiContainerSize + m_uiIncrementRate;


		//Backup array date
		TYPE* pTempArrayData = new TYPE[m_uiContainerSize];
		memcpy(pTempArrayData, m_pArrayData, sizeof(TYPE*) * m_uiContainerSize);


		//Delete current array data
		delete[] m_pArrayData;
		m_pArrayData = 0;


		//Expand array container
		m_pArrayData = new TYPE[kuiNewContainerSize];


		//Restore backup
		memcpy(m_pArrayData, pTempArrayData, sizeof(TYPE*) * m_uiContainerSize);


		//Delete temp array data
		delete[] pTempArrayData;
		pTempArrayData = 0;


		//Clean memory
		for (unsigned int i = m_uiContainerSize; i < kuiNewContainerSize; ++i)
		{
			m_pArrayData[i] = 0;
		}


		//Set new container size
		m_uiContainerSize = kuiNewContainerSize;
	}


private:


	// Member Variables
protected:


	TYPE* m_pArrayData;

	InsertCallback m_vpInsertCallback;


	unsigned int m_uiContainerSize;
	unsigned int m_uiIncrementRate;
	unsigned int m_uiMaxActiveId;


	std::vector<unsigned int> m_vecDeletedIndices;


private:


};


#endif //__IGFEB11_IG500_ARRAY_H__