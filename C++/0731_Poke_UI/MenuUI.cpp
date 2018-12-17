#include "MenuUI.h"

MenuUI::MenuUI()
{
}

MenuUI::~MenuUI()
{
}

//	�ʱ�ȭ	( �̹��� �ҷ����ų� ������ �ҷ����� �뵵)
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
	//	�޴�
	m_Box.BoxCreate(_hdc, 21, 0, 29, 14, 7, true);
	m_Txt.TextBox(_hdc, 723, (64 * 0) + 30, "����", 40);
	m_Txt.TextBox(_hdc, 723, (64 * 1) + 30, "���ϸ�", 40);
	m_Txt.TextBox(_hdc, 723, (64 * 2) + 30, "����", 40);
	m_Txt.TextBox(_hdc, 723, (64 * 3) + 30, "Ʈ���̳�", 40);
	m_Txt.TextBox(_hdc, 723, (64 * 4) + 30, "����Ʈ", 40);
	m_Txt.TextBox(_hdc, 723, (64 * 5) + 30, "����", 40);
	m_Txt.TextBox(_hdc, 723, (64 * 6) + 30, "�ݱ�", 40);

	//	�޴� ���� �ڽ�
	HDC _BGDC = IMG_MGR->GetImg("Dialog_00")->GetImgDC();
	BitBlt(_hdc, 0, 15 * 32, WIN_WIDTH, WIN_HEIGHT, _BGDC, 0, 0, SRCCOPY);

	switch (m_Box.m_Select)
	{
	case 0:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "������ ��ϵ� ���ϸ���", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "�� ������ Ȯ���մϴ�.", 44, WHITE);
	} break;
	case 1:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "���� �ִ� ���ϸ��� ���¸�", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "Ȯ���ϰ� �����մϴ�.", 44, WHITE);
	} break;

	case 2:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "������ Ȯ���ϰ�", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "����� �� �ֽ��ϴ�.", 44, WHITE);
	} break;

	case 3:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "����� Ʈ���̳� ī�带", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "Ȯ���մϴ�.", 44, WHITE);
	} break;

	case 4:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "���ݱ����� ������", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "����Ʈ�� ����մϴ�.", 44, WHITE);
	} break;

	case 5:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "����, �ӵ����� ������", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "�����մϴ�.", 44, WHITE);
	} break;

	case 6:
	{
		m_Txt.TextBox(_hdc, 1 * 32, 16 * 32, "�� �޴��� �ݰ�", 44, WHITE);
		m_Txt.TextBox(_hdc, 1 * 32, 18 * 32, "������ ��� �մϴ�.", 44, WHITE);
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
