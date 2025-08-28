#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <Windows.h>
#include <iostream>

//정방선언.
class Level;

class Engine_API Actor : public RTTI
{
	friend class Level;

	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor(const char* image = " ", Color color = Color::White,
		const Vector2& position = Vector2::Zero,char Tag = 'D');
	virtual ~Actor();

	//이벤트 함수

	//객체 생애주기(LifeTime)에 1번만 호출됨 (초기화가 목적임)
	virtual void BeginPlay();

	//프레임 마다 호출 (반복성 작업/지속성이 필요한 작업)
	virtual void Tick(float deltaTime);

	//그리기 함수
	virtual void Render();

	// BeginPlay 호출여부 확인.
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	void SetActorPosition(const Vector2& newPosition);
	Vector2 GetActorPosition() const;

	//문자열 길이 반환
	int GetWidth() const;

	//Sorting Order 설정
	void SetSortingOrder(unsigned int sortingOrder);

	//오너십 결정
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	//충돌 확인 요청 함수 (AABB로직)
	bool TestIntersect(const Actor* const other);

	//객체 삭제 함수
	void Destroy();

	//게임 종료 요청
	void QuitGame();

	char* GetImage();

	void SetImage(const char* newImage);

	void SetColor(Color newcolor);

	Actor* GetOriginalActor();
	void SetOriginalActorImage(const char* newImage);
	void SetOriginalActorColor(Color newColor);
	void SetOriginalActor(Actor* orininalActor);

	void SetNameTag(char newTag);
	char GetNameTag();

	void SetTrigger(bool Trigger);
	bool GetTrigger();
protected:
	//개체의 위치
	Vector2 position;

	//그릴 값
	char* image = nullptr;
	//리턴용 이미지.
	char* returnImage = nullptr;

	//문자열 길이
	int width = 0;


	//텍스트 색상값
	Color color;

	//BeginPlay 호출이 되었는지 확인
	bool hasBeganPlay = false;

	// 정렬 순서
	unsigned int sortingOrder = 0;

	// 액터가 활성 상태
	bool isActive = true;

	//삭제 요청됐는지 알려주는 변수
	bool isExpired = false;

	//만약이것이 복사된 액터이면 원본엑터를 참조해야함.
	Actor* OriginalActor = nullptr;

	//소유 레벨.
	Level* Owner = nullptr;

	static bool IsTrigged;

	char NameTag = ' ';
};