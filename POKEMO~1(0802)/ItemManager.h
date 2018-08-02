#pragma once
#include "stdafx.h"

/*
  - 아이템 정리 -
  중요한 물건 : 낚싯대, 자전거, 지도 등....
  도구 : 상처약, 이상한사탕, 진화돌, 상태회복약 등...
  포켓볼 : 포켓볼, 슈퍼볼, 하이퍼볼, 마스터볼 .....
*/

enum ItemType
{
	SPECIAL,
	TOOL,
	BALL,
};

enum ItemFunction
{
	POTION,
	RECOVERY,
	REVIVE,
	EVOLVE,	
	LEVUP,
};

enum SpecialItem
{
	DICTIONARY,
	MAP,
	SHOES,
	BIKE,
	ROD,
};

struct Item 
{
	short m_number;		//아이템 번호
	char m_name[20];	//아이템 이름
	short m_type;		//아이템 타입
	short m_function;	//기능 
	short m_value;		//아이템 수치
	short m_price;		//아이템 가격
};

class ItemManager
{
private:
	std::vector<Item> m_itemList;
	

private:
	ItemManager();
	~ItemManager();
	void SaveItem();
	void LoadItem();
	
public:
	static ItemManager& GetInstance()
	{
		static ItemManager Instance;
		return Instance;
	}

	void Init();
	void UseItem(short _itemNumber, Pokemon* _pokemon);
};

#define ITEM_MANAGER ItemManager::GetInstance()