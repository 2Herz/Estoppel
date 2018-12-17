#include "Scene_Intro.h"

#include "SceneMgr.h"

Scene_Intro::Scene_Intro()
{
	m_centerPos.x = 150;
	m_centerPos.y = 150;

	m_mineralPos.x = 650;
	m_mineralPos.y = 150;

	m_scvPos.x = m_centerPos.x + 10;
	m_scvPos.y = m_centerPos.y + 40;

	m_moveDist = 10;

	m_scvState = SCV_STATE::STATE_IDLE;
	m_changeTime = 2;

	m_returnPos = m_scvPos;

	m_totlaMineral = 3000;
	m_millingMineral = 0;

	m_ClickPos.x = m_mousePos.x;
	m_ClickPos.y = m_mousePos.y;
}

Scene_Intro::~Scene_Intro()
{

}

void Scene_Intro::Update(float _elapseTime)
{
	switch (m_scvState)
	{
		case SCV_STATE::STATE_IDLE:
		{
			m_changeTime = _elapseTime;
		}break;

		case SCV_STATE::STATE_MOVE:
		{
			if (m_scvPos.x > m_ClickPos.x )
			{
				m_scvPos.x -= m_ClickPos.x / m_moveSpeed * _elapseTime;
				m_scvPos.y -= m_ClickPos.y / m_moveSpeed * _elapseTime;
			}

			if ((m_mineralPos - m_scvPos).Dist() < 100)
			{
				m_scvState = SCV_STATE::STATE_MILLING;
			}
		}break;

		case SCV_STATE::STATE_MILLING:
		{
			m_moveDist = (m_mineralPos - m_scvPos).Normal();
			m_scvPos = m_scvPos + (m_moveDist * _elapseTime * m_moveSpeed);

			if (m_millingMineral > 50)
			{
				m_scvState = SCV_STATE::STATE_RETURN;
				m_returnStartPos = m_scvPos;
				m_rate = 0;
				m_totlaMineral -= 50;
				m_millingMineral += 50;
				m_changeTime = float(rand() % 3);
			}
		}break;

		case SCV_STATE::STATE_RETURN:
		{
			m_scvPos = m_returnPos * m_rate + m_returnStartPos * (1 - m_rate);
			m_rate += _elapseTime;

			if (m_rate > 1)
			{
				m_scvState = SCV_STATE::STATE_MOVE;
				m_changeTime = float(rand() % 2);
			}
		}break;
	}
}

void Scene_Intro::Render(HDC _hdc)
{
	Text commander;
	Text mineral;
	Text scv;

	//	커맨더 센터
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = SelectBrush(_hdc, brush);

	RECT commanderCenter = m_centerPos.GetRect(200);
	Rectangle(_hdc, commanderCenter.left, commanderCenter.top, commanderCenter.right, commanderCenter.bottom);
	commander << "Commander Center";
	TextOut(_hdc, (commanderCenter.right - commanderCenter.left) / 2 - 10, (commanderCenter.top + m_centerPos.y) / 2 + 30, commander.str().c_str(), commander.str().length());

	//	미네랄
	brush = CreateSolidBrush(RGB(0, 0, 255));
	oldBrush = SelectBrush(_hdc, brush);
	RECT Mineral = m_mineralPos.GetRect(80);
	Rectangle(_hdc, Mineral.left, Mineral.top, Mineral.right + 50, Mineral.bottom);
	mineral << "Mineral : " << m_totlaMineral;
	TextOut(_hdc, (Mineral.right - Mineral.left) / 2 + 30 + 560, (Mineral.top + m_mineralPos.y) / 2 + 13, mineral.str().c_str(), mineral.str().length());

	//	SCV
	brush = CreateSolidBrush(RGB(255, 0, 255));
	oldBrush = SelectBrush(_hdc, brush);
	RECT SCV = m_scvPos.GetRect(80);
	Ellipse(_hdc, SCV.left, SCV.top + 10, SCV.right, SCV.bottom - 10);
}

bool Scene_Intro::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_MOUSEMOVE:
	{
		if (isClicked == true)
		{
			float checkPosX = (float)GET_X_LPARAM(_lParam);
			float checkPosY = (float)GET_Y_LPARAM(_lParam);
		}
	}
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_KEYDOWN:
	{
		switch (_wParam)
		{
		case VK_ESCAPE: return true;	break;
		}
	}break;

	}

	return false;
}