#pragma once
#include "imazealgorithms.h"

class HuntAndKill : public IMazeAlgorithm
{
	void GenerateMaze(Grid& grid) override;
	void ApplyAlgorithm(Grid& grid, Cell* cell) override;
};