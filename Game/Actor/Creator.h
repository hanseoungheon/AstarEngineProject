#pragma once
#include "Actor/Actor.h"

class Creator : public Actor
{
	RTTI_DECLARATIONS(Creator,Actor)

public:
	Creator(Vector2& position);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	void CreatePlayer();

	void CreateTarget();

	void CreateWall();

private:
	class ICanPlayerMove* canPlayerMoveInterface = nullptr;
};