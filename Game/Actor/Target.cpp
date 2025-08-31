#include "Target.h"
#include "Input.h"
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

Target::Target(const Vector2& position)
	:Actor("T", Color::Blue, position, 'G')
{
	SetSortingOrder(2);
}

void Target::BeginPlay()
{
	Super::BeginPlay();

	//인터페이스 얻어오기.
	if (GetOwner())
	{
		canPlayerMoveInterface =
			dynamic_cast<ICanPlayerMove*>(GetOwner());

		if (!canPlayerMoveInterface)
		{
			std::cout << "Can not cast owener level to ICanPlayerMove.\n";
		}
	}

}

void Target::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Input::GetController().GetKeyDown(VK_NUMPAD4) && GetOwner()->GetLevelTrigget() == true)
	{
		if (canPlayerMoveInterface->CanPlayerMove(GetActorPosition(),
			Vector2(GetActorPosition().x - 1, GetActorPosition().y)))
		{
			Vector2 currentPosition = GetActorPosition();
			currentPosition.x -= 1;
			SetActorPosition(currentPosition);
		}
	}

	if (Input::GetController().GetKeyDown(VK_NUMPAD6) && GetOwner()->GetLevelTrigget() == true)
	{
		if (canPlayerMoveInterface->CanPlayerMove(GetActorPosition(),
			Vector2(GetActorPosition().x + 1, GetActorPosition().y)))
		{
			Vector2 currentPosition = GetActorPosition();
			currentPosition.x += 1;
			SetActorPosition(currentPosition);
		}
	}

	if (Input::GetController().GetKeyDown(VK_NUMPAD8) && GetOwner()->GetLevelTrigget() == true)
	{
		if (canPlayerMoveInterface->CanPlayerMove(GetActorPosition(),
			Vector2(GetActorPosition().x, GetActorPosition().y - 1)))
		{
			Vector2 currentPosition = GetActorPosition();
			currentPosition.y -= 1;
			SetActorPosition(currentPosition);
		}
	}

	if (Input::GetController().GetKeyDown(VK_NUMPAD2) && GetOwner()->GetLevelTrigget() == true)
	{
		if (canPlayerMoveInterface->CanPlayerMove(GetActorPosition(),
			Vector2(GetActorPosition().x, GetActorPosition().y + 1)))
		{
			Vector2 currentPosition = GetActorPosition();
			currentPosition.y += 1;
			SetActorPosition(currentPosition);
		}
	}
}

