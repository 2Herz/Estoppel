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
	short m_state;
	short m_direction;
	short m_step;
	short m_prevStep;
	float m_animationTime = 0.0f;
	ImgClass m_image;
	bool m_isMoving = false;
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
	void Init(HWND _hWnd);

	void Update(float _elapseTime);
	void Render(HDC _hdc);
	void SetDirection(short _direction);
	bool isMoving();
	void SetIsMoving(bool _isMoving);
	void SetPlayerState(short _state);
	POINT GetPosition();
	void SetPosition(POINT _position);
};

#define PLAYER_MANAGER PlayerManager::GetInstance()