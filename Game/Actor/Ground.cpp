#include "Ground.h"
#include "Input.h"

Ground::Ground(const Vector2& position)
	:Actor(".",Color::White, position,'R')
{
	SetSortingOrder(0);
}

void Ground::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (Input::GetController().GetKeyDown(VK_RETURN))
	//{
	//	SetImage("T");
	//	SetColor(Color::Blue);
	//}
}

//void Ground::Render()
//{
//	Super::Render();
//
//	if (IsTrigged == true)
//	{
//		color = Color::Green;
//		SetImage("+");
//	}
//}

