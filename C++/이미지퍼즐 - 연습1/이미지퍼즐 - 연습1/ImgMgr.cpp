#include "ImgMgr.h"

ImgMgr::~ImgMgr()
{
	for (auto &i : m_imgList)
	{
		delete i.second;
	}
	m_imgList.clear();
}

std::string ImgMgr::GetFileName(std::string _path)
{
	//	마지막 / or \\ 위치를 찾는다.
	int start = _path.find_last_of("/\\") + 1;
	int end = _path.find_last_of('.');

	return _path.substr(start, end - start);
}

bool ImgMgr::OpenImg(std::string _path, int _width, int _height)
{
	std::string name = GetFileName(_path);

	auto find = m_imgList.find(name);

	if (find != m_imgList.end())return true;

	if (m_hWnd == nullptr)	return false;

	ImgClass *newImg = new ImgClass;
	bool isLoad = newImg->LoadImg(m_hWnd, _path.c_str(), _width, _height);
	if (isLoad == false)	return false;

	m_imgList.insert(std::make_pair(name, newImg));

	return true;
}

ImgClass*	ImgMgr::GetImg(std::string _name)
{
	auto find = m_imgList.find(_name);

	if (find == m_imgList.end())return nullptr;

	return find->second;
}