//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   ------.h
//  Description :  
//
//  Author      :   Daniel Lansford
//  Mail        :   daniel.;ansford@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_DEBUGDIALOG_H__
#define __IGFEB11_IG500_DEBUGDIALOG_H__


// Library Includes


// Local Includes
#include "Resource.h"



namespace DebugDialog
{
	void
	InitialiseDialog()
	{
		//Add enemy types to combo box
		HWND hEdit;
		hEdit = GetDlgItem(_hwnd, IDC_ENEMYTYPE);
			
		if(s_bWireframe == true)
		{
			CheckDlgButton(_hwnd, IDC_CHECK2, BST_CHECKED);
		}
		if(s_bDebugInfo == true)
		{
			CheckDlgButton(_hwnd, IDC_CHECK1, BST_CHECKED);
		}
	}


	void
	HandleWMMessage(WPARAM _wparam)
	{
		switch (LOWORD(_wparam))
		{
		case IDC_OK:
			{
				EndDialog(_hwnd, 0);
				CGameWindow& rWindow = dynamic_cast<CGameWindow&>(CApplication::GetInstance().GetGameWindow());

				//Set Wireframe mode.
				if(s_bWireframe == true)
				{
					rWindow.GetRenderer()->GetDeviceManager().SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
				}
				else
				{
					rWindow.GetRenderer()->GetDeviceManager().SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
				}

				//Show debug information.
				if(s_bDebugInfo == true && rWindow.GetCurrentMainSceneType() == SCENE_GAME)
				{
					CGameScene& rGameScene = dynamic_cast<CGameScene&>(rWindow.GetCurrentMainScene());
					rGameScene.SetShowDebugInfo(true);						
				}
				else if(s_bDebugInfo == false && rWindow.GetCurrentMainSceneType() == SCENE_GAME)
				{
					CGameScene& rGameScene = dynamic_cast<CGameScene&>(rWindow.GetCurrentMainScene());
					rGameScene.SetShowDebugInfo(false);		
				}	

				if(rWindow.GetCurrentMainSceneType() == SCENE_GAME)
				{
					//Set new Player gold.
					HWND hEdit = GetDlgItem(_hwnd, IDC_EDIT1);
					wchar_t wcMsgTxt[20];
					GetWindowText(hEdit, wcMsgTxt, 19);

					s_uiPlayerGold = static_cast<unsigned int>(_wtoi(wcMsgTxt));
					CGameScene& rGameScene = dynamic_cast<CGameScene&>(rWindow.GetCurrentMainScene());
					rGameScene.GetPlayer()->SetGold(s_uiPlayerGold);

					//Set new player lives.
					hEdit = GetDlgItem(_hwnd, IDC_EDIT2);
					GetWindowText(hEdit, wcMsgTxt, 19);

					s_uiPlayerLives = static_cast<unsigned int>(_wtoi(wcMsgTxt));
					rGameScene.GetPlayer()->SetLives(s_uiPlayerLives);

					/*----------------*
					 * ENEMY SPAWNING *
					 *----------------*/
					hEdit = GetDlgItem(_hwnd, IDC_EDIT7);
					GetWindowText(hEdit, wcMsgTxt, 19);

					s_uiEnemySpawnNumber = static_cast<unsigned int>(_wtoi(wcMsgTxt));

					hEdit = GetDlgItem(_hwnd, IDC_EDIT3);
					GetWindowText(hEdit, wcMsgTxt, 19);

					s_fEnemySpawnRate =  static_cast<float>(_wtof(wcMsgTxt));

					rGameScene.GetEenmySpawner()->CreateSpawnPool(rWindow.GetRenderer(), "Fast Enemy", s_uiEnemySpawnNumber,
																  s_fEnemySpawnRate, rGameScene.GetPlayer()); 
				}

				break;
			}
			break;

		case IDC_BUTTON3:
			{
				if(rWindow.GetCurrentMainSceneType() == SCENE_GAME)
				{
					CApplication::GetInstance().GetGameWindow().GetRenderer()->GetSpriteManager().EraseAll();
					CApplication::GetInstance().GetGameWindow().SetMainScene(SCENE_MAPEDITOR, 0);
				}
			}

		case IDC_CHECK1:
			{
				if(s_bDebugInfo == true)
				{
					s_bDebugInfo = false;
				}
				else
				{
					s_bDebugInfo = true;
				}

				break;
			}
		
		case IDC_CHECK2:
			{
				if(s_bWireframe == false)
				{
					s_bWireframe = true;
				}
				else
				{
					s_bWireframe = false;
				}
				break;
			}	
		case IDC_RESET:
			{
				//CApplication::GetInstance().GetGameWindow().GetRenderer()->GetSpriteManager().EraseAll();

				CApplication::GetInstance().GetGameWindow().SetMainScene(SCENE_GAME, 0);
				EndDialog(_hwnd, 0);
				break;
			}
		case IDC_CANCEL:
			{
				EndDialog(_hwnd, 0);
				break;
			}
		}
	}



	void Close()
	{
		EndDialog(_hwnd, 0);
	}


	BOOL CALLBACK
	DlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
	{
		CGameWindow& rWindow = dynamic_cast<CGameWindow&>(CApplication::GetInstance().GetGameWindow());
		
		switch(_msg)
		{

		case WM_INITDIALOG:
			{
				DebugDialog::InitialiseDialog();
				break;
			}

		case WM_COMMAND:
			{
				DebugDialog::HandleWMMessage(WPARAM _wparam)
				break;
			}	

		case WM_CLOSE:
			{
				DebugDialog::Close()
				break;
			}
		}

		return(FALSE);
	}


