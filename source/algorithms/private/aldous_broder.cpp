#include "../public/aldous_broder.h"
#include "../public/binarytreestrategy.h"
#include "../../grid/public/grid.h"
#include "../../grid/public/cell.h"
#include "../../utils.h"
#include <vector>

void AldousBroder::GenerateMaze(Grid& grid)
{
	ResetAllCells(grid);
	ApplyAlgorithm(grid, nullptr);
}

void AldousBroder::ApplyAlgorithm(Grid& grid, Cell* cell)
{
	Cell* _cell = grid.GetRandomCell();
	int unvisited = grid.GetSize() - 1;

	while (unvisited > 0)
	{
		Cell* neighbor = Utils::Sample(_cell->GetNeighbors());

		if (neighbor->GetLinks().empty())
		{
			_cell->Link(neighbor);
			unvisited -= 1;
		}

		_cell = neighbor;
	}
}