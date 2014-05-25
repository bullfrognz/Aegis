//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   StrUtilitites.cpp
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <windows.h>
#include <cassert>


// Local Includes


// This Include
#include "StrUtilities.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


namespace StrUtilities
{


	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	Copy(const char* _kcpInput, char*& _cprOutput)
	{
		if (_kcpInput != 0)
		{
			// Get input string length
			unsigned int uiStrLength = 0;
			while(_kcpInput[uiStrLength++]);	// Includes null terminator.


			if (uiStrLength > 1)
			{
				// Create new string buffer
				_cprOutput = new char[uiStrLength];


				// Copy string memory
				memcpy(_cprOutput, _kcpInput, uiStrLength * sizeof(char));
			}
		}
	}







	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	Copy(const char* _kcpInput, const char*& _kcprOutput)
	{
		if (_kcpInput != 0)
		{
			// Get input string length
			unsigned int uiStrLength = 0;
			while(_kcpInput[uiStrLength++]);	// Includes null terminator.



			if (uiStrLength > 1)
			{
				// Create new string buffer
				char* cpBuffer = new char[uiStrLength];


				// Copy string memory
				memcpy(cpBuffer, _kcpInput, uiStrLength * sizeof(char));


				_kcprOutput = cpBuffer;
			}
		}
	}







	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* Copies wchar type variable to another wchar variable.
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	Copy(const wchar_t* _kwcpInput, wchar_t*& _wcprOutput)
	{
		if (_kwcpInput != 0)
		{
			// Get input string length
			unsigned int uiStrLength = 0;
			while(_kwcpInput[uiStrLength++]);	// Includes null terminator.



			if (uiStrLength > 1)
			{
				// Create new string buffer
				_wcprOutput = new wchar_t[uiStrLength];


				// Copy string memory
				memcpy(_wcprOutput, _kwcpInput, uiStrLength * sizeof(wchar_t));
			}
		}
	}







	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* Copies wchar type variable to another const wchar variable.
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	Copy(const wchar_t* _kwcpInput, const wchar_t*& _kwcprOutput)
	{
		if (_kwcpInput != 0)
		{
			// Get input string length
			unsigned int uiStrLength = 0;
			while(_kwcpInput[uiStrLength++]);	// Includes null terminator.


			if (uiStrLength > 1)
			{
				// Create new string buffer
				wchar_t* wcpBuffer = new wchar_t[uiStrLength];


				// Copy string memory
				memcpy(wcpBuffer, _kwcpInput, uiStrLength * sizeof(wchar_t));


				_kwcprOutput = wcpBuffer;
			}
		}
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	Trim(char*& _cprString)
	{
		TrimLeft(_cprString);
		TrimRight(_cprString);
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	TrimLeft(char*& _cprString)
	{
		// Get input string length
		UINT uiStrLength =  static_cast<UINT>(strlen(_cprString));


		UINT uiWhiteSpaceSkip = 0;

		// Loop through string to find spaces
		for (UINT i = 0; i < uiStrLength; ++i)
		{
			if (_cprString[i] == ' ' || _cprString[i] == '\t')
			{
				++ uiWhiteSpaceSkip;
			}
			else
			{
				break;
			}
		}


		// Loop through string to remove white spaces
		for (UINT i = 0; i < uiStrLength; ++i)
		{
			if (i < uiStrLength - uiWhiteSpaceSkip)
			{
				_cprString[i] = _cprString[i + uiWhiteSpaceSkip];
			}
			else
			{
				_cprString[i] = '\0';
			}
		}
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	TrimRight(char*& _cprString)
	{

		if (!_cprString)
			return;

		// Get input string length.
		unsigned int uiStrLength = 0;
		while (_cprString[uiStrLength++]);	// Includes null terminator.

		// Loop through string to remove white spaces.
		for (unsigned int uiChar = uiStrLength - 2; uiChar != 4294967295; --uiChar)
		{
			if (_cprString[uiChar] == ' ' || _cprString[uiChar] == 0x09)
			{
				_cprString[uiChar] = '\0';
			}
			else
			{
				break;
			}
		}
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	ConvertToWChar(const char* _kcpInput, wchar_t*& _wcprOutput)
	{
		// Get input string length plus null terminator
		unsigned int uiStrLength =  static_cast<UINT>(strlen(_kcpInput)) + 1;


		// Create new wchar_t variable based on string length
		_wcprOutput = new wchar_t[uiStrLength];


		// Literate thorugh input string and copy characters
		for (unsigned int i = 0; i < uiStrLength; ++i)
		{
			_wcprOutput[i] = _kcpInput[i];
		}
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	ConvertToChar(const wchar_t* _kwcpInput, char*& _cprOutput)
	{
		// Get input string length plus null terminator
		unsigned int uiStrLength =  static_cast<unsigned int>(wcslen(_kwcpInput)) + 1;


		// Create new wchar_t variable based on string length
		_cprOutput = new char[uiStrLength];


		// Literate thorugh input string and copy characters
		for (UINT i = 0; i < uiStrLength; ++i)
		{
			_cprOutput[i] = static_cast<char>(_kwcpInput[i]);
		}
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	ToUpperCase(char* _cpString)
	{
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	ToLowerCase(char* _cpString)
	{
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	AddPrefix(const char* _kcpInput, char*& _cprOutput)
	{
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	AddSuffix(const char* _kcpInput, char*& _cprOutput)
	{
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	GetNumCharEntries(const char* _kcpInput, const char* _kcpCharacter, int& _irNumEntries)
	{
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	unsigned int
	GetStringValue(const char* _kcpString)
	{
		// Set default variables
		unsigned int _uiStringValue = 0;
		unsigned int _uiIndexValue = 0;


		// Get input string length plus null terminator
		UINT uiStrLength =  static_cast<UINT>(strlen(_kcpString));


		// Literate thorugh input string
		for (UINT i = 0; i < uiStrLength; ++i)
		{
			_uiStringValue += _kcpString[i] * (i + 1);
		}


		return (_uiStringValue);
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	unsigned int
	GetStringValue(const wchar_t* _kwcpString)
	{
		// Set default variables
		unsigned int _uiStringValue = 0;
		unsigned int _uiIndexValue = 0;


		// Get input string length plus null terminator
		UINT uiStrLength =  static_cast<UINT>(wcslen(_kwcpString));


		// Literate thorugh input string
		for (UINT i = 0; i < uiStrLength; ++i)
		{
			_uiStringValue += _kwcpString[i] * (i + 1);
		}


		return (_uiStringValue);
	}


}