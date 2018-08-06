#pragma once
#include "Scene.h"

enum PokeType
{
	TYPE_NORMAL = 0,
	TYPE_FIGHT,
	TYPE_FLYING,
	TYPE_POISON,
	TYPE_GROUND,
	TYPE_ROCK,
	TYPE_BUG,
	TYPE_GHOST,
	TYPE_STEEL,
	TYPE_DARK,
	TYPE_FIRE,
	TYPE_WATER,
	TYPE_GRASS,
	TYPE_ELECTR,
	TYPE_PSYCHC,
	TYPE_ICE,
	TYPE_DRAGON,
	TYPE_RANDOM
};

class Scene_Info :
	public Scene
{
private:
	BoxUI	m_Box;
	TextUI	m_Txt;
	
	int		m_Ani = 0;
	float	m_time = 0;
	int		m_InfoPage = 0;
	int		m_NowPokemon = 0;

	//	���� ���ɸ� ������ŭ�� �迭����
	//	���ϸ� ����
	int			m_Lv[4] = {10, 20, 30, 40};			//	���ϸ�Lv
	int			m_DicNumber[4] = {1, 5, 7, 9};	//	������ȣ
	LPCSTR		m_Name[4] = {"�̰�", "�׽�Ʈ", "����", "�Դϴ�"};			//	���ϸ��̸�
	PokeType	m_Type[4] = { TYPE_DARK, TYPE_BUG, TYPE_STEEL, TYPE_FIRE};			//	Ÿ��
	LPCSTR		m_Father = "������";		//	Ʈ���̳��̸�
	int			m_Num = 34176;			//	Ʈ���̳�Number
	int			m_Poket[4] = {1, 1, 3, 0};		//	���ϰ� �ִ� ����

	//	���ϸ� �ɷ�
	int		m_HpNow[4] = {100, 111, 222, 150};		//	���� ü��
	int		m_HpAll[4] = {200, 220, 202, 180};		//	��ü ü��
	int		m_Atk[4] = {204, 99, 171, 124};			//	���ݷ�
	int		m_Def[4] = {10, 20, 30, 40};			//	����
	int		m_sAtk[4] = {40, 30, 20, 10};			//	Ư�� ���ݷ�
	int		m_sDef[4] = {100, 200, 300, 400};			//	Ư�� ����
	int		m_Speed[4] = {400, 300, 200, 100};		//	��ø��
	int		m_ExpNow[4] = {557946, 230000, 5000, 200};		//	���� ����ġ
	int		m_ExpAll[4] = {566666, 300000, 6000, 12300};		//	��ü ����ġ
	LPCSTR	m_Special[4] = {"������", "����", "����", "�𷡼���"};		//	Ư��
	
	//	�ο� ���
	PokeType	m_AtkType1[4] = { TYPE_WATER, TYPE_FIGHT, TYPE_GHOST, TYPE_GRASS };			//	Ÿ��
	LPCSTR		m_AtkList1[4] = {"��", "��", "��", "��"};		//	��� ���
	int			m_PpNowList1[4] = { 21, 12, 13, 10 };
	int			m_PpAllList1[4] = { 25, 15, 15, 30 };

	PokeType	m_AtkType2[4] = { TYPE_ROCK, TYPE_BUG, TYPE_GROUND, TYPE_STEEL };			//	Ÿ��
	LPCSTR		m_AtkList2[4] = { "��", "��", "��", "��" };		//	��� ���
	int			m_PpNowList2[4] = { 0, 15, 3, 2 };
	int			m_PpAllList2[4] = { 25, 15, 15, 20 };

	PokeType	m_AtkType3[4] = { TYPE_NORMAL, TYPE_FLYING, TYPE_POISON, TYPE_ICE };			//	Ÿ��
	LPCSTR		m_AtkList3[4] = { "��", "��", "ī", "Ÿ" };		//	��� ���
	int			m_PpNowList3[4] = { 5, 15, 7, 14 };
	int			m_PpAllList3[4] = { 35, 35, 15, 30 };

	PokeType	m_AtkType4[4] = { TYPE_DRAGON, TYPE_PSYCHC, TYPE_ELECTR, TYPE_RANDOM };			//	Ÿ��
	LPCSTR		m_AtkList4[4] = { "��", "��", "�׽�Ʈ", "�Դϴ�" };//	��� ���
	int			m_PpNowList4[4] = { 15, 3, 1, 11 };
	int			m_PpAllList4[4] = { 20, 15, 5, 20 };


public:
	Scene_Info();
	~Scene_Info();

	void	Init(HWND _hWnd);
	void	Update(float _elapseTime);
	void	Render(HDC _hdc);
	bool	WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
};

