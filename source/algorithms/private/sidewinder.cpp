#include "../public/sidewinder.h"
#include "../../grid/public/grid.h"
#include "../../grid/public/cell.h"
#include "../../utils.h"
#include <vector>

void SidewinderStrategy::GenerateMaze(Grid& grid)
{
	ResetAllCells(grid);
	grid.EachRow([this](Grid& grid, Cell* cell)
		{
			ApplyAlgorithm(grid, cell);
		});
}

void SidewinderStrategy::ApplyAlgorithm(Grid& grid, Cell* cell)
{
	std::vector<Cell*> run;
	std::vector<Cell*> currentRow = grid.GetCellRow(cell->GetRow());

	for (Cell* cell : currentRow)
	{
		run.push_back(cell);

		bool bAtEasternBoundary = !cell->GetEastNeighbor();
		bool bAtNorthernBoundary = !cell->GetNorthNeighbor();

		bool bShouldCloseOut = bAtEasternBoundary ||
			(!bAtNorthernBoundary && Utils::FlipCoin());

		if (bShouldCloseOut)
		{
			Cell* member = Utils::Sample(run);
			if (member->GetNorthNeighbor()) member->Link(member->GetNorthNeighbor());
			run.clear();
		}

		else cell->Link(cell->GetEastNeighbor());
	}
}