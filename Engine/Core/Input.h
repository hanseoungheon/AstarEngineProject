#pragma once

#include "Core.h"

class Engine_API Input
{
	friend class Engine;
	struct KeyState
	{
		//���� Ű�� ������ �ִ��� ����.
		bool isKeyDown = false;

		//���� �����ӿ� Ű�� ���ȴ��� ����.
		bool previousKeyDown = false;
	};

public:
	Input();

public:
	//Ű Ȯ�� �Լ�
	//Getter
	bool GetKey(int KeyCode);
	bool GetKeyDown(int KeyCode);
	bool GetKeyUp(int KeyCode);


	static Input& Get();
private:
	void ProcessInput();
	void SavePreviouseKeyStates();

	KeyState keyInputs[255] = { };

	static Input* instance;
};