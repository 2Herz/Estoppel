#include "PokemonUI.h"

PokemonUI::PokemonUI()
{
}

PokemonUI::~PokemonUI()
{
}

void PokemonUI::Init(HWND _hWnd)
{
	IMG_MGR->OpenImg("Image/Pokemon_00.bmp");
	IMG_MGR->OpenImg("Image/Pokemon_01.bmp");
	IMG_MGR->OpenImg("Image/Pokemon_02.bmp");
	IMG_MGR->OpenImg("Image/Pokemon_03.bmp");

	m_BGDC = IMG_MGR->GetImg("Pokemon_00")->GetImgDC();

	auto	focusImg1 = IMG_MGR->GetImg("Pokemon_01");
	if (focusImg1 != nullptr)
	{
		focusImg1->SetTrans();
		focusImg1->SetFrame(2);
	}

	auto	focusImg2 = IMG_MGR->GetImg("Pokemon_02");
	if (focusImg2 != nullptr)
	{
		focusImg2->SetTrans();
		focusImg2->SetFrame(2);
	}

	auto	focusImg3 = IMG_MGR->GetImg("Pokemon_03");
	if (focusImg3 != nullptr)
	{
		focusImg3->SetTrans();
		focusImg3->SetFrame(2);
	}
}

void PokemonUI::RenderPokemon(HDC _hdc)
{
	BitBlt(_hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, m_BGDC, 0, 0, SRCCOPY);
	auto focusImg1 = IMG_MGR->GetImg("Pokemon_01");
	auto focusImg2 = IMG_MGR->GetImg("Pokemon_02");
	auto focusImg3 = IMG_MGR->GetImg("Pokemon_03");

	

	//	지니고 있는 포켓몬에 따라 포커싱에서 출력개수 줄어들게 바꾸기

	//	포커싱
	switch (m_PokemonSelect)
	{
	case 0:
	{
		focusImg1->AniRender(_hdc, 1, 8, 72);
		for (int i = 0; i < m_PokemonCount - 1; i++)
		{
			focusImg2->AniRender(_hdc, 0, 352, (96 * i) + 36);
		}
		focusImg3->AniRender(_hdc, 0, 736, 528);
	}break;

	case 1:
	{
		focusImg1->AniRender(_hdc, 0, 8, 72);
		for (int i = 0; i < m_PokemonCount - 1; i++)
		{
			if(i == m_PokemonSelect -1)
				focusImg2->AniRender(_hdc, 1, 352, (96 * i) + 36);
			else
		 		focusImg2->AniRender(_hdc, 0, 352, (96 * i) + 36);
		}
		focusImg3->AniRender(_hdc, 0, 736, 528);
	}break;
	
	case 2:
	{
		focusImg1->AniRender(_hdc, 0, 8, 72);
		for (int i = 0; i < m_PokemonCount - 1; i++)
		{
			if (i == m_PokemonSelect - 1)
				focusImg2->AniRender(_hdc, 1, 352, (96 * i) + 36);
			else
				focusImg2->AniRender(_hdc, 0, 352, (96 * i) + 36);
		}
		focusImg3->AniRender(_hdc, 0, 736, 528);
	}break;
	
	case 3:
	{
		focusImg1->AniRender(_hdc, 0, 8, 72);
		for (int i = 0; i < m_PokemonCount - 1; i++)
		{
			if (i == m_PokemonSelect - 1)
				focusImg2->AniRender(_hdc, 1, 352, (96 * i) + 36);
			else
				focusImg2->AniRender(_hdc, 0, 352, (96 * i) + 36);
		}
		focusImg3->AniRender(_hdc, 0, 736, 528);
	}break;
	
	case 4:
	{
		focusImg1->AniRender(_hdc, 0, 8, 72);
		for (int i = 0; i < m_PokemonCount - 1; i++)
		{
			if (i == m_PokemonSelect - 1)
				focusImg2->AniRender(_hdc, 1, 352, (96 * i) + 36);
			else
				focusImg2->AniRender(_hdc, 0, 352, (96 * i) + 36);
		}
		focusImg3->AniRender(_hdc, 0, 736, 528);
	}break;
	
	case 5:
	{
		focusImg1->AniRender(_hdc, 0, 8, 72);
		for (int i = 0; i < m_PokemonCount - 1; i++)
		{
			if (i == m_PokemonSelect - 1)
				focusImg2->AniRender(_hdc, 1, 352, (96 * i) + 36);
			else
				focusImg2->AniRender(_hdc, 0, 352, (96 * i) + 36);
		}
		focusImg3->AniRender(_hdc, 0, 736, 528);
	}break;

	case 6:
	{
		focusImg1->AniRender(_hdc, 0, 8, 72);
		for (int i = 0; i < m_PokemonCount - 1; i++)
		{
			if (i == m_PokemonSelect - 1)
				focusImg2->AniRender(_hdc, 1, 352, (96 * i) + 36);
			else
				focusImg2->AniRender(_hdc, 0, 352, (96 * i) + 36);
		}
		focusImg3->AniRender(_hdc, 1, 736, 528);
	}break;
	}
	
	if (m_isClick == false)
	{
		m_Box.BoxCreate(_hdc, 0, 16, 22, 19);
		m_Txt.TextBox(_hdc, 42, (64 * 8) + 44, "포켓몬을 선택해 주십시오", 40);
		m_Txt.TextBox(_hdc, 820, (64 * 8) + 44, "취소", 40, WHITE);

		//	키입력
		if (KEYMGR.OnceKeyDown(VK_DOWN))
		{
			m_PokemonSelect++;
			if (m_PokemonSelect == m_PokemonCount)
				m_PokemonSelect = 6;
			else if (m_PokemonSelect == 7)
				m_PokemonSelect = 0;
		}
		if (KEYMGR.OnceKeyDown(VK_UP))
		{
			m_PokemonSelect--;
			if (m_PokemonSelect < 0)
				m_PokemonSelect = 6;
			else if (m_PokemonSelect > m_PokemonCount)
				m_PokemonSelect = m_PokemonCount - 1;
		}	
	}

	if (KEYMGR.OnceKeyDown('Z'))
	{
		m_isClick = !m_isClick;
		m_Box.m_Select = 0;
	}
	if (KEYMGR.OnceKeyDown(VK_SPACE))
	{
		m_isBattle = !m_isBattle;
	}

	//	선택
	if (m_isClick == true)
	{
		m_Box.BoxCreate(_hdc, 0, 16, 18, 19);
		m_Txt.TextBox(_hdc, 42, (64 * 8) + 44, "\"이름\" 어떻게할까", 40);
		//	전투중일때는 바꾼다, 상태보기, 그만두다 3가지
		if (m_isBattle == true)
		{
			m_Box.BoxCreate(_hdc, 19, 12, 29, 19, 3, true);
			m_Txt.TextBox(_hdc, 665, (64 * 6) + 30, "바꾼다", 40);
			m_Txt.TextBox(_hdc, 665, (64 * 7) + 30, "상태보기", 40);
			m_Txt.TextBox(_hdc, 665, (64 * 8) + 30, "그만두다", 40);
		}
		else
		{
			//	비전머신 기술 배움에 따라 크기 다름
			m_Box.BoxCreate(_hdc, 19, 10, 29, 19, 4, true);
			m_Txt.TextBox(_hdc, 665, (64 * 5) + 30, "상태보기", 40);
			m_Txt.TextBox(_hdc, 665, (64 * 6) + 30, "순서변경", 40);
			m_Txt.TextBox(_hdc, 665, (64 * 7) + 30, "지닌물건", 40);
			m_Txt.TextBox(_hdc, 665, (64 * 8) + 30, "그만두다", 40);
		}
	}
}


