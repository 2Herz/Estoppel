#pragma once
#include "Scene.h"

class Scene_Dictionary :
	public Scene
{
private:
	int m_imgWidth = WIN_WIDTH;
	int m_imgHeight = WIN_HEIGHT;

public:
	int m_Select = 0;	//	도감 안에서 선택을 하게 하기위한 변수
	int m_Sort = 0;

public:
	Scene_Dictionary();
	~Scene_Dictionary();

	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

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
	//	도감 - 정렬
	void Render_Dictionary_Sort(int _select);
	//	도감 - 정렬 - 가나다 순
	void Render_Dictionary_Sort_Order();
	//	도감 - 정렬 - 타입 순
	void Render_Dictionary_Sort_Type(int _select, int _type);
	//	도감 - 정렬 - 무게 순
	void Render_Dictionary_Sort_Weight(int _select, int _weight);
	//	도감 - 정렬 - 크기 순
	void Render_Dictionary_Sort_Size(int _select, int _size);
	//	도감 - 기타 - 도감을 닫는다.
	void Render_Dictionary_Etc_Close();
};