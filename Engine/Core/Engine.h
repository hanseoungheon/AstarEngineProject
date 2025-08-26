#pragma once
#include "Core.h"
#include "Input.h"
#include <Windows.h>

class Level; //���� ����.

struct EngineSetting
{
	//�ܼ�ȭ�� ���� ũ��.
	int width = 0;

	//�ܼ�ȭ�� ���� ũ��.
	int height = 0;

	//Ÿ�� ������ �ӵ�
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

	//�̱��� ���� �Լ�.
	static Engine& Get();

public:
	//ȭ�� ���� ���� ũ�� Getter.
	int ConsoleWidth() const;
	int ConsoleHeight() const;

private:
	void BeginePlay();
	void Tick(float DeltaTIme = 0.0f);
	void Render();

	//���� ���� �ε� �Լ�.
	void LoadEngineSetting();

protected:
	//�������� �÷���.
	bool IsQuit = false;

	Level* mainLevel;

	Input input;

	//�̱��� ����.
	static Engine* instance;

	EngineSetting engineSetting;
};