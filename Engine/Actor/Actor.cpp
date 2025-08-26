#include "Actor.h"
#include <Windows.h>
#include <iostream>
#include "Engine.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

Actor::Actor(const char* image, Color color, const Vector2& position)
    :color(color),position(position)
{
    //문자열의 길이 구하기.
    width = (int)strlen(image);

    //메모리 동적 할당.
    this->image = new char[width + 1];

    //인자로 받은 문자열을 image변수에복사.
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
    //AABB로직.

    //이 액터의 X,Y좌표
    int xMin = position.x;
    int xMax = position.x + width - 1; //널문자 빼기.

    int otherxMin = other->position.x;
    int otherxMax = other->position.x + other->width - 1;

    //조건 확인.
    if (otherxMin > xMax)
    {
        return false;
    }

    if (otherxMax < xMin)
    {
        return false;
    }

    //위치가 같은지 최종 확인.
    return position.y == other->position.y;
}

void Actor::Destroy()
{
    //삭제 요청 완료.
    isExpired = true;
    
    //레벨에 삭제요청.
    Owner->DestroyActor(this);
}

void Actor::QuitGame()
{
    //엔진 싱글톤 함수로 엔진 불러 온 후 Quit함수 실행.
    Engine::Get().Quit();
}

void Actor::SetPosition(const Vector2& newPosition)
{
    //예외처리 (화면 벗어났는지 확인).

//왼쪽 가장 자리가 화면 왼쪽을 벗어났는지.
    if (newPosition.x < 0)
    {
        return;
    }

    // 오른쪽 가장자리가 화면 오른쪽을 벗어났는지.
    if (newPosition.x + width - 1 > Engine::Get().GetWidth())
    {
        return;
    }

    //위쪽 가장자리가 화면의 위를 벗어났는지
    if (newPosition.y < 0)
    {
        return;
    }

    //화면 아래를 벗어났는지
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
