#include "MenuUI.h"

MenuUI::MenuUI()
{
}

MenuUI::~MenuUI()
{
}

//	초기화	( 이미지 불러오거나 데이터 불러오는 용도)
void MenuUI::Init(HWND _hWnd)
{
	m_Dic.Init(_hWnd);
	m_PokemonUI.Init(_hWnd);
	m_Setting.Init(_hWnd);
	IMG_MGR->OpenImg("Image/SaveBox1.bmp");
	IMG_MGR->OpenImg("Image/SaveBox2.bmp");
	IMG_MGR->OpenImg("Image/SaveBox3.bmp");
}

void MenuUI::RenderMenu(HDC _hdc)
{
	//	메뉴
	m_Box.BoxCreate(_hdc, 21, 0, 29, 14, 7, true);
	m_Txt.TextBox(_hdc, 723, (64 * 0) + 30, "도감", 40);
	m_Txt.TextBox(_hdc, 723, (64 * 1) + 30, "포켓몬", 40);
	m_Txt.TextBox(_hdc, 723, (64 * 2) + 30, "가방", 40);
	m_Txt.TextBox(_hdc, 723, (64 * 3) + 30, "트레이너", 40);
	m_Txt.TextBox(_hdc, 723, (64 * 4) + 30, "리포트", 40);
	m_Txt.TextBox(_hdc, 723, (64 * 5) + 30, "설정", 40);
	m_Txt.TextBox(_hdc, 723, (64 * 6) + 30, "닫기", 40);

	//	메뉴 설명 박스
	HDC _BGDC = IMG_MGR->GetImg("Dialog_00")->GetImgDC();
	BitBlt(_hdc, 0, 15 * 32, WIN_WIDTH, WIN_HEIGHT, _BGDC, 0, 0, SRCCOPY);

	switch (m_Box.m_Select)
	{
	case 0:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "도감에 기록된 포켓몬의", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "상세 정보를 확인합니다.", 44, WHITE);
	} break;
	case 1:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "같이 있는 포켓몬의 상태를", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "확인하고 관리합니다.", 44, WHITE);
	} break;

	case 2:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "도구를 확인하고", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "사용할 수 있습니다.", 44, WHITE);
	} break;

	case 3:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "당신의 트레이너 카드를", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "확인합니다.", 44, WHITE);
	} break;

	case 4:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "지금까지의 모험을", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "리포트로 기록합니다.", 44, WHITE);
	} break;

	case 5:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "사운드, 속도등의 설정을", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "변경합니다.", 44, WHITE);
	} break;

	case 6:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "이 메뉴를 닫고", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "게임을 계속 합니다.", 44, WHITE);
	} break;
	}

	if (KEYMGR.OnceKeyDown('Z'))
	{
		m_Box.m_isClick = !m_Box.m_isClick;
	}

	if (m_Box.m_isClick == true)
	{
		switch (m_Box.m_Select)
		{
		case 0:
		{
			m_Dic.Render_Main_Dictionary(_hdc);
		}break;

		case 1:
		{
			m_PokemonUI.RenderPokemon(_hdc);
		}break;

		case 2:
		{

		}break;

		case 3:
		{

		}break;

		case 4:
		{
			m_Save.SetSave(_hdc);
		}break;

		case 5:
		{
			m_Setting.MenuDisplay(_hdc);
		}break;

		case 6:
		{

		}break;
		}
	}
}
