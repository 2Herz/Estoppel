#include "stdafx.h"
#include "PokemonManager.h"


PokemonManager::PokemonManager()
{
}


PokemonManager::~PokemonManager()
{
}

void PokemonManager::SaveNPCPokemon()
{

	std::ofstream fout("DB/Pokemon.db");

	if (fout.fail() == false)
	{
		
	}
}

void PokemonManager::LoadNPCPokemon()
{
}

void PokemonManager::Init()
{
}

void PokemonManager::SetMyPokemonList(Pokemon* _pokemonList, int _size)
{
	for (int i = 0; i < _size; i++)
	{
		m_myPokemonList[i] = _pokemonList[i];
	}

	m_myCurrentPokemon = _size;
}

Pokemon* PokemonManager::GetMyPokemonList()
{
	return m_myPokemonList;
}

Pokemon PokemonManager::GetMyPokemon(int _index)
{
	if (_index >= 6) return Pokemon();
	else return m_myPokemonList[_index];
}

Pokemon * PokemonManager::GetEnemyPokemonList(int _npcNumber)
{
	return nullptr;
}

void PokemonManager::GeneratePokemon(int _area)
{	
	m_wildPokemon.m_condition = CONDITION::NO_CONDITION;
	m_wildPokemon.m_sex = rand() % 2;

	//������ ���� �����Ǵ� ���ϸ����� �ٸ��� ó��
	switch (_area)
	{
	case 0:
	{
		int indexList[3] = { 0,1,2 };
		m_wildPokemon.m_data = POKEDEX.GetPokemonData(indexList[(rand()%3)]);
		m_wildPokemon.m_level = (rand()%5) + 2;
		m_wildPokemon.m_hp = 150 * (m_wildPokemon.m_level * 0.5);
		m_wildPokemon.m_giveExp = 50 * m_wildPokemon.m_level;
		m_wildPokemon.m_requiredExp = 300 * m_wildPokemon.m_level;
		m_wildPokemon.m_currentExp = 0;
		m_wildPokemon.m_skill;
	}break;
	}
	
}

void PokemonManager::CatchPokemon()
{
	//����ִ� ���ϸ��� 6�������, ���Ϲڽ��� ����
	//�ƴ϶�� ���濡 �߰�
	m_myPokemonList[m_myCurrentPokemon] = Pokemon();
}
