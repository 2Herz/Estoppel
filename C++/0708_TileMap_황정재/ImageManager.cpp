#include "ImageManager.h"
#include "Image.h"

ImageManager::~ImageManager()
{
	for (auto &i : m_imgList)
	{
		delete i.second;
	}
	m_imgList.clear();
}

string ImageManager::GetFileName(string path)
{
	int start = path.find_last_of("/\\") + 1;
	int end = path.find_last_of('.');
	return path.substr(start, end - start);
}

bool ImageManager::OpenImg(string path, int width, int height)
{
	string name = GetFileName(path);
	auto find = m_imgList.find(name);
	if (find != m_imgList.end())return true;

	if (m_hWnd == nullptr)	return false;

	Img *newImg = new Img;
	bool isLoad = newImg->LoadImg(m_hWnd, path.c_str(), width, height);
	if (isLoad == false)	return false;

	m_imgList.insert(std::make_pair(name, newImg));

	return true;
}

Img * ImageManager::GetImg(string name)
{
	auto find = m_imgList.find(name);

	if (find == m_imgList.end())return nullptr;

	return find->second;
}