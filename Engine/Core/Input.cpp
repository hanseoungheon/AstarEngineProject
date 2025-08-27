#include "Input.h"
#include <Windows.h>

//static 변수 정의
Input* Input::instance = nullptr;

Input::Input()
{
	//싱글톤 실행을 위해 this 키워드 사용!
	instance = this;
}
void Input::ProcessInput()
{
	//키 입력 확인
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].isKeyDown
			= GetAsyncKeyState(ix) && 0x8000;
	}
}

void Input::SavePreviouseKeyStates()
{
	//현재 프레임의 입력을 기록
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].previouseKeyDown
			= keyStates[ix].isKeyDown;
	}
}

bool Input::GetKey(int KeyCode)
{
	//auto& instance =Engine().
	return keyStates[KeyCode].isKeyDown;

}

bool Input::GetKeyDown(int KeyCode)
{
	return !keyStates[KeyCode].previouseKeyDown
		&& keyStates[KeyCode].isKeyDown;
}

bool Input::GetKeyUp(int KeyCode)
{
	return keyStates[KeyCode].previouseKeyDown
		&& !keyStates[KeyCode].isKeyDown;
}

Input& Input::GetController()
{
	return *instance;
}