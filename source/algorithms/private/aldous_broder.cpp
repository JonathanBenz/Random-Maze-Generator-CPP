#include "../public/aldous_broder.h"
#include "../../grid/public/grid.h"
#include "../../grid/public/cell.h"
#include "../../utils.h"
#include <vector>

void AldousBroder::GenerateMaze(Grid& grid)
{
	ResetAllCells(grid);
	ApplyAlgorithm(grid, nullptr);
}

void AldousBroder::ApplyAlgorithm(Grid& grid, Cell* _cell)
{
	Cell* cell = grid.GetRandomCell();
	int unvisited = grid.GetSize() - 1;

	while (unvisited > 0)
	{
		Cell* neighbor = Utils::Sample(cell->GetNeighbors());

		if (neighbor->GetLinks().empty())
		{
			cell->Link(neighbor);
			unvisited -= 1;
		}

		cell = neighbor;
	}
}