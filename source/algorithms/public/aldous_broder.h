#pragma once
#include "imazealgorithms.h"

class AldousBroder : public IMazeAlgorithm
{
public:
	void GenerateMaze(Grid& grid) override;
	void ApplyAlgorithm(Grid& grid, Cell* cell) override;
};