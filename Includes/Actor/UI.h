#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <Windows.h>
#include <iostream>

class Level;

class Engine_API UI : public RTTI
{
	friend class Level;

	RTTI_DECLARATIONS(UI, RTTI)

public:
	UI(const char* image = " ", Color color = Color::White,
		const Vector2& position = Vector2::Zero, char Tag = 'D');
	virtual ~UI();

	//객체 생애주기(LifeTime)에 1번만 호출됨 (초기화가 목적임)
	virtual void BeginPlay();

	//프레임 마다 호출 (반복성 작업/지속성이 필요한 작업)
	virtual void Tick(float deltaTime);

	//그리기 함수
	virtual void Render();

	// BeginPlay 호출여부 확인.
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	//객체 삭제 함수
	void Destroy();


public:
	//Getter & Setter
	Vector2 GetActorPosition() const;
	void SetActorPosition(const Vector2& newPosition);

	//문자열 길이 반환
	int GetWidth() const;

	//오너십 결정
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	char* GetImage();

	void SetImage(const char* newImage);

	void SetColor(Color newcolor);

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
	bool isActiveUI = true;

	//삭제 요청됐는지 알려주는 변수
	bool isExpiredUI = false;

	//소유 레벨.
	Level* Owner = nullptr;

	static bool IsTrigged;

	char NameTag = ' ';

};