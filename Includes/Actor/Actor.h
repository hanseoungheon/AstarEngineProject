#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <Windows.h>

//정방선언.
class Level;

class Engine_API Actor : public RTTI
{
	friend class Level;

	RTTI_DECLARATIONS(Actor,RTTI)
public:
	Actor(const char* image = " ",Color color = Color::White, 
		const Vector2& position = Vector2::Zero);
	virtual ~Actor();

public: //이벤트 함수들.
	//객체의 생애주기에 1번만 호출되는 함수.(변수 초기화용)
	virtual void BeginPlay();
	
	//프레임마다 호출하는 Tick 함수(DeltaTime = 1/Frame)
	virtual void Tick(float DeltaTime = 0.0f);

	//렌더링 함수.
	void Render();

	//Begine함수 호출 확인.
	inline bool HasBeginPlay() const
	{
		return hasbeginPlay;
	}

	//충돌 확인 요청 함수 (AABB로직)
	bool TestIntersect(const Actor* const other);

	//객체 삭제 함수
	void Destroy();

	//게임 종료 요청
	void QuitGame();

public:
	//Getter&Setter
	//위치 설정. 위치 
	void SetActorPosition(const Vector2& newPosition);
	Vector2 GetActorPosition() const;

	//문자열 길이 반환.
	int GetWidth() const;

	//Sorting Order 설정.
	void SetSortingOrder(unsigned int sortingOrder);

	void SetOwner(Level* newOwner);
	Level* GetOwner();
	
protected:
	Vector2 position;

	//그릴 문자열.
	char* image = nullptr;

	//문자열의 길이.
	int width = 0;

	//텍스트 색상값.
	Color color;

	//Play되어있는지 확인.
	bool hasbeginPlay = false;

	//정렬 순서.
	unsigned int sortingOrder = 0;

	//액터가 활성상태인지 체크하는 변수.
	bool isActive = true;

	//삭제 요청되었는지 확인하는 변수.
	bool isExpired = false;
	
	//액터를 소유하고 있는 레벨.
	Level* Owner = nullptr;
};