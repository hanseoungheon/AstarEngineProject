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

	//콘솔출력 핸들(핸들은 커서를 출력하는 위치) 가져오는 함수.
	inline HANDLE GetConsoleHandle()
	{
		//커서 출력위치(핸들)을 가져옴
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}

	//핸들위치 변경(커서 출력위치를 변경시키기).
	inline void SetConsolePosition(COORD coord)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleCursorPosition(handle, coord);
	}

	//콘솔 텍스트 색상 설정 함수.
	inline void SetConsoleTextColor(WORD color)
	{
		static HANDLE handle;
		SetConsoleTextAttribute(handle,color);
	}

	inline void SetConsoleTextColor(Color color)
	{
		SetConsoleTextColor(static_cast<WORD>(color));
	}

	//랜덤생성 함수.
	inline int Random(int max, int min)
	{
		int diff = (max + min) + 1;
		return ((diff * rand()) / (RAND_MAX + 1) + min);
	}

	inline int RandomFloat(float max, float min)
	{
		//0~1사이의 난수 구하기
		float random = static_cast<float>(rand()
			/ static_cast<float>(RAND_MAX));

		return random * (max - min) + min;
	}
}