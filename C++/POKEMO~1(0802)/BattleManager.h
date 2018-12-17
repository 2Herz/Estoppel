#pragma once
#include "Pokemon.h"
class BattleManager
{
private:
	//Character ����
	Pokemon m_myPokemon[6]; //���� �������� ���ϸ�
	//�� Ʈ���̳� ����
	Pokemon m_enemyPokemon[6]; //�� ���ϸ� ����
	
private:
	BattleManager();
	~BattleManager();

public:
	static BattleManager& GetInstance()
	{
		static BattleManager Instance;
		return Instance;
	}

	//��Ʋ ���� + �� ��ȯ ȣ��
	void StartBattle();
	//�� ��ȯ
	void NextTurn();
	//����
	void DoAttack();
};

#define BATTLE_MANAGER BattleManager::GetInstance()