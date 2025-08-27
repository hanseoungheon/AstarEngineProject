#pragma once
#include "Actor/Actor.h"

class TestActor : public Actor
{
	RTTI_DECLARATIONS(TestActor,Actor)

public:
	TestActor(Vector2& position);
	~TestActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
};