#pragma once

enum PLAYER_STATE
{
	WALK,
	RUN,
	RIDE_BIKE,
};

class PlayerManager
{
private:
	bool m_sex;
	std::string m_name;
	short m_badgeCount;
	int m_money;
	short m_state;
	short m_direction;
	short m_step;
	short m_prevStep;
	float m_animationTime = 0.0f;
	ImgClass m_image;
	bool m_isMoving = false;
	bool m_controlActivated = true;
	POINT m_currentPosition;

private:
	PlayerManager();
	~PlayerManager();
	void Release();
	void GoUp();
	void GoDown();
	void GoLeft();
	void GoRight();

public:
	static PlayerManager& GetInstance()
	{
		static PlayerManager Instance;
		return Instance;
	}

	std::string GetName();
	void SetName(std::string _name);
	bool GetSex();
	void SetSex(bool _sex);
	short GetBadgeCount();
	void IncreaseBadge();
	int GetMoney();
	void SetMoney(int _money);
	
	void SetDirection(short _direction);
	bool isMoving();
	void SetIsMoving(bool _isMoving);
	void SetPlayerState(short _state);
	short GetPlayerState();
	POINT GetPosition();
	void SetPosition(POINT _position);

	bool IsControlActivated();
	void SetControlActivate(bool _isActivated)
	{
		m_controlActivated = _isActivated;
	}

	void Init(HWND _hWnd);
	void Update(float _elapseTime);
	void Render(HDC _hdc);
	
};

#define PLAYER_MANAGER PlayerManager::GetInstance()