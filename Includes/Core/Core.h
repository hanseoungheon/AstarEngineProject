#pragma once
#pragma warning(disable: 4251) //DLL �ܺη� ���ø� ������ �� �߻��ϴ� ��� ����
#pragma warning(disable: 4172) //���������� �ּҸ� ��ȯ�� �� �߻��ϴ� ��� ����


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#if BuildEngindDLL

#define Engine_API __declspec(dllexport)//true�� dll�� �ܺη� �����Ѵٴ� Ű����
#else
#define Engine_API __declspec(dllimport) // else�� dll�� ����Ʈ��Ű�ڴٴ� �Ҹ�.
#endif

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif


//�޸� ���� �Լ�.
template<typename T>
void SafeDelete(T*& pointer)
{
	if (pointer != nullptr)
	{
		delete pointer;
		pointer = nullptr;
	}

}

//�迭 �޸� ���� �Լ�.
template<typename T>
void SafeDeleteArray(T*& arrayStartPoint)
{
	if (arrayStartPoint != nullptr)
	{
		delete[] arrayStartPoint;
		arrayStartPoint = nullptr;
	}
}