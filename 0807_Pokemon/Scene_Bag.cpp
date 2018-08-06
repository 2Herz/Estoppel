#include "stdafx.h"
#include "Scene_Bag.h"
#include "SceneMgr.h"


Scene_Bag::Scene_Bag()
{
	m_BGDC = IMG_MGR->GetImg("Bag_00")->GetImgDC();
}


Scene_Bag::~Scene_Bag()
{
}

void Scene_Bag::Init(HWND _hWnd)
{
}

void Scene_Bag::Update(float _elapseTime)
{
	m_time += _elapseTime;

	if (0.2f <= m_time)
	{
		m_time -= 0.2f;
		m_Ani++;

		if (m_Ani > 5)
		{
			m_Ani = 0;
		}
	}
}

void Scene_Bag::Render(HDC _hdc)
{
	BitBlt(_hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, m_BGDC, 0, 0, SRCCOPY);
	auto	bagImg		= IMG_MGR->GetImg("Bag_01");
	auto	arrowUp		= IMG_MGR->GetImg("Arrow_Up");
	auto	arrowDown	= IMG_MGR->GetImg("Arrow_Down");
	auto	arrowLeft	= IMG_MGR->GetImg("Arrow_Left");
	auto	arrowRight	= IMG_MGR->GetImg("Arrow_Right");
	auto	itemImg		= IMG_MGR->GetImg("Item");
	auto	cursorImg	= IMG_MGR->GetImg("Select");
			
	switch (m_BagNum)
	{
	case ItemType::TOOL:		//	도구
	{
		bagImg->AniRender(_hdc, 0, 46, 140);
		m_Txt.TextBox(_hdc, 120, 40, "도구", 35, WHITE, GRAY);

		//	0 ~ 19
		itemImg->AniRender(_hdc, 0, 28, 492);

		std::stringstream	buf;

		cursorImg->Render(_hdc, 360, 42 + (m_cursorIndex * 66));
		
		for (int i = 0; i < MAX_ITEM_VIEW; i++)
		{
			if (i < BAG_MANAGER.GetItemList().size())
			{
				buf.str("");
				int index = BAG_MANAGER.GetItemList()[i].m_itemNumber;
				buf << ITEM_MANAGER.GetItem(index).m_name;
				m_Txt.TextBox(_hdc, 392, 40 + (64 * i), buf.str().c_str(), 50);
			}
			else if (i == BAG_MANAGER.GetItemList().size())
			{
				buf.str("");
				buf << "닫기";
				m_Txt.TextBox(_hdc, 392, 40 + (64 * i), buf.str().c_str(), 50);
			}
		}	

		buf.str("");
		buf << "세살이 솔솔 마데카솔";
		m_Txt.TextBox(_hdc, 176, 460, buf.str().c_str(), 50, WHITE);

	}break;

	case ItemType::SPECIAL:		//	중요한 물건
	{
		bagImg->AniRender(_hdc, 1, 46, 140);
		m_Txt.TextBox(_hdc, 80, 40, "중요한 물건", 35, WHITE, GRAY);

		//	25 ~ 27
		itemImg->AniRender(_hdc, 25, 28, 492);
	}break;

	case ItemType::BALL:		//	볼
	{
		bagImg->AniRender(_hdc, 2, 46, 140);
		m_Txt.TextBox(_hdc, 140, 40, "볼", 35, WHITE, GRAY);

		//	20 ~ 24
		itemImg->AniRender(_hdc, 20, 28, 492);
	}break;
	}	
	if(m_BagNum != 0)
		arrowLeft->AniRender(_hdc, m_Ani, 0, 260);
	if(m_BagNum != 2)
		arrowRight->AniRender(_hdc, m_Ani, 270, 260);

	if (m_itemIndex >= 6)
	{
		arrowUp->AniRender(_hdc, m_Ani, 610, 0);
	}
	if (m_itemIndex <= BAG_MANAGER.GetItemList().size())
	{
		arrowDown->AniRender(_hdc, m_Ani, 610, 400);
	}
	

	if (isPopup)
	{
		m_Box.BoxCreate(_hdc, 19, 12, 29, 19, 3, true);
	}
}

bool Scene_Bag::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case VK_LEFT:
		{
			m_BagNum--;
			if (m_BagNum < 0)
				m_BagNum = 0;
		}break;

		case VK_RIGHT:
		{
			m_BagNum++;
			if (m_BagNum > 2)
				m_BagNum = 2;
		}break;
		case VK_UP:
		{
			if (m_cursorIndex > 0)
			{
				if (m_itemIndex > 0)
				{
					m_cursorIndex--;
					m_itemIndex--;
				}
			}
		}break;
		case VK_DOWN:
		{
			
			if (m_cursorIndex < 5)
			{
				if (m_itemIndex < BAG_MANAGER.GetItemList().size())
				{
					m_cursorIndex++;
					m_itemIndex++;
				}
			}
		}break;
		case 'Z':
		{
			if (isPopup)
			{
				isPopup = false;
			}
			else
			{
				isPopup = true;
			}
		}break;
		case 'x':
		case 'X': {	SCENE_MGR.SetScene(SCENE_MENU); }break;

		case VK_ESCAPE: return true;	break;
		}
	}break;

	}
	return false;
}