#pragma once

#undef UNICODE
#include <Windows.h>
#include <windowsx.h>
#include <vector>
#include <string>

#include "KeyManager.h"
#include "ImgMgr.h"
#include "TimeMgr.h"

#include "TextUI.h"
#include "BoxUI.h"
using namespace std;

//#include "MenuUI.h"
//
//#include "DictionaryUI.h"
//#include "PokemonUI.h"
//#include "SaveUI.h"
//#include "SettingMenuUI.h"


#define	WIN_WIDTH	960
#define WIN_HEIGHT	640
#define WIN_NAME	"Pokemon_FireRed"

#define BLACK		RGB(0, 0, 0)
#define WHITE		RGB(255, 255, 255)
#define ORANGE		RGB(255, 69, 0)
#define RED			RGB(255, 0, 0)
#define LORANGE		RGB(224, 168, 104)
#define GRAY		RGB(96, 96, 96)
#define LGRAY		RGB(208, 208, 208)
#define BLUE		RGB(49, 81, 201)
#define LBLUE		RGB(150, 181, 236)

//	메뉴 선택 목록
enum MENU_SELECT
{
	MS_DICTIONARY = 1,
	MS_POKEMON,
	MS_BAG,
	MS_TRAINER,
	MS_REPORT,
	MS_OPTION,
	MS_CLOSE
};

//	메뉴 - 도감 선택 목록
enum DICTIONARY_SELECT
{
	DS_POKEMON_LIST = 1,
	DS_LIST,
	DS_GRASSLAND,
	DS_FOREST,
	DS_WATERFRONT,
	DS_SEA,
	DS_CAVE,
	DS_MOUNTAIN,
	DS_WILDERNESS,
	DS_CITY,
	DS_RARE,
	DS_SORT,
	DS_SORT_ORDER,
	DS_SORT_TYPE,
	DS_SORT_WEIGHT,
	DS_SORT_SIZE,
	DS_ETC
};

//	도감 - 정렬
enum DICTIONARY_SORT_SELECT
{
	DSS_LIST = 1,
	DSS_TYPE,
	DSS_WEIGHT,
	DSS_SIZE
};