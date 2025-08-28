#pragma once
#include "Actor/UI.h"

class Custom_UI : public UI
{
	RTTI_DECLARATIONS(Custom_UI,UI)

public:
	Custom_UI(const char* text = "NULL", Color color = Color::White, 
		const Vector2& position = Vector2::Zero);

private:
};