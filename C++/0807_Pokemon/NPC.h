#pragma once
#include "ImgClass.h"

/*
NPC �ൿ
1. �Ϲ� NPC
�� ���� �ֽ��ϴٰ� ���ɸ� ĳ���͸� �Ĵٺ��� ��ũ��Ʈ ���
*/

//NPC ���
enum NPC_FUNCTION 
{
	NONE,		//�Ϲ�
	HEAL,		//���ϸ���
	SHOP,		//����
	TRAINER,	//�Ϲ� Ʈ���̳�
	CHAMP,		//ü���� ����
};

//NPC ����
enum NPC_STATE
{
	NPC_NORMAL,		//�Ϲ�
	ENCOUNTER,	//����
	COMING,	
	INTERACT,	//��ȣ�ۿ�
	FINISHED,
};

//NPC �ൿ����
enum NPC_PATTERN
{
	STARRING, //�ֽ�
	TURN_ARROUND_CLOCKWISE, //�ֺ� �ð���� ���ۺ��� ��ȸ
	TURN_ARROUND_COUNTER_CLOCKWISE, //�ݽð���� ��ȸ
	TURNING, //���ڸ� ���ۺ���
	RANDOM, //���� �ൿ
};

class NPC
{
private:
	int m_number;			//NPC ��ȣ
	int m_function;			//���
	int m_searchDistance;	//Ž���Ÿ�
	int m_state;			//����
	int m_mapNumber;
	
	POINT m_prevPosition;
	POINT m_position;		//NPC ��ġ Ÿ�� ��ǥ
	POINT m_rootPosition;	//NPC �� ��ġ ��ǥ
	POINT m_realPosition;   //NPC ���� ��ġ ��ǥ
	int m_direction;
	int m_step;
	bool m_isMoving = false;
	int m_pattern;			//NPC ����
	SIZE m_moveBox;			//NPC �ൿ �ڽ�ũ��
	POINT m_moveBoxPosition; //�ൿ�ڽ� ��ǥ
	float m_animationTime;		//NPC �ִϸ��̼� �ð�

	int m_x_max; //�� width
	int m_y_max; //�� height

private:
	void GoLeft();
	void GoRight();
	void GoUp();
	void GoDown();
	void TurnUp();
	void TurnDown();
	void TurnLeft();
	void TurnRight();
	void DoPattern();
	void DoScript();
	bool CheckPlayer();

public:
	NPC();
	NPC(int _number,int _mapNumber, int _function, int _direction, int _pattern, int _searchDistance, POINT _position, SIZE _moveBoxSize);
	~NPC();

	int GetState()
	{
		return m_state;
	}
	void SetState(int _state)
	{
		m_state = _state;
	}

	POINT GetRealPosition()
	{
		return m_realPosition;
	}

	POINT GetRootPosition()
	{
		return m_rootPosition;
	}

	POINT GetPosition()
	{
		return m_position;
	}

	SIZE GetMoveBox()
	{
		return m_moveBox;
	}

	void SetPosition(POINT _position)
	{
		m_position = _position;
	}

	int GetNumber()
	{
		return m_number;
	}

	int GetDirection()
	{
		return m_direction;
	}

	int GetStep()
	{
		return m_step;
	}

	bool IsMoving()
	{
		return m_isMoving;
	}

	void DoAction(float _elapseTime);
};

