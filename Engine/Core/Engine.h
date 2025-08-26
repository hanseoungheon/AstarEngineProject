#pragma once
#include "Core.h"
#include "Input.h"
#include <Windows.h>

class Level; //전방 선언.

struct EngineSetting
{
	//콘솔화면 가로 크기.
	int width = 0;

	//콘솔화면 세로 크기.
	int height = 0;

	//타겟 프레임 속도
	float frameRate = 0.0f;
};


class Engine_API Engine
{
public:
	Engine();

	virtual ~Engine();

	void Run();

	void AddLevel();

	virtual void CleanUp();

	void Quit();

	//싱글톤 접근 함수.
	static Engine& Get();

public:
	//화면 가로 세로 크기 Getter.
	int ConsoleWidth() const;
	int ConsoleHeight() const;

private:
	void BeginePlay();
	void Tick(float DeltaTIme = 0.0f);
	void Render();

	//엔진 설정 로드 함수.
	void LoadEngineSetting();

protected:
	//엔진종료 플래그.
	bool IsQuit = false;

	Level* mainLevel;

	Input input;

	//싱글톤 변수.
	static Engine* instance;

	EngineSetting engineSetting;
};