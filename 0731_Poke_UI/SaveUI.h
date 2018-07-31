#pragma once
#pragma comment(lib, "msimg32.lib")

#include "Global.h"

class SaveUI
{
private:
	TextUI SaveText;
	BoxUI SaveBox;
	int	m_SaveMenu_Num = 0;
	int	m_SaveMenu_AnswerYes = 0;
	int	m_SaveMenu_AnswerNo = 0;
	int m_SaveMenu_SaveCount = 0;

public:
	SaveUI();
	~SaveUI();
	
	void Button_Down(int _key);
	void SetSave(HDC _hdc);
};

