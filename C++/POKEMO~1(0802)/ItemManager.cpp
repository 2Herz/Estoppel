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
	��ȣ : ������ ������ȣ
	�̸� : ������ �̸�
	Ÿ�� : � ������ ���������� (�߿��� 0 , ���� 1 , ���Ϻ� 2 )
	��� : ������ ��� ( ġ��� 0, ���¾� 1, ��Ȱ 2, ��ȭ�� 3, ������ 4) //�߿��� �����Ͻ�, � ���������� ����
	��ġ : ������ �ɷ� ��ġ (�� : ��ó���� ��ġ�� 50�̸� ü��ȸ���� 50�����ش�.)
	���� : ������ ����
	*/

	item[i++] = { i, "��ó��", TOOL, HEAL, 30, 300 };
	item[i++] = { i, "������ó��", TOOL, HEAL, 80, 500 };
	item[i++] = { i, "���ϸ�", BALL, 0, 30, 1000 };

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

	//NPC.db ���� ����
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

//���ϸ󿡰� �������� ����ϸ� ȿ���� �����Ŵ
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
