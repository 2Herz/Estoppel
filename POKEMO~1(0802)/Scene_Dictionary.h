#pragma once
#include "Scene.h"
#include <vector>
using namespace std;

class Scene_Dictionary :
	public Scene
{
private:
	POINT m_ImgPos = { 0, 0 };
	SIZE m_CellSize = { 32, 32 };
	POINT m_StartPos = {};
	POINT m_EndPos = {};

	bool m_isSelect = false;
	bool m_isDraw	= false;
	bool m_isFocus	= false;
	int m_isKey	= 0;


	int m_MaxNum;
	int m_TopIndex = 0;
	int m_CursorIndex = 0;
	int m_ViewCount = 9;

	vector<char> textList;

	const char* Dictionary_Title = "���ϸ�   ����   ����";

	const char* m_category[23] =
	{
		{ "���ϸ�   ���" },{ "������ҿ�   ���   ���ϸ�" },{ "��ȣ  ��" },
	{ "�ʿ���   ���   ���ϸ�" },{ "����   ���   ���ϸ�" },{ "������   ���   ���ϸ�" },
	{ "�ٴٿ�   ���   ���ϸ�" },{ "������   ���   ���ϸ�" },{ "�꿡   ���   ���ϸ�" },
	{ "Ȳ�߿�   ���   ���ϸ�" },{ "���ÿ�   ���   ���ϸ�" },{ "�����   ���ϸ�" },{ "��   ��" },
	{ "������   ��" },{ "Ÿ��   ��" },{ "����   ��" },{ "ũ��   ��" },
	{ "��Ÿ" },{ "������   �ݴ´�" },{ "����" },{ "����" },{ "�߰���  ���ϸ�" },{ "����  ���ϸ�" }
	};

public:
	const char*	m_Select ="��";
	bool	m_isClick = false;
	int		m_WordSize = 40;
	int		m_posY = 206;

public:
	Scene_Dictionary();
	~Scene_Dictionary();

	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

	//	���� - ��ȣ ��
	void Render_Dictionary_List(HDC _hdc, int width, int _height);
	//	���� - �ʿ��� ��� ���ϸ�
	void Render_Dictionary_GrassLand(HDC _hdc, int _width, int _height);
	//	���� - ���� ��� ���ϸ�
	void Render_Dictionary_Forest(HDC _hdc, int _width, int _height);
	//	���� - ������ ��� ���ϸ�
	void Render_Dictionary_WaterFront(HDC _hdc, int _width, int _height);
	//	���� - �ٴٿ� ��� ���ϸ�
	void Render_Dictionary_Sea(HDC _hdc, int _width, int _height);
	//	���� - ������ ��� ���ϸ�
	void Render_Dictionary_Cave(HDC _hdc, int _width, int _height);
	//	���� - �꿡 ��� ���ϸ�
	void Render_Dictionary_Mountain(HDC _hdc, int _width, int _height);
	//	���� - Ȳ�߿� ��� ���ϸ�
	void Render_Dictionary_Wilderness(HDC _hdc, int _width, int _height);
	//	���� - ���ÿ� ��� ���ϸ�
	void Render_Dictionary_City(HDC _hdc, int _width, int _height);
	//	���� - ����� ���ϸ�
	void Render_Dictionary_Rare(HDC _hdc, int _width, int _height);
	//	���� - ����
	void Render_Dictionary_Sort(int _select);
	//	���� - ���� - ������ ��
	void Render_Dictionary_Sort_Order();
	//	���� - ���� - Ÿ�� ��
	void Render_Dictionary_Sort_Type(int _select, int _type);
	//	���� - ���� - ���� ��
	void Render_Dictionary_Sort_Weight(int _select, int _weight);
	//	���� - ���� - ũ�� ��
	void Render_Dictionary_Sort_Size(int _select, int _size);
	//	���� - ��Ÿ - ������ �ݴ´�.
	void Render_Dictionary_Etc_Close();
};