	BOOL CALLBACK
	SaveProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
	{
		switch(_msg)
		{
		case WM_INITDIALOG:
			{
				
			}
		case WM_COMMAND:
			{
				switch (LOWORD(_wparam))
				{
				case IDC_SAVE:
					{
						s_pParser = new CINIParser();
				
						//------Set new Player gold.------------
						HWND hEdit = GetDlgItem(_hwnd, IDC_DIAL2EDIT1);
						wchar_t wcMsgTxt[20];
						GetWindowText(hEdit, wcMsgTxt, 19);

						int iGold = static_cast<int>(_wtoi(wcMsgTxt));

						if(iGold <= 20)
						{
							iGold = 20;
						}

						char GoldAmmount[20];
						_itoa_s(iGold, GoldAmmount, 20, 10);

						//---------------------------------------------------

						//-------Set new player lives.---------------
						hEdit = GetDlgItem(_hwnd, IDC_DIAL2EDIT2);
						GetWindowText(hEdit, wcMsgTxt, 19);

						int iLives = static_cast<int>(_wtoi(wcMsgTxt));

						if(iLives <= 0)
						{
							iLives = 1;
						}

						char LivesAmmount[20];
						_itoa_s(iLives, LivesAmmount, 20, 10);

						//----------------------------------------------------

						//-------Set the starting difficulty---------------
						hEdit = GetDlgItem(_hwnd, IDC_DIAL2EDIT3);
						GetWindowText(hEdit, wcMsgTxt, 19);

						int iWaveLength = static_cast<int>(_wtoi(wcMsgTxt));

						if(iWaveLength <= 0)
						{
							iWaveLength = 1;
						}

						char WaveNumber[20];
						_itoa_s(iWaveLength, WaveNumber, 20, 10);

						//----------------------------------------------------------

						//--------Save The Map----------------				

						OPENFILENAME File;
						ZeroMemory(&File, sizeof(OPENFILENAME));

						wchar_t wcFilePath[256];
						wcFilePath[0] = NULL;

						File.lStructSize = sizeof(OPENFILENAME);
						File.hwndOwner = _hwnd;
						File.lpstrFilter = L".Map";
						File.nFilterIndex = 1;
						File.lpstrFile = wcFilePath;
						File.nMaxFile = 256;
						File.lpstrDefExt = L"map";
						File.Flags = OFN_CREATEPROMPT | OFN_PATHMUSTEXIST |
									OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
						File.lpstrInitialDir = L"Maps/";

						GetSaveFileName(&File);

						File.lpstrFilter;

						char* kcFileName = new char[256];

						size_t temp = 0;
						wcstombs_s(&temp, kcFileName, (size_t)256, File.lpstrFile, (size_t)256);


						CGameWindow& rWindow = dynamic_cast<CGameWindow&>(CApplication::GetInstance().GetGameWindow());
						//-------------------------------------------------------------------									

						s_pParser->LoadINIFile(kcFileName);			
						s_pParser->AddValue("[PlayerStats]", "Gold", GoldAmmount);
						s_pParser->AddValue("[PlayerStats]", "Lives", LivesAmmount);
						s_pParser->AddValue("[WaveStartingNumber]", "Wave", WaveNumber);
						s_pParser->SaveINIFile(kcFileName);
						dynamic_cast<CMapEditor*>(&rWindow.GetCurrentMainScene())->Save(kcFileName);

						delete s_pParser;
						s_pParser = 0;

						delete kcFileName;

						EndDialog(_hwnd, 0);
						break;
					}
					break;			
				case IDCANCEL:
					{
						EndDialog(_hwnd, 0);
						break;
					}
				}
				break;
			}	
			break;

		case WM_CLOSE:
			{
				EndDialog(_hwnd, 0);
				break;
			}
		}


		return(FALSE);
	}




	BOOL CALLBACK
	LoadProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
	{
		switch(_msg)
		{
		case WM_INITDIALOG:
			{		
				s_pParser = new CINIParser();
				
				//--------Load The Map----------------
				OPENFILENAME File;
				ZeroMemory(&File, sizeof(OPENFILENAME));

				wchar_t wcFilePath[256];
				wcFilePath[0] = NULL;

				File.lStructSize = sizeof(OPENFILENAME);
				File.hwndOwner = _hwnd;
				File.lpstrFilter = L".Map";
				File.nFilterIndex = 1;
				File.lpstrFile = wcFilePath;
				File.nMaxFile = 256;
				File.lpstrDefExt = L"map";
				File.Flags = OFN_CREATEPROMPT | OFN_PATHMUSTEXIST |
							OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
				File.lpstrInitialDir = L"Maps/";

				GetOpenFileName(&File);

				File.lpstrFilter;

				char* kcFileName = new char[256];

				size_t temp = 0;
				wcstombs_s(&temp, kcFileName, (size_t)256, File.lpstrFile, (size_t)256);


				CGameWindow& rWindow = dynamic_cast<CGameWindow&>(CApplication::GetInstance().GetGameWindow());
				
				//----------------------------------------			
				
				dynamic_cast<CMapEditor*>(&rWindow.GetCurrentMainScene())->Load(kcFileName);
				s_pParser->SaveINIFile(kcFileName);

				delete s_pParser;
				s_pParser = 0;

				delete kcFileName;

				EndDialog(_hwnd, 0);
				
			}
			break;			
				

		case WM_CLOSE:
			{
				EndDialog(_hwnd, 0);
				break;
			}
		}


		return(FALSE);
	}


}




#endif //__IGFEB11_IG500_DEBUGDIALOG_H__