#pragma once
#include "Actor/Actor.h"

class Custom_UI : public Actor
{
	RTTI_DECLARATIONS(Custom_UI,Actor)

public:
	Custom_UI(const char* text = "NULL", Color color = Color::White, 
		const Vector2& position = Vector2::Zero);

private:
};