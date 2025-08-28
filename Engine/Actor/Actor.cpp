#include "Actor.h"
#include <Windows.h>
#include "Engine.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

bool Actor::IsTrigged = false;

Actor::Actor(const char* image, Color color, const Vector2& position,char Tag)
    :color(color),position(position),NameTag(Tag)
{
    //문자열의 길이 구하기.
    width = (int)strlen(image);

    //메모리 동적 할당.
    this->image = new char[width + 1];

    //인자로 받은 문자열을 image변수에복사.
    strcpy_s(this->image, width + 1, image);

    //IsTrigged = false;
}

Actor::~Actor()
{
    SafeDeleteArray(image);
    SafeDeleteArray(returnImage);
}

void Actor::BeginPlay()
{
    hasBeganPlay = true;
}

void Actor::Tick(float DeltaTime)
{
}

void Actor::Render()
{
    Utils::SetConsolePosition(position);

    Utils::SetConsoleTextColor(static_cast<WORD>(color));

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

void Actor::SetActorPosition(const Vector2& newPosition)
{
    //예외처리 (화면 벗어났는지 확인).

//왼쪽 가장 자리가 화면 왼쪽을 벗어났는지.
    if (newPosition.x < 0)
    {
        return;
    }

    // 오른쪽 가장자리가 화면 오른쪽을 벗어났는지.
    if (newPosition.x + width - 1 > Engine::Get().ConsoleWidth())
    {
        return;
    }

    //위쪽 가장자리가 화면의 위를 벗어났는지
    if (newPosition.y < 0)
    {
        return;
    }

    //화면 아래를 벗어났는지
    if (newPosition.y - 1 > Engine::Get().ConsoleHeight())
    {
        return;
    }

    if (position == newPosition)
    {
        return;
    }

    //지울 위치 확인하기. 
    Vector2 direction = newPosition - position; //갈 위치 - 현재위치 = 방향벡터.

    position.x = (direction.x >= 0) ? position.x : position.x + width - 1;

    Utils::SetConsolePosition(position);

    std::cout << ' ';

    position = newPosition;
}

Vector2 Actor::GetActorPosition() const
{
    return position;
}

int Actor::GetWidth() const
{
    return width;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
    this->sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
    Owner = newOwner;
}

Level* Actor::GetOwner()
{
    return Owner;
}

char* Actor::GetImage()
{
	size_t length = width;
	returnImage = new char[length + 1];

	strcpy_s(returnImage, length + 1, image);
	return returnImage;
}

void Actor::SetImage(const char* newImage)
{
	size_t length = strlen(newImage) + 1;

	if (image != nullptr)
		image = nullptr;

	image = new char[length];

	strcpy_s(image, length, newImage);
}

void Actor::SetColor(Color newColor)
{
    color = newColor;
}

Actor* Actor::GetOriginalActor()
{
    return OriginalActor;
}

void Actor::SetOriginalActorImage(const char* newImage)
{
    if (OriginalActor == nullptr)
    {
        return;
    }

    size_t length = strlen(newImage) + 1;
    
    if (OriginalActor->image != nullptr)
    {
        OriginalActor->image = nullptr;
    }

    OriginalActor->image = new char[length];

    strcpy_s(OriginalActor->image, length, newImage);
}

void Actor::SetOriginalActorColor(Color newColor)
{
    if (OriginalActor != nullptr)
    {
        OriginalActor->color = newColor;
    }
}

void Actor::SetOriginalActor(Actor* orininalActor)
{
    OriginalActor = orininalActor;
}

void Actor::SetNameTag(char newTag)
{
    NameTag = newTag;
}

char Actor::GetNameTag()
{
    return NameTag;
}

void Actor::SetTrigger(bool Trigger)
{
    IsTrigged = Trigger;
}

bool Actor::GetTrigger()
{
    return IsTrigged;
}
