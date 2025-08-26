#include "Input.h"
#include <Windows.h>
//싱글톤 변수.
Input* Input::instance = nullptr;

Input::Input()
{
    //싱글톤 실행(단 하나만의 객체만이 존재한다는 뜻)
    instance = this;
}

Input& Input::Get()
{
    return *instance;
}

void Input::ProcessInput()
{
    //키 입력 확인!
    for (int i = 0; i < 255; ++i)
    {
        keyInputs[i].isKeyDown =
            GetAsyncKeyState(i) && 0x8000;
    }
}

void Input::SavePreviouseKeyStates()
{
    //현재 프레임의 입력을 기록하기.
    for (int i = 0; i < 255; ++i)
    {
        keyInputs[i].previousKeyDown =
            keyInputs[i].isKeyDown;
    }
}

bool Input::GetKey(int KeyCode)
{
    return keyInputs[KeyCode].isKeyDown;
}

bool Input::GetKeyDown(int KeyCode)
{
    return keyInputs[KeyCode].isKeyDown && !keyInputs[KeyCode].previousKeyDown;
}

bool Input::GetKeyUp(int KeyCode)
{
    return !keyInputs[KeyCode].isKeyDown && keyInputs[KeyCode].previousKeyDown;
}
