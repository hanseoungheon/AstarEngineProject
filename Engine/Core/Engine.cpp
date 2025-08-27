#include <iostream>
#include <Windows.h>
#include "Engine.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

//�̱��� ���� �ʱ�ȭ.
Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		//Engine�� �޸� ����
		//Engine::Get().~Engine();
		Engine::Get().CleanUp();
		return false;
	}

	return false;
}

Engine::Engine()
{
	instance = this;

	//�ܼ� Ŀ�� ����.

	//HANDLE
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);

	//�ܼ�â �̺�Ʈ ���.
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);


	//���� ���� �ε�.
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
	//�и� ������ ������ ���� �ð� �˷���
	//float currentTime = timeGetTime();

	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	//Windosw ī����
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	//�ϵ���� �ð������е�(���ļ� ��������)
	//���߿� �ʷ� ��ȯ�ϱ� ����
	LARGE_INTEGER freqeuncy;
	QueryPerformanceFrequency(&freqeuncy);

	//Ÿ�� ������
	float targetFramRate
		= (engineSetting.frameRate == 0.0f) ? 60.0f : engineSetting.frameRate;


	//Ÿ�� �� ������ �ð�
	float oneFrameTime = 1.0f / targetFramRate;

	while (true)
	{
		if (IsQuit)
		{
			//���� ����
			break;
		}

		//������ �ð� ���
		//(���� �ð� - �����ð�) / ���ļ�
		QueryPerformanceCounter(&currentTime);


		//������ �ð�
		float deltaTime =
			(currentTime.QuadPart - previousTime.QuadPart)
			/ (float)freqeuncy.QuadPart;

		//�Է��� �ִ��� ����
		input.ProcessInput();

		//���� ������
		if (deltaTime >= oneFrameTime)
		{
			//���� �����ӿ� �߰� �� ���� ��û�� ���� ó��
			if (mainLevel)
			{
				mainLevel->ProcessAddAndDestroyActors();
			}

			BeginPlay();
			Tick(deltaTime);
			Render();

			////���� FPS ���
			//char title[50] = {};
			//sprintf_s(title, 50, "FPS: %f", (1.0f/deltaTime));
			////A�� �ܹ���, W�� w_char
			//SetConsoleTitleA(title);

			//�ð� ������Ʈ
			previousTime = currentTime;

			//���� �������� �Է��� ���
			input.SavePreviouseKeyStates();


		}
	}

	//����
	//��� �ؽ�Ʈ ���� ������� ��������
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
	//���� ���� ���� ����
	FILE* file = nullptr;
	fopen_s(&file, "../Settings/settings.txt", "rt");

	//������ ����
	if (file == nullptr)
	{
		std::cout << "Failed to load engine settings.\n";
		__debugbreak();
		return;
	}

	//�ε�

	//FP �����͸� ���� �ڷ� �ű��
	fseek(file, 0, SEEK_END);

	//�� ��ġ ���ϱ�
	size_t fileSize = ftell(file);

	// �ٽ� ù ��ġ�� �ǵ�����
	//fseek(file, 0, SEEK_SET); �̰� �ᵵ ��
	rewind(file);

	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);

	// ���� �б�
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);



	//���� �ؼ�(�Ľ�) => �ʿ��� ���� �ؼ�
	char* context = nullptr;
	char* token = nullptr;

	token = strtok_s(buffer, "\n", &context);

	while (token != nullptr)
	{
		// Ű/�� �и�
		char header[10] = { };

		//�Ʒ� ������ ����� �����Ϸ��� Ű�� �� ���̿� ��ĭ�� �־ ��.
		sscanf_s(token, "%s", header, 10);

		//��� ���ڿ� �� true 0 , false => �������� ũ�� ����, ������ ũ�� ���
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
		//�� ���� �� �и�
	}

	SafeDeleteArray(buffer);

	fclose(file);

}
