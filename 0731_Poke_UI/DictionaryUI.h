#pragma once
#include "Global.h"

class DictionaryUI
{
private:
	POINT m_ImgPos = { 0, 0 };
	SIZE m_CellSize = { 32, 32 };
	POINT m_StartPos = {};
	POINT m_EndPos = {};

	bool m_isSelect = false;
	bool m_isDraw = false;
	bool m_isFocus = false;

	int m_MaxNum;
	int m_TopIndex = 0;
	int m_CursorIndex = 0;
	int m_ViewCount = 9;

	vector<int> textList;

	const char* Dictionary_Title = "���ϸ�   ����   ����";

	const char* m_category[23] =
	{
		{"���ϸ�   ���"}, {"������ҿ�   ���   ���ϸ�"}, { "��ȣ  ��" }, 
		{ "�ʿ���   ���   ���ϸ�" }, { "����   ���   ���ϸ�" }, { "������   ���   ���ϸ�" },
		{ "�ٴٿ�   ���   ���ϸ�" }, { "������   ���   ���ϸ�" }, { "�꿡   ���   ���ϸ�" }, 
		{ "Ȳ�߿�   ���   ���ϸ�" }, { "���ÿ�   ���   ���ϸ�" }, { "�����   ���ϸ�" }, { "��   ��" }, 
		{ "������   ��" }, { "Ÿ��   ��" }, { "����   ��" }, { "ũ��   ��" }, 
		{ "��Ÿ" }, { "������   �ݴ´�" }, { "����" }, { "����" }, { "�߰���  ���ϸ�" }, { "����  ���ϸ�" }
	};

public:
	int		m_Select = 0;
	bool	m_isClick = false;
	int		m_WordSize = 40;
	int		m_posY = 206;

public:
	DictionaryUI();
	~DictionaryUI();

	void Init(HWND _hWnd);	//	�ʱ�ȭ

	//	���� ù ȭ��
	void Render_Main_Dictionary(HDC _hdc, int _width = WIN_WIDTH, int _height = WIN_HEIGHT, bool _select = false);
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
	//	���� - ���� - ������ ��
	void Render_Dictionary_Sort_Order();
	//	���� - ���� - Ÿ�� ��
	void Render_Dictionary_Sort_Type(int _select, int _type);
	//	���� - ���� - ���� ��
	void Render_Dictionary_Sort_Weight(int _select, int _weight);
	//	���� - ���� - ũ�� ��
	void Render_Dictionary_Sort_Size(int _select, int _size);
};