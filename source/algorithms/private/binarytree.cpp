#include "../public/binarytree.h"
#include "../../grid/public/grid.h"
#include "../../grid/public/cell.h"
#include "../../utils.h"
#include <vector>

void BinaryTreeStrategy::GenerateMaze(Grid& grid)
{
	ResetAllCells(grid);
	grid.EachCell([this](Grid& grid, Cell* cell) // Pass lambda (internally a functor) as argument
		{
			ApplyAlgorithm(grid, cell);
		});
}

void BinaryTreeStrategy::ApplyAlgorithm(Grid& grid, Cell* cell)
{
	if (!cell) return;

	// Try to get the North and East cell neighbors
	std::vector<Cell*> neighbors;
	if (cell->GetNorthNeighbor()) neighbors.push_back(cell->GetNorthNeighbor());
	if (cell->GetEastNeighbor()) neighbors.push_back(cell->GetEastNeighbor());

	// Randomly choose to link one of the neighbors if possible
	if (neighbors.empty()) return;
	Cell* neighbor = neighbors.at((Utils::BoundedRand(neighbors.size())));
	if (neighbor) cell->Link(neighbor);
}