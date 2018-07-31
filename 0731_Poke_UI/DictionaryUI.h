#pragma once
#include "Global.h"

class DictionaryUI
{
private:
	int m_imgWidth = WIN_WIDTH;
	int m_imgHeight = WIN_HEIGHT;
	POINT m_ImgPos = { 0, 0 };
	SIZE m_CellSize = { 32, 32 };
	const char* m_str[15] = { { "��ȣ ��" }, { "�ʿ���  ���  ���ϸ�" }, { "����  ���  ���ϸ�" }, { "������  ���  ���ϸ�" }, { "�ٴٿ�  ���  ���ϸ�" }, { "������  ���  ���ϸ�" }, { "�꿡  ���  ���ϸ�" }, { "Ȳ�߿�  ���  ���ϸ�" }, { "���ÿ�  ���  ���ϸ�" }, { "�����  ���ϸ�" }, { "������  ��" }, { "Ÿ��   ��" }, { "����   ��" }, { "ũ��   ��" }, { "������   �ݴ´�" }};

public:
	int m_Select = 0;
	bool m_isSelect = false;
	bool m_isClick = false;


public:
	DictionaryUI();
	~DictionaryUI();

	void Init(HWND _hWnd);	//	�ʱ�ȭ

	//	���� ù ȭ��
	void Render_Main_Dictionary(HDC _hdc, int _width = WIN_WIDTH, int _height = WIN_HEIGHT);
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