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
	int m_myCurrentPokemon;			//������ ���ϸ� ��
	Pokemon m_wildPokemon;			//�߻����ϸ�

private:
	PokemonManager();
	~PokemonManager();
	void SaveNPCPokemon();
	void LoadNPCPokemon();
	
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
	//�� Ʈ���̳� ���ϸ� �ҷ�����
	Pokemon* GetEnemyPokemonList(int _npcNumber);

	//�߻����ϸ� ������Ű��
	void GeneratePokemon(int _area);
	//�߻����ϸ� ��� ó��
	void CatchPokemon();


};

#define POKEMON_MANAGER PokemonManager::GetInstance()