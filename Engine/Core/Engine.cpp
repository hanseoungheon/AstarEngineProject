#include <iostream>
#include <Windows.h>
#include "Engine.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

//싱글톤 변수 초기화.
Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		//Engine의 메모리 해제.
		//Engine::Get(), ~Engine();
		Engine::Get().CleanUp();
		return false;
	}

	return false;
}

Engine::Engine()
{
	instance = this;

	//콘솔 커서 끄기.

	//HANDLE
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);

	//콘솔창 이벤트 등록.
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);


	//엔진 설정 로드.
	LoadEngineSetting();

	srand(static_cast<unsigned int>(time(nullptr)));
}

Engine::~Engine()
{
	CleanUp();
}

Engine& Engine::Get()
{
	return *instance;
}

void Engine::BeginePlay()
{
	if (mainLevel != nullptr)
	{
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float DeltaTime)
{
	if (mainLevel != nullptr)
	{
		mainLevel->Tick(DeltaTime);
	}
}

void Engine::Render()
{
	Utils::SetConsoleTextColor
	(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	if (mainLevel != nullptr)
	{
		mainLevel->Render();
	}
}

void Engine::Run()
{
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;

	//Windosw 카운터. -> 운영체제가 시작된 이후 발생한 총 틱 수를 반환시킴.
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	//하드웨어 시계의 정밀도(주파수 가져오기).
	//나중에 초로 변환시키기 위해.
	LARGE_INTEGER frequency;
	QueryPerformanceCounter(&frequency);

	float targetFrameRate
		= (engineSetting.frameRate == 0.0f) ? 60.0f : engineSetting.frameRate;

	//타겟 한 프레임 시간.
	float oneFrameTime = 1.0f / targetFrameRate;

	while (true)
	{
		if (IsQuit) //종료 명령이 떨어졌을시
		{
			break; //루프 종료.
		}

		//프레임 시간 계산
		//(현재 시간 - 이전시간) / 주파수
		QueryPerformanceCounter(&currentTime);

		//델타타임.
		float deltaTime =
			(currentTime.QuadPart - previousTime.QuadPart)
			/ (float)frequency.QuadPart;

		input.ProcessInput();

		//고정 프레임.
		if (deltaTime >= oneFrameTime)
		{
			BeginePlay();
			Tick(deltaTime);
			Render();

			previousTime = currentTime;

			input.SavePreviouseKeyStates();
		}
	}

	//정리
	//모든 텍스트 색상 원래대로 돌려놓기
	Utils::SetConsoleTextColor
	(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Engine::AddLevel(Level* newLevel)
{
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}

	mainLevel = newLevel;
}

void Engine::CleanUp()
{
	SafeDelete(mainLevel);
}

void Engine::Quit()
{
	IsQuit = true;
}

int Engine::ConsoleHeight() const
{
	return engineSetting.width;
}

int Engine::ConsoleWidth() const
{
	return engineSetting.height;
}

void Engine::LoadEngineSetting()
{
	FILE* file = nullptr;
	fopen_s(&file, "../Settings/setting.txt", "rt");

	if (file == nullptr)
	{
		std::cout << "Failed to load Engine Setting.\n";
		__debugbreak();
		return;
	}

	fseek(file, 0, SEEK_END);

	size_t fileSize = ftell(file);

	rewind(file);

	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);

	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	char* context = nullptr;
	char* token = nullptr;

	token = strtok_s(buffer, "\n", &context);

	while (token != nullptr)
	{
		char header[10] = { };

		//아래 구문이 제대로 동작하려면 키와 값 사이에 빈칸이 있어여 함.
		sscanf_s(token, "%s", header, 10);

		//헤더 문자열 비교 true 0 , false => 오른쪽이 크면 음수, 왼쪽이 크면 양수
		if (strcmp(header, "framerate") == 0)
		{
			sscanf_s(token, "framerate = %f", &engineSetting.frameRate);
		}
		else if (strcmp(header, "width") == 0)
		{
			sscanf_s(token, "width = %d", &engineSetting.width);
		}
		else if (strcmp(header, "height") == 0)
		{
			sscanf_s(token, "height = %d", &engineSetting.height);
		}


		token = strtok_s(nullptr, "\n", &context);
	}

}
