#pragma once
#include "../public/imazealgorithms.h"

class SidewinderStrategy : public IMazeAlgorithm
{
public:
	virtual void GenerateMaze(Grid& grid) override;
	virtual void ApplyAlgorithm(Grid& grid, Cell* cell) override;
};