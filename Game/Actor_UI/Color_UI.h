#pragma once
#include "Actor/Actor.h"

class Color_UI : public Actor
{
	RTTI_DECLARATIONS(Color_UI,Actor)

public:
	Color_UI(const char* text = "NoneColor",Color color = Color::Idensity,
		const Vector2& position = Vector2::Zero, char NameTag = 'D');

	virtual void Tick(float DeltaTime) override;

	void SetActiveColor(bool IsActiveColor);
private:
	bool IsActiveColor = false;
};