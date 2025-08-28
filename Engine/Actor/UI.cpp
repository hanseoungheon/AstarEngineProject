#include "UI.h"
#include <Windows.h>
#include "Engine.h"
#include "Level/Level.h"
#include "Utils/Utils.h"

bool UI::IsTrigged = false;

UI::UI(const char* image, Color color, const Vector2& position, char Tag)
    : color(color), position(position), NameTag(Tag)
{
    //문자열의 길이 구하기.
    width = (int)strlen(image);

    //메모리 동적 할당.
    this->image = new char[width + 1];

    //인자로 받은 문자열을 image변수에복사.
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
    //삭제 요청 완료.
    isExpiredUI = true;

    //레벨에 삭제요청.
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

//문자열 길이 반환
int UI::GetWidth() const
{
    return width;
}

Level* UI::GetOwner()
{
    return Owner;
}
//오너십 결정
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
