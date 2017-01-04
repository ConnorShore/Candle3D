#pragma once

class Time
{

public:
	Time();
	~Time();

	void FpsLimitInit();
	void TimeInit();
	void CalculateFPS(bool printFPS);
	void LimitFPS(const float MAX_FPS = 1000);
	void calcDeltaTime();

	const int getFPS() { return _fpsCurrent; }
	const float getDeltaTime() { return _deltaTime; }

private:
	unsigned int _initTick, _fpsLastTime, _fpsCurrent, _fpsFrames;
	float _deltaTime;
};
