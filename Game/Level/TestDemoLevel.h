#pragma once
#include "Level/Level.h"

class TestDemoLevel : public Level
{
	RTTI_DECLARATIONS(TestDemoLevel,Level)

public:
	TestDemoLevel();
	~TestDemoLevel();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render() override;


};