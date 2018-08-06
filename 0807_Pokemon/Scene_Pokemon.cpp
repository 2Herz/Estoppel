#include "stdafx.h"
#include "Scene_Pokemon.h"
#include "SceneMgr.h"

Scene_Pokemon::Scene_Pokemon()
{
	m_BGDC = IMG_MGR->GetImg("Pokemon_00")->GetImgDC();
}

Scene_Pokemon::~Scene_Pokemon()
{
}

void Scene_Pokemon::Init(HWND _hWnd)
{
}

void Scene_Pokemon::Update(float _elapseTime)
{
}

void Scene_Pokemon::Render(HDC _hdc)
{
	BitBlt(_hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, m_BGDC, 0, 0, SRCCOPY);
	auto focusImg1	= IMG_MGR->GetImg("Pokemon_01");
	auto focusImg2	= IMG_MGR->GetImg("Pokemon_02");
	auto focusImg3	= IMG_MGR->GetImg("Pokemon_03");
	auto changeImg1	= IMG_MGR->GetImg("PokemonChange_01");
	auto changeImg2 = IMG_MGR->GetImg("PokemonChange_02");
	//	���ϰ� �ִ� ���ϸ� ���� ��Ŀ�̿��� ��°��� �پ��� �ٲٱ�

	//	��Ŀ��
	switch (m_PokemonSelect)
	{
	case 0:
	{
		if (m_isChange == false)
			focusImg1->AniRender(_hdc, 1, 8, 72);
		else
			changeImg1->AniRender(_hdc, 1, 8, 72);

		for (int i = 1; i < m_PokemonCount; i++)
		{
			if (m_isCheck[i] == true)
				changeImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
			else
				focusImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
		}
		focusImg3->AniRender(_hdc, 0, 736, 528);
	}break;

	case 1:
	{
		if(m_isCheck[0] == false)
			focusImg1->AniRender(_hdc, 0, 8, 72);
		else
			changeImg1->AniRender(_hdc, 0, 8, 72);

		for (int i = 1; i < m_PokemonCount; i++)
		{
			if (i == m_PokemonSelect)
				if (m_isChange == false)
					focusImg2->AniRender(_hdc, 1, 352, (96 * (i - 1)) + 36);
				else
					changeImg2->AniRender(_hdc, 1, 352, (96 * (i - 1)) + 36);
			else
				if (m_isCheck[i] == true)
					changeImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
				else
					focusImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
		}
		focusImg3->AniRender(_hdc, 0, 736, 528);
	}break;
	
	case 2:
	{
		if (m_isCheck[0] == false)
			focusImg1->AniRender(_hdc, 0, 8, 72);
		else
			changeImg1->AniRender(_hdc, 0, 8, 72);

		for (int i = 1; i < m_PokemonCount; i++)
		{
			if (i == m_PokemonSelect)
				if (m_isChange == false)
					focusImg2->AniRender(_hdc, 1, 352, (96 * (i - 1)) + 36);
				else
					changeImg2->AniRender(_hdc, 1, 352, (96 * (i - 1)) + 36);
			else
				if (m_isCheck[i] == true)
					changeImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
				else
					focusImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
		}
		focusImg3->AniRender(_hdc, 0, 736, 528);
	}break;
	
	case 3:
	{
		if (m_isCheck[0] == false)
			focusImg1->AniRender(_hdc, 0, 8, 72);
		else
			changeImg1->AniRender(_hdc, 0, 8, 72);

		for (int i = 1; i < m_PokemonCount; i++)
		{
			if (i == m_PokemonSelect)
				if(m_isChange == false)
					focusImg2->AniRender(_hdc, 1, 352, (96 * (i - 1)) + 36);
				else
					changeImg2->AniRender(_hdc, 1, 352, (96 * (i - 1)) + 36);
			else
				if (m_isCheck[i] == true)
					changeImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
				else
					focusImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
		}
		focusImg3->AniRender(_hdc, 0, 736, 528);
	}break;
	
	case 4:
	{
		if (m_isCheck[0] == false)
			focusImg1->AniRender(_hdc, 0, 8, 72);
		else
			changeImg1->AniRender(_hdc, 0, 8, 72);

		for (int i = 1; i < m_PokemonCount; i++)
		{
			if (i == m_PokemonSelect)
				if (m_isChange == false)
					focusImg2->AniRender(_hdc, 1, 352, (96 * (i - 1)) + 36);
				else
					changeImg2->AniRender(_hdc, 1, 352, (96 * (i - 1)) + 36);
			else
				if (m_isCheck[i] == true)
					changeImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
				else
					focusImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
		}
		focusImg3->AniRender(_hdc, 0, 736, 528);
	}break;
	
	case 5:
	{
		if (m_isCheck[0] == false)
			focusImg1->AniRender(_hdc, 0, 8, 72);
		else
			changeImg1->AniRender(_hdc, 0, 8, 72);

		for (int i = 1; i < m_PokemonCount; i++)
		{
			if (i == m_PokemonSelect)
				if (m_isChange == false)
					focusImg2->AniRender(_hdc, 1, 352, (96 * (i - 1)) + 36);
				else
					changeImg2->AniRender(_hdc, 1, 352, (96 * (i - 1)) + 36);
			else
				if (m_isCheck[i] == true)
					changeImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
				else
					focusImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
		}
		focusImg3->AniRender(_hdc, 0, 736, 528);
	}break;

	case 6:
	{
		if (m_isCheck[0] == false)
			focusImg1->AniRender(_hdc, 0, 8, 72);
		else
			changeImg1->AniRender(_hdc, 0, 8, 72);

		for (int i = 1; i < m_PokemonCount; i++)
		{
			if (i == m_PokemonSelect)
				if (m_isChange == false)
					focusImg2->AniRender(_hdc, 1, 352, (96 * (i - 1)) + 36);
				else
					changeImg2->AniRender(_hdc, 1, 352, (96 * (i - 1)) + 36);
			else
				if (m_isCheck[i] == true)
					changeImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
				else
					focusImg2->AniRender(_hdc, 0, 352, (96 * (i - 1)) + 36);
		}
		focusImg3->AniRender(_hdc, 1, 736, 528);
	}break;
	}
	
	//	���� == false
	if (m_isClick == false && m_isChange == false)
	{
		m_Box.BoxCreate(_hdc, 0, 16, 22, 19);
		m_Txt.TextBox(_hdc, 42, (64 * 8) + 44, "���ϸ��� ������ �ֽʽÿ�", 40);
		m_Txt.TextBox(_hdc, 820, (64 * 8) + 44, "���", 40, WHITE);
	}

	if (m_isChange == true)
	{
		m_Box.BoxCreate(_hdc, 0, 16, 22, 19);
		m_Txt.TextBox(_hdc, 42, (64 * 8) + 44, "���� �̵��ұ�?", 40);
		m_Txt.TextBox(_hdc, 820, (64 * 8) + 44, "���", 40, WHITE);
	}

	//	���� == true
	if (m_isClick == true)
	{
		m_Box.BoxCreate(_hdc, 0, 16, 18, 19);
		m_Txt.TextBox(_hdc, 42, (64 * 8) + 44, "\"�̸�\" ����ұ�", 40);
		//	�������϶��� �ٲ۴�, ���º���, �׸��δ� 3����
		if (m_isBattle == true)
		{
			m_Box.BoxCreate(_hdc, 19, 12, 29, 19, 3, true);
			m_Txt.TextBox(_hdc, 665, (64 * 6) + 30, "�ٲ۴�", 40);
			m_Txt.TextBox(_hdc, 665, (64 * 7) + 30, "���º���", 40);
			m_Txt.TextBox(_hdc, 665, (64 * 8) + 30, "�׸��δ�", 40);
		}
		else
		{
			//	�����ӽ� ��� ��� ���� ũ�� �ٸ�
			m_Box.BoxCreate(_hdc, 19, 10, 29, 19, 4, true);
			m_Txt.TextBox(_hdc, 665, (64 * 5) + 30, "���º���", 40);
			m_Txt.TextBox(_hdc, 665, (64 * 6) + 30, "��������", 40);
			m_Txt.TextBox(_hdc, 665, (64 * 7) + 30, "���ѹ���", 40);
			m_Txt.TextBox(_hdc, 665, (64 * 8) + 30, "�׸��δ�", 40);
		}
	}
}

