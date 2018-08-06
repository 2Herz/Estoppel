#include "stdafx.h"
#include "PokemonManager.h"


PokemonManager::PokemonManager()
{
}


PokemonManager::~PokemonManager()
{
}

void PokemonManager::SaveMyPokemon()
{
}

void PokemonManager::LoadMyPokemon()
{
}

void PokemonManager::SaveNPCPokemon()
{
	EnemyPokemonTable* table = new EnemyPokemonTable[TRAINER_TOTAL_NUMBER];

	short i = 0;

	/*
	NPC 번호 : NPC.db에 작성된 번호랑 일치해야함
	포켓몬 정보 : 
		- 포켓몬 번호
		- 스킬 1
		- 스킬 2
		- 스킬 3
		- 스킬 4
	*/
	table[i++] = { 0,{ 11, 15, 16, -1,-1 } };
	table[i++] = { 5,{ 11, 15, 16, -1,-1 } };

	std::ofstream fout("DB/NPC_Pokemon.db");

	if (fout.fail() == false)
	{
		fout.write((const char*)table, sizeof(EnemyPokemonTable) * TRAINER_TOTAL_NUMBER);
	}

	delete[] table;
}

void PokemonManager::LoadNPCPokemon()
{
	EnemyPokemonTable* table = new EnemyPokemonTable[TRAINER_TOTAL_NUMBER];
	std::ifstream fout;

	fout.open("DB/NPC_Pokemon.db");

	if (fout.fail() == false)
	{
		fout.read((char*)table, sizeof(EnemyPokemonTable) * TRAINER_TOTAL_NUMBER);
		fout.close();

		for (int i = 0; i < TRAINER_TOTAL_NUMBER; i++)
		{
			EnemyPokemonTable temp;
			temp.npcNumber = table[i].npcNumber;
			temp.PokemonList[0] = table[i].PokemonList[0];
			temp.PokemonList[1] = table[i].PokemonList[1];
			temp.PokemonList[2] = table[i].PokemonList[2];
			temp.PokemonList[3] = table[i].PokemonList[3];
			temp.PokemonList[4] = table[i].PokemonList[4];
			temp.PokemonList[5] = table[i].PokemonList[5];
			m_enemyTable.push_back(temp);
		}
	}
}

void PokemonManager::SavePokemonTable()
{
	PokemonTable* table = new PokemonTable[POKEMON_TOTAL_NUMBER];
	std::ofstream fout("DB/SkillTable.db");

	short i = 0;

	/*for (short i = 0; i < POKEMON_TOTAL_NUMBER; i++)
	{
		PokedexData pokemon = POKEDEX.GetPokemonData(i);
		table[i].pokemonIndex = pokemon.m_number;

		int max = pokemon.m_evolvedLevel + 1;
		for (int j = 0; j < 4; j++)
		{
			if (j < max)
			{
				Skill temp;
				bool end = true;
				while (end)
				{
					temp = SKILL_MANAGER.GetSkill(rand() % SKILL_TOTAL_NUMBER);
					
					if (temp.m_type == pokemon.m_type_1 || temp.m_type == pokemon.m_type_2 || temp.m_type == Type::NORMAL)
					{
						end = false;
					}

					for (int k = 0; k < j; k++)
					{
						if (table[i].skill[k] == temp.m_number)
						{
							end = true;
						}
					}
				}
				
				table[i].skill[j] = temp.m_number;
			}
			else
			{
				table[i].skill[j] = -1;
			}
		}
		
	}*/

	/*
	포켓몬 번호
	기술 1 번호
	기술 2 번호
	기술 3 번호
	기술 4 번호
	기술 없으면 -1
	*/

	table[i++] = { i, 32, 72, -1, -1 }; //이상해씨 - 몸통박치기, 씨뿌리기
	table[i++] = { i, 74, 72, 21, -1 }; //이상해풀 - 잎날가르기, 씨뿌리기, 덩굴채찍
	table[i++] = { i, 74, 72, 21, 75 }; //이상해꽃 - 몸통박치기, 씨뿌리기, 솔라빔

	if (fout.fail() == false)
	{
		for (int i = 0; i < 3; i++)
		{
			fout << table[i].pokemonIndex << " "
				<< table[i].skill[0] << " "
				<< table[i].skill[1] << " "
				<< table[i].skill[2] << " "
				<< table[i].skill[3] << std::endl;
		}
		fout.close();
	}

	delete[] table;
}

void PokemonManager::LoadPokemonTable()
{
	std::ifstream fout;

	fout.open("DB/SkillTable.db");

	if (fout.fail() == false)
	{
		for (int i = 0; i < 3; i++)
		{
			PokemonTable temp;
			fout >> temp.pokemonIndex
				>> temp.skill[0]
				>> temp.skill[1]
				>> temp.skill[2]
				>> temp.skill[3];
			m_pokemonTable.push_back(temp);
		}
		fout.close();
	}
}

void PokemonManager::Init()
{
	SaveNPCPokemon();
	LoadNPCPokemon();
	SavePokemonTable();
	LoadPokemonTable();
}

void PokemonManager::SetMyPokemonList(Pokemon* _pokemonList, int _size)
{
	for (int i = 0; i < _size; i++)
	{
		m_myPokemonList[i] = _pokemonList[i];
	}

	m_pokemonCount = _size;
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

Pokemon* PokemonManager::GetSelectedMyPokemon()
{
	return &m_myPokemonList[m_currentMyIndex];
}

void PokemonManager::SetSelectedMyPokemon(int _index)
{
	m_currentMyIndex = _index;
}

Pokemon* PokemonManager::GetEnemyPokemonList(int _npcNumber)
{
	m_enemyTable[_npcNumber];
	return m_enemyPokemonList;
}

Pokemon* PokemonManager::GetSelectedEnemyPokemon()
{
	return &m_enemyPokemonList[m_currentEnemyIndex];
}

void PokemonManager::SetSelectedEnemyPokemon(int _index)
{
	m_currentEnemyIndex = _index;
}

void PokemonManager::GeneratePokemon(int _area)
{	
	m_wildPokemon.m_condition = CONDITION::NO_CONDITION;
	m_wildPokemon.m_sex = rand() % 2;

	//지역에 따라 생성되는 포켓몬목록이 다르게 처리
	switch (_area)
	{
	case 0:
	{
		int indexList[3] = { 0,3,6 }; //등장 포켓몬 번호
		m_wildPokemon.m_data = POKEDEX.GetPokemonData(indexList[(rand()%3)]);
		m_wildPokemon.m_level = (rand()%5) + 2;
		m_wildPokemon.m_hpMax = 100 * m_wildPokemon.m_level;
		m_wildPokemon.m_hp = m_wildPokemon.m_hpMax;
		m_wildPokemon.m_giveExp = 50 * m_wildPokemon.m_level;
		m_wildPokemon.m_requiredExp = 300 * m_wildPokemon.m_level;
		m_wildPokemon.m_currentExp = 0;
		for (int i = 0; i < 4; i++)
		{
			m_wildPokemon.m_skill[i] = SKILL_MANAGER.GetSkillByType(m_wildPokemon.m_data.m_type_1, m_wildPokemon.m_data.m_type_2);
		}
	}break;
	}
	
}

Pokemon* PokemonManager::GetWildPokemon()
{
	return &m_wildPokemon;
}

void PokemonManager::CatchPokemon()
{
	//들고있는 포켓몬이 6마리라면, 포켓박스로 전송
	if (m_pokemonCount == 6)
	{

	}
	//아니라면 가방에 추가
	m_myPokemonList[m_pokemonCount] = m_wildPokemon;
}
