// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#undef UNICODE
// Windows 헤더 파일:
#include <Windows.h>
#include <windowsx.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "TemplateSingletonA.h"
#include "NPC.h"
#include "ImgMgr.h"
#include "TimerManager.h"
#include "DataManager.h"
#include "NPCManager.h"
#include "MapManager.h"
#include "BattleManager.h"
#include "SkillManager.h"
#include "ItemManager.h"
#include "Pokedex.h"
#include "PlayerManager.h"
#include "BagManager.h"
#include "KeyManager.h"

#include "SceneMgr.h"

#define BLACK		RGB(0, 0, 0)
#define WHITE		RGB(255, 255, 255)
#define ORANGE		RGB(255, 69, 0)
#define RED			RGB(255, 0, 0)
#define LORANGE		RGB(224, 168, 104)
#define GRAY		RGB(96, 96, 96)
#define LGRAY		RGB(208, 208, 208)
#define BLUE		RGB(49, 81, 201)
#define LBLUE		RGB(150, 181, 236)

#define MAP_TILE_SIZE 64
#define HERO_WIDTH 80
#define HERO_HEIGHT 88
#define WIN_WIDTH 960
#define WIN_HEIGHT 640
#define DEFAULT_FPS 60
#define NPC_TOTAL_NUMBER 3
#define POKEMON_TOTAL_NUMBER 151
#define SKILL_TOTAL_NUMBER 165
#define ITEM_TOTAL_NUMBER 3
#define TRANS_COLOR RGB(255,0,255)

//방향
enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum STEP
{
	NO_FEET,
	R_FEET,
	L_FEET,
};

enum SEX
{
	MALE,
	FEMALE,
};

enum CONDITION
{
	NO_CONDITION,
	POISONED,
	SLEEP,
	PARELIZED,
	ICED,
	BURN,
};