bool Scene_Pokemon::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case VK_UP:
		{
			if (m_isClick == false)
			{
				m_PokemonSelect--;
				if (m_PokemonSelect < 0)
					m_PokemonSelect = 6;
				else if (m_PokemonSelect > m_PokemonCount)
					m_PokemonSelect = m_PokemonCount - 1;
			}
			else
			{
				m_isSelect--;
				if (m_isSelect < 1)
					m_isSelect = 4;
			}
		}break;

		case VK_DOWN:
		{
			if (m_isClick == false)
			{
				m_PokemonSelect++;
				if (m_PokemonSelect == m_PokemonCount)
					m_PokemonSelect = 6;
				else if (m_PokemonSelect == 7)
					m_PokemonSelect = 0;
			}
			else
			{
				m_isSelect++;
				if (m_isSelect > 4)
					m_isSelect = 1;
			}
		}break;

		case 'z':
		case 'Z':
		{
			if (m_isChange == true)
			{
				m_isChange = false;
				m_isClick = false;
				m_Box.m_Select = 0;

				//	��� ������ �ƴ϶��
				if (m_PokemonSelect != 6)
				{
					for (int i = 0; i < 6; i++)
					{
						if (m_isCheck[i] == true)
						{
							//	���� �ٲٴ� �ڵ� �̰���
							//	�迭 ���� ã�Ƽ� true�� ���� ���� ���õ� ��ü�� ���ϸ�
							//	temp�ϳ� ����� ���� �ڸ��� �ٲ��ָ� ��
						}
					}
				}
				//	�ʱ�ȭ
				for (int i = 0; i < 6; i++)
				{
					m_isCheck[i] = false;
				}
				break;
			}
			if (m_PokemonSelect == 6)
				SCENE_MGR.SetScene(SCENE_MENU);

			if (m_isClick == false)
			{
				m_isClick = true;
				m_isSelect = 1;
			}
			else if (m_isClick == true && m_isSelect == 1)	//	���º���
			{
				m_Box.m_Select = 0;
				SCENE_MGR.SetScene(SCENE_INFO);
			}
			else if (m_isClick == true && m_isSelect == 2)	//	��������
			{
				m_isChange	= true;
				m_isClick	= false;
				m_isCheck[m_PokemonSelect] = true;
				m_Box.m_Select = 0;
			}
			else if (m_isClick == true && m_isSelect == 3)	//	���ѹ���
			{

				m_Box.m_Select = 0;
			}
			else if (m_isClick == true && m_isSelect == 4)	//	�׸��δ�
			{
				m_isClick = false;
				m_Box.m_Select = 0;
			}
			
			
		}break;

		case 'x':
		case 'X': 
		{	
			if (m_isClick == true)
			{
				m_isClick = false;
				m_Box.m_Select = 0;
			}
			else
				SCENE_MGR.SetScene(SCENE_MENU); 
		}break;

		case 'b':
		case 'B': {	m_isBattle = !m_isBattle; }break;

		case VK_ESCAPE: return true;	break;
		}
	}break;

	}
	return false;
}