#pragma once
#pragma warning(disable: 4251) //DLL 외부로 템플릿 내보낼 때 발생하는 경고 끄기
#pragma warning(disable: 4172) //지역변수의 주소를 반환할 때 발생하는 경고 끄기

#if BuildEngindDLL

#define Engine_API __declspec(dllexport)//true면 dll를 외부로 방출한다는 키워드
#else
#define Engine_API __declspec(dllimport) // else면 dll을 임포트시키겠다는 소리.
#endif


//메모리 해제 함수.
template<typename T>
void SafeDelete(T*& pointer)
{
	if (pointer != nullptr)
	{
		delete pointer;
		pointer = nullptr;
	}

}

//배열 메모리 해제 함수.
template<typename T>
void SafeDeleteArray(T*& arrayStartPoint)
{
	if (arrayStartPoint != nullptr)
	{
		delete[] arrayStartPoint;
		arrayStartPoint = nullptr;
	}
}