#pragma once
#include "Actor/Actor.h"

class Target : public Actor
{
	RTTI_DECLARATIONS(Target,Actor)

public:
	Target(const Vector2& position);

	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime) override;

private:
	class ICanPlayerMove* canPlayerMoveInterface = nullptr;
};