#pragma once
#include "Scene.h"
#include "FPOINT.h"
#include <vector>
#include <sstream>
using namespace std;

enum SCV_STATE
{
	STATE_IDLE,
	STATE_MOVE,
	STATE_MILLING,
	STATE_RETURN
};

typedef stringstream Text;

class Scene_Intro : public Scene
{
private:
	//	Ŀ�Ǵ������� ��ǥ
	FPOINT m_centerPos;
	//	�̳׶��� ��ǥ
	FPOINT m_mineralPos;

	//	�ϲ��� ��ǥ
	FPOINT m_scvPos;

	//	���콺�̵� ��ǥ
	POINT m_mousePos;
	//	�Ÿ�
	FPOINT m_moveDist;
	//	�̵��ӵ�
	float m_moveSpeed;

	//	�ϲ��� ����
	SCV_STATE m_scvState;
	//	���°� �ٲ�� �ð�
	float m_changeTime;

	//	���ͽ�����ǥ
	FPOINT m_returnStartPos;
	//	������ǥ
	FPOINT m_returnPos;
	//	����
	float m_rate;

	//	�̳׶�����
	int m_totlaMineral;

	//	ä���� �̳׶�
	int m_millingMineral;

	bool isClicked = false;

	FPOINT m_ClickPos;

public:
	Scene_Intro();
	~Scene_Intro();

	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
};

