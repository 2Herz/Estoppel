#pragma once

#include <map>
#include <string>
#include <Windows.h>
#include "Image.h"
#include "SingletonB.h"
using namespace std;

class ImageManager : public MySingletonB<ImageManager>
{
	friend MySingletonB;

private:
	HWND				m_hWnd;
	map<string, Img*>	m_imgList;

private:
	ImageManager() = default;
	~ImageManager();

	string GetFileName(string path);

public:
	void SethWnd(HWND hWnd)
	{
		m_hWnd = hWnd;
	}

	bool OpenImg(string path, int width = 0, int height = 0);
	Img* GetImg(string name);
};

#define		IMG_MGR		ImageManager::GetInst()
