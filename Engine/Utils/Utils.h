#pragma once
#include <Windows.h>
#include "Math/Vector2.h"
#include "Math/Color.h"

namespace Utils
{
	template<typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	//�ܼ���� �ڵ�(�ڵ��� Ŀ���� ����ϴ� ��ġ) �������� �Լ�.
	inline HANDLE GetConsoleHandle()
	{
		//Ŀ�� �����ġ(�ڵ�)�� ������
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}

	//�ڵ���ġ ����(Ŀ�� �����ġ�� �����Ű��).
	inline void SetConsolePosition(COORD coord)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleCursorPosition(handle, coord);
	}

	//�ܼ� �ؽ�Ʈ ���� ���� �Լ�.
	inline void SetConsoleTextColor(WORD color)
	{
		static HANDLE handle;
		SetConsoleTextAttribute(handle,color);
	}

	inline void SetConsoleTextColor(Color color)
	{
		SetConsoleTextColor(static_cast<WORD>(color));
	}

	//�������� �Լ�.
	inline int Random(int max, int min)
	{
		int diff = (max + min) + 1;
		return ((diff * rand()) / (RAND_MAX + 1) + min);
	}

	inline int RandomFloat(float max, float min)
	{
		//0~1������ ���� ���ϱ�
		float random = static_cast<float>(rand()
			/ static_cast<float>(RAND_MAX));

		return random * (max - min) + min;
	}
}