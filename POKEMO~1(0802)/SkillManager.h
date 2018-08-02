#pragma once
#include "Skill.h"

enum Type
{
	NORMAL,
	FIRE,
	WATER,
	GRASS,
	THUNDER,
	ICE,
	FIGHT,
	POISON,
	GROUND,
	FLY,	
	ESPER,
	BUG,
	ROCK,
	GHOST,
	DRAGON,
	EVIL,
	STEEL,
	FAIRY,
};

class SkillManager
{
private:
	std::vector<Skill> m_skillList;

private:
	SkillManager();
	~SkillManager();
	void SaveSkill();
	void LoadSkill();

public:
	static SkillManager& GetInstance()
	{
		static SkillManager Instance;
		return Instance;
	}

	void Init();
	Skill GetSkill(int _skillNumber);
	float GetDamageRate(int _typeA, int _typeB);
};

#define SKILL_MANAGER SkillManager::GetInstance()