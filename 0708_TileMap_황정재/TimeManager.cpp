#undef UNICODE
#include "Time.h"
#include "TimeManager.h"
#include <sstream>
using namespace std;
typedef stringstream Text;

TimeManager::TimeManager()
{
	timer = new Time();
}

TimeManager::~TimeManager()
{
	delete timer;
	timer;
}

float TimeManager::Tick()
{
	return timer->Tick();
}

unlong TimeManager::GetFPS()
{
	return timer->GetFPS();
}

void TimeManager::SetFPS(unlong lockFPS)
{
	timer->SetFPS(lockFPS);
}

float TimeManager::GetElapseTime()
{
	return timer->GetElapsedTime();
}

float TimeManager::GetPlayTime()
{
	return timer->GetPlayTime();
}

void TimeManager::RenderFPS(HDC hdc, int x, int y)
{
	Text text;

	text << "현재 프레임 : " << timer->GetFPS();
	TextOut(hdc, x, y, text.str().c_str(), text.str().length());
	text.str("");

	text << "경과시간 : " << timer->GetPlayTime();
	TextOut(hdc, x, y + 15, text.str().c_str(), text.str().length());
	text.str("");
}