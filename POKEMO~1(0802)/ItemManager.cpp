#include "stdafx.h"
#include "ItemManager.h"

ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
	m_itemList.clear();
}

void ItemManager::Init()
{
	SaveItem();
	LoadItem();
}

void ItemManager::SaveItem()
{
	Item* item = new Item[ITEM_TOTAL_NUMBER];
	short i = 0;

	/*
	{ number, name, type, function, value, price }
	번호 : 아이템 고유번호
	이름 : 아이템 이름
	타입 : 어떤 종류의 아이템인지 (중요한 0 , 도구 1 , 포켓볼 2 )
	기능 : 아이템 기능 ( 치료약 0, 상태약 1, 부활 2, 진화돌 3, 렙업돌 4) //중요한 물건일시, 어떤 아이템인지 저장
	수치 : 아이템 능력 수치 (예 : 상처약은 수치가 50이면 체력회복을 50시켜준다.)
	가격 : 아이템 가격
	*/

	item[i++] = { i, "상처약", TOOL, HEAL, 30, 300 };
	item[i++] = { i, "좋은상처약", TOOL, HEAL, 80, 500 };
	item[i++] = { i, "포켓몬볼", BALL, 0, 30, 1000 };

	std::ofstream fout("DB/Item.db");

	if (fout.fail() == false)
	{
		fout.write((const char *)item, sizeof(Item) * ITEM_TOTAL_NUMBER);
		fout.close();
	}

	delete[] item;
}

void ItemManager::LoadItem()
{
	Item *data = new Item[ITEM_TOTAL_NUMBER];
	std::ifstream fout;

	//NPC.db 파일 열기
	fout.open("DB/Item.db");

	if (fout.fail() == false)
	{
		fout.read((char*)data, sizeof(Item) * ITEM_TOTAL_NUMBER);
		fout.close();

		for (int i = 0; i < ITEM_TOTAL_NUMBER; i++)
		{
			Item temp = data[i];
			m_itemList.push_back(temp);
		}
	}

	delete[] data;
}

//포켓몬에게 아이템을 사용하면 효과를 적용시킴
void ItemManager::UseItem(short _itemNumber, Pokemon * _pokemon)
{
	switch (m_itemList[_itemNumber].m_type)
	{
	case SPECIAL:
	{
		
	}break;
	case TOOL:
	{
		
	}break;
	case BALL:
	{
		
	}break;
	}
}
