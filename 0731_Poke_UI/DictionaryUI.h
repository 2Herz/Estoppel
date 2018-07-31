#pragma once
#include "Global.h"

class DictionaryUI
{
private:
	int m_imgWidth = WIN_WIDTH;
	int m_imgHeight = WIN_HEIGHT;
	POINT m_ImgPos = { 0, 0 };
	SIZE m_CellSize = { 32, 32 };
	const char* m_str[15] = { { "번호 순" }, { "초원에  사는  포켓몬" }, { "숲에  사는  포켓몬" }, { "물가에  사는  포켓몬" }, { "바다에  사는  포켓몬" }, { "동굴에  사는  포켓몬" }, { "산에  사는  포켓몬" }, { "황야에  사는  포켓몬" }, { "도시에  사는  포켓몬" }, { "희귀한  포켓몬" }, { "가나다  순" }, { "타입   순" }, { "무게   순" }, { "크기   순" }, { "도감을   닫는다" }};

public:
	int m_Select = 0;
	bool m_isSelect = false;
	bool m_isClick = false;


public:
	DictionaryUI();
	~DictionaryUI();

	void Init(HWND _hWnd);	//	초기화

	//	도감 첫 화면
	void Render_Main_Dictionary(HDC _hdc, int _width = WIN_WIDTH, int _height = WIN_HEIGHT);
	//	도감 - 번호 순
	void Render_Dictionary_List(HDC _hdc, int width, int _height);
	//	도감 - 초원에 사는 포켓몬
	void Render_Dictionary_GrassLand(HDC _hdc, int _width, int _height);
	//	도감 - 숲에 사는 포켓몬
	void Render_Dictionary_Forest(HDC _hdc, int _width, int _height);
	//	도감 - 물가에 사는 포켓몬
	void Render_Dictionary_WaterFront(HDC _hdc, int _width, int _height);
	//	도감 - 바다에 사는 포켓몬
	void Render_Dictionary_Sea(HDC _hdc, int _width, int _height);
	//	도감 - 동굴에 사는 포켓몬
	void Render_Dictionary_Cave(HDC _hdc, int _width, int _height);
	//	도감 - 산에 사는 포켓몬
	void Render_Dictionary_Mountain(HDC _hdc, int _width, int _height);
	//	도감 - 황야에 사는 포켓몬
	void Render_Dictionary_Wilderness(HDC _hdc, int _width, int _height);
	//	도감 - 도시에 사는 포켓몬
	void Render_Dictionary_City(HDC _hdc, int _width, int _height);
	//	도감 - 희귀한 포켓몬
	void Render_Dictionary_Rare(HDC _hdc, int _width, int _height);
	//	도감 - 정렬 - 가나다 순
	void Render_Dictionary_Sort_Order();
	//	도감 - 정렬 - 타입 순
	void Render_Dictionary_Sort_Type(int _select, int _type);
	//	도감 - 정렬 - 무게 순
	void Render_Dictionary_Sort_Weight(int _select, int _weight);
	//	도감 - 정렬 - 크기 순
	void Render_Dictionary_Sort_Size(int _select, int _size);
};