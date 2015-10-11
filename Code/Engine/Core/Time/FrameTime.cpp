#include "FrameTime.h"
#include <assert.h>
#include "TimeHelper.h"
#include <assert.h>

Engine::Time::FrameTime* Engine::Time::FrameTime::mFrameTime = nullptr;
Engine::SharedPointer<Engine::Time::FrameTime> Engine::Time::FrameTime::getFrameTimeController()
{
	if (mFrameTime == nullptr)
	{
		LARGE_INTEGER *tempFrequency = new LARGE_INTEGER;
		LARGE_INTEGER *tempStartCounter = new LARGE_INTEGER;
		assert(QueryPerformanceFrequency(tempFrequency)); //takes Pointer
		assert(QueryPerformanceCounter(tempStartCounter)); //tekes Pointer
		mFrameTime = new FrameTime(tempFrequency, tempStartCounter);
	}
	return mFrameTime;
}
Engine::Time::FrameTime::FrameTime(LARGE_INTEGER * i_frequency, LARGE_INTEGER * i_hRCounter)
		{
			frameTimeFrequency = i_frequency->QuadPart;
			lastTick = i_hRCounter->QuadPart;
			currentTick = 0;
			isTimerPaused = false;
			pauseTimerTick = 0;
			deltaTime = 0;
			delete i_frequency;
			delete i_hRCounter;
			i_frequency = nullptr;
			i_hRCounter = nullptr;
		}
void Engine::Time::FrameTime::pauseTimer(bool i_input)
{
	if (i_input == true)
	{
		isTimerPaused = true;
		LARGE_INTEGER *tempTick = new LARGE_INTEGER;
		assert(QueryPerformanceCounter(tempTick));
		pauseTimerTick = tempTick->QuadPart;
		delete tempTick;
	} // end - if
	else
		isTimerPaused = false;
}
void Engine::Time::FrameTime::updateDeltaTime()
{
	LARGE_INTEGER *tempTick = new LARGE_INTEGER;
	assert(QueryPerformanceCounter(tempTick)); //takes Pointer
	currentTick = tempTick->QuadPart;
	deltaTime = static_cast<float>(Engine::Time::getTimeDiff(lastTick, currentTick) / static_cast<float>(frameTimeFrequency));

	//checking timer was paused or not, if stopped subtracting the pause time from the time difference
	if (pauseTimerTick != 0)
	{
		deltaTime -= static_cast<uint32_t>((Engine::Time::getTimeDiff(pauseTimerTick, currentTick)) / frameTimeFrequency);
		pauseTimerTick = 0;
	}

	//	if (timeDiff > (1 / 60)) timeDiff = (1 / 60);
	lastTick = currentTick;
	delete tempTick;
}
float Engine::Time::FrameTime::getdeltaTime()
{
	return deltaTime;
}
uint64_t Engine::Time::FrameTime::getCurrentTick()
{
	LARGE_INTEGER *tempTick = new LARGE_INTEGER;
	assert(QueryPerformanceCounter(tempTick));
	return (tempTick->QuadPart);
}
float Engine::Time::FrameTime::getdeltaTimeDuringFrame()
{
	LARGE_INTEGER *tempTick = new LARGE_INTEGER;
	assert(QueryPerformanceCounter(tempTick)); //takes Pointer
	uint64_t tempCurrentTick = tempTick->QuadPart;
	float o_deltaTime = static_cast<float>(Engine::Time::getTimeDiff(lastTick, tempCurrentTick) / static_cast<float>(frameTimeFrequency));
	delete tempTick;
	return o_deltaTime;
}
bool Engine::Time::FrameTime::getTimerStatus()
{
	return isTimerPaused;
}
