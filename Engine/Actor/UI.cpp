#include "UI.h"
#include <Windows.h>
#include "Engine.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

bool UI::IsTrigged = false;

UI::UI(const char* image, Color color, const Vector2& position, char Tag)
    : color(color), position(position), NameTag(Tag)
{
    //���ڿ��� ���� ���ϱ�.
    width = (int)strlen(image);

    //�޸� ���� �Ҵ�.
    this->image = new char[width + 1];

    //���ڷ� ���� ���ڿ��� image����������.
    strcpy_s(this->image, width + 1, image);
}

UI::~UI()
{
    SafeDeleteArray(image);
    SafeDeleteArray(returnImage);
}

void UI::BeginPlay()
{
	hasBeganPlay = true;
}

void UI::Tick(float DeltaTime)
{

}

void UI::Render()
{
    Utils::SetConsolePosition(position);

    Utils::SetConsoleTextColor(static_cast<WORD>(color));

    std::cout << image;
}

void UI::Destroy()
{
    //���� ��û �Ϸ�.
    isExpiredUI = true;

    //������ ������û.
    Owner->DestroyUI(this);
}



Vector2 UI::GetActorPosition() const
{
    return position;
}
void UI::SetActorPosition(const Vector2& newPosition)
{
    position = newPosition;
}

//���ڿ� ���� ��ȯ
int UI::GetWidth() const
{
    return width;
}

Level* UI::GetOwner()
{
    return Owner;
}
//���ʽ� ����
void UI::SetOwner(Level* newOwner)
{
    Owner = newOwner;
}


char* UI::GetImage()
{
    size_t length = width;
    returnImage = new char[length + 1];

    strcpy_s(returnImage, length + 1, image);
    return returnImage;
}

void UI::SetImage(const char* newImage)
{
    size_t length = strlen(newImage) + 1;

    if (image != nullptr)
        image = nullptr;

    image = new char[length];

    strcpy_s(image, length, newImage);
}

void UI::SetColor(Color newcolor)
{
    color = newcolor;
}

void UI::SetNameTag(char newTag)
{
    NameTag = newTag;
}

char UI::GetNameTag()
{
    return NameTag;
}

void UI::SetTrigger(bool Trigger)
{
    IsTrigged = Trigger;

}

bool UI::GetTrigger()
{
    return IsTrigged;
}
