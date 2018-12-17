#pragma once
#include "Pokemon.h"
#include "Skill.h"
#include "Item.h"

class BattleManager
{
private:
	Skill m_selectedSkill;
	Item m_selectedItem;

	bool isWin = false;
	
private:
	BattleManager();
	~BattleManager();
	

public:
	static BattleManager& GetInstance()
	{
		static BattleManager Instance;
		return Instance;
	}

	//��Ʋ ���� + �� ��ȯ ȣ�� + ���� ��������
	void StartBattle();
	//��Ʋ ���� + �� ��ȯ ȣ�� + ���� ��������
	void EndBattle();

	void AttackEnemy(Pokemon* _enemy);
	void UseItem(int _itemNumber);
	bool TryCatch();
};

#define BATTLE_MANAGER BattleManager::GetInstance()