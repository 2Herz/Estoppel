#pragma once

enum MAP_NUMBER
{
	HOME_TOWN,
	ROAD_NO_1,
	VIRIDIAN_CITY,
	CHAMPION_ROAD,

};

class MapManager
{

private:
	POINT m_camPosition;
	POINT m_prevCamPosition;
	POINT m_mapPosition;
	float m_xOffset = 0.0f;
	float m_yOffset = 0.0f;
	float m_elapseTime = 0.0f;
	bool m_gridMode = false;
	std::vector<ImgClass*> m_mapList;
	int m_currentMap = 0;

private:
	MapManager();
	~MapManager();

public:
	static MapManager& GetInstance()
	{
		static MapManager Instance;
		return Instance;
	}

	POINT GetCamPosition();
	void Init(HWND _hWnd);
	void Update(float _elapseTime);
	void Render(HDC _hdc);

	void SetCamPosition(int _x, int _y);
	void SetMap(int _mapNumber);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void ToggleGrid();
	void DrawGrid(HDC _hdc);
};

#define MAP_MANAGER MapManager::GetInstance()