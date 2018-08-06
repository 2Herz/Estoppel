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

	//	지닌 포케몬 개수만큼의 배열변수
	//	포켓몬 정보
	int			m_Lv[4] = {10, 20, 30, 40};			//	포켓몬Lv
	int			m_DicNumber[4] = {1, 5, 7, 9};	//	도감번호
	LPCSTR		m_Name[4] = {"이건", "테스트", "변수", "입니다"};			//	포켓몬이름
	PokeType	m_Type[4] = { TYPE_DARK, TYPE_BUG, TYPE_STEEL, TYPE_FIRE};			//	타입
	LPCSTR		m_Father = "히히히";		//	트레이너이름
	int			m_Num = 34176;			//	트레이너Number
	int			m_Poket[4] = {1, 1, 3, 0};		//	지니고 있는 물건

	//	포켓몬 능력
	int		m_HpNow[4] = {100, 111, 222, 150};		//	현재 체력
	int		m_HpAll[4] = {200, 220, 202, 180};		//	전체 체력
	int		m_Atk[4] = {204, 99, 171, 124};			//	공격력
	int		m_Def[4] = {10, 20, 30, 40};			//	방어력
	int		m_sAtk[4] = {40, 30, 20, 10};			//	특수 공격력
	int		m_sDef[4] = {100, 200, 300, 400};			//	특수 방어력
	int		m_Speed[4] = {400, 300, 200, 100};		//	민첩성
	int		m_ExpNow[4] = {557946, 230000, 5000, 200};		//	현재 경험치
	int		m_ExpAll[4] = {566666, 300000, 6000, 12300};		//	전체 경험치
	LPCSTR	m_Special[4] = {"독가시", "부유", "위협", "모래숨기"};		//	특성
	
	//	싸울 기술
	PokeType	m_AtkType1[4] = { TYPE_WATER, TYPE_FIGHT, TYPE_GHOST, TYPE_GRASS };			//	타입
	LPCSTR		m_AtkList1[4] = {"가", "나", "다", "라"};		//	기술 목록
	int			m_PpNowList1[4] = { 21, 12, 13, 10 };
	int			m_PpAllList1[4] = { 25, 15, 15, 30 };

	PokeType	m_AtkType2[4] = { TYPE_ROCK, TYPE_BUG, TYPE_GROUND, TYPE_STEEL };			//	타입
	LPCSTR		m_AtkList2[4] = { "마", "바", "사", "아" };		//	기술 목록
	int			m_PpNowList2[4] = { 0, 15, 3, 2 };
	int			m_PpAllList2[4] = { 25, 15, 15, 20 };

	PokeType	m_AtkType3[4] = { TYPE_NORMAL, TYPE_FLYING, TYPE_POISON, TYPE_ICE };			//	타입
	LPCSTR		m_AtkList3[4] = { "자", "차", "카", "타" };		//	기술 목록
	int			m_PpNowList3[4] = { 5, 15, 7, 14 };
	int			m_PpAllList3[4] = { 35, 35, 15, 30 };

	PokeType	m_AtkType4[4] = { TYPE_DRAGON, TYPE_PSYCHC, TYPE_ELECTR, TYPE_RANDOM };			//	타입
	LPCSTR		m_AtkList4[4] = { "파", "하", "테스트", "입니다" };//	기술 목록
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

