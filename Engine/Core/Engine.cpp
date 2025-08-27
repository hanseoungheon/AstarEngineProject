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
		//Engine의 메모리 해제
		//Engine::Get().~Engine();
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

void Engine::BeginPlay()
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
	//밀리 세컨드 단위로 현재 시간 알려줌
	//float currentTime = timeGetTime();

	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	//Windosw 카운터
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	//하드웨어 시계의정밀도(주파수 가져오기)
	//나중에 초로 변환하기 위해
	LARGE_INTEGER freqeuncy;
	QueryPerformanceFrequency(&freqeuncy);

	//타겟 프레임
	float targetFramRate
		= (engineSetting.frameRate == 0.0f) ? 60.0f : engineSetting.frameRate;


	//타겟 한 프레임 시간
	float oneFrameTime = 1.0f / targetFramRate;

	while (true)
	{
		if (IsQuit)
		{
			//루프 종료
			break;
		}

		//프레임 시간 계산
		//(현재 시간 - 이전시간) / 주파수
		QueryPerformanceCounter(&currentTime);


		//프레임 시간
		float deltaTime =
			(currentTime.QuadPart - previousTime.QuadPart)
			/ (float)freqeuncy.QuadPart;

		//입력은 최대한 빨리
		input.ProcessInput();

		//고정 프레임
		if (deltaTime >= oneFrameTime)
		{
			//이전 프레임에 추가 및 삭제 요청된 액터 처리
			if (mainLevel)
			{
				mainLevel->ProcessAddAndDestroyActors();
			}

			BeginPlay();
			Tick(deltaTime);
			Render();

			////제목에 FPS 출력
			//char title[50] = {};
			//sprintf_s(title, 50, "FPS: %f", (1.0f/deltaTime));
			////A는 단문자, W는 w_char
			//SetConsoleTitleA(title);

			//시간 업데이트
			previousTime = currentTime;

			//현재 프레임의 입력을 기록
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
	//엔진 설정 파일 열기
	FILE* file = nullptr;
	fopen_s(&file, "../Settings/settings.txt", "rt");

	//파일이 터짐
	if (file == nullptr)
	{
		std::cout << "Failed to load engine settings.\n";
		__debugbreak();
		return;
	}

	//로드

	//FP 포인터를 가장 뒤로 옮기기
	fseek(file, 0, SEEK_END);

	//이 위치 구하기
	size_t fileSize = ftell(file);

	// 다시 첫 위치로 되돌리기
	//fseek(file, 0, SEEK_SET); 이거 써도 됨
	rewind(file);

	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);

	// 내용 읽기
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);



	//구문 해석(파싱) => 필요한 정보 해석
	char* context = nullptr;
	char* token = nullptr;

	token = strtok_s(buffer, "\n", &context);

	while (token != nullptr)
	{
		// 키/값 분리
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
		//그 다음 줄 분리
	}

	SafeDeleteArray(buffer);

	fclose(file);

}
