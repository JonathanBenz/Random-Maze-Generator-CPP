#include "../public/distances.h"
#include "../public/cell.h"
#include "../../utils.h"

Distances::Distances(Cell* root)
{
	if (root)
	{
		m_Root = root;
		m_Cells[root] = 0;
	}
}

Distances Distances::PathTo(Cell* goal)
{
	if (!goal) return nullptr;
	Cell* currentCell = goal;

	Distances breadcrumbs(m_Root);
	breadcrumbs.SetDistance(currentCell, m_Cells[currentCell]);

	while (currentCell != m_Root)
	{
		for (Cell* neighbor : currentCell->GetLinks())
		{
			if (m_Cells[neighbor] < m_Cells[currentCell])
			{
				breadcrumbs.SetDistance(neighbor, m_Cells[neighbor]);
				currentCell = neighbor;
				break;
			}
		}
	}

	return breadcrumbs;
}

// Returns the cells in order from root to goal
std::vector<Cell*> Distances::GetCells()
{
	std::multimap<unsigned int, Cell*> mapOrderedByDistance = Utils::FlipMap(m_Cells);

	std::vector<Cell*> cells;
	cells.reserve(mapOrderedByDistance.size());

	for (auto& e : mapOrderedByDistance)
		cells.push_back(e.second);

	return cells;
}

// return -1 if key does not exist
int Distances::GetDistanceFrom(Cell* cell)
{
	return m_Cells.find(cell) != m_Cells.end() ? static_cast<int>(m_Cells[cell]) : -1;
}

int Distances::GetDistanceFrom(const Cell* cell) const
{
	// For the const version of this method we cannot use the [] operator for the map. That is why we get the iterator instead. 
	auto it = m_Cells.find(const_cast<Cell*>(cell));
	return it != m_Cells.end() ? static_cast<int>(it->second) : -1;
}

Cell* Distances::GetMaxCell() const
{
	std::multimap<unsigned int, Cell*> mapOrderedByDistance = Utils::FlipMap(m_Cells);
	return mapOrderedByDistance.rbegin()->second;
}

unsigned int Distances::GetMaxDistance() const
{
	std::multimap<unsigned int, Cell*> mapOrderedByDistance = Utils::FlipMap(m_Cells);
	return mapOrderedByDistance.rbegin()->first;
}

std::pair<Cell*, unsigned int> Distances::GetMaxCellAndDistance() const
{
	return std::pair<Cell*, unsigned int>(GetMaxCell(), GetMaxDistance());
}

void Distances::SetDistance(Cell* cell, unsigned int distance)
{
	m_Cells[cell] = distance;
}