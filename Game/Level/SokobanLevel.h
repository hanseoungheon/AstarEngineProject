#pragma once
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"
#include <vector>

class SokobanLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)

public:
	SokobanLevel();

	virtual bool CanPlayerMove(
		const Vector2& playerPosition,
		const Vector2& newPosition) override;

private:
	virtual void Render() override;
	void ReadMapFile(const char* fileName);

	bool CheckGameClear();

public:
	//Getter
	std::vector<std::vector<char>> GetMapGrid() const
	{
		return MapGrid;
	}

private:
	int targetScore = 0;
	bool isGameClear = false;
	std::vector<std::vector<char>> MapGrid;
	std::vector<char> MapBuffer;
};