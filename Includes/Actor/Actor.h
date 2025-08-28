#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <Windows.h>
#include <iostream>

//���漱��.
class Level;

class Engine_API Actor : public RTTI
{
	friend class Level;

	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor(const char* image = " ", Color color = Color::White,
		const Vector2& position = Vector2::Zero,char Tag = 'D');
	virtual ~Actor();

	//�̺�Ʈ �Լ�

	//��ü �����ֱ�(LifeTime)�� 1���� ȣ��� (�ʱ�ȭ�� ������)
	virtual void BeginPlay();

	//������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�)
	virtual void Tick(float deltaTime);

	//�׸��� �Լ�
	virtual void Render();

	// BeginPlay ȣ�⿩�� Ȯ��.
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	void SetActorPosition(const Vector2& newPosition);
	Vector2 GetActorPosition() const;

	//���ڿ� ���� ��ȯ
	int GetWidth() const;

	//Sorting Order ����
	void SetSortingOrder(unsigned int sortingOrder);

	//���ʽ� ����
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	//�浹 Ȯ�� ��û �Լ� (AABB����)
	bool TestIntersect(const Actor* const other);

	//��ü ���� �Լ�
	void Destroy();

	//���� ���� ��û
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
	bool isActive = true;

	//���� ��û�ƴ��� �˷��ִ� ����
	bool isExpired = false;

	//�����̰��� ����� �����̸� �������͸� �����ؾ���.
	Actor* OriginalActor = nullptr;

	//���� ����.
	Level* Owner = nullptr;

	static bool IsTrigged;

	char NameTag = ' ';
};