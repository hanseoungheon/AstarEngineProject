#include "Actor.h"
#include <Windows.h>
#include <iostream>
#include "Engine.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

Actor::Actor(const char* image, Color color, const Vector2& position)
    :color(color),position(position)
{
    //���ڿ��� ���� ���ϱ�.
    width = (int)strlen(image);

    //�޸� ���� �Ҵ�.
    this->image = new char[width + 1];

    //���ڷ� ���� ���ڿ��� image����������.
    strcpy_s(this->image, width + 1, image);

}

Actor::~Actor()
{
    SafeDeleteArray(image);
}

void Actor::BeginPlay()
{
    hasbeginPlay = true;
}

void Actor::Tick(float DeltaTime)
{
}

void Actor::Render()
{
    Utils::SetConsolePosition(position);

    Utils::SetConsoleTextColor(color);

    std::cout << image;
}

bool Actor::TestIntersect(const Actor* const other)
{
    //AABB����.

    //�� ������ X,Y��ǥ
    int xMin = position.x;
    int xMax = position.x + width - 1; //�ι��� ����.

    int otherxMin = other->position.x;
    int otherxMax = other->position.x + other->width - 1;

    //���� Ȯ��.
    if (otherxMin > xMax)
    {
        return false;
    }

    if (otherxMax < xMin)
    {
        return false;
    }

    //��ġ�� ������ ���� Ȯ��.
    return position.y == other->position.y;
}

void Actor::Destroy()
{
    //���� ��û �Ϸ�.
    isExpired = true;
    
    //������ ������û.
    Owner->DestroyActor(this);
}

void Actor::QuitGame()
{
    //���� �̱��� �Լ��� ���� �ҷ� �� �� Quit�Լ� ����.
    Engine::Get().Quit();
}

void Actor::SetPosition(const Vector2& newPosition)
{
    //����ó�� (ȭ�� ������� Ȯ��).

//���� ���� �ڸ��� ȭ�� ������ �������.
    if (newPosition.x < 0)
    {
        return;
    }

    // ������ �����ڸ��� ȭ�� �������� �������.
    if (newPosition.x + width - 1 > Engine::Get().GetWidth())
    {
        return;
    }

    //���� �����ڸ��� ȭ���� ���� �������
    if (newPosition.y < 0)
    {
        return;
    }

    //ȭ�� �Ʒ��� �������
    if (newPosition.y - 1 > Engine::Get().Height())
    {
        return;
    }

    if (position == newPosition)
    {
        return;
    }
}

Vector2 Actor::GetPosition() const
{
    return Vector2();
}

int Actor::GetWidth() const
{
    return 0;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
}

void Actor::SetOwner(Level* newOwner)
{
}

Level* Actor::GetOwner()
{
    return nullptr;
}
