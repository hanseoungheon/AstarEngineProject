#pragma once
#include "Actor/UI.h";

class Color_UI : public UI
{
	RTTI_DECLARATIONS(Color_UI,UI)

public:
	Color_UI(const char* text = "NoneColor",Color color = Color::Idensity,
		const Vector2& position = Vector2::Zero, char NameTag = 'D');

	virtual void Tick(float DeltaTime) override;

	void SetActiveColor(bool IsActiveColor);
private:
	bool IsActiveColor = false;
};