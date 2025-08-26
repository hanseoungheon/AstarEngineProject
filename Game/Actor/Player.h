#pragma once
#include "Actor/Actor.h"

class Player : public Actor
{
	RTTI_DECLARATIONS(Player,Actor)

public:
	Player(const Vector2& position);

	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime)override;

private:
	class ICanPlayerMove* canPlayerMoveInterface = nullptr;
};