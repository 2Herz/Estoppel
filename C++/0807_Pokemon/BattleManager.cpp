#include "stdafx.h"
#include "BattleManager.h"


BattleManager::BattleManager()
{
}


BattleManager::~BattleManager()
{
}

void BattleManager::StartBattle()
{
	//전환 애니메이션
	//배틀씬으로 전환
	//SCENE_MGR.SetScene(SCENE_BATTLE);
	
}

void BattleManager::EndBattle()
{
	//전투 정산
	if (isWin)
	{
		PLAYER_MANAGER.SetMoney(PLAYER_MANAGER.GetMoney() + 1000);
	}
	else
	{
		PLAYER_MANAGER.SetMoney(PLAYER_MANAGER.GetMoney() - 500);
	}

	//전환 애니메이션
	//필드화면으로 전환
	SCENE_MGR.SetScene(SCENE_MAIN);
}

void BattleManager::AttackEnemy(Pokemon * _enemy)
{
	POKEMON_MANAGER.GetSelectedEnemyPokemon()->m_hp -= m_selectedSkill.m_damage;
}

bool BattleManager::TryCatch()
{
	if (m_selectedItem.m_value > (rand() % 100))
	{
		POKEMON_MANAGER.CatchPokemon();
	}

	return false;
}

void BattleManager::UseItem(int _itemNumber)
{
	
}
