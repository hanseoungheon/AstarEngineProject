#include "Input.h"
#include <Windows.h>
//�̱��� ����.
Input* Input::instance = nullptr;

Input::Input()
{
    //�̱��� ����(�� �ϳ����� ��ü���� �����Ѵٴ� ��)
    instance = this;
}

Input& Input::Get()
{
    return *instance;
}

void Input::ProcessInput()
{
    //Ű �Է� Ȯ��!
    for (int i = 0; i < 255; ++i)
    {
        keyInputs[i].isKeyDown =
            GetAsyncKeyState(i) && 0x8000;
    }
}

void Input::SavePreviouseKeyStates()
{
    //���� �������� �Է��� ����ϱ�.
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
