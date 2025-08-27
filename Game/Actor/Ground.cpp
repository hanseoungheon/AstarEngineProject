#include "Ground.h"
#include "Input.h"

Ground::Ground(const Vector2& position)
	:Actor(".",Color::White, position)
{
	SetSortingOrder(0);
}

void Ground::Tick(float DeltaTime)
{
	if (Input::GetController().GetKeyDown(VK_RETURN))
	{
		SetImage("T");
		SetColor(Color::Blue);
	}
}

