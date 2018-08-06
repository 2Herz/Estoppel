#pragma once
#include "Pokemon.h"

/*
���ϸ� �����ڰ� �ϴ°�
- ���� ���� ���ϸ� 6���� ������ ����/�ҷ�����
- �� Ʈ���̳� ���ϸ� ������ ����/�ҷ�����
- �߻����ϸ� ������Ű��

*/

class PokemonManager
{
private:
	Pokemon m_myPokemonList[6];		//���ϸ� ����Ʈ
	int m_currentMyIndex = 0;
	Pokemon m_enemyPokemonList[6];	//�� ���ϸ� ����Ʈ
	int m_currentEnemyIndex = 0;
	int m_pokemonCount;			//������ ���ϸ� ��
	Pokemon m_wildPokemon;			//�߻����ϸ�
	std::vector<PokemonTable> m_pokemonTable;
	std::vector<EnemyPokemonTable> m_enemyTable;

private:
	PokemonManager();
	~PokemonManager();
	void SaveMyPokemon();
	void LoadMyPokemon();
	void SaveNPCPokemon();
	void LoadNPCPokemon();
	void SavePokemonTable();
	void LoadPokemonTable();
	
public:
	static PokemonManager& GetInstance()
	{
		static PokemonManager Instance;
		return Instance;
	}

	void Init();
	
	//���ϸ� ����Ʈ �ҷ�����
	void SetMyPokemonList(Pokemon* _pokemonList, int _size);
	//�� ���ϸ� ����Ʈ ��������
	Pokemon* GetMyPokemonList();
	//�� ���ϸ� ��������
	Pokemon GetMyPokemon(int _index);
	Pokemon* GetSelectedMyPokemon();
	void SetSelectedMyPokemon(int _index);
	//�� Ʈ���̳� ���ϸ� �ҷ�����
	Pokemon* GetEnemyPokemonList(int _npcNumber);
	Pokemon* GetSelectedEnemyPokemon();
	void SetSelectedEnemyPokemon(int _index);

	//�߻����ϸ� ������Ű��
	void GeneratePokemon(int _area);
	Pokemon* GetWildPokemon();
	//�߻����ϸ� ��� ó��
	void CatchPokemon();


};

#define POKEMON_MANAGER PokemonManager::GetInstance()