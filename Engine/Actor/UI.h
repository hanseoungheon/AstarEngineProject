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

	//��ü �����ֱ�(LifeTime)�� 1���� ȣ��� (�ʱ�ȭ�� ������)
	virtual void BeginPlay();

	//������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�)
	virtual void Tick(float deltaTime);

	//�׸��� �Լ�
	virtual void Render();

	// BeginPlay ȣ�⿩�� Ȯ��.
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	//��ü ���� �Լ�
	void Destroy();


public:
	//Getter & Setter
	Vector2 GetActorPosition() const;
	void SetActorPosition(const Vector2& newPosition);

	//���ڿ� ���� ��ȯ
	int GetWidth() const;

	//���ʽ� ����
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
	//��ü�� ��ġ
	Vector2 position;

	//�׸� ��
	char* image = nullptr;
	//���Ͽ� �̹���.
	char* returnImage = nullptr;

	//���ڿ� ����
	int width = 0;


	//�ؽ�Ʈ ����
	Color color;

	//BeginPlay ȣ���� �Ǿ����� Ȯ��
	bool hasBeganPlay = false;

	// ���� ����
	unsigned int sortingOrder = 0;

	// ���Ͱ� Ȱ�� ����
	bool isActiveUI = true;

	//���� ��û�ƴ��� �˷��ִ� ����
	bool isExpiredUI = false;

	//���� ����.
	Level* Owner = nullptr;

	static bool IsTrigged;

	char NameTag = ' ';

};