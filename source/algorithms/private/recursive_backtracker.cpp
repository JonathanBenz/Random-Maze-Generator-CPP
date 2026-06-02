#include "../public/recursive_backtracker.h"
#include "../../grid/public/grid.h"
#include "../../grid/public/cell.h"
#include "../../utils.h"
#include <stack>
#include <vector>

void RecursiveBacktracker::GenerateMaze(Grid& grid)
{
	ResetAllCells(grid);
	ApplyAlgorithm(grid, nullptr);
}

void RecursiveBacktracker::ApplyAlgorithm(Grid& grid, Cell* _cell)
{
	std::stack<Cell*> stack;
	stack.push(grid.GetRandomCell());

	while (!stack.empty())
	{
		Cell* current = stack.top();

		std::vector<Cell*> neighbors;
		neighbors.reserve(4);
		for (Cell* neighbor : current->GetNeighbors())
		{ 
			if (neighbor->GetLinks().empty())
				neighbors.push_back(neighbor);
		}

		if (neighbors.empty()) 
			stack.pop();

		else
		{
			Cell* neighbor = Utils::Sample(neighbors);
			current->Link(neighbor);
			stack.push(neighbor);
		}
	}
}