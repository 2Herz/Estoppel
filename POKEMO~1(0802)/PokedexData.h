#pragma once

class PokedexData
{
public:
	short m_number;			//포켓몬 번호
	char m_name[20];		//종 이름
	short m_type_1;			//타입1
	short m_type_2;			//타입2
	short m_evolutionLevel;	// 총 진화 단계
	short m_evolvedLevel;	// 진화 단계
};