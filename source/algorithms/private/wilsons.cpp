#include "../public/wilsons.h"
#include "../../grid/public/grid.h"
#include "../../grid/public/cell.h"
#include "../../utils.h"
#include <vector>
#include <set>

void Wilsons::GenerateMaze(Grid& grid)
{
	ResetAllCells(grid);
	ApplyAlgorithm(grid, nullptr);
}

void Wilsons::ApplyAlgorithm(Grid& grid, Cell* _cell)
{
	// Initialize starting phase. Get a random cell and mark it as visited, while the rest are unvisited. 
	std::set<Cell*> unvisited;

	grid.EachCell([&](Grid& grid, Cell* cell) { unvisited.insert(cell); });

	Cell* first = Utils::Sample(unvisited);
	unvisited.erase(first);

	// Perform algorithm until all cells are finally visited.
	while (!unvisited.empty())
	{
		Cell* cell = Utils::Sample(unvisited);
		std::vector<Cell*> path = { cell };

		// Start loop-erased random walk until reaching a visited cell
		while (unvisited.find(cell) != unvisited.end())
		{
			cell = Utils::Sample(cell->GetNeighbors());
			int position = Utils::GetIndex(path, cell);

			// If the cell has already been visited before (e.g., it is already in the path), 
			// then perform a loop-erase by truncating path to what it was before the loop. 
			if (position != -1) 
				path = std::vector<Cell*>(path.begin(), path.begin() + position + 1);
			
			else path.push_back(cell);
		}

		// When reaching a visited cell, link the paths together and then mark those cells as visited. 
		for (size_t i = 0; i + 1 < path.size(); i++)
		{
			path.at(i)->Link(path.at(i + 1));
			unvisited.erase(path.at(i));
		}
	}
}