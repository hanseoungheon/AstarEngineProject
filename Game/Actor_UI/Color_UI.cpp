#include "Color_UI.h"

Color_UI::Color_UI(const char* text, Color color, const Vector2& position, char NameTag)
	:Actor(text,color,position,NameTag)
{
	SetSortingOrder(5);
}

void Color_UI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsActiveColor == false)
	{
		if (NameTag == 'P')
		{
			SetColor(Color::LightRed);
		}
		else if (NameTag == 'T')
		{
			SetColor(Color::Idensity);
		}
	}
	else
	{
		if (NameTag == 'P')
		{
			SetColor(Color::Idensity);
		}

		if (NameTag == 'T')
		{
			SetColor(Color::LightBlue);
		}
	}
}

void Color_UI::SetActiveColor(bool IsActiveColor)
{
	this->IsActiveColor = IsActiveColor;
}


