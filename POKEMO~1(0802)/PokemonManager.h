#pragma once
#include "Pokemon.h"

/*
포켓몬 관리자가 하는것
- 내가 가진 포켓몬 6마리 데이터 저장/불러오기
- 적 트레이너 포켓몬 데이터 저장/불러오기
- 야생포켓몬 출현시키기

*/
class PokemonManager
{
private:
	Pokemon m_myPokemonList[6];		//포켓몬 리스트
	int m_myCurrentPokemon;			//보유한 포켓몬 수
	Pokemon m_wildPokemon;			//야생포켓몬

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
	
	//포켓몬 리스트 불러오기
	void SetMyPokemonList(Pokemon* _pokemonList, int _size);
	//내 포켓몬 리스트 가져오기
	Pokemon* GetMyPokemonList();
	//내 포켓몬 가져오기
	Pokemon GetMyPokemon(int _index);
	//적 트레이너 포켓몬 불러오기
	Pokemon* GetEnemyPokemonList(int _npcNumber);

	//야생포켓몬 출현시키기
	void GeneratePokemon(int _area);
	//야생포켓몬 잡기 처리
	void CatchPokemon();


};

#define POKEMON_MANAGER PokemonManager::GetInstance()