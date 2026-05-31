#include "../public/distance_grid.h"
#include "../public/cell.h"
#include "../public/distances.h"

void DistanceGrid::SetDistances(const Distances& distances)
{
	m_Distances = std::make_unique<Distances>(distances);
}

std::string DistanceGrid::GetContentsOf(const Cell* cell) const
{
	if (m_Distances && m_Distances->GetDistanceFrom(cell) != -1)
		return std::to_string(m_Distances->GetDistanceFrom(cell));

	else return Grid::GetContentsOf(cell);
}