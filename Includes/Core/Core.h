#pragma once
#pragma warning(disable: 4251) //DLL �ܺη� ���ø� ������ �� �߻��ϴ� ��� ����
#pragma warning(disable: 4172) //���������� �ּҸ� ��ȯ�� �� �߻��ϴ� ��� ����

#if BuildEngindDLL

#define Engine_API __declspec(dllexport)//true�� dll�� �ܺη� �����Ѵٴ� Ű����
#else
#define Engine_API __declspec(dllimport) // else�� dll�� ����Ʈ��Ű�ڴٴ� �Ҹ�.
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