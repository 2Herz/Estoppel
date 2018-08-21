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
	//	커맨더센터의 좌표
	FPOINT m_centerPos;
	//	미네랄의 좌표
	FPOINT m_mineralPos;

	//	일꾼의 좌표
	FPOINT m_scvPos;

	//	마우스이동 좌표
	POINT m_mousePos;
	//	거리
	FPOINT m_moveDist;
	//	이동속도
	float m_moveSpeed;

	//	일꾼의 상태
	SCV_STATE m_scvState;
	//	상태가 바뀌는 시간
	float m_changeTime;

	//	복귀시작좌표
	FPOINT m_returnStartPos;
	//	복귀좌표
	FPOINT m_returnPos;
	//	비율
	float m_rate;

	//	미네랄총합
	int m_totlaMineral;

	//	채굴한 미네랄
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

