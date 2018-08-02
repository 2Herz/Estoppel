#pragma once
#include "Pokemon.h"
class BattleManager
{
private:
	//Character 정보
	Pokemon m_myPokemon[6]; //현재 출전중인 포켓몬
	//적 트레이너 정보
	Pokemon m_enemyPokemon[6]; //적 포켓몬 정보
	
private:
	BattleManager();
	~BattleManager();

public:
	static BattleManager& GetInstance()
	{
		static BattleManager Instance;
		return Instance;
	}

	//배틀 시작 + 씬 전환 호출
	void StartBattle();
	//턴 전환
	void NextTurn();
	//공격
	void DoAttack();
};

#define BATTLE_MANAGER BattleManager::GetInstance()