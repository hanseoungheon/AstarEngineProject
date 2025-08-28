#include "Actor.h"
#include <Windows.h>
#include "Engine.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

bool Actor::IsTrigged = false;

Actor::Actor(const char* image, Color color, const Vector2& position,char Tag)
    :color(color),position(position),NameTag(Tag)
{
    //���ڿ��� ���� ���ϱ�.
    width = (int)strlen(image);

    //�޸� ���� �Ҵ�.
    this->image = new char[width + 1];

    //���ڷ� ���� ���ڿ��� image����������.
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

void Actor::SetActorPosition(const Vector2& newPosition)
{
    //����ó�� (ȭ�� ������� Ȯ��).

//���� ���� �ڸ��� ȭ�� ������ �������.
    if (newPosition.x < 0)
    {
        return;
    }

    // ������ �����ڸ��� ȭ�� �������� �������.
    if (newPosition.x + width - 1 > Engine::Get().ConsoleWidth())
    {
        return;
    }

    //���� �����ڸ��� ȭ���� ���� �������
    if (newPosition.y < 0)
    {
        return;
    }

    //ȭ�� �Ʒ��� �������
    if (newPosition.y - 1 > Engine::Get().ConsoleHeight())
    {
        return;
    }

    if (position == newPosition)
    {
        return;
    }

    //���� ��ġ Ȯ���ϱ�. 
    Vector2 direction = newPosition - position; //�� ��ġ - ������ġ = ���⺤��.

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
