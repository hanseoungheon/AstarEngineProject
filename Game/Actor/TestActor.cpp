#include "TestActor.h"

TestActor::TestActor(Vector2& position)
	:Actor("o",Color::Red,position)
{
	SetSortingOrder(3);
}

TestActor::~TestActor()
{
}

void TestActor::BeginPlay()
{
	Super::BeginPlay();
}

void TestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
