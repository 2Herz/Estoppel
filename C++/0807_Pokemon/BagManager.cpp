#include "stdafx.h"
#include "BagManager.h"


BagManager::BagManager()
{
}


BagManager::~BagManager()
{
}

void BagManager::SaveBag()
{
	ItemData* bag = new ItemData[5];
	std::ofstream fout("DB/Bag.db");
	
	bag[0] = {0, 30};
	bag[1] = {1, 20};
	bag[2] = {2, 10};
	bag[3] = {19, 5};
	bag[4] = {20, 15};

	if (fout.fail() == false)
	{
		fout.write((const char*)bag, sizeof(ItemData) * 5);
		fout.close();
	}

	delete[] bag;
}

void BagManager::LoadBag()
{
	ItemData* bag = new ItemData[5];
	std::ifstream fout;

	fout.open("DB/Bag.db");

	if (fout.fail() == false)
	{
		fout.read((char*)bag, sizeof(ItemData) * 5);
		fout.close();
	}

	for (int i = 0; i < 5; i++)
	{
		m_toolList.push_back(bag[i]);
	}

	delete[] bag;
}

void BagManager::Init()
{
	SaveBag();
	LoadBag();
}

std::vector<ItemData> BagManager::GetItemList()
{
	return m_toolList;
}

Item BagManager::GetSelectedItem()
{
	return m_selectedItem;
}

void BagManager::SetSelectedItem(int _index)
{
	m_selectedItem = ITEM_MANAGER.GetItem(m_toolList[_index].m_itemNumber);
}

//void BagManager::UseItem(short _itemNumber)
//{
//	switch (m_selectedItem.m_type)
//	{
//	case SPECIAL:
//	{
//
//	}break;
//	case TOOL:
//	{
//		if (SCENE_MGR.GetFrom() == SCENE_BATTLE)
//		{
//			switch (m_selectedItem.m_function)
//			{
//			case ItemFunction::POTION:
//			{
//				
//			}break;
//			case ItemFunction::REVIVE:
//			{
//				SCENE_MGR.SetScene(SCENE_POKEMON);
//			}
//			}
//		}
//
//	}break;
//	case BALL:
//	{
//		BATTLE_MANAGER.TryCatch();
//	}break;
//	}
//}
