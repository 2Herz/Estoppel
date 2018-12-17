#pragma once
#include "PokedexData.h"
#include "Skill.h"

class Pokemon
{
	friend class PokemonManager;

private:
	PokedexData m_data;				//포켓몬 데이터
	char m_nickname[20];			//닉네임
	bool m_sex;						//성별
	Skill m_skill[4] = {};			//보유 스킬
	short m_level;					//레벨
	short m_hp;						//체력
	short m_condition;				//상태이상
	unsigned short m_giveExp;		//주는경험치
	unsigned short m_currentExp;	//현재경험치
	unsigned short m_requiredExp;	//필요경험치

public:
	Pokemon();
	~Pokemon();
};