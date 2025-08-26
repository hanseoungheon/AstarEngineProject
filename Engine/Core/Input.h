#pragma once

#include "Core.h"

class Engine_API Input
{
	friend class Engine;
	struct KeyState
	{
		//현재 키가 눌리고 있는지 여부.
		bool isKeyDown = false;

		//이전 프레임에 키가 눌렸는지 여부.
		bool previousKeyDown = false;
	};

public:
	Input();

public:
	//키 확인 함수
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