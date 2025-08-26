#pragma once
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"
class SokobanLevel : public Level, public ICanPlayerMove
{
public:
	SokobanLevel();

	virtual bool CanPlayerMove(
		const Vector2& playerPosition,
		const Vector2& newPosition) override;

private:
	virtual void Render() override;
	void ReadMapFile(const char* fileName);

	bool CheckGameClear();

private:
	int targetScore = 0;
	bool isGameClear = false;
};