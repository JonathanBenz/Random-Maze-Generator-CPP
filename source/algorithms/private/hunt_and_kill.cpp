#include "../public/hunt_and_kill.h"
#include "../../grid/public/grid.h"
#include "../../grid/public/cell.h"
#include "../../utils.h"
#include <vector>

void HuntAndKill::GenerateMaze(Grid& grid)
{
	ResetAllCells(grid);
	ApplyAlgorithm(grid, nullptr);
}

void HuntAndKill::ApplyAlgorithm(Grid& grid, Cell* _cell)
{
	Cell* current = grid.GetRandomCell();

	while (current)
	{
		// Check for unvisited neighbors
		std::vector<Cell*> unvisitedNeighbors;
		unvisitedNeighbors.reserve(4);
		for (Cell* neighbor : current->GetNeighbors())
		{
			if (neighbor->GetLinks().empty()) 
				unvisitedNeighbors.push_back(neighbor);
		}
		
		// Link to random unvisited neighbor, if there are any
		if (!unvisitedNeighbors.empty())
		{
			Cell* neighbor = Utils::Sample(unvisitedNeighbors);
			current->Link(neighbor);
			current = neighbor;
		}

		// Else, find the first instance of an unvisited cell that has a neighbor which is a visited cell
		// e.g., the "Hunt" portion of this algorithm. 
		else
		{
			current = nullptr;
			grid.EachCell([&](Grid& grid, Cell* cell)
				{
					// If cell is already linked, then it is already visited. 
					if (!cell->GetLinks().empty()) return;

					// If we have completed the hunt, then return. There is no way to break early unfortunately. 
					if (current) return;

					// Check for visited neighbors
					std::vector<Cell*> visitedNeighbors;
					visitedNeighbors.reserve(4);
					for (Cell* neighbor : cell->GetNeighbors())
					{
						// If a neighbor cell has links, then it must have been visited before. 
						if (!neighbor->GetLinks().empty()) 
							visitedNeighbors.push_back(neighbor);
					}

					// The "Kill" portion of this algorithm I guess. 
					if (!visitedNeighbors.empty())
					{
						current = cell;
						Cell* neighbor = Utils::Sample(visitedNeighbors);
						current->Link(neighbor);
					}
				});
		}
	}
}