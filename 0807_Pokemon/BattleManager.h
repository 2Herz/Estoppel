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

	//배틀 시작 + 씬 전환 호출 + 정보 가져오기
	void StartBattle();
	//배틀 종료 + 씬 전환 호출 + 정보 가져오기
	void EndBattle();

	void AttackEnemy(Pokemon* _enemy);
	void UseItem(int _itemNumber);
	bool TryCatch();
};

#define BATTLE_MANAGER BattleManager::GetInstance()