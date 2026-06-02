#pragma once
#include "imazealgorithms.h"

class RecursiveBacktracker : public IMazeAlgorithm
{
	void GenerateMaze(Grid& grid) override;
	void ApplyAlgorithm(Grid& grid, Cell* cell) override;
};