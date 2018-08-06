#pragma once
#include "Scene.h"
using namespace std;

enum DICTIONARY_TYPE
{
	NUMBER,
	CLOSE
};

class Scene_Dictionary :
	public Scene
{
private:
	POINT m_ImgPos = { 0, 0 };
	SIZE m_CellSize = { 32, 32 };

	int		m_DicNum = 0;
	int		m_CursorIndex = 0;
	int		m_select = 0;
	int		m_WordSize = 40;
	int		m_isClick = 0;
	int		m_size = 0;

	bool	isPopup = false;
	bool	m_isSelect = false;
	bool	m_isDraw = false;
	bool	m_isFocus = false;

	LPCSTR Dictionary_Title = "포켓몬   도감   목차";

	LPCSTR m_category[9] =
	{
		{ "포켓몬   목록"	},
		{ "번호  순"		},
		{ "기타"			},
		{ "도감을   닫는다"	},
		{ "선택"			},
		{ "결정"			},
		{ "발견한  포켓몬"	},
		{ "잡은  포켓몬"	}
	};

	LPCSTR m_Numbering[19] = { 
		{ "No001   - - - - - "	},
		{ "No002   - - - - - "	},
		{ "No003   - - - - - "	},
		{ "No004   - - - - - "	},
		{ "No005   - - - - - "	},
		{ "No006   - - - - - "	},
		{ "No007   - - - - - "	},
		{ "No008   - - - - - "	},
		{ "No009   - - - - - "	} ,
		{ "No010   - - - - - "	} ,
		{ "No011   - - - - - "	} ,
		{ "No012   - - - - - "	},
		{ "No013   - - - - - "	} ,
		{ "No014   - - - - - "	} ,
		{ "No015   - - - - - "	} ,
		{ "No016   - - - - - "	} ,
		{ "No018   - - - - - "	} ,
		{ "No018   - - - - - "	} ,
		{ "No019   - - - - - "	} 
	};

public:
	Scene_Dictionary();
	~Scene_Dictionary();

	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

	//	커서만들기
	void Create_Arrow(HDC _hdc, int posX, int posY, int _MaxNum, bool _select);

	//	도감 - 번호 순
	void Render_Dictionary_List(HDC _hdc, int width, int _height);

	//	도감 - 기타 - 도감을 닫는다.
	void Render_Dictionary_Close()
	{
		SCENE_MGR.SetScene(SCENE_MENU);
	}
};