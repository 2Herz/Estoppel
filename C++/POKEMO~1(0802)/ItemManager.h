#pragma once
#include "stdafx.h"

/*
  - ������ ���� -
  �߿��� ���� : ���˴�, ������, ���� ��....
  ���� : ��ó��, �̻��ѻ���, ��ȭ��, ����ȸ���� ��...
  ���Ϻ� : ���Ϻ�, ���ۺ�, �����ۺ�, �����ͺ� .....
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
	short m_number;		//������ ��ȣ
	char m_name[20];	//������ �̸�
	short m_type;		//������ Ÿ��
	short m_function;	//��� 
	short m_value;		//������ ��ġ
	short m_price;		//������ ����
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