#pragma once
#include "PokedexData.h"
#include "Skill.h"

class Pokemon
{
	friend class PokemonManager;

private:
	PokedexData m_data;				//���ϸ� ������
	char m_nickname[20];			//�г���
	bool m_sex;						//����
	Skill m_skill[4] = {};			//���� ��ų
	short m_level;					//����
	short m_hp;						//ü��
	short m_condition;				//�����̻�
	unsigned short m_giveExp;		//�ִ°���ġ
	unsigned short m_currentExp;	//�������ġ
	unsigned short m_requiredExp;	//�ʿ����ġ

public:
	Pokemon();
	~Pokemon();
};