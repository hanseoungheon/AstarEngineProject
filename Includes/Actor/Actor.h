#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <Windows.h>

//���漱��.
class Level;

class Engine_API Actor : public RTTI
{
	friend class Level;

	RTTI_DECLARATIONS(Actor,RTTI)
public:
	Actor(const char* image = " ",Color color = Color::White, 
		const Vector2& position = Vector2::Zero);
	virtual ~Actor();

public: //�̺�Ʈ �Լ���.
	//��ü�� �����ֱ⿡ 1���� ȣ��Ǵ� �Լ�.(���� �ʱ�ȭ��)
	virtual void BeginPlay();
	
	//�����Ӹ��� ȣ���ϴ� Tick �Լ�(DeltaTime = 1/Frame)
	virtual void Tick(float DeltaTime = 0.0f);

	//������ �Լ�.
	void Render();

	//Begine�Լ� ȣ�� Ȯ��.
	inline bool HasBeginPlay() const
	{
		return hasbeginPlay;
	}

	//�浹 Ȯ�� ��û �Լ� (AABB����)
	bool TestIntersect(const Actor* const other);

	//��ü ���� �Լ�
	void Destroy();

	//���� ���� ��û
	void QuitGame();

public:
	//Getter&Setter
	//��ġ ����. ��ġ 
	void SetActorPosition(const Vector2& newPosition);
	Vector2 GetActorPosition() const;

	//���ڿ� ���� ��ȯ.
	int GetWidth() const;

	//Sorting Order ����.
	void SetSortingOrder(unsigned int sortingOrder);

	void SetOwner(Level* newOwner);
	Level* GetOwner();
	
protected:
	Vector2 position;

	//�׸� ���ڿ�.
	char* image = nullptr;

	//���ڿ��� ����.
	int width = 0;

	//�ؽ�Ʈ ����.
	Color color;

	//Play�Ǿ��ִ��� Ȯ��.
	bool hasbeginPlay = false;

	//���� ����.
	unsigned int sortingOrder = 0;

	//���Ͱ� Ȱ���������� üũ�ϴ� ����.
	bool isActive = true;

	//���� ��û�Ǿ����� Ȯ���ϴ� ����.
	bool isExpired = false;
	
	//���͸� �����ϰ� �ִ� ����.
	Level* Owner = nullptr;
};