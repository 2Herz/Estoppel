#pragma once
#include "NPC.h"

class DataManager
{

private:
	DataManager();
	~DataManager();

public:
	static DataManager& GetInstance()
	{
		static DataManager Instance;
		return Instance;
	}

	void SaveData();
	void LoadData();
};

#define DATA_MANAGER DataManager::GetInstance()