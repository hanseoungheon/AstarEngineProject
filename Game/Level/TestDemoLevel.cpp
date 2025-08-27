#include "TestDemoLevel.h"
#include "Actor/TestActor.h"
TestDemoLevel::TestDemoLevel()
{
	Vector2 position = Vector2(2,0);
	AddActor(new TestActor(position));
}

TestDemoLevel::~TestDemoLevel()
{

}

void TestDemoLevel::BeginPlay()
{
	Super::BeginPlay();
}

void TestDemoLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void TestDemoLevel::Render()
{
	Super::Render();
}
